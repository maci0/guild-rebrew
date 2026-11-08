#include <stdio.h>
#include <string.h>

extern int g_6798d4;
extern unsigned char* lpGebaeudePROT;
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

/* ADDRESS: GOLD 0x004a47c0 */
/* ADDRESS: GOLDTL 0x004a4200 */
int __cdecl amt_GetDesireByName(char* name)
{
	char buf[0x80];

	if (_strcmpi(name, "APS") == 0) {
		return 0;
	}
	if (_strcmpi(name, "UNVERSEHRTHEIT") == 0) {
		return 1;
	}
	if (_strcmpi(name, "WOHNUNG") == 0) {
		return 2;
	}
	if (_strcmpi(name, "GELD") == 0) {
		return 3;
	}
	if (_strcmpi(name, "BERUF") == 0) {
		return 4;
	}
	if (_strcmpi(name, "VERGNUEGEN") == 0) {
		return 5;
	}
	if (_strcmpi(name, "ANSEHEN") == 0) {
		return 6;
	}
	if (_strcmpi(name, "AMT") == 0) {
		return 7;
	}
	if (_strcmpi(name, "BILDUNG") == 0) {
		return 8;
	}
	if (_strcmpi(name, "RECHTSCHAFFENHEIT") == 0) {
		return 9;
	}
	if (_strcmpi(name, "GEMEINHEIT") == 0) {
		return 10;
	}
	if (_strcmpi(name, "SICHERHEIT") == 0) {
		return 11;
	}
	if (_strcmpi(name, "FORTPFLANZUNG") == 0) {
		return 12;
	}
	if (_strcmpi(name, "TRAEGHEIT") == 0) {
		return 13;
	}
	sprintf(buf, "amt_GetDesireByName(): Unbekanntes Bed\xfcrfnis: %s", name);
	return -1;
}
