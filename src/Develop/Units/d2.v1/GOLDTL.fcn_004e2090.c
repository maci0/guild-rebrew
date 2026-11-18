#include <stdio.h>
extern int cut_EventLoopFlags, d2_SuppressOverlay;
extern char g_6b5c60[];
extern char g_6811b0[];

char* __cdecl gm_LookupEntityRecordById(int);
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
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char* fmt, ...);
int __cdecl fcn_004e4b20(int, int, char*, int);
int __cdecl fcn_00423460(int);
int __cdecl fcn_004e4540(int, void*, int*);
int __cdecl fcn_004e1ff0(int*);

/* ADDRESS: GOLDTL 0x004e2090 */
void __cdecl fcn_004e2090(int event)
{
	unsigned short* entity1;
	unsigned short* entity2;
	unsigned short* swapEntity;
	char text[256];
	int value;
	int otherName;
	int scene[4];





	entity1 = (unsigned short*) gm_LookupEntityRecordById(*(int*) (event + 0x34));
	if (entity1 == 0) {
		return;
	}
	entity2 = (unsigned short*) gm_LookupEntityRecordById(*(int*) (event + 0x38));
	if (entity2 == 0) {
		return;
	}
	if (((char*) entity1)[2] == 6) {
		fcn_004b4650((char*) entity1, 0x28);
	}
	if (((char*) entity2)[2] == 6) {
		fcn_004b4650((char*) entity2, 0x28);
	}
	cut_EventLoopFlags = 0x702c6;
	d2_SuppressOverlay = 1;
	fcn_004c5420(*(int*) &entity1[2], 0x1c8, 4, 0, 0x40000);
	fcn_004c5420(*(int*) &entity2[2], 0x1c8, 4, 0, 0x40000);
	value = (int) fcn_004fda30(*entity1);
	otherName = (int) fcn_004fda30(*entity2);
	if (((char*) entity1)[9] == 0) {
		sprintf(text, "%s %s %i", (char*) (value + 4), (char*) (otherName + 4), 1);
	} else {
		swapEntity = entity2; entity2 = entity1; entity1 = swapEntity;
		sprintf(text, "%s %s %i", (char*) (otherName + 4), (char*) (value + 4), 1);
	}




	scene[2] = fcn_004e4ae0("ADDON\\HOCHZEIT_NEU.sbf", 0);
	fcn_004e4730("KIRCHE_HOCHZEIT.ed3");
	fcn_004e4e90("cd2\\Hochzeit.mp3");
	scene[1] = fcn_00470820(0, 0, "cutscenes\\hochzeit");
	fcn_00471d80(scene[1], 3);
	fcn_00471af0(scene[1], 0);
	scene[0] = fcn_004e44b0("cutscenes\\hochzeit\\hochzeit-create.esc", text);
	scene[0] = fcn_004e44b0("cutscenes\\hochzeit\\hochzeit-intro.esc", g_6b5c60);
	scene[0] = fcn_004e44b0("cutscenes\\hochzeit\\hochzeit-reden1.esc", g_6b5c60);
	if (fcn_004e4d00(0x5dc, (int) fcn_004e1ff0, scene)) {
		return;
	}
	fcn_00471af0(scene[1], 1);
	d2_SetForm(scene[1], 0);
	io_AppendText((char*) 0x1aa9, *entity1, *entity2);
	scene[3] = fcn_004e4b20(0xfffffff9, scene[2], "_HOCHZEIT_NEU_MAIN_00", 0);
	value = fcn_00423460(scene[3]);
	while (value != 0) {
		if (fcn_004e4d00(1000, (int) fcn_004e1ff0, scene)) {
			return;
		}
		value = fcn_00423460(scene[3]);
	}
	if (fcn_004e4d00(1000, (int) fcn_004e1ff0, scene)) {
		return;
	}
	d2_SetForm(scene[1], 0);
	io_AppendText(g_6811b0);
	fcn_00471af0(scene[1], 0);
	value = fcn_004e4540(scene[0], (void*) fcn_004e1ff0, scene);
	if (value != 0) {
		return;
	}
	if (fcn_004e4d00(1000, (int) fcn_004e1ff0, scene)) {
		return;
	}
	scene[0] = fcn_004e44b0("cutscenes\\hochzeit\\hochzeit-reden2.esc", g_6b5c60);
	d2_SetForm(scene[1], 0);
	fcn_00471af0(scene[1], 1);
	io_AppendText((char*) 0x1aac, *entity1, *entity2);
	scene[3] = fcn_004e4b20(0xfffffff9, scene[2], "_HOCHZEIT_NEU_MAIN_03", 0);
	value = fcn_00423460(scene[3]);
	while (value != 0) {
		if (fcn_004e4d00(1000, (int) fcn_004e1ff0, scene)) {
			return;
		}
		value = fcn_00423460(scene[3]);
	}
	if (fcn_004e4d00(1000, (int) fcn_004e1ff0, scene)) {
		return;
	}
	d2_SetForm(scene[1], 0);
	io_AppendText(g_6811b0);
	fcn_00471af0(scene[1], 0);
	if (fcn_004e4d00(500, (int) fcn_004e1ff0, scene)) {
		return;
	}
	fcn_00471af0(scene[1], 1);
	d2_SetForm(scene[1], 0);
	io_AppendText((char*) 0x1aab);
	scene[3] = fcn_004e4b20(0xfffffff9, scene[2], "_HOCHZEIT_NEU_M", 0);
	value = fcn_00423460(scene[3]);
	while (value != 0) {
		if (fcn_004e4d00(1000, (int) fcn_004e1ff0, scene)) {
			return;
		}
		value = fcn_00423460(scene[3]);
	}
	if (fcn_004e4d00(1000, (int) fcn_004e1ff0, scene)) {
		return;
	}
	value = fcn_004e4540(scene[0], (void*) fcn_004e1ff0, scene);
	if (value != 0) {
		return;
	}
	scene[0] = fcn_004e44b0("cutscenes\\hochzeit\\hochzeit-reden3.esc", g_6b5c60);
	fcn_00471af0(scene[1], 0);
	d2_SetForm(scene[1], 0);
	io_AppendText(g_6811b0);
	if (fcn_004e4d00(0x5dc, (int) fcn_004e1ff0, scene)) {
		return;
	}
	fcn_00471af0(scene[1], 1);
	d2_SetForm(scene[1], 0);
	io_AppendText((char*) 0x1aaa, *entity2, *entity1);
	scene[3] = fcn_004e4b20(0xfffffff9, scene[2], "_HOCHZEIT_NEU_MAIN_01", 0);
	value = fcn_00423460(scene[3]);
	while (value != 0) {
		if (fcn_004e4d00(1000, (int) fcn_004e1ff0, scene)) {
			return;
		}
		value = fcn_00423460(scene[3]);
	}
	if (fcn_004e4d00(500, (int) fcn_004e1ff0, scene)) {
		return;
	}
	fcn_00471af0(scene[1], 0);
	d2_SetForm(scene[1], 0);
	io_AppendText(g_6811b0);
	if (fcn_004e4d00(500, (int) fcn_004e1ff0, scene)) {
		return;
	}
	fcn_00471af0(scene[1], 1);
	d2_SetForm(scene[1], 0);
	io_AppendText((char*) 0x1aab);
	scene[3] = fcn_004e4b20(0xfffffff9, scene[2], "_HOCHZEIT_NEU_W", 0);
	value = fcn_00423460(scene[3]);
	while (value != 0) {
		if (fcn_004e4d00(1000, (int) fcn_004e1ff0, scene)) {
			return;
		}
		value = fcn_00423460(scene[3]);
	}
	if (fcn_004e4d00(500, (int) fcn_004e1ff0, scene)) {
		return;
	}
	value = fcn_004e4540(scene[0], (void*) fcn_004e1ff0, scene);
	if (value != 0) {
		return;
	}
	scene[0] = fcn_004e44b0("cutscenes\\hochzeit\\hochzeit-reden4.esc", g_6b5c60);
	d2_SetForm(scene[1], 0);
	io_AppendText((char*) 0x1aad);
	scene[3] = fcn_004e4b20(0xfffffff9, scene[2], "_HOCHZEIT_NEU_MAIN_04", 0);
	value = fcn_00423460(scene[3]);
	while (value != 0) {
		if (fcn_004e4d00(1000, (int) fcn_004e1ff0, scene)) {
			return;
		}
		value = fcn_00423460(scene[3]);
	}
	if (fcn_004e4d00(500, (int) fcn_004e1ff0, scene)) {
		return;
	}
	fcn_00471af0(scene[1], 0);
	d2_SetForm(scene[1], 0);
	io_AppendText(g_6811b0);
	if (fcn_004e4540(scene[0], (void*) fcn_004e1ff0, scene)) {
		return;
	}
	scene[0] = 0xffffffff;
	fcn_004e1ff0(scene);
}
