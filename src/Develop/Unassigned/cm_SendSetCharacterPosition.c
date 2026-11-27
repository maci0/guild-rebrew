

void __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int a;
	int b;
	int c;
} Triple3;
// SIZE 0xc

void __cdecl cm_SendSetCharacterPosition(int entityId, Triple3* firstTriple, Triple3* secondTriple)
{
	char buf[0x9c];

	buf[0] = 0x32;
	*(int*) (buf + 0x10) = entityId;
	if (firstTriple != 0) {
		*(Triple3*) (buf + 0x14) = *firstTriple;
	}
	if (secondTriple != 0) {
		*(Triple3*) (buf + 0x24) = *secondTriple;
	}
	cm_EnqueueClientPacket(buf);
}
