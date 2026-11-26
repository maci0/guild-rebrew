extern char* lpObjektePROT;
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/object_prototype.h"
char* __cdecl fcn_00503d10(int id);
double __cdecl fcn_0042e450(char a, int b);
void __cdecl cm_SendSellObjekt(int a, int b, int c, int d);

/* ADDRESS: GOLDTL 0x00515340 */
void __cdecl fcn_00515340(int idx)
{
	char* rec;
	char* p;
	int i;
	int h;

	rec = (char*) 0x85ab90 + idx * 0x2a90;
	i = 0x55;
	do {
		p = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) rec]);
		h = (int) fcn_00503d10(*(unsigned short*) rec);
		if (h != 0) {
			if (*(unsigned char*) p == 0x17 || *(unsigned char*) p == 0x25) {
				cm_SendSellObjekt(*(int*) (h + 2), -1, *(unsigned short*) rec,
				    (int) ((fcn_0042e450((char) g_773d75, 0) + *(double*) 0x662908)
				    * *(float*) (rec + 0x20)));
			} else {
				cm_SendSellObjekt(*(int*) (h + 2), -1, *(unsigned short*) rec,
				    (int) ((fcn_0042e450((char) g_773d75, 0) + *(double*) 0x6628f0)
				    * *(float*) (rec + 0x20)));
			}
		}
		rec += 0x80;
		i--;
	} while (i != 0);
}
