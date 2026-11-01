#include <string.h>

unsigned short* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_00470820(int, int, char*);
int __cdecl fcn_0052dee0(int, int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_0057e880(int, char*, int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl fcn_00533a60(int, int, int*, int, ...);
int __cdecl fcn_00472170(int, int);
float __cdecl fcn_0050bbb0(int);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
int __cdecl fcn_00472830(int, int, int, int*, int*, int*);
void __cdecl fcn_00533dc0(int, int, int);
void __cdecl fcn_00533f40(int, int, int, int);
void __cdecl io_AppendText(int, ...);
void __cdecl fcn_00594340(void);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_005c5da0(int, int, int, int, int);
void __cdecl fcn_00525ef0(void);

/* One 0xf0-byte inventory entity slot. Only the eight bytes at +0x0c..+0x18
   and the two three-int arrays at +0xd8 are written by the native body so far;
   everything between them is still an unnamed region. */
typedef struct {
	int f00;
	int f04;
	int f08;
	int f0c;
	int f10;
	int f14;
	int f18;
	char pad1c[0xbc];
	int fD8[3];
	int fE4[3];
} Ent5ba910;

/*
 * Trade/transport inventory panel controller, frameless __chkstk frame
 * 0x1848 with saved ebx, ebp, esi, edi; arg1 at 0x184c, arg2 at 0x1850.
 * Native extents (offsets from the frame base, i.e. the value added to esp):
 * scalars 0x00..0x158, struct 0xb4 at 0x15c, 16 entity slots of 0xf0 at
 * 0x6d8, two 0x100 objects at 0x15d8/0x16d8, int[28] at 0x17d8.
 * The frame struct below holds those extents while the 0x5ba910 body
 * (3413 instructions) is reconstructed; native locals stay separate and the
 * register assignment (ebp as the zero register, esi for arg1) only
 * converges once the whole body exists.
 */
typedef struct {
	int v10;
	int v14;
	int v18;
	int v1c;
	int v20;
	int v24;
	int v28;
	int v2c;
	int v30;
	int v34;
	int v38;
	int v3c;
	int v40;
	int v44;
	int v48;
	int v4c;
	float v50;
	int v54;
	int v58;
	int v5c;
	int v60;
	float v64;
	int v68;
	int v6c;
	int v70;
	int v74;
	int v78;
	int v7c;
	int v80;
	float v84;
	int v88;
	float v8c;
	int v90;
	int v94;
	int v98;
	int v9c;
	int vA0;
	int vA4;
	int vA8;
	int vAC;
	int vB0;
	int vB4;
	int vB8;
	int vBC;
	int vC0;
	int vC4;
	int vC8;
	int vCC;
	int vD0;
	int vD4[7];
	int vF0[7];
	int v10C[9];
	int v130;
	int v134;
	int v138;
	int v13C;
	int v140;
	int v144;
	int v148;
	int v14C;
	int v150;
	int v154;
	int v158;
	char v15C[0xb4];
	char v210[0x4c8];
	Ent5ba910 v6D8[16];
	char v15D8[0x100];
	char v16D8[0x100];
	char v17D8[0x80];
} frame_t;

/* ADDRESS: GOLDTL 0x005ba910 */
int __cdecl fcn_005ba910(int a1, int a2)
{
	frame_t f;
	int idx;
	int i;
	int j;
	Ent5ba910* e;

	f.v158 = 0;
	memset(f.v15C, 0, 0xb4);
	f.v18 = 0;
	f.v44 = 0;
	f.v94 = 0;
	f.v7c = a1;
	f.v88 = 0;
	f.v10C[0] = 0x51;
	f.v10C[1] = 0;
	f.v10C[2] = 0;
	f.v10C[3] = 0x30;
	f.v10C[4] = 0x71;
	f.v10C[5] = 0;
	f.v10C[6] = 0x11;
	f.v10C[7] = 0x52;
	f.v10C[8] = 0x93;
	f.v38 = 0;
	f.v68 = 0;
	f.v40 = 0;
	f.v3c = 0;
	f.v4c = 0;
	f.v60 = 0;
	f.v50 = 1.0f;
	f.v90 = -1;
	f.vD4[0] = -1;
	f.vD4[1] = -1;
	f.vD4[2] = -1;
	f.vD4[3] = -1;
	f.vD4[4] = -1;
	f.vD4[5] = -1;
	f.vD4[6] = -1;
	f.vF0[0] = 0x95;
	f.vF0[1] = 0x92;
	f.vF0[2] = 0x93;
	f.vF0[3] = 0x94;
	f.vF0[4] = 0x97;
	f.vF0[5] = 0x96;
	f.vF0[6] = 0x2db;
	f.vA4 = -1;
	f.v14 = a1;
	f.v80 = a2 & 8;

	if (f.v80 != 0) {
		int i;

		f.vA4 = fcn_00470820(*(int*) 0x1040494 - 0x68, 0x106, (char*) 0x6ac3b4);
		for (i = 0; i < 7; i++) {
			f.vD4[i] = fcn_0052dee0(0, 0xc + i * 0x18, *(int*) (0x14a56e8 + i * 4));
			if (*(short*) 0x7746cc == f.vF0[i]) {
				*(int*) (*(int*) 0x1015ea0 + f.vD4[i] * 0x2f4 + 0x38) = 1;
				*(int*) (*(int*) 0x1015ea0 + f.vD4[i] * 0x2f4 + 0x3c) = 1;
			}
		}
		f.v14 = *(int*) 0x773d78;
	}

	/* 0x5bab17: table-row pointer for the first selected entity */
	*(char*) 0x77531c = 0;
	idx = *(unsigned char*) a1;
	f.v74 = *(int*) 0x868050 + idx + idx * 0x24c;

	if (*(int*) 0x7746cc != 0) {
		f.v70 = a2 & 1;
		if (f.v70 != 0) {
			/* 0x5bab5a: refresh slot 0xff, then the 0x2a and 0x116 rows */
			f.v44 = (int) fcn_00502cd0(*(int*) (*(int*) 0x7746cc + 0x14), 2, 0, 0xff, 6);
			f.v18 = (int) fcn_00502cd0(*(int*) (*(int*) 0x7746cc + 0x14), 2, 4, 5, 6);
			if (f.v18 == 0) {
				f.v18 = (int) fcn_00502cd0(*(int*) (*(int*) 0x7746cc + 0x14), 1, 4, 0x11);
			}
			if (f.v18 == 0) {
				f.v18 = (int) fcn_00502cd0(*(int*) (a1 + 0x5d), 2, 0, 0x2a, 6);
			}
			if (f.v18 == 0) {
				f.v18 = (int) fcn_00502cd0(*(int*) (a1 + 0x5d), 2, 0, 0x116, 6);
			}
			if (f.v18 != 0) {
				goto l_packet;
			}
		} else {
			/* 0x5babe5: the a2 == 2 / a2 == 4 rows, nothing otherwise */
			if (a2 == 2) {
				f.v18 = (int) fcn_00502cd0(*(int*) (*(int*) 0x7746cc + 0x14), a2, 0, 0x1db, 6);
			} else if (a2 == 4) {
				f.v18 = (int) fcn_00502cd0(*(int*) (*(int*) 0x7746cc + 0x14), 2, 0, 0x1dc, 6);
			} else {
				goto l_after;
			}
			if (f.v18 != 0) {
				goto l_packet;
			}
			goto l_after;
		}
	} else {
		f.v70 = a2 & 1;
		if (f.v70 != 0) {
			/* 0x5bac1b: entity slot rows without an open container */
			f.v18 = (int) fcn_00502cd0(*(int*) (a1 + 0x5d), 2, 0, 0x2a, 6);
			if (f.v18 != 0) {
				goto l_packet;
			}
			f.v18 = (int) fcn_00502cd0(*(int*) (a1 + 0x5d), 2, 0, 0x116, 6);
			if (f.v18 != 0) {
				goto l_packet;
			}
			goto l_after;
		} else {
			if (a2 == 2) {
				f.v18 = (int) fcn_00502cd0(*(int*) (a1 + 0x5d), a2, 0, 0x1db, 6);
			} else if (a2 == 4) {
				f.v18 = (int) fcn_00502cd0(*(int*) (a1 + 0x5d), 2, 0, 0x1dc, 6);
			} else {
				goto l_after;
			}
			if (f.v18 != 0) {
				goto l_packet;
			}
			goto l_after;
		}
	}

l_packet:
	/* 0x5bac7d: the packet header word indexes the 0x41-byte record table */
	{
		int pk;

		pk = *(unsigned short*) (char*) f.v18;
		f.v94 = *(int*) 0x99ec10 + (pk << 6) + pk;
	}

l_after:
	/* 0x5bac98: clear the 16 entity slots */
	e = f.v6D8;
	for (i = 0; i < 16; i++) {
		e->f0c = -1;
		e->f10 = -1;
		e->f14 = -1;
		e->f18 = -1;
		e->f00 = 0;
		e->f04 = 0;
		e->f08 = 0;
		for (j = 0; j < 3; j++) {
			e->fD8[j] = -1;
			e->fE4[j] = -1;
		}
		e++;
	}

	/* 0x5bacd6: open the panel window and select its fourth page */
	fcn_0057e880(0x23, (char*) a1, 0, 0);
	f.v2c = fcn_00470820(0, 0, (char*) 0x6aa5d0);
	fcn_00471b60(f.v2c);
	d2_SetForm(f.v2c, 4);

	if (f.v70 != 0) {
		/* 0x5bad0e: four row ids through the shared layout helper */
		fcn_00533a60(*(int*) 0x772514, 0, &f.v138, 4,
			*(int*) 0x14a566c, *(int*) 0x14a5668,
			*(int*) 0x14a5664, *(int*) 0x14a5670);
		f.v6c = f.v140;
		f.v58 = f.v144;
		f.v34 = *(unsigned char*) 0x773d75;
		f.v54 = f.v13C;
	} else {
		/* 0x5bad6d: one row id, then the entity's own selection field */
		fcn_00533a60(*(int*) 0x772514, 0, &f.v138, 1, *(int*) 0x14a566c);
		f.v6c = -1;
		f.v58 = -1;
		f.v34 = *(int*) (f.v14 + 0x65);
		f.v54 = -1;
	}

	/* 0x5bada3: page zero, then the transport-entity branch */
	f.vA0 = f.v138;
	d2_SetForm(f.v2c, 0);

	if (a2 == 2) {
		f.v40 = 1;
		f.v50 = fcn_0050bbb0(*(unsigned short*) 0x774970);
	} else if (a2 == 4) {
		f.v3c = 1;
		f.v50 = fcn_0050bbb0(*(unsigned short*) 0x774970);
	} else if (*(short*) (f.v14 + 0x27) == *(short*) 0x774970) {
		f.v4c = 1;
	} else {
		if (*(char*) f.v74 == 0xa) {
			f.v58 = 1;
			/* /O2 colours stack slots: this slot held a1 at 0x5ba95f */
			f.v7c = (int) gm_StartFilteredEntitySearch(1, 0, 0x44);
			f.v40 = 1;
			f.v50 = fcn_0050bbb0(*(unsigned short*) 0x774970);
		}
		f.v3c = 1;
		if (f.v54 != -1) {
			fcn_00472170(f.v54, 0);
		}
		if (f.v6c != -1) {
			fcn_00472170(f.v6c, 0);
		}
		if (f.v58 != -1) {
			fcn_00472170(f.v58, 0);
		}
	}

	d2_SetForm(f.v2c, 0);

	/* 0x5baec2: status-line message id for the current container state */
	if (*(int*) 0x7746c4 == 0 && *(int*) 0x7746c8 == 0) {
		fcn_00533dc0(*(int*) 0x772514, 0x70b, 0x73f);
	} else {
		int msg;

		/* The native chain tests al in case order. Written here as an
		   else-if ladder it needs one more 4-byte local, which moves the
		   0x1848 frame; the switch keeps the frame until the rest of the
		   body is present. */
		switch (*(unsigned char*) f.v74) {
		case 0x13:
		case 4:
		case 0x10:
			msg = 0x72f;
			break;
		case 8:
		case 0xe:
			msg = 0x70f;
			break;
		case 6:
			msg = 0x713;
			break;
		case 0x16:
			msg = 0x717;
			break;
		case 0xd:
		case 0xc:
		case 0xb:
			msg = 0x71b;
			break;
		case 2:
		case 7:
			msg = 0x737;
			break;
		default:
			msg = 0x70b;
			break;
		}
		if (f.v3c != 0) {
			fcn_00533dc0(*(int*) 0x772514, msg, 0x741);
		} else {
			fcn_00533dc0(*(int*) 0x772514, msg, 0x73f);
		}
	}

	/* 0x5baf75: the item rectangle and its definition-table entry */
	fcn_00533f40(0x270, 0x15c, *(int*) 0x772514,
	             fcn_00472830(f.v2c, 2, 0x5e2, &f.v130, &f.v134, &f.vB4));
	*(int*) (*(int*) 0x1015ea0 + f.vB4 * 0x2f4 + 0x84) = 0x54;
	d2_SetForm(f.v2c, 3);

	if (a2 == 2) {
		io_AppendText(0xd0, (char*) (0x868060 + *(int*) (f.v14 + 0x65) * 0x2f4));
	} else if (a2 == 4) {
		io_AppendText(0xcf, (char*) (0x868060 + *(int*) (f.v14 + 0x65) * 0x2f4));
	} else if (*(int*) 0x7746cc != 0 && *(int*) 0x7746c4 == 0
	           && *(int*) 0x7746c8 == 0) {
		io_AppendText(0x9a8 + *(unsigned short*) 0x7746cc * 2);
	} else {
		io_AppendText(f.v3c != 0 ? 0xcd : 0xcc);
	}

	d2_SetForm(f.v2c, 2);
	fcn_00594340();
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(f.v2c, 0);

	/* 0x5bb0ab: the two scroll-bar rows and the item table entry */
	fcn_005c5da0(*(int*) 0x772514, 0x172, 0x64,
	             *(unsigned short*) 0x774970, 0x1f3c);
	d2_SetForm(f.v2c, 0);
	f.v78 = fcn_0046f740(0x261, 0xd2, 0x528, *(int*) 0x772514);
	*(int*) (*(int*) 0x1015ea0 + f.v78 * 0x2f4 + 0x1d0) = 3;
	*(int*) (*(int*) 0x1015ea0 + f.v78 * 0x2f4 + 0x58) = 1;
	f.vB0 = fcn_0046f740(0x261, 0x104, 0x527, *(int*) 0x772514);
	f.v9c = f.vB0 * 0x2f4;
	*(int*) (*(int*) 0x1015ea0 + f.v9c + 0x1d0) = 3;
	fcn_00525ef0();
	f.vA8 = f.vA0 * 0x2f4;
	f.vAC = f.v2c * 0xaf;
}
