#include <string.h>
extern unsigned char* lpGebaeudePROT;
extern unsigned char* lpGebaeudeINST;
extern unsigned char g_773d75;
extern double g_662a48;
extern double g_664360;
extern float g_6628d8;
extern float g_664198;

int __cdecl fcn_0050e4a0(int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int, unsigned char);
float __cdecl fcn_004fc460(char*);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_00495400(int, int, int, void*, void*);
int __cdecl fcn_0050d170(int);
int __cdecl fcn_004a4bb0(int, char*, int, void*, void*, int);

/* ADDRESS: GOLDTL 0x0049d300 */
int __cdecl ai_StartBuergermeister(int a0, unsigned short* a1, int a2,
	unsigned int* a3, unsigned int* a4)
{
	int ptrs[6];
	int vals[6];
	unsigned char* e;
	unsigned char* best;
	int r;
	int i;
	int n;
	int kind;
	int mask;
	unsigned short flags;
	int val;
	float buf[10];

	best = 0;
	ptrs[0] = 0;
	ptrs[1] = 0;
	vals[0] = 0;
	vals[1] = 0;
	if (a0 != 0 || a2 != 0 || *(unsigned char*) &a1[0xb3] != 0x0f) {
		return 0;
	}
	r = fcn_0050e4a0(1);
	if (r == 0) {
		return 0;
	}
	r = fcn_00502cd0(*(int*) (r + 0x5d), 2, 6, 0, 0x115);
	a0 = fcn_0050b810(*(int*) (r + 0x14), g_773d75);
	fcn_004fc460((char*) buf);
	e = lpGebaeudeINST;
	a2 = 0x100;
	do {
		kind = *e;
		if (kind != 0 && lpGebaeudePROT[kind * 0x24d] == 1) {
			flags = *(unsigned short*) (e + 0x5a);
			if ((flags & 0x45) == 0) {
				if (*(char*) (e + 0x5c) <= 0x4f
					&& (best == 0 || *(char*) (e + 0x5c) < *(char*) (best + 0x5c))) {
					best = e;
				}
				if (kind == 3) {
					/* counted below */
				}
				else if (kind == 2) {
					vals[1] += 1;
					if ((flags & 0x45) == 0) {
						ptrs[1] = (int) e;
					}
				}
				else {
					vals[0] += 1;
					if ((flags & 0x45) == 0) {
						ptrs[0] = (int) e;
					}
				}
			}
		}
		e += 0xa9;
		a2 -= 1;
	} while (a2 != 0);
	if ((*(float*) ((char*) a1 + 0x100) - g_662a48) * g_664360 < buf[3]) {
		if (vals[0] != 0 && ptrs[0] != 0) {
			*(unsigned char*) a3 = 4;
			a3[1] = 2;
			n = fcn_0050d170(2);
			e = (unsigned char*) ptrs[0];
		} else if (vals[1] != 0 && ptrs[1] != 0) {
			*(unsigned char*) a3 = 4;
			a3[1] = 3;
			n = fcn_0050d170(3);
			e = (unsigned char*) ptrs[1];
		} else {
			*(unsigned char*) ptrs = 5;
			ptrs[1] = 1;
			n = fcn_0050d170(1);
			if ((double) a0 < (double) n * g_664198)
				return 0;
			ptrs[2] = 1;
			*(unsigned char*) vals = 0;
			vals[1] = 0;
			vals[2] = 0;
			if (fcn_004a4bb0(0, (char*) a1, 1, ptrs, vals, 1) == 0)
				return 0;
			memcpy(a3, ptrs, 0x18);
			memcpy(a4, vals, 0x18);
			return 0x2e;
		}
		if ((double) a0 < (double) n * g_6628d8)
			return 0;
		a3[2] = 1;
		*(unsigned char*) a4 = 4;
		a4[1] = *(unsigned int*) (e + 1);
		a4[2] = 1;
		return 0x2e;
	} else if (best != 0) {
		val = *(char*) (best + 0x5c);
		if (val - (gm_RandomMod(0x20) & 0xffff) < 0x42) {
			*(unsigned char*) ptrs = 4;
			ptrs[1] = *(int*) (best + 1);
			ptrs[2] = 1;
			if (val < 0x21)
				ptrs[4] = 50;
			else
				ptrs[4] = val < 0x42 ? 30 : 10;
			*(unsigned char*) vals = 1;
			vals[1] = *(int*) (r + 2);
			vals[2] = a0;
			vals[4] = 1;
			n = fcn_00495400(0xf, *a1, 0, ptrs, vals);
			if (n != 0) {
				memcpy(a3, ptrs, 0x18);
				memcpy(a4, vals, 0x18);
				return n;
			}
		}
	}
	return 0;
}
