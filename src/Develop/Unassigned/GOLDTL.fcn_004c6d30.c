


void __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int v[6];
} Body6;
// SIZE 0x18

void __cdecl cm_RequestAhmCommand(Body6* source)
{
	char buf[0x9c];

	buf[0] = 0x64;
	*(Body6*) (buf + 0x10) = *source;
	cm_EnqueueClientPacket(buf);
}
