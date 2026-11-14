extern unsigned char* lpGebaeudePROT;
extern unsigned char g_773d75;
#include <string.h>
int __cdecl fcn_0048d610(char*, char**);
int __cdecl fcn_005463a0(int, ...);
int __cdecl fcn_0050d170(int);
int __cdecl fcn_0050d200(char*, int);
int __cdecl fcn_0050b810(int, unsigned char);
int __cdecl fcn_004a4bb0(int, char*, int, int*, int*, int);
int __cdecl ai_StartKreditNehmen(int, char*, int, int*, int*);

/* ADDRESS: GOLDTL 0x0048d6c0 */
int __cdecl ai_StartDomizil(int a0, char* a1, int a2, int* a3, int* a4)
{
	int v12[6];
	int v13[6];
	int first;
	int second;
	int rem;
	int* tail_src;
	char* entity = a1;

	if (fcn_0048d610(a1, (char**) &a1) && a2 == 0 && (a0 == 0x40 || a0 == 0) &&
	    fcn_005463a0(2, 0, 0xd, 2, *(unsigned short*) entity) == 0) {
		if (a1 != 0) {
			if (*(unsigned char*) (lpGebaeudePROT + *(unsigned char*) a1 * 0x24d + 0x247) < 3 &&
			    !(a1[0x5a] & 0x41)) {
				v13[1] = *(unsigned char*) a1 + 1;
				v13[2] = 1;
				*(unsigned char*) v12 = 4;
				v12[1] = *(int*) (a1 + 1);
				v12[2] = 1;
				first = (int) (fcn_0050d170(v13[1]) * 0.3f);
				if (fcn_004a4bb0(a0, entity, 0, v13, v12, 0) != 0) {
					second = (int) (fcn_0050b810(*(int*) (entity + 0x178), g_773d75) * 0.95f);
					if (second < first) {
						rem = first - second;
						if ((float) rem / first < 0.25f) {
							a3[2] = rem;
							*(char*) a3 = 0x12;
							return ai_StartKreditNehmen(0x40, entity, 0, a3, a4);
						}
					} else {
						memcpy(a3, v13, sizeof(v13));
						tail_src = v12;
						goto do_copy40;
					}
				}
			}
		} else {
			*(unsigned char*) v12 = 5;
			v12[1] = 0x4b;
			v12[2] = 1;
			if (fcn_004a4bb0(a0, entity, 0, v12, v13, 1) != 0) {
				first = fcn_0050d200(entity, v12[1]);
				second = (int) (fcn_0050b810(*(int*) (entity + 0x178), g_773d75) * 0.95f);
				if (second < first) {
					rem = first - second;
					if ((float) rem / first < 0.25f) {
						a3[2] = rem;
						*(char*) a3 = 0x12;
						return ai_StartKreditNehmen(0x40, entity, 0, a3, a4);
					}
				} else {
					memcpy(a3, v12, sizeof(v12));
					tail_src = v13;
do_copy40:
					memcpy(a4, tail_src, 24);
					return 0x40;
				}
			}
		}
	}
	return 0;
}
