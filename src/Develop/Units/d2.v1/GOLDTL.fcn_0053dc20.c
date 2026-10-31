extern int __cdecl fcn_00470820(int a, int b, const char *name);
extern void __cdecl fcn_00471b60(int obj);
extern void __cdecl d2_SetForm(int obj, int a);
extern int __cdecl fcn_0051e070(void);
extern int __cdecl io_AppendText(int id, ...);
extern int __cdecl fcn_00472250(int obj, int a, int b);
extern int __cdecl d2_CreateRadioGroup(int a, int b, int c, int d);
extern void __cdecl fcn_004695a0(int obj, int a);
extern int __cdecl fcn_005373e0(int proc, int a);
extern void __cdecl fcn_00469510(int obj);
extern void __cdecl fcn_00471e30(int obj);
extern void __cdecl fcn_00469630(int obj);
extern void __cdecl fcn_004b20d0(int a);
extern void __cdecl fcn_00471af0(int obj, int a);
extern int __cdecl fcn_004b41b0(void);
extern int __cdecl fcn_004e4470(const char *name);
extern void __cdecl fcn_004e44f0(int a);
extern int __cdecl fcn_004fdec0(const char *name);
extern int __cdecl fcn_0053d490(int a, int b);
extern int __cdecl fcn_0053e8a0(int a);
extern int __cdecl fcn_0053cd40(int a);
extern unsigned int *__cdecl fcn_00506d50(char *buf, int a);
extern void __cdecl fcn_004432d0(int a, int b);
extern int __cdecl fcn_005268c0(int a, int b);
extern int __cdecl fcn_0053c560(int a);

/* ADDRESS: GOLDTL 0x0053dc20 */
int __cdecl fcn_0053dc20(void)
{
	char buf[8];
	int again;
	int v10;
	int v11;
	int v12;
	int v13;
	int mode;
	int v2;
	int r;
	int obj;
	int v4;
	int dlg;
	unsigned int *p;

	again = 0;
	v2 = 0;
	v12 = -1;
	v13 = 0xff;
	obj = fcn_00470820(0, 0, (const char *) 0x68116c);
	fcn_00471b60(obj);
	d2_SetForm(obj, 0);
	if (fcn_0051e070()) {
		v4 = io_AppendText(0x1ac0, 0x1ac2, 0x1ac4, 0x1ac2);
		v10 = fcn_00472250(obj, 0, v4);
		v11 = fcn_00472250(obj, 0, v4 + 1);
		dlg = d2_CreateRadioGroup(3, v10, v11, fcn_00472250(obj, 0, v4 + 2));
	} else {
		v4 = io_AppendText(0x1ac0, 0x1ac2, 0x1ac3, 0x1ac4, 0x1ac2, 0x1ac3,
		    0x1ac4, 1);
		v10 = fcn_00472250(obj, 0, v4);
		v12 = fcn_00472250(obj, 0, v4 + 1);
		v11 = fcn_00472250(obj, 0, v4 + 2);
		dlg = d2_CreateRadioGroup(4, v10, v12, v11, fcn_00472250(obj, 0, v4 + 3));
	}
	if (*(int *) 0x7766fc == 0) {
		mode = 2;
	} else if (*(int *) 0x7766fc == 1) {
		mode = 0;
	} else if (*(int *) 0x7766fc == 2) {
		mode = 1;
	} else {
		goto label_53dd68;
	}
	fcn_004695a0(dlg, mode);
label_53dd68:
	r = fcn_005373e0(0x53dc20, 0xc6);
	while (1) {
		if (!r) {
			fcn_00469510(dlg);
			fcn_00471e30(obj);
			if (!again) {
				*(int *) 0x7747b0 = 0;
				return 0;
			}
			*(int *) 0x7747b0 |= 8;
			return again;
		}
		fcn_00469630(dlg);
		if (*(int *) 0x14ce8e0 || *(char *) 0x14cf950 == 1) {
			*(int *) 0x774654 = 1;
		}
		if (*(int *) 0x100f1dc == 2 || *(char *) 0x14cf950 == 0x1c || again) {
			if (v2) {
				goto label_53de5c;
			}
			if (*(int *) 0x67d370 != v10) {
				if (*(int *) 0x67d370 == v12) {
					mode = 2;
					goto label_53de0b;
				}
				if (*(int *) 0x67d370 == v11 || *(char *) 0x14cf950 == 0x1c) {
					mode = 0;
					fcn_004b20d0(mode);
				}
			} else {
				mode = 1;
label_53de0b:
				fcn_004b20d0(mode);
			}
			*(int *) 0x7766fc = *(int *) 0x7728d4;
			if (*(int *) 0x7766fc == 0) {
				mode = 2;
label_53de37:
				fcn_004695a0(dlg, mode);
			} else if (*(int *) 0x7766fc == 1) {
				mode = 0;
				goto label_53de37;
			} else if (*(int *) 0x7766fc == 2) {
				mode = 1;
				fcn_004695a0(dlg, mode);
			}
			fcn_00471af0(obj, 0);
			v13 = fcn_004b41b0();
			fcn_00471af0(obj, 1);
label_53de5c:
			fcn_00471af0(obj, 0);
			again = 0;
			if (v13 != 0xff || v2) {
				*(int *) 0x7e242c = v13;
				if (!v2) {
					*(int *) 0x7e46ac = 0x12d6;
					fcn_004e44f0(fcn_004e4470((const char *) 0x6a4040));
				}
				v2 = 0;
				again = fcn_0053d490(0xc6, 0);
				if (again) {
					v4 = fcn_0053e8a0(0);
					if (v4 != 1) {
						if (v4) {
							if (v4 == -1) {
								again = 0;
								v2 = 1;
							}
						} else {
							if (fcn_0053cd40(0xc6)) {
								p = fcn_00506d50(buf, *(int *) 0x7e23e3);
								*(int *) 0x7e2430 = *p;
								*(char *) 0x7e2434 = (char) *(unsigned short *) &p[1];
								*(int *) 0x7e2468 =
								    fcn_004fdec0((const char *) 0x6a3db4) + 0x639;
								goto label_53df85;
							}
							fcn_004432d0(0, 0);
							again = 0;
							v2 = 0;
						}
					} else {
						*(int *) 0x7725c8 = v4;
						*(int *) 0x6a37f8 = fcn_005268c0(*(int *) 0x14abf04, 0);
						if (fcn_0053c560(0)) {
label_53df85:
							again = 1;
							*(int *) 0x774654 = 1;
						} else {
							fcn_004432d0(0, 0);
							v2 = 1;
						}
					}
				} else {
					*(int *) 0x7e46ac = 0x12d6;
					fcn_004e44f0(fcn_004e4470((const char *) 0x6a4024));
					v2 = 0;
				}
			}
			fcn_00471af0(obj, 1);
		} else {
			if (v2) {
				goto label_53de5c;
			}
			v2 = 0;
			if (*(int *) 0x100f1dc == 1) {
				*(int *) 0x774654 = 1;
			}
		}
		r = fcn_005373e0(0x53dc20, 0xc6);
	}
}
