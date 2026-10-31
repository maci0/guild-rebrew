/*
 * Parent-profession chooser of the "ChooseProfession" dialog chain.
 *
 * Entries 4 and 5 of the 0x7e1fc0 table select the father and mother slot;
 * each of the six 48-byte rows below holds the relation named by the
 * fcn_0053b090 profession figures ("dummy_VATER", "dummy_MUTTER", the four
 * grandparent relations).  The candidate figure comes from the dialog at
 * 0x7746a0 and is stored in its +0x23c slot field once picked.
 */
#include <string.h>

#include "Develop/Units/d3/d3_camera.h"

typedef struct {
	float a;
	float b;
	float c;
} Vec3;

/* SIZE 0x240 */
typedef struct {
	char pad0[0x23c];
	int slot;
} Figure;

typedef void (__cdecl *VirtFn)(int, int, int, int);


int __cdecl fcn_00533880(void);
int __cdecl fcn_005338a0(void);
int __cdecl fcn_004432d0(int, int);
Figure *__cdecl fcn_0053b090(char *, char *, int);
int __cdecl fcn_00470820(int, int, char *);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_004e4b60(char *);
int __cdecl fcn_00445f50(unsigned int, float, float, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_005373e0(int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_00433780(void *);
void __cdecl fcn_00412cf0(char *, Vec3 *, Vec3 *, int, int);
char *__cdecl fcn_00445600(char *, int, char *, char *);
void __cdecl fcn_0040b920(char *, char *);
int __cdecl fcn_0053b1b0(void);
int __cdecl fcn_0053cd40(int);
unsigned int __cdecl fcn_0053b6b0(int);
void __cdecl fcn_00471af0(int, int);
char *__cdecl fcn_004730c0(int, int, int, int, char *, int, int);
int __cdecl fcn_004030e0(char *);
void *__cdecl fcn_00426cc0(int);
int __cdecl fcn_00428720(char *);
void __cdecl fcn_005312d0(int);
void __cdecl gv_Free3Fields(void *);
void __cdecl fcn_004e4c00(void);
void __cdecl fcn_00473150(char *);

/* ADDRESS: GOLDTL 0x0053c560 */
int __cdecl fcn_0053c560(void)
{
	int ret = 0;
	Figure *rhFrau;
	Figure *rhMann;
	Figure *hwMann;
	Figure *vhFrau;
	Figure *kampfMann;
	Figure *nnFrau;
	Figure *vhMann;
	Figure *hwFrau;
	Figure *nnMann;
	char *spr = 0;
	Vec3 parentB;
	int oldSound;
	Vec3 parentA;
	int i;
	char buf[6][48] = {
		"dummy_GROSSVATER_VAETERLICH",
		"dummy_GROSSMUTTER_VAETERLICH",
		"dummy_GROSSVATER_MUETTERLICH",
		"dummy_GROSSMUTTER_MUETTERLICH",
		"dummy_VATER",
		"dummy_MUTTER"
	};
	int mode;
	int flag = 1;
	int obj;
	Figure *obj2;
	char *found;
	int base;
	int sub;
	VirtFn fn;

	memset((void *) 0x7e1fc0, 0, 0x2c);
	memset((void *) 0x7e1fc0, -1, 0x18);
	fcn_00533880();
	fcn_005338a0();
	fcn_004432d0(1, 0);
	if (*(int *) 0x67a370 != 0) {
		base = *(int *) 0x67a370;
		sub = *(int *) (base + 0x3c8);
		if (sub != 0) {
			fn = *(VirtFn *) (sub + 0x210);
			if (fn != 0)
				fn(base, 4, sub + 0x214, 0);
		}
	}
	oldSound = *(int *) 0x6791d0;
	if (*(int *) 0x6b8300 != 0) {
		base = *(int *) 0x6b8300;
		*(unsigned char *) (base + 0x8036) =
		    (unsigned char) ((*(unsigned char *) (base + 0x8036) & 0xeb) | 8);
	}
	nnMann = fcn_0053b090((char *) 0x6a3ecc, (char *) 0x6a3ee8, 0);
	nnFrau = fcn_0053b090((char *) 0x6a3eb0, (char *) 0x6a3c34, 8);
	hwMann = fcn_0053b090((char *) 0x6a3e84, (char *) 0x6a3ea0, 1);
	hwFrau = fcn_0053b090((char *) 0x6a3e68, (char *) 0x6a3ccc, 7);
	kampfMann = fcn_0053b090((char *) 0x6a3e54, (char *) 0x6a3d7c, 4);
	vhMann = fcn_0053b090((char *) 0x6a3e3c, (char *) 0x67fa28, 3);
	vhFrau = fcn_0053b090((char *) 0x6a3e24, (char *) 0x68d45c, 5);
	rhMann = fcn_0053b090((char *) 0x6a3e00, (char *) 0x6a3e14, 2);
	rhFrau = fcn_0053b090((char *) 0x6a3dec, (char *) 0x6a3c78, 6);
	obj = fcn_00470820(0, 0, (char *) 0x6a3dd4);
	fcn_00471d80(obj, 1);
	fcn_004e4b60((char *) 0x6a3dc4);
	i = 4;
	fcn_00445f50(i, 0, 1.0f, 1);
	if (*(int *) 0x6a37f8 != -1) {
		fcn_00471e30(*(int *) 0x6a37f8);
		*(int *) 0x6a37f8 = -1;
	}
	*(int *) 0x7725c8 = 0;
	if (fcn_005373e0(0x53c560, 0x12d6) != 0) {
		do {
			if (flag) {
				for (i = 4; i < 6; i++) {
					if (((int *) 0x7e1fc0)[i] == -1)
						break;
				}
				if (i < 6) {
					d2_SetForm(obj, 0);
					io_AppendText(0x6811b0);
					io_AppendText(0x1ae6, i + 0x1aea);
					if (i % 2) {
						parentA = *(Vec3 *) (g_6b8014 + 0xfc);
						parentB = *(Vec3 *) (g_6b8014 + 0x108);
					} else {
						parentA = *(Vec3 *) (g_6b8014 + 0xe4);
						parentB = *(Vec3 *) (g_6b8014 + 0xf0);
					}
					fcn_00433780(g_6b8014);
					*(int *) 0x6b5cbc = 0;
					*(int *) 0x6b5cc0 = 0;
					fcn_00412cf0(g_6b8014, &parentA, &parentB, 0x50, 8);
				}
				flag = 0;
			}
			if (*(int *) 0x14ce8e0 != 0)
				*(int *) 0x774654 = 1;
			if (*(int *) 0x7746a0 != 0) {
				obj2 = (Figure *) *(int *) (*(int *) 0x7746a0 + 0x204);
				if (obj2 != 0) {
					if (obj2->slot == -1) {
						mode = 0;
						if (obj2 == nnMann || obj2 == nnFrau)
							mode = 2;
						else if (obj2 == vhMann || obj2 == vhFrau)
							mode = 0;
						else if (obj2 == kampfMann)
							mode = 3;
						else if (obj2 == rhMann || obj2 == rhFrau)
							mode = 4;
						else if (obj2 == hwMann || obj2 == hwFrau)
							mode = 1;
						if (i % 2) {
							if (obj2 == nnFrau || obj2 == vhFrau ||
							    obj2 == rhFrau || obj2 == hwFrau) {
								i = 5;
								goto slot_found;
							}
						} else if (obj2 == nnMann || obj2 == vhMann ||
						    obj2 == rhMann || obj2 == hwMann ||
						    obj2 == kampfMann) {
							i = 4;
slot_found:
							((int *) 0x7e1fc0)[i] = mode;
							obj2->slot = i;
							found = fcn_00445600(0, 0x100, 0, buf[i]);
							if (found != 0)
								fcn_0040b920((char *) obj2, found);
						}
					}
					flag = 1;
				}
			}
			if (i >= 6) {
				d2_SetForm(obj, 0);
				io_AppendText(0x6811b0);
				fcn_00471af0(obj, 0);
				fcn_00433780(g_6b8014);
				*(int *) 0x6b5cbc = 0;
				*(int *) 0x6b5cc0 = 0;
				fcn_00412cf0(g_6b8014,
				    (Vec3 *) (g_6b8014 + 0x114),
				    (Vec3 *) (g_6b8014 + 0x120), 0x50, 8);
				if (fcn_0053b1b0()) {
					if (fcn_0053cd40(0xc6) &&
					    fcn_0053b6b0(*(unsigned char *) 0x7e23e3)) {
						*(int *) 0x774654 = 1;
						ret = 1;
					} else if (!ret) {
						fcn_00471af0(obj, 1);
					}
				} else {
					*(int *) 0x774654 = 1;
					ret = 0;
					fcn_00471af0(obj, 1);
				}
			}
		} while (fcn_005373e0(0x53c560, 0x12d6) != 0);
		if (ret == 1) {
			spr = fcn_004730c0(0, 0, *(int *) 0x1040494,
			    *(int *) 0x1040490, (char *) 0x67d67c, 0x5a, 1);
			while ((*(unsigned char *) spr & 4) == 0)
				fcn_005373e0(0, 0xc6);
		}
	}
	if (nnMann != 0)
		fcn_004030e0((char *) nnMann);
	if (nnFrau != 0)
		fcn_004030e0((char *) nnFrau);
	if (hwMann != 0)
		fcn_004030e0((char *) hwMann);
	if (hwFrau != 0)
		fcn_004030e0((char *) hwFrau);
	if (kampfMann != 0)
		fcn_004030e0((char *) kampfMann);
	if (vhMann != 0)
		fcn_004030e0((char *) vhMann);
	if (vhFrau != 0)
		fcn_004030e0((char *) vhFrau);
	if (rhFrau != 0)
		fcn_004030e0((char *) rhFrau);
	if (rhMann != 0)
		fcn_004030e0((char *) rhMann);
	if (obj != -1)
		fcn_00471e30(obj);
	if (oldSound != -1) {
		found = fcn_00426cc0(oldSound);
		if (found != 0)
			fcn_00428720(found);
		fcn_005312d0(oldSound);
	}
	if (*(int *) (*(int *) 0x67a370 + 0xb0) != 0) {
		gv_Free3Fields((void *) *(int *) (*(int *) 0x67a370 + 0xb0));
		*(int *) (*(int *) 0x67a370 + 0xb0) = 0;
	}
	fcn_004e4c00();
	if (*(int *) 0x67a370 != 0) {
		base = *(int *) 0x67a370;
		sub = *(int *) (base + 0x3c8);
		if (sub != 0) {
			fn = *(VirtFn *) (sub + 0x294);
			if (fn != 0)
				fn(base, 5, sub + 0x298, 0);
		}
	}
	fcn_00433780(g_6b8014);
	*(int *) 0x6b5cbc = 0;
	*(int *) 0x6b5cc0 = 0;
	if (spr != 0)
		fcn_00473150(spr);
	return ret;
}
