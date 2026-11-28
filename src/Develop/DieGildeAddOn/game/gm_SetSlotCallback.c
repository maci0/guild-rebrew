


typedef struct
{
	char data[0x5c];
	int active;
	int x60;
	int x64;
} Sub68;
// SIZE 0x68

typedef struct
{
	int id;
	int flags;
	float s[3];
	int x14;
	Sub68 sub[3];
	int used[3];
	int h[3];
	void* fn;
	void* ctx;
} Slot170;
// SIZE 0x170

typedef struct
{
	char b[0x38];
} Set;
// SIZE 0x38

#include "Develop/client_types.h"
extern Slot170_7731b8 gm_CannonTowers[8];
extern Set g_772ff8[8];

Slot170* __cdecl gm_FindSlot170Entry(int id);
int __cdecl gm_NotifyDomizilCallback(Set* p);

void __cdecl gm_SetSlotCallback(int id, void* fn, void* ctx)
{
	Slot170* slot;

	if (id == -1) {
		return;
	}
	slot = gm_FindSlot170Entry(id);
	if (slot == 0) {
		return;
	}
	if (fn != 0) {
		slot->fn = fn;
		slot->ctx = ctx;
	} else {
		slot->fn = (void*) gm_NotifyDomizilCallback;
		slot->ctx = &g_772ff8[slot - ((Slot170*)gm_CannonTowers)];
	}
}
