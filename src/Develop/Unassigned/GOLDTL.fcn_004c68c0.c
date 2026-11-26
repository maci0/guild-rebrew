


void __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int v[5];
} Body5;
// SIZE 0x14

void __cdecl fcn_004c68c0(Body5* body)
{
	char buf[0x9c];

	buf[0] = 0x53;
	*(Body5*) (buf + 0x10) = *body;
	cm_EnqueueClientPacket(buf);
}
