#include <stdio.h>
#include <string.h>
#include "client_data.h"
extern int g_6798d4;
extern unsigned char* lpGebaeudePROT;
extern int g_6b7fdc;




extern int g_772514;

int __cdecl fcn_0042f690(char* a, int b, int c, char* out);
int __cdecl fcn_0050d200(int a, int b);
char* __cdecl _strupr(char* s);
void __cdecl fcn_005986f0(char* a, int b);
void __cdecl fcn_00598740(float* out, int obj);
void __cdecl fcn_004c5530(int a1);

extern int g_6b8010;
extern char* g_773da8;
extern int g_6798d4;    
extern char g_7e1ae0[]; 
extern char g_67f0ac[]; 
extern char g_68de2c[]; 

void __cdecl ReportClientMessage(const char*);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00455350(char*, char*, int*);
void __cdecl fcn_004c5530(int a1);
int __cdecl fcn_004e8240(unsigned char, char*, char*, int, int);
void __cdecl fcn_004ea4b0(void*, unsigned int);
void __cdecl fcn_004ea560(void*, unsigned int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_WalkEntityChain(unsigned short);
void __cdecl fcn_00597ff0(int, char*);
int __cdecl fcn_00598150(char*, int*);
void __cdecl fcn_00598740(float* out, int obj);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl strupr(char*);

/* ADDRESS: GOLDTL 0x004a4d90 */
int __cdecl amt_ExecGebaeudeBauen(int a0, char* a1, char* a2)
{
	char v8[260];
	char v9[260];
	char v10[256];
	char event[0xf8];














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
	strcat(v8, (char*) (lpGebaeudePROT + *(int*) (a1 + 4) * 0x24d + 1));
	_strupr(v8 + 2);
	v4 = 0;
	for (;;) {
		if (v4) {
			sprintf(v9, (char*) 0x67f0c0, (char*) 0x7e1ae0, v8,
				(char) (v4 + '@'));
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
	sprintf(event + 0x9c, (char*) 0x679060, v9);
	*(int*) (event + 0x28) = g_7f4c00.a;
	v6 = *(unsigned int*) (a0 + 4);
	*(int*) (event + 0x2c) = g_7f4c00.b;
	*(int*) (event + 0x30) = g_7f4c00.c;
	v4 = *(unsigned int*) (a1 + 4);
	event[4] = 13;
	*(short*) (event + 0x34) = g_7f4c00.d;
	event[0x36] = 2;
	*(int*) (event + 0xc) = *(int*) (event + 8) = v6;
	*(int*) (event + 0x58) = v6;
	*(int*) (event + 0x5c) = v4; *(int*) (event + 0x60) = fcn_0050d200(a0, v4);
	fcn_005986f0(event + 0x80, v3);
	fcn_00598740((float*) (event + 0x90), v3);
	fcn_004c5530((int) event);
	return 1;
}
