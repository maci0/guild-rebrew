


#include <string.h>

typedef struct {
	short v[7];
} stamp14;
// SIZE 0xe

extern char g_6a4870[];

int __cdecl cm_EnqueueClientPacket(char*);
void __cdecl cm_StageRawPacketPayload(int, void*);

int __cdecl cm_SendSetHE(char a1, unsigned char* e)
{
	char buf[0x9c];

	buf[0] = 0x1d;
	*(int*) (buf + 0x10) = *(int*) (e + 4);
	*(stamp14*) (buf + 0x14) = *(stamp14*) (e + 0x44);
	*(stamp14*) (buf + 0x22) = *(stamp14*) (e + 0x52);
	*(stamp14*) (buf + 0x30) = *(stamp14*) (e + 0x60);
	buf[0x3e] = a1;
	strcpy(buf + 0x3f, g_6a4870 + *e * 0x20);
	cm_StageRawPacketPayload(0xa0, e + 0xac);
	return cm_EnqueueClientPacket(buf);
}
