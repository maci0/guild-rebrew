/* Drive the merchant trade page: validate the sell request, place the item
 * and report the trade result. */

extern unsigned char g_773d75;

void __cdecl fcn_00546190(int);
int __cdecl fcn_004c4450(int);
void __cdecl gm_ResolveEntityById(int*, int, int, int);
int __cdecl fcn_004c5620(int, int);
void __cdecl fcn_00500bb0(int, int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_RandomMod(int);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_005b23e0(int, int, int);
void __cdecl fcn_004c4510(int, int);
void __cdecl fcn_004c4570(int, int, int, int*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004fd4f0(int, int*);
int __cdecl io_FormatTextBuffer(char*, int, int, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_004c5150(int, int, int, int);
int __cdecl fcn_00493200(int, int);

/* ADDRESS: GOLDTL 0x0054a6a0 */
void __cdecl fcn_0054a6a0(int a0)
{
	int v2;
	int v3;
	int v4;
	int v7;
	char v8;
	char v9;
	unsigned int v10;
	unsigned int v14;
	int v15;
	int pair[2];
	char v12[256];
	char v1;

	v2 = a0;
	v7 = 0;
	if (*(int*) (a0 + 0x70) == -1 || *(int*) (a0 + 0x70) == -2) {
		fcn_00546190(a0);
		return;
	}
	if (*(unsigned char*) (a0 + 0x78) & 4) {
		return;
	}
	v4 = *(int*) (a0 + 0x84);
	if (v4 != -1 && !fcn_004c4450(v4)) {
		return;
	}
	*(int*) (v2 + 0x84) = 0xffffffff;
	gm_ResolveEntityById(&v7, 0, 0, *(int*) (v2 + 0x10));
	if (!v7) {
		fcn_004c5620(0xffffffff, v2);
		return;
	}
	if (*(short*) (v7 + 0x27) == -1) {
		fcn_00500bb0(v2 + 0x52, 0x18, 0, 0);
		*(unsigned short*) (v2 + 0x56) = 7;
		fcn_004c5620(0, v2);
		return;
	}
	v3 = fcn_00502cd0(*(int*) (v7 + 0x5d), 1, 0, 0, 0x1b5);
	v4 = *(int*) (v2 + 0x70);
	if (v4) {
		if (v4 == 1) {
			fcn_00500bb0(v2 + 0x52,
			              (int) ((gm_RandomMod(2) & 0xffff) + 1), 0, 0);
			*(int*) (v2 + 0x84) = fcn_004c5620(2, v2);
			return;
		}
		if (v4 != 2) {
			return;
		}
		if (v3 && *(char*) (v3 + 0x22)) {
			v8 = 0;
			v9 = (char) 0xff;
			v10 = 0xffffffff;
			v15 = 0;
			v4 = gm_LookupEntityRecordById(*(int*) (v3 + 0x1e));
			if (v4) {
				v15 = v4;
				fcn_005b23e0(
				    (int) ((unsigned int) *(unsigned short*) (v7 + 0x27) *
				               0x21c +
				           0x7f4ca0),
				    v4, v7);
			}
			fcn_004c4510(v3, *(int*) (v3 + 2));
			fcn_004c4570(1, 1, 0x22, (int*) &v8);
			fcn_004c4570(1, 1, 0x1c, (int*) &v9);
			fcn_004c4570(1, 1, 0x1d, (int*) &v9);
			fcn_004c4570(4, 1, 0x1e, (int*) &v10);
			fcn_004c5360();
			v4 = fcn_004fd4f0(v7, pair);
			if (v4) {
				v1 = *(char*) ((unsigned int) *(unsigned short*) (v7 + 0x27) *
			                       0x21c +
			                   0x7f4ca2);
				if (v1 == 6 || v1 == 7) {
					io_FormatTextBuffer(v12, 0x19a7, pair[1], pair[0]);
					fcn_00545d40(*(int*) ((unsigned int) *
					                              (unsigned short*) (v7 + 0x27) *
					                              0x21c +
					                          0x7f4ca4),
					             0xffffffff, v12, 0, 0x5ff, (char*) 0x6b5c60);
				}
				fcn_004c5150(*(int*) ((unsigned int) *
				                          (unsigned short*) (v7 + 0x27) *
				                          0x21c +
				                      0x7f4ca4),
				             0xffffffff, g_773d75, pair[0]);
				fcn_004c4510(v7, *(int*) (v7 + 1));
				fcn_004c4570(4, 1, 0x69, (int*) &pair[0]);
				fcn_004c5360();
			}
		}
		fcn_00500bb0(v2 + 0x52, 0x18, 0, 0);
		*(unsigned short*) (v2 + 0x56) = 7;
		*(int*) (v2 + 0x84) = fcn_004c5620(0, v2);
		return;
	}
	v4 = (unsigned int) *(unsigned short*) (v7 + 0x27) * 0x21c;
	v1 = *(char*) (v4 + 0x7f4ca2);
	if (v1 != 6 && v1 != 7) {
		if (!v3 || !fcn_00493200(v4 + 0x7f4ca0, v3)) {
			fcn_00500bb0(v2 + 0x52, 0x18, 0, 0);
			*(unsigned short*) (v2 + 0x56) = 7;
			*(int*) (v2 + 0x84) = fcn_004c5620(0, v2);
			return;
		}
	} else if (!v3 || !*(char*) (v3 + 0x22)) {
		fcn_00500bb0(v2 + 0x52, 0x18, 0, 0);
		*(unsigned short*) (v2 + 0x56) = 7;
		v14 = 0;
		*(int*) (v2 + 0x84) = fcn_004c5620(v14, v2);
		return;
	}
	fcn_00500bb0(v2 + 0x52, 1, 0, 0);
	v14 = 1;
	*(int*) (v2 + 0x84) = fcn_004c5620(v14, v2);
}
