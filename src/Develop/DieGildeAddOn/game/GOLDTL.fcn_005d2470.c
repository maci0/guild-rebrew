int __cdecl gm_WalkEntityChain(int);
int __cdecl gm_AccumulateTyped2(int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl fcn_0050b710(int, int);
int __cdecl fcn_0050b750(int, int);
int __cdecl fcn_00526010(void*, int, int);
void __cdecl fcn_004c5150(int, int, int, int);
void __cdecl fcn_004c4510(void*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c4ef0(char*);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

#define SHP_ID (*(unsigned short*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c))

/* ADDRESS: GOLDTL 0x005d2470 */
int __cdecl fcn_005d2470(int* arg1, int* arg2, unsigned short* arg3)
{
	int v14;
	int v4;
	int v8;
	int ebp;
	int flag;
	int dlg;
	int v18;
	int vc;
	int v10;
	int r;
	int hv;
	int uv;

	v10 = -1;
	vc = -1;
	v18 = -1;
	v14 = (int) ((float) gm_WalkEntityChain(SHP_ID) * 0.005f);
	if (v14 < 0x640) {
		v14 = 0x640;
	} else {
		v14 = (int) ((float) gm_WalkEntityChain(SHP_ID) * 0.005f);
	}
	v4 = (int) ((float) gm_WalkEntityChain(SHP_ID) * 0.05f);
	v8 = gm_AccumulateTyped2(SHP_ID);
	if ((float) v8 <= (float) v4) {
		v8 = (int) ((float) gm_WalkEntityChain(SHP_ID) * 0.05f);
	} else {
		v8 = gm_AccumulateTyped2(SHP_ID);
	}
	if (v8 < 0xc80) {
		ebp = 0xc80;
	} else {
		v4 = (int) ((float) gm_WalkEntityChain(SHP_ID) * 0.05f);
		v8 = gm_AccumulateTyped2(SHP_ID);
		if ((float) v8 <= (float) v4) {
			ebp = (int) ((float) gm_WalkEntityChain(SHP_ID) * 0.05f);
		} else {
			ebp = gm_AccumulateTyped2(SHP_ID);
		}
		if (ebp < 1) {
			return 0;
		}
	}
	flag = (*(unsigned int*) ((char*) arg2 + 0x1c8) >> 5) & 1;
	dlg = fcn_00470820(0, 0, (char*) 0x6acbac);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1f4c);
	if (flag == 0) {
		v10 = fcn_00472250(dlg, 1,
		    io_AppendText(0x1f4d, *arg3, *(unsigned char*) 0x773d75));
		hv = io_AppendText(0x1f4e);
		v18 = fcn_00472250(dlg, 1, hv);
		vc = fcn_00472250(dlg, 1, hv + 1);
		fcn_00472380(v10,
		    fcn_0050b710(v14, *(unsigned char*) 0x773d75),
		    fcn_0050b710(ebp, *(unsigned char*) 0x773d75),
		    fcn_0050b710(v14, *(unsigned char*) 0x773d75));
	} else {
		io_AppendText(0x1f4f);
	}
	*(int*) 0x100f1dc = -1;
	r = 0;
	while (fcn_005373e0((void*) fcn_005d2470, 0x677c7) != 0) {
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
		if (*(int*) 0x100f1dc == -1 || flag != 0) {
			continue;
		}
		if (*(int*) 0x67d370 == v10) {
			hv = fcn_00471f80(v18);
			uv = fcn_0050b750(hv, *(unsigned char*) 0x773d75);
			if (fcn_00526010((void*) (0x7f4ca0 +
				*(unsigned short*) 0x774970 * 0x21c), uv,
				*(unsigned char*) 0x773d75) != 0) {
				*(unsigned int*) ((char*) arg2 + 0x1c8) |= 0x20;
				uv = *(unsigned int*) ((char*) arg2 + 0x1c8);
				fcn_004c4eb0((char*) 0x6acba4);
				fcn_004c5150(*(int*) ((char*) arg1 + 4),
				    *(int*) ((char*) arg2 + 4),
				    *(unsigned char*) 0x773d75, uv);
				fcn_004c4510(arg2, *(int*) ((char*) arg2 + 4));
				fcn_004c4570(4, 1, 0x1c8, &uv);
				fcn_004c5360();
				fcn_004c4ef0((char*) 0x6acba4);
			}
			r = 1;
			*(int*) 0x774654 = 1;
		} else if (*(int*) 0x67d370 == vc) {
			*(int*) 0x774654 = 1;
		}
	}
	fcn_00471e30(dlg);
	return r;
}
