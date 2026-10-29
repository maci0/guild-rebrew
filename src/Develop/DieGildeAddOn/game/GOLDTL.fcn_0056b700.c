#include "client_types.h"

typedef struct
{
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats;

extern char* __cdecl fcn_00508e40(int);
extern void __cdecl fcn_00529160(int, int, int, char*);
extern int __cdecl fcn_004c5da0(int, int, int, char*, int, char*);
extern int __cdecl fcn_004c5620(int, char*);
extern int __cdecl fcn_004c4450(int);
extern char* __cdecl fcn_004c4480(int);
extern int __cdecl fcn_004e6a30(int);
extern void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
extern int __cdecl fcn_00500cb0(pos14_7f4c00*, pos14_7f4c00*);
extern void __cdecl fcn_00546190(char*);
extern void __cdecl fcn_004432d0(int, int);
extern char* __cdecl fcn_00445600(int, int, int, char*);
extern void __cdecl fcn_00455350(char*, char*, float*);
extern int __cdecl fcn_00451840(float*, float*, float);
extern void __cdecl he_CharacterBehavior(char*, int);
extern char* __cdecl fcn_005463a0(int, int, int);
extern char* __cdecl he_fn_Handlung(void);
extern char* __cdecl gm_FindRecordById(int);
extern int __cdecl fcn_0050de80(char*, Stats*);
extern int __cdecl _ftol(float);
extern char* __cdecl fcn_00502cd0(int, ...);
extern char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern void* __cdecl fcn_004e69e0(int, int);
extern int __cdecl gm_RandomMod(int);
extern int __cdecl fcn_0064d470(char*, char*);
extern void __cdecl fcn_004d1d40(char*, unsigned char);
extern int __cdecl fcn_004c5980(void*);

/* ADDRESS: GOLDTL 0x0056b700 */
void __cdecl fcn_0056b700(char* obj)
{
	unsigned char msg[0x114];
	Stats stats;
	float pos[3];
	char* list[4];
	char* sel[3];
	char* rec;
	char* door;
	char* slot;
	char* cur;
	char* iter;
	char* ent;
	int code;
	int saved;
	int count;
	int i;
	int limit;
	int nearby;
	int r;
	int prev;
	int v11;
	unsigned char mode;

	code = *(int*) (obj + 0x84);
	if (code != -1 && !fcn_004c4450(code))
		return;
	saved = *(int*) 0x6b8010;
	*(int*) (obj + 0x84) = -1;
	switch (*(int*) (obj + 0x70)) {
	case 0:
		if (*(unsigned char*) (obj + 0x78) & 2) {
			count = 0;
			iter = obj + 0x8c;
			*(int*) (obj + 0xe4) = 0;
			for (i = 8; i != 0; i--) {
				if (*(int*) iter != -1) {
					rec = fcn_00508e40(*(int*) iter);
					if (rec != 0) {
						fcn_00529160(0, 0, *(unsigned short*) rec, obj);
						fcn_004c5da0(*(int*) iter, -1, -1, obj + 0xac, 1, (char*) 0x6a6aa0);
						count++;
						*(int*) (obj + 0xe4) += *(unsigned char*) (rec + 0x82);
					}
				}
				iter += 4;
			}
			if (count == 0) {
				*(int*) (obj + 0x84) = fcn_004c5620(-1, obj);
				*(int*) (obj + 0xe4) = 0;
				return;
			}
			*(int*) (obj + 0xe4) /= count;
		}
		*(pos14_7f4c00*) (obj + 0x52) = *(pos14_7f4c00*) 0x7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (obj + 0x52), 0, 0x1e, 0);
		*(int*) (obj + 0x70) = *(int*) (obj + 0x70) + 1;
		return;
	case 1:
		goto label_56b858;
	case 2:
		saved = *(int*) (obj + 0xdc);
		if (!fcn_004c4450(saved))
			return;
		cur = fcn_004c4480(*(int*) (obj + 0xdc));
		if (cur != 0) {
			*(int*) (obj + 0xe0) = *(int*) cur;
			*(pos14_7f4c00*) (obj + 0x52) = *(pos14_7f4c00*) 0x7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (obj + 0x52), 0, 1, 0);
			*(int*) (obj + 0x70) = 3;
			return;
		}
		*(int*) (obj + 0x84) = fcn_004c5620(1, obj);
		return;
	case 3:
		if (!fcn_004e6a30(*(int*) (obj + 0xe0))) {
			*(pos14_7f4c00*) (obj + 0x52) = *(pos14_7f4c00*) 0x7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (obj + 0x52), 0, 0, 1);
			*(int*) (obj + 0x70) = -1;
			return;
		}
		*(pos14_7f4c00*) (obj + 0x52) = *(pos14_7f4c00*) 0x7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (obj + 0x52), 0, 5, 0);
		return;
	case -2:
	case -1:
		if (*(unsigned char*) (obj + 0x78) & 2) {
			ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (obj + 0x10));
			iter = obj + 0x8c;
			for (i = 8; i != 0; i--) {
				if (*(int*) iter != -1) {
					rec = fcn_00508e40(*(int*) iter);
					if (rec != 0) {
						if (ent != 0)
							fcn_004c5da0(*(int*) (rec + 4), *(int*) (ent + 1), -1, 0, 0, (char*) 0x6a6aa0);
						fcn_00529160(0, 0, *(unsigned short*) rec, 0);
					}
				}
				iter += 4;
			}
		}
		fcn_00546190(obj);
		return;
	default:
		return;
	}
label_56b858:
	if (*(unsigned char*) (obj + 0x78) & 2) {
		nearby = 1;
		door = 0;
		prev = -1;
		count = 0;
		list[0] = 0;
		list[1] = 0;
		list[2] = 0;
		fcn_004432d0(0, 1);
		door = fcn_00445600(0, 0x100, 0, obj + 0xac);
		if (door != 0)
			fcn_00455350(door, door + 0x4c, pos);
		for (i = 0, iter = obj + 0x8c; i < 8; i++, iter += 4) {
			if (*(int*) iter == -1)
				continue;
			cur = fcn_00508e40(*(int*) iter);
			if (cur == 0)
				continue;
			cur = *(char**) (*(int*) (cur + 0x184) + 0x34);
			if (!fcn_00451840((float*) (cur + 0x4c), pos, 25000.0f)) {
				nearby = 0;
				break;
			}
		}
		he_CharacterBehavior(obj, (int) pos);
		list[3] = fcn_005463a0(1, 0, 0x51);
		ent = fcn_005463a0(1, 0, 0xf);
		if (nearby) {
			while (door != 0 && ent != 0 && count <= 2) {
				if (*(char*) (ent + 0xf0) == 0 &&
				    *(unsigned short*) (ent + 8) != *(unsigned short*) (obj + 8) &&
				    (prev == -1 ||
				     prev == *(int*) ((unsigned int) *(unsigned short*) (ent + 8) * 0x21c + 0x7f4ca4))) {
					cur = gm_FindRecordById(*(int*) (ent + 0xac));
					if (cur == 0)
						goto next;
					r = fcn_00451840((float*) (*(int*) (*(int*) (cur + 0x3b) + 0x34) + 0x4c), pos, 1500.0f);
					fcn_0050de80(cur, &stats);
					code = stats.xb0;
					if (code <= 0)
						goto next;
					v11 = _ftol((float) ((double) *(unsigned int*) (obj + 0xe4) * *(float*) 0x664168));
					if (v11 == 0) {
						if (code <= 100 || code >= 500) {
							if (!r)
								goto next;
							goto accept;
						}
					} else if (v11 == 1) {
						if (code <= 200 || code >= 750) {
							if (!r)
								goto next;
							goto accept;
						}
					} else if (v11 == 2) {
						if (code <= 300 || code >= 1000) {
							if (!r)
								goto next;
							goto accept;
						}
					} else if (v11 == 3) {
						if (code <= 500 || code >= 1500) {
							if (!r)
								goto next;
							goto accept;
						}
					} else if (v11 == 4) {
						if (code <= 600 || code >= 1750) {
							if (!r)
								goto next;
							goto accept;
						}
					} else if (v11 == 5) {
						if (code <= 700) {
							if (!r)
								goto next;
							goto accept;
						}
					} else if (!r)
						goto next;
				accept:
					sel[count] = ent;
					prev = *(int*) ((unsigned int) *(unsigned short*) (ent + 8) * 0x21c + 0x7f4ca4);
					*(char*) (ent + 0xf0) = 1;
					list[count] = fcn_00502cd0(0, 2, 7, 1, *(int*) (ent + 0xac));
					count++;
				}
			next:
				ent = he_fn_Handlung();
			}
		}
		limit = 0x50;
		if (list[3] != 0)
			limit -= 0x32;
		if (*(int*) 0x774800)
			limit = 0;
		fcn_004432d0(saved, 1);
		if (count != 0 && fcn_004e69e0(3, -1) == 0 &&
		    limit < (int) (gm_RandomMod(100) & 0xffff)) {
			slot = gm_StartFilteredEntitySearch(1, 1, *(int*) (obj + 0x10));
			if (slot != 0) {
				memset(msg, 0, sizeof(msg));
				msg[8] = 3;
				msg[0x26] = 0xa2;
				*(int*) (msg + 0xc) = *(int*) ((unsigned int) *(unsigned short*) 0x774970 * 0x21c + 0x7f4ca4);
				*(int*) (msg + 0x14) = -1;
				msg[0x30] = 2;
				msg[0x7c] = 1;
				*(int*) (msg + 0x38) = prev;
				*(int*) (msg + 0x34) = *(int*) ((unsigned int) *(unsigned short*) (slot + 0x27) * 0x21c + 0x7f4ca4);
				if (door != 0 && fcn_0064d470(door, (char*) 0x6a1d10) != 0)
					msg[0x7c] |= 8;
				for (i = 0; i < 0x10; i++) {
					*(int*) (msg + 0x80 + i * 4) = -1;
					*(int*) (msg + 0xc0 + i * 4) = -1;
				}
				for (i = 0; i < 3; i++) {
					if (list[i] != 0)
						*(int*) (msg + 0x100 + i * 4) = *(int*) (list[i] + 2);
					else
						*(int*) (msg + 0x100 + i * 4) = -1;
				}
				for (i = 0; i < count; i++) {
					mode = *(unsigned char*) (list[i] + 0x28);
					if (mode != 2 || count != 1) {
						fcn_004d1d40((char*) msg, mode);
					} else {
						fcn_004d1d40((char*) msg, mode);
						fcn_004d1d40((char*) msg, 1);
					}
				}
				*(int*) (msg + 0x10c) = *(int*) (slot + 1);
				for (i = 0; i < 8; i++)
					*(int*) (msg + 0xc0 + i * 4) = *(int*) (obj + 0x8c + i * 4);
				*(pos14_7f4c00*) (msg + 0x18) = *(pos14_7f4c00*) 0x7f4c00;
				fcn_00500bb0((pos14_7f4c00*) (msg + 0x18), 0xf, 0, 0);
				*(int*) (obj + 0xdc) = fcn_004c5980(msg);
				*(pos14_7f4c00*) (obj + 0x52) = *(pos14_7f4c00*) 0x7f4c00;
				*(int*) (obj + 0x70) = 2;
				return;
			}
			fcn_00546190(obj);
			return;
		}
	}
	if (fcn_00500cb0((pos14_7f4c00*) 0x7f4c00, (pos14_7f4c00*) (obj + 0xcc)) >= 0) {
		*(int*) (obj + 0x84) = fcn_004c5620(-1, obj);
		return;
	}
	*(pos14_7f4c00*) (obj + 0x52) = *(pos14_7f4c00*) 0x7f4c00;
	limit = (gm_RandomMod(5) & 0xffff) + 10;
	fcn_00500bb0((pos14_7f4c00*) (obj + 0x52), 0, limit, 0);
}
