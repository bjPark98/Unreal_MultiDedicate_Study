#pragma once

enum ELoginPacketHeader
{
	LPH_Login
};


struct FPacketInfo
{
	int32	Header;
	int32	Length;
	uint8	Packet[1024];
};

namespace EChatType
{
	enum Type
	{
		Normal
	};
}
