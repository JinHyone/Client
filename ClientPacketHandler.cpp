#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "SceneMananger.h"
#include "DevScene.h"
#include "MyPlayer.h"

void ClientPacketHandler::HandlePacket(ServerSessionRef session, BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	switch (header.id)
	{
	case S_EnterGame:
		Handle_S_EnterGame(session, buffer, len);
		break;
	case S_MyPlayer:
		Handle_S_MyPlayer(session, buffer, len);
		break;
	case S_AddObject:
		Handle_S_AddObject(session, buffer, len);
		break;
	case S_RemoveObject:
		Handle_S_RemoveObject(session, buffer, len);
		break;
	case S_Move:
		Handle_S_Move(session, buffer, len);
	}
}


void ClientPacketHandler::Handle_S_EnterGame(ServerSessionRef session, BYTE* buffer, int32)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint32 size = header->size;

	Protocol::S_EnterGame pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	bool success = pkt.success();
	uint64 acountId = pkt.accountid();
}

void ClientPacketHandler::Handle_S_MyPlayer(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint32 size = header->size;

	Protocol::S_MyPlayer pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	const Protocol::ObjectInfo info = pkt.info();

	DevScene* scene = GS(SceneMananger)->GetDevScene();
	if (scene)
	{
		MyPlayer* myPlayer = scene->SpawnObject<MyPlayer>(Vec2Int(info.posx(), info.posy()));
		myPlayer->info = info;
		GS(SceneMananger)->SetMyPlayer(myPlayer);
	}
}

void ClientPacketHandler::Handle_S_AddObject(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint32 size = header->size;

	Protocol::S_AddObject pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	DevScene* scene = GS(SceneMananger)->GetDevScene();
	if (scene)
	{
		scene->Handle_S_AddObject(pkt);
	}
}

void ClientPacketHandler::Handle_S_RemoveObject(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint32 size = header->size;

	Protocol::S_RemoveObject pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	DevScene* scene = GS(SceneMananger)->GetDevScene();
	if (scene)
	{
		scene->Handle_S_RemoveObject(pkt);
	}
}

void ClientPacketHandler::Handle_S_Move(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint32 size = header->size;

	Protocol::S_Move pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));


	const Protocol::ObjectInfo info = pkt.info();

	DevScene* scene = GS(SceneMananger)->GetDevScene();
	if (scene)
	{
		uint64 myPlayerId = GS(SceneMananger)->GetMyPlayerId();
		if (myPlayerId == info.objectid()) return;

		GameObject* gameObject = scene->GetObject(info.objectid());
		if (gameObject)
		{
			gameObject->SetDir(info.dir());
			gameObject->SetState(info.state());
			gameObject->SetCellPos(Vec2Int(info.posx(), info.posy()));
		}
	}
}

SendBufferRef ClientPacketHandler::Make_C_Move()
{
	Protocol::C_Move pkt;

	MyPlayer* myPlayer = GS(SceneMananger)->GetMyPlayer();
	*pkt.mutable_info() = myPlayer->info;

	return MakeSendBuffer(pkt, C_Move);
}
