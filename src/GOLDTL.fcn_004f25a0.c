/* Hires a production worker like the server's gv_HireProductionWorker, and
 * also notifies the owning player when that player is of kind 6. */

extern char g_7f4ca0[];
extern char* g_773da8;
extern unsigned char* g_868050;
extern int g_6652f8[];
extern float g_6652d8[];
extern unsigned char g_773d75;
extern char g_8680b4[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

int __cdecl fcn_005015e0(void**, void**, void**, int);
int __cdecl gv_CheckSlotActive(void* slot, int type);
void* __cdecl FindSlotEntryFiltered(void* a, void* b, int c, void* d, int e);
int __cdecl fcn_004f1840(void*, int*);
void __cdecl fcn_00503930(int, int, int);
void __cdecl fcn_005037c0(int, int, int);
void __cdecl fcn_005b2cb0(char*, void*, void*, int, int, int);

// FUNCTION: GOLDTL 0x004f25a0
// SIZE: 620
int __cdecl fcn_004f25a0(char* req)
{
	void* entity1;
	void* entity2;
	void* workers;
	char* slot;
	char* player;
	int type;
	int j;
	int off;

	fcn_005015e0(&entity1, 0, 0, *(int*) (req + 8));
	if (entity1 == 0 || *(unsigned short*) ((char*) entity1 + 0x27) == 0xffff ||
	    g_7f4ca0 + *(unsigned short*) ((char*) entity1 + 0x27) * 0x21c == g_773da8) {
		return -1;
	}
	type = *(unsigned char*) entity1;
	if (g_868050[type + type * 588] != 0x1d) {
		return -2;
	}
	workers = *(void**) ((char*) entity1 + 0x65);
	if (workers == 0) {
		return -3;
	}
	if (!gv_CheckSlotActive(workers, *(int*) (req + 0xc))) {
		return -4;
	}
	fcn_005015e0(0, 0, &entity2, *(int*) (req + 4));
	if (entity2 == 0) {
		return -6;
	}
	if (*(int*) (req + 0xc) < 0 || *(int*) (req + 0xc) > 3) {
		return -5;
	}
	slot = FindSlotEntryFiltered(entity2, entity1, 0, (void*) fcn_004f1840, *(int*) (req + 0xc));
	if (slot == 0) {
		return -7;
	}
	*(int*) (slot + 4) = *(int*) ((char*) entity2 + 4);
	*(unsigned short*) (slot + 8) = *(unsigned short*) ((char*) entity2 + 0x50);
	*(unsigned short*) (slot + 0xa) = *(unsigned short*) (req + 0x11) + (unsigned short) g_7f4c00.a;
	*(unsigned char*) (slot + 0xc) = 0xff;
	for (j = 0; j < g_6652f8[*(int*) (req + 0xc)]; j++) {
		*(int*) (*(char**) (slot + 0x10) + j * 0x44) = -1;
	}
	if (*(int*) (req + 0x13) > 0) {
		fcn_00503930(*(int*) ((char*) entity2 + 4), (unsigned short) ((int*)g_8680b4)[g_773d75 * 189],
			*(int*) (req + 0x13));
		fcn_005037c0(*(int*) (g_7f4ca0 + 4 + *(unsigned short*) ((char*) entity1 + 0x27) * 0x21c),
			(unsigned short) ((int*)g_8680b4)[g_773d75 * 189],
			(int) (*(int*) (req + 0x13) * g_6652d8[*(int*) (req + 0xc)]));
		off = *(unsigned short*) ((char*) entity1 + 0x27) * 0x21c;
		player = g_7f4ca0 + off;
		if ((char*) entity2 != player && g_7f4ca0[off + 2] == 6) {
			fcn_005b2cb0(player, entity2, entity1, *(int*) (req + 0xc), *(int*) (req + 0x13),
				(int) (*(int*) (req + 0x13) * g_6652d8[*(int*) (req + 0xc)]));
		}
	}
	return 0;
}
