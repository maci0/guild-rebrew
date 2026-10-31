#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern unsigned char g_773d75;
extern float g_664168;

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_0050b750(int, unsigned char);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_00500bb0(char*, int, int, int);
void __cdecl fcn_004c5c80(int);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
void __cdecl fcn_004c5ed0(int, char*, int);
void __cdecl fcn_00529160(int, int, int, char*);
void __cdecl fcn_00546190(char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, int);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
int __cdecl fcn_00500d20(char*, char*);
int __cdecl sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x0054da10 */
void __cdecl fcn_0054da10(char* a)
{
	char text[0x40];
	char buf[0x200];
	char* ent;
	char* q;
	char* e;
	char* p;
	int n = 0;
	int i = 0;
	int flags;
	int idx;
	int hits;
	int damage;
	int base;
	int kind;
	int dmg;

	if (*(int*) (a + 0x70) == -1) {
		fcn_00546190(a);
		return;
	}
	if (*(unsigned char*) (a + 0x78) & 4) {
		if (*(int*) (a + 0x70) != -2) {
			return;
		}
		fcn_00546190(a);
		return;
	}
	flags = 0;
	p = a + 0xc4;
	do {
		if (gm_LookupEntityRecordById(*(int*) p) != 0) {
			break;
		}
		n++;
		i++;
		p += 4;
	} while (i < 4);
	if (n == 4) {
		goto nopos;
	}
	if (*(int*) (a + 0x70) == -2) {
		flags = 1;
		*(int*) (a + 0x70) = 1;
	}
	if (*(int*) (a + 0xd4) != -1) {
		*(int*) (a + 0x70) = 0x400;
	}
	idx = *(int*) (a + 0x70);
	if (idx > 2) {
		if (idx == 3) {
			i = *(int*) (a + 0xd8);
			if (i <= 3 && *(int*) (a + 0xb4 + i * 4) != -1) {
				if (fcn_00500d20(a + 0x44, (char*) 0x7f4c00) > 0x1e0) {
					*(pos14_7f4c00*) (a + 0x52) = g_7f4c00;
					fcn_00500bb0(a + 0x52, 0, 2, 0);
					*(int*) (a + 0x84) = fcn_004c5620(1, a);
					return;
				}
				ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (a + 0xb4 + i * 4));
				*(int*) (a + 0xd8) = i + 1;
				if (ent == 0) {
					*(pos14_7f4c00*) (a + 0x52) = g_7f4c00;
					fcn_00500bb0(a + 0x52, 0, 2, 0);
					*(int*) (a + 0x84) = fcn_004c5620(1, a);
					return;
				}
				p = a + 0xc4;
				for (i = 4; i != 0; i--) {
					if (*(int*) p != -1) {
						e = gm_LookupEntityRecordById(*(int*) p);
						if (e != 0 && *(int*) (e + 0x184) != 0) {
							char gest[3][0x20] = {
								"gestik/kopf_kratzen",
								"gestik/durch_haar_fahr",
								"gestik/kinn_kratzen"
							};

							fcn_00529160(0, 0, *(unsigned short*) e, a);
							fcn_004c5c80(*(int*) p);
							fcn_004c5da0(*(int*) p, *(int*) (ent + 1),
							    -1, 0, 1, (char*) 0x6a5ad0);
							fcn_004c5ed0(*(int*) p,
							    gest[gm_RandomMod(3) & 0xffff],
							    (gm_RandomMod(2) & 0xffff) + 1);
						} else {
							*(int*) p = -1;
						}
					}
					p += 4;
				}
				*(pos14_7f4c00*) (a + 0x52) = g_7f4c00;
				fcn_00500bb0(a + 0x52, 0, 2, 0);
				*(int*) (a + 0x84) = fcn_004c5620(2, a);
				sprintf(text, (char*) 0x6a5a8c, *(int*) (ent + 1));
				return;
			}
			if (fcn_00500d20(a + 0x44, (char*) 0x7f4c00) > 0x1e0) {
				*(pos14_7f4c00*) (a + 0x52) = g_7f4c00;
				fcn_00500bb0(a + 0x52, 0, 2, 0);
				*(int*) (a + 0x84) = fcn_004c5620(1, a);
				return;
			}
			*(int*) (a + 0xd8) = 0;
			*(char*) (a + 0xdc) = (char) (*(char*) (a + 0xdc) + 1);
			*(pos14_7f4c00*) (a + 0x52) = g_7f4c00;
			fcn_00500bb0(a + 0x52, 0, 2, 0);
			*(int*) (a + 0x84) = fcn_004c5620(0, a);
			return;
		}
		if (idx != 0x400) {
			return;
		}
		p = a + 0xc4;
		i = 0;
		do {
			if (*(int*) p != -1) {
				e = gm_LookupEntityRecordById(*(int*) p);
				if (e != 0 && *(int*) (e + 0x184) != 0
				    && *(int*) (*(int*) (e + 0x184) + 0x128) != 0) {
					fcn_00500bb0(a + 0x52, 0, 4, 0);
					*(int*) (a + 0x84) = fcn_004c5620(0x400, a);
					return;
				}
			}
			i++;
			p += 4;
		} while (i < 4);
		*(pos14_7f4c00*) (a + 0x52) = g_7f4c00;
		*(int*) (a + 0xd4) = -1;
		fcn_00500bb0(a + 0x52, 0, 2, 0);
		*(int*) (a + 0x84) = fcn_004c5620(3, a);
		return;
	}
	if (idx == 2) {
		i = 0;
		p = a + 0xc4;
		do {
			if (*(int*) p != -1) {
				e = gm_LookupEntityRecordById(*(int*) p);
				if (e != 0 && *(int*) (e + 0x184) != 0
				    && *(int*) (*(int*) (e + 0x184) + 0x128) != 0) {
					return;
				}
			}
			i++;
			p += 4;
		} while (i < 4);
		*(pos14_7f4c00*) (a + 0x52) = g_7f4c00;
		fcn_00500bb0(a + 0x52, 0, 2, 0);
		*(int*) (a + 0x84) = fcn_004c5620(3, a);
		return;
	}
	if (idx == 0) {
		ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (a + 0xac));
		if (ent == 0) {
			goto nopos;
		}
		p = a + 0xc4;
		for (i = 4; i != 0; i--) {
			if (*(int*) p != -1) {
				e = gm_LookupEntityRecordById(*(int*) p);
				if (e != 0 && *(int*) (e + 0x184) != 0) {
					fcn_00529160(0, 0, *(unsigned short*) e, a);
					fcn_004c5c80(*(int*) p);
					fcn_004c5da0(*(int*) p, *(int*) (ent + 1), -1, 0, 1,
					    (char*) 0x6a5ad0);
				} else {
					*(int*) p = -1;
				}
			}
			p += 4;
		}
		sprintf(text, (char*) 0x6a5ab0, *(int*) (ent + 1));
		*(pos14_7f4c00*) (a + 0x52) = g_7f4c00;
		fcn_00500bb0(a + 0x52, 0, 2, 0);
		*(int*) (a + 0x84) = fcn_004c5620(2, a);
		return;
	}
	if (idx != 1) {
		return;
	}
	ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (a + 0xb0));
	if (ent == 0) {
		goto nopos;
	}
	q = fcn_00502cd0(*(int*) (ent + 0x5d), 1, 0, 0x146);
	damage = 0;
	hits = 0;
	p = a + 0xc4;
	for (i = 4; i != 0; i--) {
		if (*(int*) p != -1) {
			e = gm_LookupEntityRecordById(*(int*) p);
			if (e != 0 && *(int*) (e + 0x184) != 0) {
				base = (int) ((float) *(unsigned char*) (e + 0x82) * g_664168
				    + 1.0f);
				kind = (gm_RandomMod(4) & 0xffff) + 3;
				while (kind != 0) {
					damage += (gm_RandomMod((base + 1) * base)
					    & 0xffff) + base * 2;
					kind--;
				}
				hits++;
				fcn_004c5c80(*(int*) p);
				fcn_004c5da0(*(int*) p, *(int*) (ent + 1), *(int*) (q + 2),
				    0, 0, (char*) 0x6a5ad0);
				fcn_00529160(0, 0, *(unsigned short*) e, a);
			} else {
				*(int*) p = -1;
			}
		}
		p += 4;
	}
	if (flags) {
		fcn_00546190(a);
		return;
	}
	if (hits != 0) {
		dmg = fcn_0050b750(damage, g_773d75);
		io_FormatTextBuffer(buf, 0x1a6a, dmg);
		he_MessageBoxQuickjump(*(int*) ((char*) 0x7f4ca4 + *(unsigned short*) (a + 8) * 0x21c),
		    -1, buf, 0, 0x5ec, *(int*) (ent + 1), -1, 0, 0);
		fcn_004c5150(*(int*) ((char*) 0x7f4ca4 + *(unsigned short*) (a + 8) * 0x21c),
		    -1, g_773d75, dmg);
	}
	*(pos14_7f4c00*) (a + 0x52) = g_7f4c00;
	fcn_00500bb0(a + 0x52, 0, 2, 0);
	*(int*) (a + 0x84) = fcn_004c5620(-1, a);
	sprintf(text, (char*) 0x6a5ac0, *(int*) (ent + 1));
	return;
nopos:
	*(pos14_7f4c00*) (a + 0x52) = g_7f4c00;
	fcn_00500bb0(a + 0x52, 0, 1, 0);
	*(int*) (a + 0x84) = fcn_004c5620(-1, a);
	return;
}
