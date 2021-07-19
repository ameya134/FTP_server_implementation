#pragma once
#include <stdint.h>

enum PACKETTYPE{
	DATA_PACKET= (uint32_t)0,
	COMMAND_PACKET=(uint32_t)1
};

typedef struct metadata{
	enum PACKETTYPE packetType;
	uint32_t payload_len;
}metadata_t;

typedef struct packet{
	metadata_t metaData;
	char payload[1024];

}packet_t;
