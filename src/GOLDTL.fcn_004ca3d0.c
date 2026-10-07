#include <string.h>

extern int g_6b8010;
extern char g_1043695[];

int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl fcn_004032b0(char*);
char* __cdecl gm_FindRecordById(int);
char* __cdecl gm_SearchTable67(int);
int __cdecl fcn_00515540(char*);
int __cdecl fcn_005155e0(char*);
void __cdecl fcn_004432d0(int, int);
char* __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_00406670(char*, char*);
char* __cdecl fcn_0040b730(char*, char*);
char* __cdecl fcn_0040c120(char*, int, int);

// FUNCTION: GOLDTL 0x4ca3d0

int __cdecl fcn_004ca3d0(char* a1, char* a2)
{
	int saved;
	char buf[0x80];
	char* o;
	char* s;
	char* r;
	char* w;
	char* q;
	int k;

	s = 0;
	r = 0;
	fcn_0064d41a(buf, "sp_%i", *(int*) (a1 + 0x10));
	o = fcn_004032b0(buf);
	if (o == 0)
		return 1;
	if (*(int*) (a1 + 0x18) != -1)
		s = gm_FindRecordById(*(int*) (a1 + 0x18));
	else
		r = gm_SearchTable67(*(int*) (a1 + 0x14));
	saved = g_6b8010;
	if (*(int*) (a1 + 0x18) != -1)
		k = fcn_00515540(s);
	else if (*(int*) (a1 + 0x14) != -1)
		k = fcn_005155e0(r);
	else
		k = 0;
	if (k == -1)
		return 2;
	if (g_1043695[k * 988] != 0)
		return 3;
	if (a1[0x1c] != 0) {
		fcn_004432d0(k, 1);
		w = fcn_00445600(0, 0x160, 0, a1 + 0x1c);
		fcn_004432d0(saved, 1);
		if (w == 0)
			return 4;
		fcn_00406670(o, "sitzend/aufstehen");
		q = fcn_0040b730(o, w);
		if (q != 0)
			strcpy(q + 0x70, "cm_ExChrWalkToDummy");
	} else {
		fcn_00406670(o, "sitzend/aufstehen");
		fcn_0040c120(o, 0x39, k);
	}
	if (a2 != 0) {
		a2[0] = 1;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	return 0;
}
