


void __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int v[5];
} ELECTION_TRADE_BODY;
// SIZE 0x14

void __cdecl cm_RequestElectionOrTrade(ELECTION_TRADE_BODY* body)
{
	char buf[0x9c];

	buf[0] = 0x53;
	*(ELECTION_TRADE_BODY*) (buf + 0x10) = *body;
	cm_EnqueueClientPacket(buf);
}
