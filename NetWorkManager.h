#pragma once

class ServerSession;
using ServerSessionRef = shared_ptr<ServerSession>;

class NetWorkManager
{
	GNERATE_SINGLE(NetWorkManager);

public:
	void Init();
	void Update();

	ServerSessionRef CreateSession();
	void SendPacket(SendBufferRef sendBuffer);

	ServerSessionRef GetServerSession() { return _session; }

private:
	ClientServiceRef _service;
	ServerSessionRef _session;
};

