


#include <string.h>

typedef struct {
	int g;
	int a;
	char name[0x40];
} info48;
// SIZE 0x48

typedef struct {
	char kind;
	char pad1[0xf];
	int f10;
	info48 info;
	char pad5c[0x40];
} msg9c;
// SIZE 0x9c

#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl cm_EnqueueClientPacket(msg9c*);
char* __cdecl fcn_0064d530(char*, char*, int);

int __cdecl cm_SendChatMessage(int channel, char* text)
{
	info48 info;
	msg9c m;

	memset(&m.f10, 0, 0x80);
	info.g = lb_LocalClientId;
	m.kind = 0x5f;
	info.a = channel;
	fcn_0064d530(info.name, text, 0x3f);
	info.name[0x3f] = 0;
	m.f10 = 6;
	m.info = info;
	return cm_EnqueueClientPacket(&m);
}
