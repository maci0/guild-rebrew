


#include <string.h>

// SIZE 0x21c
typedef struct {
	char pad0[0x80];
	unsigned char levels[5];
	char pad85[0x21c - 0x85];
} Obj;

// SIZE 0x204
typedef struct {
	int ids[64];
	int vals[64];
	int count;
} Hits;

extern char* g_7746cc;
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int g_67a370;
extern float g_664168;
extern float g_6628cc;

int __cdecl fcn_00505840(void);
void __cdecl d3_VisitSceneObjects(int h, int a, int b, int (__cdecl* cb)(void), Hits* out);
void __cdecl d3_SetSubtreeVisible(int id, int on);

void __cdecl d3_UpdateEntityStageMeshes(int unused, int who, int id)
{
	int want[5];
	Hits hits;
	int t;
	int i;
	int k;

	if ((*(int*)&g_7746cc) == who) {
		for (i = 0; i < 5; i++) {
			t = (int) (((ENTITY_RECORD_VIEW*)g_7f4ca0)[id].levels[i] * g_664168 - g_6628cc) + i * 6 + 0x17f;
			if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[id].levels[i] == 0) {
				t = 0;
			}
			want[i] = t;
		}
		memset(&hits, 0, sizeof(hits));
		d3_VisitSceneObjects(g_67a370, 0, 0xc0, fcn_00505840, &hits);
		for (k = 0; k < hits.count; k++) {
			d3_SetSubtreeVisible(hits.ids[k], 0);
			for (i = 0; i < 5; i++) {
				if (hits.vals[k] == want[i]) {
					d3_SetSubtreeVisible(hits.ids[k], 1);
				}
			}
		}
	}
}
