

void __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int a;
	int b;
	int c;
} EVIDENCE_CLEAR_ARGS;
// SIZE 0xc

/* ADDRESS: GOLDDE 0x004b3290 */
void __cdecl cm_RequestClearEvidenceLink(int key, int owner, int unused)
{
	char buf[0x9c];

	buf[0] = 0x25;
	*(int*) (buf + 0x14) = owner;
	*(int*) (buf + 0x10) = key;
	*(int*) (buf + 0x18) = unused;
	cm_EnqueueClientPacket(buf);
}
