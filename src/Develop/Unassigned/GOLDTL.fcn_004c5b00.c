


typedef struct
{
	short s;
	char c;
} ShortChar;
// SIZE 0x4

int __cdecl cm_EnqueueClientPacket(void*);

int __cdecl cm_RequestAllocThemaPredigt(int ownerId, int topic, ShortChar extra)
{
	char buf[0x9c];

	*(int*) (buf + 0x18) = topic;
	*(short*) (buf + 0x1c) = extra.s;
	buf[0] = 0x2d;
	buf[0x1e] = extra.c;
	*(int*) (buf + 0x14) = ownerId;
	return cm_EnqueueClientPacket(buf);
}
