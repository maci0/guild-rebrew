#include <string.h>
#include <windows.h>

typedef struct Handler Handler;

struct Handler {
	int unused;
};

void __cdecl fcn_00412630(void);
char *__cdecl fcn_004730c0(int, int, int, int, char *, int, int);
int __cdecl fcn_005356e0(void);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00442e30(void);
int __cdecl fcn_0051e070(void);
int __cdecl fcn_00448360(char *, int, int);
void __cdecl fcn_0041d9e0(char *);
void __cdecl fcn_00438da0(float, float, int, int, int, int, int, int, int);
void __cdecl fcn_0046b4f0(void);
int __cdecl fcn_00469e30(int);
int __cdecl fcn_00470820(int, int, char *);
int __cdecl fcn_00471d80(int, int);
int __cdecl fcn_004727a0(int, int);
int __cdecl fcn_0053a3a0(int, int, int);
int __cdecl fcn_004693b0(int, int, int, int, int, int, int, int, int, int);
int __cdecl fcn_0064d3f8(void);
int __cdecl fcn_0041fd70(char *, int);
void __cdecl fcn_00473150(int);
void __cdecl fcn_00420200(int);
void __cdecl fcn_0042a070(void);
int __cdecl fcn_00469630(int);
void __cdecl fcn_00472170(int, int);
int __cdecl fcn_005dfb40(int, int, char *, char *, char *, char *);
int __cdecl fcn_0064d41a(char *, char *, char *, ...);
int __cdecl fcn_005392a0(char *, int);
int __cdecl fcn_005e4970(void);
void __cdecl fcn_0041fe10(int, int);
void __cdecl fcn_0053a2f0(void);
void __cdecl fcn_005e3520(void);
void __cdecl fcn_005e3150(void);
void __cdecl fcn_005e2b60(void);
int __cdecl fcn_005e0700(void);
int __cdecl fcn_0053a160(void);
int __cdecl fcn_005845e0(void);
void __cdecl fcn_00584530(void);
void __cdecl fcn_00469e70(void);
void __cdecl fcn_004acee0(void);
int __cdecl fcn_0053f460(void);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00420120(int, int);

/* ADDRESS: GOLDTL 0x0053a400 */
void __cdecl fcn_0053a400(void)
{
	char v7[260];
	char v8[260];
	char v9[96];
	char v10[260];
	char v11[260];
	char v12[96];
	char *v4;
	char *v14;
	int v5;
	int v20;
	int v23;
	int v26;
	int v19;
	int v24;
	int v27;
	int v22;
	int v18;
	int v21;
	int v16;
	int v25;
	int v17;
	int v28;
	int v6;
	int v15;
	unsigned char v29;

	v25 = -1;
	v17 = -1;
	v18 = -1;
	v21 = -1;
	v16 = -1;
	fcn_005356e0();
	fcn_00412630();
	*(unsigned char *)0x14cf950 = 0;
	fcn_0042a070();
	v4 = fcn_004730c0(0, 0, *(int *)0x1040494, *(int *)0x1040490, (char *)0x67d67c, 0, 1);
	while ((*(unsigned char *)v4 & 4) == 0) {
		fcn_005373e0(0, 0x24087);
	}
	*(int *)0x7725c8 = 1;
	fcn_004432d0(0, 0);
	fcn_00442e30();
	if (fcn_0051e070() != 0) {
		v14 = (char *)0x6a39ac;
	} else {
		v14 = (char *)0x6a39cc;
	}
	fcn_00448360(v14, 0, 0);
	fcn_005356e0();
	fcn_004432d0(1, 0);
	fcn_00442e30();
	if (!fcn_00448360((char *)0x6a3b98, 0, 0)) {
		fcn_0041d9e0((char *)0x6a3b70);
	}
	fcn_00438da0((float)*(int *)0x1040494, (float)*(int *)0x1040490, 0, 0, *(int *)0x10529c8, *(int *)0x10421a0, *(int *)0x10432a4, *(int *)0x1040494, *(int *)0x1040490);
	*(int *)0x774658 = *(int *)0x774650 + 1;
	*(int *)0x7747b0 = 0;
	v28 = 0x8c;
	memset((void *)0x7e23e0, 0, v28);
	*(int *)0x1040480 = *(int *)0x1040494;
	*(int *)0x7725c8 = 0;
	*(int *)0x1040488 = 0;
	*(int *)0x1040484 = 0;
	*(int *)0x104048c = *(int *)0x1040490;
	fcn_0046b4f0();
	fcn_00469e30(0x797);
	v29 = 0;
	v15 = fcn_00470820(0, 0, (char *)0x6a3b60);
	fcn_00471d80(v15, 3);
	fcn_004727a0(v15, 0);
	v5 = *(int *)0x772514;
	v20 = fcn_0053a3a0(0, *(int *)0x14ac4ac, v5);
	v23 = fcn_0053a3a0(1, *(int *)0x14ac490, v5);
	v26 = fcn_0053a3a0(2, *(int *)0x14b4f84, v5);
	v19 = fcn_0053a3a0(3, *(int *)0x14ac4b0, v5);
	v24 = fcn_0053a3a0(4, *(int *)0x14ac498, v5);
	v27 = fcn_0053a3a0(7, *(int *)0x14ac4b4, v5);
	v22 = fcn_0053a3a0(8, *(int *)0x14ac4b8, v5);
	if (*(int *)0x774814 != 0) {
		v18 = fcn_0053a3a0(4, (int)(char *)0x6a3b48, v5);
		v21 = fcn_0053a3a0(5, (int)(char *)0x6a3b30, v5);
		v16 = fcn_0053a3a0(6, (int)(char *)0x6a3b20, v5);
		v28 = fcn_004693b0(9, v20, v23, v26, v19, v24, v18, v21, v27, v22);
	} else {
		v25 = fcn_0053a3a0(5, *(int *)0x14ac49c, v5);
		v17 = fcn_0053a3a0(6, *(int *)0x14ac4a0, v5);
		v28 = fcn_004693b0(9, v20, v23, v26, v19, v24, v25, v17, v27, v22);
	}
	if (*(int *)0x774930 != 0) {
		v6 = fcn_0064d3f8() % 3;
		if (v6 == 0) {
			v14 = (char *)0x6a3adc;
		} else if (v6 == 1) {
			v14 = (char *)0x6a3af0;
		} else {
			v14 = (char *)0x6a3b04;
		}
		*(int *)0x7747d0 = fcn_0041fd70(v14, 1);
	}
	fcn_00473150((int)v4);
	fcn_004730c0(0, 0, *(int *)0x1040494, *(int *)0x1040490, (char *)0x67d67c, 0x5a, 10);
	*(unsigned char *)0x14cf950 = 0;
	fcn_00420200(2000);
	do {
		fcn_00469630(v28);
		if (v29) {
			fcn_00469e30(0x797);
			v29 = 0;
		}
		if (*(unsigned char *)0x14ce8d8 != 0 && *(int *)0x67d370 != -1) {
			if (*(int *)0x67d370 == v20) {
				fcn_00472170(v5, 0);
				fcn_00469e70();
				fcn_004acee0();
				if (fcn_0053f460()) {
					*(int *)0x7747b0 |= 1;
					*(int *)0x774654 = 1;
				} else {
					goto label_53a8e3;
				}
			} else if (*(int *)0x67d370 == v26) {
				fcn_00472170(v5, 0);
				if (fcn_005845e0()) {
					fcn_00584530();
					*(int *)0x6a375c = 1;
					*(char *)0x7e1d00 = *(char *)0x6a3ad0;
					*(char *)0x7e1d01 = *(char *)0x6a3ad1;
					*(char *)0x7e1d02 = *(char *)0x6a3ad2;
					*(char *)0x7e1d03 = *(char *)0x6a3ad3;
					*(char *)0x7e1d04 = *(char *)0x6a3ad4;
					*(char *)0x7e1d05 = *(char *)0x6a3ad5;
					*(char *)0x7e1d06 = *(char *)0x6a3ad6;
					*(char *)0x7e1d07 = *(char *)0x6a3ad7;
					*(char *)0x7e1d08 = *(char *)0x6a3ad8;
					*(int *)0x7747b0 = 0x89;
					*(int *)0x774654 = 1;
				} else {
label_53a8e3:
					fcn_00472170(v5, 1);
				}
			} else if (*(int *)0x67d370 == v18) {
				fcn_00472170(v5, 0);
				if (fcn_005dfb40(0x24087, 1, (char *)0x6a3ab8, (char *)0x6a3778, (char *)0x6a3ac8, v7)) {
					fcn_0064d41a(v8, (char *)0x67728c, (char *)0x6a3448, v7);
					GetPrivateProfileStringA((char *)0x6a2278, (char *)0x6a2288, (char *)0x6a2294, v9, 0x60, v8);
					fcn_005392a0(v9, 0);
				}
				goto label_53a8e3;
			} else if (*(int *)0x67d370 == v21) {
				fcn_00472170(v5, 0);
				if (fcn_005dfb40(0x24087, 1, (char *)0x6a3ab8, (char *)0x6a3778, (char *)0x6a3ac8, v10)) {
					fcn_0064d41a(v11, (char *)0x67728c, (char *)0x6a3448, v10);
					GetPrivateProfileStringA((char *)0x6a2278, (char *)0x6a2288, (char *)0x6a2294, v12, 0x60, v11);
					fcn_005392a0(v12, 1);
				}
				fcn_00472170(v5, 1);
			} else if (*(int *)0x67d370 == v23) {
				fcn_00472170(v5, 0);
				if (fcn_005e0700()) {
					*(int *)0x774654 = 1;
				}
				fcn_00472170(v5, 1);
			} else if (*(int *)0x67d370 == v19) {
				fcn_00472170(v5, 0);
				if (fcn_0053a160()) {
					*(int *)0x774654 = 1;
				} else {
					fcn_00472170(v5, 1);
					*(int *)0x7747b0 = 0;
				}
			} else if (*(int *)0x67d370 == v25) {
				fcn_00472170(v5, 0);
				fcn_005e2b60();
				fcn_00472170(v5, 1);
				v29 = 1;
				if (*(int *)0x77495c != 0) {
					*(int *)0x774654 = 1;
				}
			} else if (*(int *)0x67d370 == v17) {
				fcn_00472170(v5, 0);
				fcn_005e3150();
				fcn_00472170(v5, 1);
			} else if (*(int *)0x67d370 == v24) {
				fcn_00472170(v5, 0);
				fcn_005e3520();
				fcn_00472170(v5, 1);
			} else if (*(int *)0x67d370 == v22) {
				*(int *)0x774954 = 1;
				*(int *)0x77496c = 1;
				*(int *)0x774654 = 1;
			} else if (*(int *)0x67d370 == v16) {
				fcn_0053a2f0();
			} else if (*(int *)0x67d370 == v27) {
				fcn_00472170(v5, 0);
				if (*(int *)0x774930 != 0) {
					fcn_00420200(1000);
					fcn_0041fd70((char *)0x6a3aa4, 1);
				}
				fcn_005e4970();
				fcn_00472170(v5, 1);
				if (*(int *)0x774930 != 0) {
					fcn_00420200(1000);
					fcn_0041fe10(*(int *)0x7747d0, 1);
				}
			}
		}
		if (*(unsigned char *)0x14cf950 == 1) {
			*(int *)0x77496c = 1;
			*(int *)0x774654 = 1;
		}
	} while (fcn_005373e0((int)(void *)0x53a400, 0x24087) != 0);
	fcn_00469510(v28);
	fcn_00471e30(v15);
	fcn_0046b4f0();
	fcn_004432d0(0, 0);
	fcn_00442e30();
	fcn_004432d0(1, 0);
	fcn_00442e30();
	fcn_00420200(1000);
	if (*(int *)0x7747d0 != 0) {
		fcn_00420120(*(int *)0x7747d0, 1);
		*(int *)0x7725c8 = 1;
		while (*(char *)(*(int *)0x7747d0 + 0x104)) {
			fcn_005373e0(0, *(int *)0x7e46ac);
		}
		Sleep(1000);
	}
	fcn_00420200(5000);
}
