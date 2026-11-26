


void __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int a;
	int b;
	int c;
} Small3i;
// SIZE 0xc

void __cdecl cm_RequestJoinLeaveElection(Small3i* data)
{
	char buf[0x9c];

	buf[0] = 0x54;
	*(Small3i*) (buf + 0x10) = *data;
	cm_EnqueueClientPacket(buf);
}
