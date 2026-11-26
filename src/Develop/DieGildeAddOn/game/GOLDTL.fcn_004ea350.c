#include "client_types.h"

extern Rec18_68da68 amt_OfficeSlots[42];
extern char g_7f4ca0[];

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl amt_VacateOfficeSlot(unsigned char);
int __cdecl amt_SendOfficeCommand(unsigned char, char*, char*, int, int);
int __cdecl fcn_004c4450(int);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, int*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00535960(void);

/* ADDRESS: GOLDTL 0x004ea350 */
void __cdecl fcn_004ea350(void)
{
	unsigned char* r;
	char* p;
	char* e;
	int res;



	for (r = &amt_OfficeSlots[0].x10; (int) r < (int) &amt_OfficeSlots[30].x10; r += 0x18) {
		e = gm_LookupEntityRecordById(*(int*) (r - 0xc));
		res = -1;
		if (e != 0 && *(unsigned char*) (e + 8) != 0) {
			if (*r != 1) {
				res = amt_SendOfficeCommand(*(unsigned char*) (r - 0x10), e, 0, 1, 0xff);
			}
		} else {
			if (*r != 3) {
				res = amt_VacateOfficeSlot(*(unsigned char*) (r - 0x10));
			}
			if (e != 0 && *(unsigned char*) (e + 0x166) != 0) {
				int n = *(int*) (e + 4);
				int v;
				v = 0;
				cm_BeginPacketFieldDelta(e, n);
				cm_AppendPacketFieldDelta(1, 1, 0x166, &v);
				fcn_004c5360();
			}
		}
		if (res != -1) {
			while (1) {
				if (fcn_004c4450(res) != 0) {
					break;
				}
				fcn_00535960();
			}
		}
	}
	for (p = g_7f4ca0 + 0x168; (int) p < (int) (g_7f4ca0 + 0x168 + 0x65400); p += 0x21c) {
		if (*(unsigned char*) p != 0) {
			int v = 0;
			cm_BeginPacketFieldDelta(p - 0x168, *(int*) (p - 0x164));
			cm_AppendPacketFieldDelta(1, 1, 0x168, &v);
			fcn_004c5360();
		}
	}
}
