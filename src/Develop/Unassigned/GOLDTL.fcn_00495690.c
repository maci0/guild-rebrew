#include "client_method_registry.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern AM_METHOD g_1008540[];
extern char* g_77261c;

void __cdecl fcn_004c47e0(void*);
void __cdecl cm_BeginPacketFieldDelta(void*, int);
void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c53e0(void);
void __cdecl fcn_004c4820(int, float);
void* __cdecl fcn_0064d740(void* dst, const void* src, unsigned int n);

/* ADDRESS: GOLDTL 0x00495690 */
int __cdecl fcn_00495690(int a0)
{
	ENTITY_RECORD* b;
	void* fn;
	int i;

	b = &((ENTITY_RECORD*) g_7f4ca0)[a0];
	if (((ENTITY_RECORD*) g_7f4ca0)[a0].unk_132) {
		fn = g_1008540[((ENTITY_RECORD*) g_7f4ca0)[a0].unk_132].run;
		if (fn && ((int (__cdecl*) (void*, void*, void*)) fn) (b, (char*) b + 0x134, (char*) b + 0x14c)) {
			fcn_004c47e0(b);
			for (i = 0; i < 4; i++) {
				if (g_1008540[b->unk_131].effects[i].type < 0xe)
					fcn_004c4820(g_1008540[b->unk_131].effects[i].type,
						g_1008540[b->unk_131].effects[i].value * -0.5f);
			}
			for (i = 0; i < 4; i++) {
				if (g_1008540[b->unk_132].effects[i].type < 0xe)
					fcn_004c4820(g_1008540[b->unk_132].saved_effects[i].type,
						g_1008540[b->unk_132].saved_effects[i].value * -0.5f);
			}
			if (b->unk_131 == b->unk_132) {
				fcn_004c4820(0xd, 500.0f);
				if (g_77261c && *(int*) (g_77261c + 4) == b->unk_210) {
					*(unsigned char*) &a0 = 2;
					cm_BeginPacketFieldDelta(b, b->entity_id);
					cm_AppendPacketFieldValue(1, 1, 0x215, &a0);
					fcn_004c5360();
				}
			} else {
				fcn_004c4820(0xd, 250.0f);
				if (g_77261c && *(int*) (g_77261c + 4) == b->unk_210) {
					*(unsigned char*) &a0 = 1;
					cm_BeginPacketFieldDelta(b, b->entity_id);
					cm_AppendPacketFieldValue(1, 1, 0x215, &a0);
					fcn_004c5360();
				}
			}
			fcn_004c53e0();
			fcn_0064d740(g_1008540[b->unk_132].saved_effects, g_1008540[b->unk_132].effects, 0x20);
			return 1;
		}
	}
	if (g_77261c && *(int*) (g_77261c + 4) == b->unk_210) {
		*(unsigned char*) &a0 = 3;
		cm_BeginPacketFieldDelta(b, b->entity_id);
		cm_AppendPacketFieldValue(1, 1, 0x215, &a0);
		fcn_004c5360();
	}
	return 0;
}
unsigned char _dpad_77261c[672];
