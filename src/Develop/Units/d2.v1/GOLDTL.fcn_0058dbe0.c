/* Open the arena betting page: query the match, build the layout and poll
 * input until the page is closed. */

void __cdecl io_FormatTextBuffer(char*, int, int);
int __cdecl fcn_005463a0(int, int, int, int, int);
void __cdecl fcn_004c30a0(int, int, char*, int, int);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005bdc30(int, int*, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_00468cd0(int, int);
void __cdecl fcn_00468b80(int, int);
void __cdecl fcn_00468bb0(int, int, int, int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_00525f60(int, int);
void __cdecl fcn_004c5530(int*);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* The reference frame keeps EBP; /O2 /Gd omits the frame pointer, so restore
 * it here instead of overriding the locked CFLAGS. */
#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0058dbe0 */
void __cdecl fcn_0058dbe0(int a0)
{
	int query[0x14];
	char text[1024];
	int req[0x3e];
	int v2;
	int v3;
	int v4;
	int v5;
	int v6;
	int v9;
	int v11;
	int v12;
	int v13;
	int v14;
	int v15;
	int v16;
	int v17;
	int v18;
	int v19;
	int v20;
	int v21;
	int* v27;
	int* v30;

	io_FormatTextBuffer(text, 0x40c8, 0x40b6);
	if (fcn_005463a0(2, 0, 0x90, 3, *(int*) (a0 + 1))) {
		fcn_004c30a0(0xffffffff, 0, (char*) 0x6a9780, 0, 100);
		fcn_00526120(text, 0);
		return;
	}
	for (v6 = 0; v6 < 0x50; v6++) {
		((char*) query)[v6] = 0;
	}
	query[0] = 1;
	query[1] = -1;
	query[2] = (int) 0xa07c43b4;
	query[3] = 1;
	query[4] = 6;
	query[0x13] = 0x727;
	v6 = fcn_005bdc30(1, query, *(int*) 0x14b55f8, 0, 0);
	if (!v6) {
		fcn_00532ef0();
		return;
	}
	v2 = fcn_00470820(0, 0, (char*) 0x6a9768);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(v2);
	d2_SetForm(v2, 0);
	fcn_005340f0(*(int*) 0x772514);
	d2_SetForm(v2, 1);
	io_AppendText(0x40b7, 0x40b6, *(unsigned short*) (v6 + 0x27), v6);
	v3 = fcn_004677e0(100, 0xa0, 200, 0, 2, 0x7b, 0x82,
	                  *(int*) 0x772514);
	fcn_00472380(v3, 0, 2, 0);
	fcn_00468cd0(v3, 0x82);
	fcn_00468b80(v3, *(int*) 0x14b561c);
	fcn_00468bb0(v3, 3, *(int*) 0x14b5620, *(int*) 0x14b5624,
	             *(int*) 0x14b5628);
	v4 = fcn_004677e0(100, 0xbe, 200, 0, 2, 0x7b, 0x82,
	                  *(int*) 0x772514);
	fcn_00472380(v4, 0, 2, 0);
	fcn_00468cd0(v4, 0x82);
	fcn_00468b80(v4, *(int*) 0x14b562c);
	fcn_00468bb0(v4, 3, *(int*) 0x14b5630, *(int*) 0x14b5634,
	             *(int*) 0x14b5638);
	d2_SetForm(v2, 2);
	v30 = (int*) io_AppendText(0x40be);
	v27 = (int*) fcn_00472250(v2, 2, (int) v30);
	v30 = (int*) fcn_00472250(v2, 2, (int) v30 + 1);
	*(int*) 0x100f1dc = -1;
	do {
		d2_SetForm(v2, 3);
		io_AppendText(0x6811b0);
		v6 = fcn_00471f80(v4);
		v6 = (v6 + 2) * (fcn_00471f80(v3) + 2);
		io_AppendText(0x40b9);
		io_AppendText(0x40ba, v6);
		if (*(int*) 0x14ce8e0) {
			goto label_58df76;
		}
		if (*(int*) 0x100f1dc != -1) {
			if (*(int**) 0x67d370 != v27) {
				if (*(int**) 0x67d370 == v30) {
					goto label_58df76;
				}
			} else {
				v5 = *(int*) 0x774970;
				if (fcn_00525f60(v5 * 0x21c + 0x7f4ca0, v6) == 1) {
					for (v9 = 0; v9 < 0x3e; v9++) {
						req[v9] = 0;
					}
					v11 = 0x90;
					v18 = 2;
					v12 = *(int*) (*(int*) 0x774970 * 0x21c + 0x7f4ca4);
					v13 = *(int*) (a0 + 1);
					v14 = *(int*) 0x7f4c00;
					v15 = *(int*) 0x7f4c04;
					v16 = *(int*) 0x7f4c08;
					v17 = *(unsigned short*) 0x7f4c0c;
					v20 = fcn_00471f80(v3);
					v21 = fcn_00471f80(v4);
					v19 = *(int*) (v6 + 1);
					((int*) req)[0] = v11;
					((int*) req)[1] = v12;
					((int*) req)[2] = v13;
					((int*) req)[4] = v14;
					((int*) req)[5] = v15;
					((int*) req)[6] = v16;
					((unsigned short*) req)[0xe] = v17;
					((char*) req)[0x10] = v18;
					((int*) req)[0x1c] = v19;
					((int*) req)[0x20] = v20;
					((int*) req)[0x21] = v21;
					fcn_004c5530(req);
				label_58df76:
					*(int*) 0x774654 = 1;
				}
			}
		}
		if (!fcn_005373e0(0x58dbe0, 0x677c7)) {
			fcn_00471e30(v2);
			fcn_00532ef0();
			return;
		}
	} while (1);
}
#pragma optimize("", on)
