


void __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int v[0x20];
} Body20;
// SIZE 0x80

void __cdecl cm_SendAdjustResourceSlots(Body20* source)
{
	char buf[0x9c];

	buf[0] = 0x67;
	*(Body20*) (buf + 0x10) = *source;
	cm_EnqueueClientPacket(buf);
}
