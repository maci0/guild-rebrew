extern int g_7746d8;
extern int g_14ce8d8;
#include "Develop/Units/d2.v1/d2_gui.h"

extern char* lpObjektePROT;
extern char* g_aed32c;

char* __cdecl fcn_00502cd0(int, int, int, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl fcn_0050dfd0(char*, int);
int __cdecl gm_GetMsgField(char*, void*);
int __cdecl fcn_004c4510(int, int);
int __cdecl fcn_004c4700(int, int, int, int*);
void __cdecl fcn_004c53a0(void);
int __cdecl fcn_00471f80(int);
int __cdecl CountDisplayCounters(void);

/* ADDRESS: GOLDTL 0x00595e20 */
int __cdecl fcn_00595e20(char* a0, char* a1)
{
	unsigned int tbl1[36];
	unsigned int tbl2[18];
	int cat;
	register int found;
	int i;
	unsigned int* p;
	unsigned short* ent;
	char* q;

	tbl1[2] = 0;
	tbl1[0x12] = 0;
	tbl1[3] = 0;
	tbl1[0xa] = 0;
	tbl1[0x13] = 0;
	tbl1[0x16] = 0;
	tbl1[0xb] = 0;
	tbl1[0x17] = 0;
	tbl1[6] = 0;
	tbl1[0x1a] = 0;
	tbl1[0xc] = 3;
	tbl1[0x14] = 3;
	tbl1[0x1d] = 3;
	tbl2[7] = 3;
	tbl2[0xb] = 3;
	tbl2[0xe] = 3;
	tbl1[0] = 2;
	tbl1[4] = 2;
	tbl1[7] = 0;
	tbl1[8] = 2;
	tbl1[0x15] = 2;
	tbl1[0x19] = 2;
	tbl1[0x1b] = 0;
	tbl2[1] = 2;
	tbl2[3] = 2;
	tbl2[5] = 2;
	tbl2[0xa] = 2;
	tbl2[0xc] = 2;
	tbl1[0xe] = 0;
	tbl1[0x1e] = 0;
	tbl1[0xf] = 0;
	tbl1[0x1f] = 0;
	tbl1[0x22] = 0;
	tbl1[1] = 0;
	tbl1[5] = 0;
	tbl1[9] = 0;
	tbl1[0xd] = 0;
	tbl1[0x10] = 4;
	tbl1[0x11] = 0;
	tbl1[0x18] = 4;
	tbl1[0x1c] = 4;
	tbl1[0x20] = 4;
	tbl1[0x21] = 4;
	tbl1[0x23] = 0;
	tbl2[0] = 0;
	tbl2[2] = 0;
	tbl2[4] = 0;
	tbl2[6] = 0;
	tbl2[8] = 0;
	tbl2[9] = 4;
	tbl2[0xd] = 4;
	tbl2[0xf] = 4;
	tbl2[0x10] = 4;
	tbl2[0x11] = 4;

	cat = gm_GetBuildingTypeCategory(*(unsigned char*) a0);

	i = 0;
	for (p = (unsigned int*) 0x778d4c; (int) p < 0x778d9c; p += 5) {
		*p = tbl1[*(unsigned char*) (a1 + 0x1c) * 4 + i];
		i++;
	}
	i = 0;
	for (p = (unsigned int*) 0x77912c; (int) p < 0x779154; p += 5) {
		*p = tbl2[*(unsigned char*) (a1 + 0x1d) * 2 + i];
		i++;
	}

	ent = (unsigned short*) fcn_00502cd0(*(int*) (a1 + 0x14), 1, 5);
	while (ent != 0) {
		if (cat == 2) {
			if (*(char*) (lpObjektePROT + *ent * 0x41) == 0x17)
				goto add16;
		} else {
			q = lpObjektePROT + *ent * 0x41;
			if (*q == 0x17 || *q == 0x25)
				goto add16;
		}

		for (i = 0, p = (unsigned int*) 0x7796e0; (int) p < 0x7798a0; p += 0xe) {
			if (*p == *ent)
				break;
			i++;
		}
		if (i < 8) {
			*(int*) (i * 0x38 + 0x77970c) =
			    (unsigned int) (fcn_0050dfd0(a1, *ent) * *(int*) (ent + 0xe)) >> 2;
			*(int*) (i * 0x38 + 0x779710) = gm_GetMsgField(a1, ent);
			*(int*) (i * 0x38 + 0x779714) = fcn_0050dfd0(a1, *ent);
			goto next;
		}
		for (i = 0, p = (unsigned int*) 0x7796e0; (int) p < 0x7798a0; p += 0xe) {
			if (*p == 0)
				break;
			i++;
		}
		if (i < 8) {
			*(int*) (i * 0x38 + 0x7796e0) = *ent;
			*(int*) (i * 0x38 + 0x77970c) =
			    (unsigned int) (fcn_0050dfd0(a1, *ent) * *(int*) (ent + 0xe)) >> 2;
			*(int*) (i * 0x38 + 0x779710) = gm_GetMsgField(a1, ent);
			*(int*) (i * 0x38 + 0x779714) = fcn_0050dfd0(a1, *ent);
		}
		goto next;

	add16:
		for (i = 0, p = (unsigned int*) 0x778da0; (int) p < 0x779120; p += 0xe) {
			if (*p == *ent)
				break;
			i++;
		}
		if (i < 16) {
			*(int*) (i * 0x38 + 0x778dcc) =
			    (unsigned int) (fcn_0050dfd0(a1, *ent) * *(int*) (ent + 0xe)) >> 2;
			*(int*) (i * 0x38 + 0x778dd0) = gm_GetMsgField(a1, ent);
			*(int*) (i * 0x38 + 0x778dd4) = fcn_0050dfd0(a1, *ent);
			goto next;
		}
		for (i = 0, p = (unsigned int*) 0x778da0; (int) p < 0x779120; p += 0xe) {
			if (*p == 0)
				break;
			i++;
		}
		if (i < 16) {
			*(int*) (i * 0x38 + 0x778da0) = *ent;
			*(int*) (i * 0x38 + 0x778dcc) =
			    (unsigned int) (fcn_0050dfd0(a1, *ent) * *(int*) (ent + 0xe)) >> 2;
			*(int*) (i * 0x38 + 0x778dd0) = gm_GetMsgField(a1, ent);
			*(int*) (i * 0x38 + 0x778dd4) = fcn_0050dfd0(a1, *ent);
		}

	next:
		ent = (unsigned short*) gm_NextEntityQueryMatch();
	}

	for (p = (unsigned int*) 0x778da0; (int) p < 0x779120; p += 0xe) {
		if (!fcn_00502cd0(*(int*) (a1 + 0x14), 1, 0, *p))
			*p = 0;
	}
	for (p = (unsigned int*) 0x7796e0; (int) p < 0x7798a0; p += 0xe) {
		if (!fcn_00502cd0(*(int*) (a1 + 0x14), 1, 0, *p))
			*p = 0;
	}

	found = 0;
	for (p = (unsigned int*) 0x778db0; !found && (int) p < 0x779130; p += 0xe) {
		if (*p != (unsigned int) -1
		    && *(int*) (g_1015ea0 + *p * 0x2f4 + 0x20) == 0x41
		    && fcn_00471f80(*p))
			found = 1;
	}
	if (!found) {
		for (p = (unsigned int*) 0x7796f0; !found && (int) p < 0x7798b0; p += 0xe) {
			if (*p != (unsigned int) -1
			    && *(int*) (g_1015ea0 + *p * 0x2f4 + 0x20) == 0x41
			    && fcn_00471f80(*p))
				found = 1;
		}
	}

	if ((g_7746d8 & 0x200) != 0 && g_14ce8d8 != 0 && !CountDisplayCounters()) {
		for (p = (unsigned int*) 0x778dc0; (int) p < 0x779140; p += 0xe) {
			if (*p == (unsigned int) -1 || *p != *(unsigned int*) 0x67d370)
				continue;
			ent = (unsigned short*) fcn_00502cd0(*(int*) (a1 + 0x14), 1, 0, p[-8]);
			if (ent == 0)
				break;
			if (*(unsigned int*) (ent + 0xe) >= 4)
				cat = 0;
			else
				cat = *(unsigned int*) (ent + 0xe) + 1;
			fcn_004c4510((int) ent, *(int*) (ent + 1));
			fcn_004c4700(4, 1, (int) ((char*) ent - g_aed32c) + 0x1c, &cat);
			fcn_004c53a0();
			*(int*) (ent + 0xe) = cat;
		}
		for (p = (unsigned int*) 0x779700; (int) p < 0x7798c0; p += 0xe) {
			if (*p == (unsigned int) -1 || *p != *(unsigned int*) 0x67d370)
				continue;
			ent = (unsigned short*) fcn_00502cd0(*(int*) (a1 + 0x14), 1, 0, p[-8]);
			if (ent == 0)
				break;
			if (*(unsigned int*) (ent + 0xe) >= 4)
				cat = 0;
			else
				cat = *(unsigned int*) (ent + 0xe) + 1;
			fcn_004c4510((int) ent, *(int*) (ent + 1));
			fcn_004c4700(4, 1, (int) ((char*) ent - g_aed32c) + 0x1c, &cat);
			fcn_004c53a0();
			*(int*) (ent + 0xe) = cat;
		}
	}
	return found;
}
