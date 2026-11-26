


void __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int v[0xa];
} SCHEDULER_STATE_CMD;
// SIZE 0x28

void __cdecl cm_SendRandomEventState(SCHEDULER_STATE_CMD* body)
{
	char buf[0x9c];

	buf[0] = 0x56;
	*(SCHEDULER_STATE_CMD*) (buf + 0x10) = *body;
	cm_EnqueueClientPacket(buf);
}
