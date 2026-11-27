


void __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int v[9];
} Body9;
// SIZE 0x24

void __cdecl cm_SendAllocAlchemist(Body9* source)
{
	char buf[0x9c];

	buf[0] = 0x63;
	*(Body9*) (buf + 0x10) = *source;
	cm_EnqueueClientPacket(buf);
}
