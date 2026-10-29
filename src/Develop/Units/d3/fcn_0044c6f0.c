int __cdecl fcn_004112b0(int, int);
void __cdecl fcn_00411500(int, char*, int);
void __cdecl fcn_00411520(int, char*, char*);
void __cdecl fcn_00411550(int, char*, int);
void __cdecl fcn_00411340(int);

/* ADDRESS: GOLDTL 0x0044c6f0 */
void __cdecl fcn_0044c6f0(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8,
			  int a9, int a10, int a11, int a12, int a13, int a14, int a15, int a16,
			  int a17, int a18, int a19, int a20, int a21, int a22, int a23)
{
	char* v2;
	char buf[0x100];
	int v1;

	v1 = fcn_004112b0(a23, 2);
	if (v1 == -1) {
		return;
	}
	fcn_00411500(v1, (char*) 0x67b218, a1);
	fcn_00411500(v1, (char*) 0x67b208, a2);
	fcn_00411500(v1, (char*) 0x67b1f4, a3);
	fcn_00411500(v1, (char*) 0x67b1e4, a4);
	fcn_00411500(v1, (char*) 0x67b1d4, a6);
	fcn_00411500(v1, (char*) 0x67b1c4, a7);
	fcn_00411500(v1, (char*) 0x67b1b4, a8);
	fcn_00411500(v1, (char*) 0x67b19c, a12);
	fcn_00411500(v1, (char*) 0x67b188, a9);
	fcn_00411500(v1, (char*) 0x67b16c, a10);
	fcn_00411500(v1, (char*) 0x67b15c, a5);
	v2 = buf;
	switch (*(int*) 0x67ac90) {
	case 1:
		*(int*) (v2 + 0) = *(int*) 0x67b12c;
		*(int*) (v2 + 4) = *(int*) 0x67b130;
		*(int*) (v2 + 8) = *(int*) 0x67b134;
		*(int*) (v2 + 0xc) = *(int*) 0x67b138;
		break;
	case 2:
		*(int*) (v2 + 0) = *(int*) 0x67b13c;
		*(int*) (v2 + 4) = *(int*) 0x67b140;
		*(int*) (v2 + 8) = *(int*) 0x67b144;
		v2[0xc] = *(char*) 0x67b148;
		break;
	case 4:
		*(int*) (v2 + 0) = *(int*) 0x67b14c;
		*(int*) (v2 + 4) = *(int*) 0x67b150;
		*(int*) (v2 + 8) = *(int*) 0x67b154;
		*(short*) (v2 + 0xc) = *(short*) 0x67b158;
		break;
	default:
		v2[0] = *(char*) 0x6b5c60;
		break;
	}
	fcn_00411520(v1, (char*) 0x67b11c, v2);
	fcn_00411550(v1, (char*) 0x67b10c, a16);
	fcn_00411550(v1, (char*) 0x67b0f8, a17);
	fcn_00411550(v1, (char*) 0x67b0e4, a18);
	fcn_00411550(v1, (char*) 0x67b0d0, a19);
	fcn_00411550(v1, (char*) 0x67b0bc, a20);
	fcn_00411550(v1, (char*) 0x67b0ac, a21);
	fcn_00411550(v1, (char*) 0x67b094, a22);
	fcn_00411500(v1, (char*) 0x67b080, 3);
	fcn_00411340(v1);
}
