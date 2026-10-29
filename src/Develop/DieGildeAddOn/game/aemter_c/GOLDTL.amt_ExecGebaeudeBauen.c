#include <stdio.h>
#include <string.h>

extern int g_6798d4;
extern char* lpGebaeudePROT;
extern int g_6b7fdc;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern int g_772514;

int __cdecl fcn_0042f690(char* a, int b, int c, char* out);
int __cdecl fcn_0050d200(int a, int b);
char* __cdecl _strupr(char* s);
void __cdecl fcn_005986f0(char* a, int b);
void __cdecl fcn_00598740(char* a, int b);
int __cdecl fcn_004c5530(char* a);

/* ADDRESS: GOLDTL 0x004a4d90 */
int __cdecl amt_ExecGebaeudeBauen(int a0, char* a1, char* a2)
{
	char v8[260];
	char v9[260];
	char v10[256];
	char v11[92];
	char v12[16];
	char v13[12];
	char v14[4];
	char v18;
	unsigned int v19;
	unsigned int v20;
	unsigned int v21;
	unsigned int v22;
	unsigned int v23;
	unsigned short v24;
	char v25;
	unsigned int v26;
	unsigned int v27;
	unsigned int v28;
	int v3;
	int v4;
	int v6;

	if (*a1 != 5) {
		return 0;
	}
	if (*a2 != 12) {
		return 0;
	}
	v3 = *(unsigned int*) (a2 + 4);
	*(int*) v8 = g_6798d4;
	strcat(v8 + 8, (char*) (lpGebaeudePROT + *(int*) (a1 + 4) * 0x24d + 1));
	_strupr(v8 + 10);
	v4 = 0;
	for (;;) {
		if (v4) {
			sprintf(v9, (char*) 0x67f0c0, (char*) 0x7e1ae0, v8,
				v4 + '@');
		}
		else {
			sprintf(v9, (char*) 0x67f0ac, (char*) 0x7e1ae0, v8);
		}
		v6 = fcn_0042f690(v9, g_6b7fdc, g_6b7fdc, v10);
		if (v6) {
			break;
		}
		if (v4) {
			sprintf(v8, (char*) 0x67f074,
				(char*) (lpGebaeudePROT + *(int*) (a1 + 4) * 0x24d + 1));
			return 0;
		}
		v4 = 1;
	}
	sprintf(v11, (char*) 0x679060, v9);
	v21 = g_7f4c00;
	v19 = *(unsigned int*) (a0 + 4);
	v22 = g_7f4c04;
	v23 = g_7f4c08;
	v27 = *(unsigned int*) (a1 + 4);
	v18 = 13;
	v24 = g_7f4c0c;
	v25 = 2;
	v20 = v19;
	v26 = v19;
	v28 = fcn_0050d200(a0, v27);
	fcn_005986f0(v12, v3);
	fcn_00598740(v13, v3);
	fcn_004c5530(v14);
	return 1;
}
