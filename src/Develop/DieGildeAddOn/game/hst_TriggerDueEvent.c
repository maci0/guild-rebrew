#include <string.h>

typedef struct Val {
	int x0;
	int x4;
	int x8;
	int xc;
} Val;
// SIZE 0x10

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67fcb0;
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char* gm_CityEntity;

int __cdecl hst_ParseDate(int pos, int k, Val* v, char* buf);
void __cdecl cm_SendCopyEntityData(char* msg);

/* ADDRESS: GOLDTL 0x004b1b60 */
/* ADDRESS: GOLDDE 0x0049fe80 */
int __cdecl hst_TriggerDueEvent(void)
{
	char msg[0xf8];
	char key[0x10];
	Val v;
	char buf[0x10];
	int pos;

	pos = g_67fcb4;
	if (g_67fcac <= -1 && (g_67fcb4 < g_67fcac || g_67fcb4 >= g_67fcb0)) {
		return 0;
	}
	{
		char* p;
		int len;

		len = sizeof(key);
		p = key;
		/* block-fill prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov ebx, len
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L1:
			add ecx, ebx
			rep stosb
		}
	}
	{
		int len;
		char* p;

		len = strlen(g_1007ba0);
		p = key;
		/* block-copy prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov esi, offset g_1007ba0
			mov ebx, len
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L2:
			add ecx, ebx
			rep movsb
		}
	}
	{
		char* p;
		int len;

		len = sizeof(buf);
		p = buf;
		/* block-fill prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov ebx, len
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L3
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L3:
			add ecx, ebx
			rep stosb
		}
	}
	if (hst_ParseDate(pos, 4, &v, buf) == 0) {
		return 0;
	}
	do {
		if (memcmp(key, buf, strlen(buf)) == 0) {
			g_67fcb4 = pos + 6;
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x52;
			*(int*) (msg + 8) = *(int*) (gm_CityEntity + 4);
			*(int*) (msg + 0xc) = -1;
			*(int*) (msg + 0x58) = pos - g_67fcac;
			msg[0x36] = 0x12;
			cm_SendCopyEntityData(msg);
			return 1;
		}
		if (v.x0 > (*(int*)&gm_GameTime)) {
			return 0;
		}
		pos += 6;
		if (hst_ParseDate(pos, 4, &v, buf) == 0) {
			return 0;
		}
	} while (g_67fcb4 < g_67fcb0);
	return 0;
}
