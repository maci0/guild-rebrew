


void __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int v[0xa];
} Body10;
// SIZE 0x28

void __cdecl fcn_004c6a00(Body10* body)
{
	char buf[0x9c];

	buf[0] = 0x56;
	*(Body10*) (buf + 0x10) = *body;
	cm_EnqueueClientPacket(buf);
}
