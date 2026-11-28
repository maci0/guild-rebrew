


void __cdecl cm_EnqueueClientPacket(void*);

#pragma pack(push, 1)

typedef struct
{
	int a;
	int b;
	char c;
} Small3;
// SIZE 0x9

#pragma pack(pop)

/* ADDRESS: GOLDDE 0x004b3cb0 */
void __cdecl cm_RequestSetLaw(Small3* body)
{
	char buf[0x9c];

	buf[0] = 0x46;
	*(Small3*) (buf + 0x10) = *body;
	cm_EnqueueClientPacket(buf);
}
