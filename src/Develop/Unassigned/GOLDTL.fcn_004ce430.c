#include <string.h>

#include "g_9baa20.h"

#pragma pack(1)
struct NET_SCENE_ENTRY {
	int v[21];
	short w;
	char b;
};
// SIZE 0x57
#pragma pack()

struct NET_CHAT_LOG_PAYLOAD {
	int a;
	int b;
	char text[0x40];
};
// SIZE 0x48

extern Rec9baa20 g_9baa20;
extern int g_9baa08;
extern int g_9baa04;

int* __cdecl d3_LookupSceneEntry(int);
struct NET_SCENE_ENTRY* __cdecl d3_FindFreeSceneEntry(void);
void __cdecl lb_AppendChatLog(int, int, char*);


/* ADDRESS: GOLDTL 0x004ce430 */
int __cdecl d3_ApplyLobbySceneUpdate(char* rec, char* out)
{
	struct NET_CHAT_LOG_PAYLOAD tmp;
	int* r;

	if (out != 0)
		out[0] = 2;
	switch (*(int*) (rec + 0x10)) {
	case 0:
		g_9baa20 = *(Rec9baa20*) (rec + 0x14);
		break;
	case 1:
		r = d3_LookupSceneEntry(*(int*) (rec + 0x14));
		if (r == 0)
			return -2;
		r[0] = *(int*) (rec + 0x14);
		r[1] = *(int*) (rec + 0x18);
		break;
	case 2:
		r = (int*) d3_FindFreeSceneEntry();
		if (r == 0)
			return -1;
		*(struct NET_SCENE_ENTRY*) r = *(struct NET_SCENE_ENTRY*) (rec + 0x14);
		break;
	case 3:
		r = d3_LookupSceneEntry(*(int*) (rec + 0x14));
		if (r == 0)
			return -2;
		if (*(int*) (rec + 0x18) == 1)
			g_9baa08 = 1;
		memset(r, 0, sizeof(struct NET_SCENE_ENTRY));
		break;
	case 4:
		r = d3_LookupSceneEntry(*(int*) (rec + 0x14));
		if (r == 0)
			return -2;
		*(struct NET_SCENE_ENTRY*) r = *(struct NET_SCENE_ENTRY*) (rec + 0x14);
		break;
	case 5:
		r = d3_LookupSceneEntry(*(int*) (rec + 0x14));
		if (r == 0)
			return -2;
		*(struct NET_SCENE_ENTRY*) r = *(struct NET_SCENE_ENTRY*) (rec + 0x14);
		break;
	case 6:
		tmp = *(struct NET_CHAT_LOG_PAYLOAD*) (rec + 0x14);
		lb_AppendChatLog(tmp.a, tmp.b, tmp.text);
		break;
	default:
		return 1;
	}
	if (out != 0)
		out[0] = 1;
	g_9baa04 = 1;
	return 0;
}
