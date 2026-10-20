#include <stdio.h>

extern char g_6b5c60[];
extern char g_6811b0[];

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004b4650(char*, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
char* __cdecl fcn_004fda30(int);
int __cdecl fcn_004e4ae0(char*, int);
void __cdecl fcn_004e4730(char*);
void __cdecl fcn_004e4e90(char*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_004e44b0(char*, char*);
int __cdecl fcn_004e4d00(int, int, int*);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(char* fmt, ...);
int __cdecl fcn_004e4b20(int, int, char*, int);
int __cdecl fcn_00423460(int);
int __cdecl fcn_004e4540(int, void*, int*);
int __cdecl fcn_004e1ff0(int*);

/* ADDRESS: GOLDTL 0x004e2090 */
void __cdecl fcn_004e2090(int a0)
{
	unsigned short* v1;
	unsigned short* v2;
	unsigned short* v7;
	char v5[256];
	int v3;
	int v4;
	int v6;
	int v8;
	int v9;
	int v10;
	int v11;

	v1 = (unsigned short*) fcn_00508e40(*(int*) (a0 + 0x34));
	if (v1 == 0) {
		return;
	}
	v2 = (unsigned short*) fcn_00508e40(*(int*) (a0 + 0x38));
	if (v2 == 0) {
		return;
	}
	if (((char*) v1)[2] == 6) {
		fcn_004b4650((char*) v1, 0x28);
	}
	if (((char*) v2)[2] == 6) {
		fcn_004b4650((char*) v2, 0x28);
	}
	*(int*) 0x68bfb8 = 0x702c6;
	*(int*) 0x7725c8 = 1;
	fcn_004c5420(*(int*) &v1[2], 0x1c8, 4, 0, 0x40000);
	fcn_004c5420(*(int*) &v2[2], 0x1c8, 4, 0, 0x40000);
	v3 = (int) fcn_004fda30(*v1);
	v4 = (int) fcn_004fda30(*v2);
	if (((char*) v1)[9] != 0) {
		v7 = v2;
		v8 = v4 + 4;
		v3 = v3 + 4;
	} else {
		v7 = v1;
		v1 = v2;
		v8 = v3 + 4;
		v3 = v4 + 4;
	}
	sprintf(v5, "%s %s %i", (char*) v8, (char*) v3, 1);
	v10 = fcn_004e4ae0("ADDON\\HOCHZEIT_NEU.sbf", 0);
	fcn_004e4730("KIRCHE_HOCHZEIT.ed3");
	fcn_004e4e90("cd2\\Hochzeit.mp3");
	v9 = fcn_00470820(0, 0, "cutscenes\\hochzeit");
	fcn_00471d80(v9, 3);
	fcn_00471af0(v9, 0);
	v6 = fcn_004e44b0("cutscenes\\hochzeit\\hochzeit-create.esc", v5);
	v6 = fcn_004e44b0("cutscenes\\hochzeit\\hochzeit-intro.esc", g_6b5c60);
	v6 = fcn_004e44b0("cutscenes\\hochzeit\\hochzeit-reden1.esc", g_6b5c60);
	if (fcn_004e4d00(0x5dc, 0x4e1ff0, &v6)) {
		return;
	}
	fcn_00471af0(v9, 1);
	fcn_004727a0(v9, 0);
	fcn_00519190((char*) 0x1aa9, *v7, *v1);
	v11 = fcn_004e4b20(0xfffffff9, v10, "_HOCHZEIT_NEU_MAIN_00", 0);
	v3 = fcn_00423460(v11);
	while (v3 != 0) {
		if (fcn_004e4d00(1000, 0x4e1ff0, &v6)) {
			return;
		}
		v3 = fcn_00423460(v11);
	}
	if (fcn_004e4d00(1000, 0x4e1ff0, &v6)) {
		return;
	}
	fcn_004727a0(v9, 0);
	fcn_00519190(g_6811b0);
	fcn_00471af0(v9, 0);
	v3 = fcn_004e4540(v6, (void*) 0x4e1ff0, &v6);
	if (v3 != 0) {
		return;
	}
	if (fcn_004e4d00(1000, 0x4e1ff0, &v6)) {
		return;
	}
	v6 = fcn_004e44b0("cutscenes\\hochzeit\\hochzeit-reden2.esc", g_6b5c60);
	fcn_004727a0(v9, 0);
	fcn_00471af0(v9, 1);
	fcn_00519190((char*) 0x1aac, *v7, *v1);
	v11 = fcn_004e4b20(0xfffffff9, v10, "_HOCHZEIT_NEU_MAIN_03", 0);
	v3 = fcn_00423460(v11);
	while (v3 != 0) {
		if (fcn_004e4d00(1000, 0x4e1ff0, &v6)) {
			return;
		}
		v3 = fcn_00423460(v11);
	}
	if (fcn_004e4d00(1000, 0x4e1ff0, &v6)) {
		return;
	}
	fcn_004727a0(v9, 0);
	fcn_00519190(g_6811b0);
	fcn_00471af0(v9, 0);
	if (fcn_004e4d00(500, 0x4e1ff0, &v6)) {
		return;
	}
	fcn_00471af0(v9, 1);
	fcn_004727a0(v9, 0);
	fcn_00519190((char*) 0x1aab);
	v11 = fcn_004e4b20(0xfffffff9, v10, "_HOCHZEIT_NEU_M", 0);
	v3 = fcn_00423460(v11);
	while (v3 != 0) {
		if (fcn_004e4d00(1000, 0x4e1ff0, &v6)) {
			return;
		}
		v3 = fcn_00423460(v11);
	}
	if (fcn_004e4d00(1000, 0x4e1ff0, &v6)) {
		return;
	}
	v3 = fcn_004e4540(v6, (void*) 0x4e1ff0, &v6);
	if (v3 != 0) {
		return;
	}
	v6 = fcn_004e44b0("cutscenes\\hochzeit\\hochzeit-reden3.esc", g_6b5c60);
	fcn_00471af0(v9, 0);
	fcn_004727a0(v9, 0);
	fcn_00519190(g_6811b0);
	if (fcn_004e4d00(0x5dc, 0x4e1ff0, &v6)) {
		return;
	}
	fcn_00471af0(v9, 1);
	fcn_004727a0(v9, 0);
	fcn_00519190((char*) 0x1aaa, *v1, *v7);
	v11 = fcn_004e4b20(0xfffffff9, v10, "_HOCHZEIT_NEU_MAIN_01", 0);
	v3 = fcn_00423460(v11);
	while (v3 != 0) {
		if (fcn_004e4d00(1000, 0x4e1ff0, &v6)) {
			return;
		}
		v3 = fcn_00423460(v11);
	}
	if (fcn_004e4d00(500, 0x4e1ff0, &v6)) {
		return;
	}
	fcn_00471af0(v9, 0);
	fcn_004727a0(v9, 0);
	fcn_00519190(g_6811b0);
	if (fcn_004e4d00(500, 0x4e1ff0, &v6)) {
		return;
	}
	fcn_00471af0(v9, 1);
	fcn_004727a0(v9, 0);
	fcn_00519190((char*) 0x1aab);
	v11 = fcn_004e4b20(0xfffffff9, v10, "_HOCHZEIT_NEU_W", 0);
	v3 = fcn_00423460(v11);
	while (v3 != 0) {
		if (fcn_004e4d00(1000, 0x4e1ff0, &v6)) {
			return;
		}
		v3 = fcn_00423460(v11);
	}
	if (fcn_004e4d00(500, 0x4e1ff0, &v6)) {
		return;
	}
	v3 = fcn_004e4540(v6, (void*) 0x4e1ff0, &v6);
	if (v3 != 0) {
		return;
	}
	v6 = fcn_004e44b0("cutscenes\\hochzeit\\hochzeit-reden4.esc", g_6b5c60);
	fcn_004727a0(v9, 0);
	fcn_00519190((char*) 0x1aad);
	v11 = fcn_004e4b20(0xfffffff9, v10, "_HOCHZEIT_NEU_MAIN_04", 0);
	v3 = fcn_00423460(v11);
	while (v3 != 0) {
		if (fcn_004e4d00(1000, 0x4e1ff0, &v6)) {
			return;
		}
		v3 = fcn_00423460(v11);
	}
	if (fcn_004e4d00(500, 0x4e1ff0, &v6)) {
		return;
	}
	fcn_00471af0(v9, 0);
	fcn_004727a0(v9, 0);
	fcn_00519190(g_6811b0);
	if (fcn_004e4540(v6, (void*) 0x4e1ff0, &v6)) {
		return;
	}
	v6 = 0xffffffff;
	fcn_004e1ff0(&v6);
}
