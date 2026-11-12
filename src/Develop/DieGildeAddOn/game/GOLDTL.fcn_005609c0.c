#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern double g_6640e8;
extern double g_6629c8;
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004c5c80(int);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
int __cdecl fcn_00500bb0(unsigned int*, int, int, int);
int __cdecl fcn_00500cb0(int, int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl fcn_005049a0(int);
int __cdecl fcn_0050dc90(int);
int __cdecl fcn_0050c710(int, int, int);
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
int __cdecl io_FormatTextBuffer(char*, int, int, int);
int __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, int);
void __cdecl fcn_00529160(int, int, int, int);
void __cdecl fcn_00546190(int);
int __cdecl strcat(char*, char*);
int __cdecl strlen(char*);

/* ADDRESS: GOLDTL 0x005609c0 */
void __cdecl fcn_005609c0(char* a0)
{
	char text[256];
	char name[256];
	int i;
	int slot;
	double f;
	int rec;
	int ent;
	int tmp;
	int v19;
	int len;

	switch (*(int*) (a0 + 0x70)) {
	case 0:
		i = 0;
		if (*(unsigned char*) (a0 + 0xac) != 0) {
			while (i < *(unsigned char*) (a0 + 0xac)) {
				ent = gm_LookupEntityRecordById(*(int*) (a0 + 0x8c + i * 4));
				if (ent != 0 && *(int*) (ent + 0x16c) != 0) {
					fcn_004c5c80(*(int*) (a0 + 0x8c + i * 4));
					fcn_004c5da0(*(int*) (a0 + 0x8c + i * 4),
						*(int*) (*(int*) (ent + 0x16c) + 1),
						*(int*) (a0 + 0xb4), 0, 0, (char*) 0x6a6510);
				}
				i += 1;
			}
		}
		*(pos14_7f4c00*) (a0 + 0x52) = g_7f4c00;
		fcn_00500bb0((unsigned int*) (a0 + 0x52), 2, gm_RandomMod(0x1e), 0);
		*(int*) (a0 + 0x70) = *(int*) (a0 + 0x70) + 1;
		return;
	case 1:
		break;
	case -2:
	case -1:
		i = 0;
		if (*(unsigned char*) (a0 + 0xac) != 0) {
			while (i < *(unsigned char*) (a0 + 0xac)) {
				ent = gm_LookupEntityRecordById(*(int*) (a0 + 0x8c + i * 4));
				if (ent != 0) {
					fcn_00529160(*(int*) ((unsigned short*) ent + 0xb6), 0,
						*(unsigned short*) ent, 0);
				}
				i += 1;
			}
		}
		fcn_00546190((int) a0);
		return;
	default:
		return;
	}
	/* state 1: wait for the delay, then spawn the object */
	if (fcn_00500cb0((int) (a0 + 0x52), 0x7f4c00) >= 0) {
		return;
	}
	rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0x10));
	if (rec == 0) {
		*(int*) (a0 + 0x70) = -1;
		return;
	}
	v19 = fcn_00502cd0(*(int*) (rec + 0x5d), 1, 0, 0xdd);
	if (v19 == 0) {
		v19 = fcn_005049a0(rec);
	}
	ent = fcn_00502cd0(*(int*) (rec + 0x5d), 2, 6, 0, 0x2a);
	if (ent != 0) {
		tmp = fcn_0050dc90(rec);
		f = (double) fcn_0050c710(rec, 0xb, 1) * g_6640e8 + g_6629c8;
		len = (int) ((gm_RandomMod(5) + 5) * f);
		fcn_004c51f0(*(int*) (ent + 2), -1, *(unsigned short*) (a0 + 0xae),
			len, *(unsigned char*) 0x773d75, 0);
		io_FormatTextBuffer(text, 0x1809, 0x1805, rec);
		io_FormatTextBuffer(name, 0x180a, len,
			*(unsigned short*) (a0 + 0xae) * 2 + 0x9a8);
		strcat(text, name);
		slot = *(unsigned short*) (a0 + 8) * 0x21c;
		if ((*(unsigned char*) (slot + 0x7f4ca2) == 6
				|| *(unsigned char*) (slot + 0x7f4ca2) == 7)
			&& (tmp == 0 || (*(unsigned char*) (tmp + 0x1b4) & 1) == 0)) {
			if (v19 != 0) {
				he_MessageBoxQuickjump(*(int*) (slot + 0x7f4ca4), -1, text, 0, 0x5ec,
					*(int*) (rec + 1), -1, 0, 0);
				*(int*) (a0 + 0x70) = -1;
				return;
			}
			/* native reads *(int*) (v19 + 2) with v19 == 0 here (0x560c80) */
			he_MessageBoxQuickjump(*(int*) (slot + 0x7f4ca4), -1, text, 0, 0x5ec,
				*(int*) (rec + 1), *(int*) (v19 + 2), 0, 0);
		}
	}
	*(int*) (a0 + 0x70) = -1;
}
