#include "client_types.h"

typedef struct {
	char pad_00[4];
	unsigned char v04;
	char pad_05[3];
	int v08;
	int v0c;
	char pad_10[0x18];
	pos14_7f4c00 v28;
	unsigned char v36;
	char pad_37[0x21];
	int v58;
	char pad_5c[0x14];
	int v70;
	char pad_74[0x84];
} Dlgs_0059dcf0;

extern void* g_7e4260[];
extern int g_7f4ca4[];
extern pos14_7f4c00 g_7f4c00;

int __cdecl fcn_00525fb0(void*);
void __cdecl fcn_0052a0c0(void*, int);
int __cdecl fcn_00526120(void*, int);
void __cdecl fcn_004c5530(void*);
void __cdecl fcn_004c35f0(void);
void __cdecl fcn_005305a0(void);
void __cdecl fcn_0052a2d0(void);

extern char g_7746cc[];
/* ADDRESS: GOLDTL 0x0059dcf0 */
void __cdecl fcn_0059dcf0(void* entity)
{
	Dlgs_0059dcf0 message;
	void* entry;
	void* selection;
	int i;
	int idx;

	entry = 0;
	if (fcn_00525fb0(entity) != 0)
		return;
	fcn_0052a0c0(entity, 0);
	if (fcn_00526120((void*) *(int*) 0x14abb7c, 1) != 0) {
		for (i = 0; i < 0x20; i++) {
			if (g_7e4260[i] != 0
			    && *(unsigned char*) ((char*) g_7e4260[i] + 0x188) != 0) {
				entry = g_7e4260[i];
				break;
			}
		}
		message.v04 = 0x6c;
		idx = *(unsigned short*) ((char*) entity + 0x27);
		message.v36 = 1;
		message.v08 = g_7f4ca4[idx * 0x87];
		message.v0c = *(int*) ((char*) entity + 1);
		message.v28 = g_7f4c00;
		selection = *(void**) g_7746cc;
		message.v58 = *(int*) ((char*) entry + 4);
		message.v70 = (selection != 0 && *(unsigned short*) selection != 0xfd) ? *(int*) ((char*) selection + 2) : -1;
		fcn_004c5530(&message);
		fcn_004c35f0();
		fcn_005305a0();
	}
	fcn_0052a2d0();
}
