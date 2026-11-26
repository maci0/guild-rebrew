


void __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int v[0x20];
} Body20;
// SIZE 0x80

void __cdecl cm_SendLoadChunk(Body20* data)
{
	char buf[0x9c];

	buf[0] = 9;
	*(Body20*) (buf + 0x10) = *data;
	cm_EnqueueClientPacket(buf);
}
