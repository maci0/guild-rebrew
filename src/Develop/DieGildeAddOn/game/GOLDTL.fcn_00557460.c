#include "client_dialog_helpers.h"
#include "client_types.h"

/* Dark corner dialog ("Dunkle Ecke"). Resolves the current target, offers
 * the neighbouring entities as the next target and books the skill checks
 * that decide whether the corner stays dark. */

extern char g_9a3800[];
extern int g_664398[];
extern char* g_aed32c;
typedef struct BuildingRow557460 { unsigned char kind; char fields[0x24c]; } BuildingRow557460;

int __cdecl fcn_004c4450(int h);
int* __cdecl fcn_004c4480(int h);
int __cdecl fcn_004c5620(int a, char* dlg);
void __cdecl fcn_004c5c80(int a);
void __cdecl fcn_004c5da0(int a, int b, int c, int d, int e, char* s);
void __cdecl fcn_00546190(char* dlg);
void __cdecl fcn_005015e0(int* out, int a, int b, int c);
int __cdecl fcn_00529670(char* e, char* h);
char* __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
int __cdecl fcn_00500cb0(char* a, char* b);
void __cdecl fcn_00500bb0(int* r, int a, int b, int c);
float __cdecl gm_GetEntitySkill(char* e, int i);
float __cdecl fcn_0042e450(void);
int __cdecl fcn_0042e410(int n);
void __cdecl fcn_004c58b0(int a, int b);

/* ADDRESS: GOLDTL 0x00557460 */
void __cdecl fcn_00557460(char* dlg)
{
	char* hit;
	char text[0x400];

	if (*(int*) (dlg + 0x70) == -1 || *(int*) (dlg + 0x70) == -2) {
		if (*(unsigned char*) (dlg + 0x78) & 2) {
			char* e;

			e = gm_LookupEntityRecordById(*(int*) (dlg + 0xac));
			if (e != 0) {
				fcn_004c5c80(*(int*) (e + 4));
				fcn_004c57e0(*(int*) (e + 4), 1);
			}
		}
		fcn_00546190(dlg);
		return;
	}
	if (*(unsigned char*) (dlg + 0x78) & 4) {
		return;
	}
	if (*(int*) (dlg + 0x84) != -1) {
		if (fcn_004c4450(*(int*) (dlg + 0x84)) == 0) {
			return;
		}
	}
	switch (*(int*) (dlg + 0x70)) {
	case 0: {
		int* p;
		int v;

		if (fcn_004c4450(*(int*) (dlg + 0xac)) == 1) {
			p = fcn_004c4480(*(int*) (dlg + 0xac));
			v = *(int*) ((char*) p + 4);
			fcn_00500bb0((int*) (dlg + 0x52), 0, 1, 0);
			*(int*) (dlg + 0xac) = v;
			*(int*) (dlg + 0x84) = fcn_004c5620(1, dlg);
			return;
		}
		fcn_00500bb0((int*) (dlg + 0x52), 0x18, 0, 0);
		*(int*) (dlg + 0x84) = fcn_004c5620(4, dlg);
		return;
	}
	case 1: {
		int scan;
		int tries;
		unsigned char kind;
		unsigned int mask;
		unsigned int mask2;
		char* e;

		scan = *(int*) (dlg + 0xc4);
		tries = 0x100;
		do {
			hit = (char*) (lpGebaeudeINST + scan * 0xa9);
			kind = ((BuildingRow557460*) lpGebaeudePROT)[*(unsigned char*) hit].kind;
			mask = 0;
			mask2 = 0;
			if (kind > 0x1f) {
				mask2 = 1 << (kind - 0x20);
			} else {
				mask = 1 << kind;
			}
			if (((mask & 0xa7fcc3a6) || (mask2 & 1))
			    && *(int*) (hit + 1) != *(int*) (dlg + 0xb0)) {
				break;
			}
			hit = 0;
			tries--;
			scan = (scan + *(int*) (dlg + 0xc8)) % 0x100;
		} while (tries != 0);
		scan = (scan + *(int*) (dlg + 0xc8)) % 0x100;
		*(int*) (dlg + 0xc4) = scan;
		if (hit == 0) {
			fcn_00500bb0((int*) (dlg + 0x52), 0, 1, 0);
			*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
			return;
		}
		io_FormatTextBuffer(text, 0x6a5f7c, (void*) hit);
		e = gm_LookupEntityRecordById(*(int*) (dlg + 0xac));
		if (e == 0) {
			fcn_00500bb0((int*) (dlg + 0x52), 0, 1, 0);
			*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
			return;
		}
		fcn_004c5c80(*(int*) (e + 4));
		fcn_004c5da0(*(int*) (e + 4), *(int*) (hit + 1), -1, 0, 1,
		    "Dunkle Ecke");
		fcn_00500bb0((int*) (dlg + 0x52), 0, 5, 0);
		*(int*) (dlg + 0xb8) = *(int*) (hit + 1);
		*(int*) (dlg + 0x84) = fcn_004c5620(2, dlg);
		return;
	}
	case 2: {
		char* e;
		float f;

		fcn_005015e0((int*) &hit, 0, 0, *(int*) (dlg + 0xb8));
		fcn_00500bb0((int*) (dlg + 0x52), 0, 5, 0);
		if (hit == 0) {
			*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
			return;
		}
		e = gm_LookupEntityRecordById(*(int*) (dlg + 0xac));
		if (e == 0) {
			fcn_00500bb0((int*) (dlg + 0x52), 0, 1, 0);
			*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
			return;
		}
		if (fcn_00529670(e, (char*) hit) == 0) {
			*(int*) (dlg + 0x70) = 2;
			fcn_00500bb0((int*) (dlg + 0x52), 0, 5, 0);
			*(int*) (dlg + 0x84) = fcn_004c5620(2, dlg);
			return;
		}
		*(int*) (dlg + 0xbc) = *(int*) (dlg + 0xbc) - 1;
		f = gm_GetEntitySkill(g_7f4ca0
		    + *(unsigned short*) (hit + 0x27) * 0x21c, 2);
		if (*(int*) (dlg + 0xc0) >= 1) {
			*(int*) (dlg + 0xc0) = *(int*) (dlg + 0xc0)
			    + (fcn_0042e450() * 0.5f < f);
		} else {
			*(int*) (dlg + 0xc0) = *(int*) (dlg + 0xc0) + 1;
		}
		if (*(int*) (dlg + 0xc0) > 2) {
			*(int*) (dlg + 0xbc) = 0;
		}
		fcn_005015e0((int*) &hit, 0, 0, *(int*) (dlg + 0xb0));
		if (hit == 0) {
			*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
			return;
		}
		if (*(short*) (hit + 0x27) == -1) {
			*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
			return;
		}
		if (*(int*) (dlg + 0xbc) > 0) {
			*(int*) (dlg + 0x84) = fcn_004c5620(1, dlg);
			return;
		}
		fcn_004c5c80(*(int*) (e + 4));
		fcn_004c5da0(*(int*) (e + 4), *(int*) (hit + 1),
		    *(int*) (dlg + 0xb4), 0, 0, "Dunkle Ecke");
		*(int*) (dlg + 0x84) = fcn_004c5620(3, dlg);
		return;
	}
	case 3: {
		char* e;
		char* rec;
		int found[3];
		int idx;
		int step;
		int tries;
		int i;
		int j;
		unsigned int off;

		fcn_00500bb0((int*) (dlg + 0x52), 0, 5, 0);
		fcn_005015e0((int*) &hit, 0, 0, *(int*) (dlg + 0xb0));
		if (hit == 0) {
			*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
			return;
		}
		if (*(short*) (hit + 0x27) == -1) {
			*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
			return;
		}
		e = gm_LookupEntityRecordById(*(int*) (dlg + 0xac));
		if (e != 0 && fcn_00529670(e, (char*) hit) == 0) {
			*(int*) (dlg + 0x70) = 3;
			fcn_00500bb0((int*) (dlg + 0x52), 0, 5, 0);
			*(int*) (dlg + 0x84) = fcn_004c5620(3, dlg);
			return;
		}
		{
			int v2;

			v2 = *(int*) (dlg + 0xc0);
			if (v2 >= 3) {
				v2 = 3;
			} else if (v2 <= 0) {
				v2 = 0;
			}
			*(int*) (dlg + 0xc0) = v2;
		}
		if (*(int*) (dlg + 0xc0) != 0) {
			found[0] = -1;
			found[1] = -1;
			found[2] = -1;
			idx = (unsigned short) fcn_0042e410(0x200);
			step = g_664398[fcn_0042e410(8) & 0xffff];
			tries = 0x200;
			i = 0;
			do {
				if (i >= *(int*) (dlg + 0xc0)) {
					break;
				}
				rec = g_9a3800 + idx * 0x2d;
				if (*(int*) rec != -1 && *(int*) (rec + 0x25) == 1
				    && *(int*) (rec + 0x16) != *(int*) (g_7f4ca0
				    + *(unsigned short*) (hit + 0x27) * 0x21c + 4)
				    && fcn_00500cb0(dlg + 0x44, rec + 4) != 1) {
					found[i] = *(int*) rec;
					i++;
				}
				idx = (idx + step) % 0x200;
				tries--;
			} while (tries != 0);
			*(int*) (dlg + 0xc0) = i;
			j = 0;
			while (j < i) {
				fcn_004c58b0(found[j], *(int*) (g_7f4ca0
				    + *(unsigned short*) (hit + 0x27) * 0x21c + 4));
				j++;
			}
			rec = fcn_00502cd0(*(int*) (hit + 0x5d), 2, 6, 0, 0x12c);
			if (rec != 0) {
				fcn_004c4510(rec, *(int*) (rec + 2));
				j = 0;
				while (j < 3) {
					off = (unsigned int) (rec + 0x1c + j * 4 - g_aed32c);
					fcn_004c4570(4, 1, (int) off, &found[j]);
					j++;
				}
				fcn_004c5360();
			}
		}
		io_FormatTextBuffer(text,
		    *(int*) (dlg + 0xc0) != 0 ? 0x18a9 : 0x18aa);
		((void (__cdecl*) (int, int, char*, int, int, int, int, int, char*))
		    fcn_00545e80)(*(int*) (g_7f4ca0
		    + *(unsigned short*) (hit + 0x27) * 0x21c + 4), -1, text, 0,
		    0x5ec, *(int*) (hit + 1), *(int*) (dlg + 0xb4), 0,
		    (char*) 0x6b5c60);
		*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
		return;
	}
	case 4: {
		char* rec;
		int found[3];
		int idx;
		int step;
		int tries;
		int i;
		int j;
		int k;
		float f;

		fcn_005015e0((int*) &hit, 0, 0, *(int*) (dlg + 0xb0));
		if (hit == 0) {
			*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
			return;
		}
		if (*(short*) (hit + 0x27) == -1) {
			*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
			return;
		}
		*(int*) (dlg + 0xc0) = 0;
		k = 3;
		do {
			f = gm_GetEntitySkill(g_7f4ca0
			    + *(unsigned short*) (hit + 0x27) * 0x21c, 2);
			*(int*) (dlg + 0xc0) = *(int*) (dlg + 0xc0)
			    + (fcn_0042e450() * 0.66f < f);
			k--;
		} while (k != 0);
		if (*(int*) (dlg + 0xc0) != 0) {
			found[0] = -1;
			found[1] = -1;
			found[2] = -1;
			idx = (unsigned short) fcn_0042e410(0x200);
			step = g_664398[fcn_0042e410(8) & 0xffff];
			tries = 0x200;
			i = 0;
			do {
				if (i >= *(int*) (dlg + 0xc0)) {
					break;
				}
				rec = g_9a3800 + idx * 0x2d;
				if (*(int*) rec != -1 && *(int*) (rec + 0x25) == 1
				    && *(int*) (rec + 0x16) != *(int*) (g_7f4ca0
				    + *(unsigned short*) (hit + 0x27) * 0x21c + 4)
				    && fcn_00500cb0(dlg + 0x44, rec + 4) != 1) {
					found[i] = *(int*) rec;
					i++;
				}
				idx = (idx + step) % 0x200;
				tries--;
			} while (tries != 0);
			*(int*) (dlg + 0xc0) = i;
			j = 0;
			while (j < i) {
				fcn_004c58b0(found[j], *(int*) (g_7f4ca0
				    + *(unsigned short*) (hit + 0x27) * 0x21c + 4));
				j++;
			}
			rec = fcn_00502cd0(*(int*) (hit + 0x5d), 2, 6, 0, 0x12c);
			if (rec != 0) {
				fcn_004c4510(rec, *(int*) (rec + 2));
				j = 0;
				while (j < 3) {
					fcn_004c4570(4, 1, (int) (rec + 0x1c + j * 4 - g_aed32c),
					    &found[j]);
					j++;
				}
				fcn_004c5360();
			}
		}
		io_FormatTextBuffer(text,
		    *(int*) (dlg + 0xc0) != 0 ? 0x18a9 : 0x18aa);
		((void (__cdecl*) (int, int, char*, int, int, int, int, int, char*))
		    fcn_00545e80)(*(int*) (g_7f4ca0
		    + *(unsigned short*) (hit + 0x27) * 0x21c + 4), -1, text, 0,
		    0x5ec, *(int*) (hit + 1), *(int*) (dlg + 0xb4), 0,
		    (char*) 0x6b5c60);
		*(pos14_7f4c00*) (dlg + 0x52) = *(pos14_7f4c00*) &g_7f4c00;
		*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
		return;
	}
	}
}
