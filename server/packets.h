#pragma once

enum PACKETTYPE{
	DATA_PACKET,
	COMMAND_PACKET
};

typedef struct metadata{
	int packet_len;
	enum PACKETTYPE packetType;
}metadata_t;

typedef struct packet{
	metadata_t metaData;
	char payload[1024];

}packet_t;
