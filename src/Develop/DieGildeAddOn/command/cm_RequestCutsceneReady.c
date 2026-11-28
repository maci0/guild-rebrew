


void __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int v[0x12];
} CUTSCENE_READY_BODY;
// SIZE 0x48

void __cdecl cm_RequestCutsceneReady(CUTSCENE_READY_BODY* body)
{
	char buf[0x9c];

	buf[0] = 0x59;
	*(CUTSCENE_READY_BODY*) (buf + 0x10) = *body;
	cm_EnqueueClientPacket(buf);
}
