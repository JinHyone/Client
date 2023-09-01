#include "pch.h"
#include "NetWorkManager.h"
#include "ServerSession.h"
#include "ThreadManager.h"
#include "Service.h"

NetWorkManager* NetWorkManager::s_instance = nullptr;

void NetWorkManager::Init()
{
	SocketUtils::Init();

	_service = make_shared<ClientService>(
		NetAddress(L"127.0.0.1", 7895),
		make_shared<IocpCore>(),
		[=]() { return CreateSession(); },
		1
	);

	assert(_service->Start());
}

void NetWorkManager::Update()
{
	_service->GetIocpCore()->Dispatch(0);
}

ServerSessionRef NetWorkManager::CreateSession()
{
	return _session = make_shared<ServerSession>();
}

void NetWorkManager::SendPacket(SendBufferRef sendBuffer)
{
	if (_session)
		_session->Send(sendBuffer);
}
