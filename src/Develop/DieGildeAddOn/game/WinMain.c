#include "Develop/Units/Msx/msx.h"

#include <stdio.h>

typedef struct {
	int image;
	int window;
	char pad8[0x2bc - 8];
} Screen;

typedef struct {
	char pad0[0x10];
	int height;
	char pad14[0x27c - 0x14];
	int id;
	char pad280[0x3cc - 0x280];
} Window;

extern int g_774818;
extern unsigned char g_77534c;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6a3550[];
#include "client_types.h"
extern Page_1038144 g_1038144[];
extern Win_1015f40 g_1015f40[0x60];
extern int d2_ScreenHeight;
extern int g_1040494;
extern char g_7e25a0[];
extern char* g_7747b8;
extern char g_7e2080[];
extern int g_774820;
extern int g_774824;
extern char g_7e23e0[];
extern char g_774944;
extern int g_67a590;
extern unsigned int g_67a0d8;

void __cdecl txt_OpenText(char*, int);
int __cdecl txt_LoadTextFileDefinition(char*);
#include "Develop/Units/Error/error_message.h"
void __cdecl txt_ResetHistoryTextBanks(void);
void __cdecl d2_ClearScreen(void);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_PositionWindow(int, int);
void __cdecl d2_PositionControl(int, int, int);
void __cdecl io_AppendText(int, char*);
void __cdecl nt_ConnectTcp(int, int);
void __cdecl cm_ResetCommandQueue(void);
void __cdecl fcn_00590650(void);
void __cdecl gm_InitGameData(char*);
void __cdecl gm_ResetSlot170Table(void);
void __cdecl init_LoadCharacterNames(void);
void __cdecl ls_FreeList774a78(void);
float __cdecl eval_ObjektPreis2Credits(int, int);
void __cdecl msx_InitAIL(void);
int __cdecl sb_Init(int, int, int, int, int);
void __cdecl d3snd_InitSources(int);
void __cdecl d3sndw_Init(int);
void __cdecl sb_SetSampleBasePath(char*);
int __cdecl sb_LoadSampleBank(char*, int);
void __cdecl main_PreloadSound(char*);
void __cdecl msx_InitDrivers(int, int, int);
void __cdecl msx_ApplyAudioSettings(void);
void __cdecl main_InitFrameProfile(void);
void __cdecl d3_ResetSceneContextIndices(void);
void __cdecl ch_InitActionQueue(void);
void __cdecl d3_InitRenderVertexBuffers(void);
void __cdecl ai_InitContextAndGoodsLists(void);
void __cdecl ahm_ReloadAlchemyPrototypes(int);
void __cdecl hmt_CreateBinaryFile(void);
void __cdecl gm_LoadHistoricalTable(void);
void __cdecl cut_InitCombatActionWeights(void);
void __cdecl d2_DestroyForm(int);
unsigned char* __cdecl d2_StartScreenFade(int, int, int, int, char*, int, int);
void __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_ReleaseOverlaySprite(unsigned char*);
void __cdecl evt_AllocScriptEngineBuffers(void);
void __cdecl evt_RegisterCoreCommands(void);
void __cdecl evt_RegisterSceneCommands(void);
void __cdecl ch_RegisterScriptCommands(void);
void __cdecl evt_RegisterSoundCommands(void);
void __cdecl evt_GetLoadAndRunGfxScriptFunc(void);
void __cdecl gm_ApplyGameSettings(void);
int __cdecl main_PumpWindowMessages(void);
#include <windows.h>
#include <stdlib.h>
#include <string.h>

typedef struct rec6 {
	short w[3];
} Rec6;

typedef struct str9 {
	char b[9];
} Str9;

typedef struct str8 {
	char b[8];
} Str8;

typedef struct str7 {
	char b[7];
} Str7;

extern char* __cdecl fcn_0064d1a0(char* s, int c);
extern char* __cdecl fcn_0064e790(char* s, int c);
extern int __cdecl atoi(char* s);
extern int __cdecl fcn_0065f220(char* a, char* b);
extern int __cdecl gm_RandomMod(int n);
extern int __cdecl gm_FindHeadIconIndex(char* name);
extern void __cdecl hst_SetHistoryScrollModeFlag(unsigned char v);
extern void __cdecl main_LoadMessageFilterMask(char* ini);
extern int __cdecl main_CheckExistingInstance(void** handle);
extern int __cdecl main_CreateWindow(HINSTANCE inst, int unused, int windowed);
extern int __cdecl main_InitRuntime(void);
extern void __cdecl main_PlayIntroMovies(void);
extern int __cdecl main_CreateGameWindowAndDevice(int topmost);
extern int __cdecl main_OpenEngine(void);
extern void __cdecl main_ShutdownEngine(void);
extern void __cdecl main_ShutdownSubsystems(void);
extern int __cdecl main_PumpWindowMessages(void);
extern void __cdecl main_Menue(void);
extern void __cdecl main_SetLanguageByName(char* language);
extern Rec6* __cdecl gm_GetStatRecord(Rec6* dst, int idx);
extern void __cdecl main_RunGameLoop(int v);
extern void __cdecl main_SetScreensaverActive(void* p);

int __cdecl main_OpenEngine(void);
/* ADDRESS: GOLDTL 0x00544c50 */
int __stdcall WinMain(void *instance, void *previous, char *command, int show)
{
	char text[0x100];
	char pbuf[0x8c];
	void *mutex;
	int server;
	int windowed;
	char *p;
	char *e;
	char *q;
	int i;
	int n;
	int mode;
	int val;

	server = 0;
	*(void**) 0x7e1f80 = instance;
	{
	OSVERSIONINFOA os;
	os.dwOSVersionInfoSize = sizeof(os);
	GetVersionExA(&os);
	*(int*) 0x7e246c = (os.dwPlatformId != 1);
	}

	GetModuleFileNameA(*(HMODULE*) 0x7e1f80, (char*) 0x7e22c0, 0x104);
	strcpy((char*) 0x7e2080, (char*) 0x7e22c0);
	p = fcn_0064d1a0((char*) 0x7e2080, 0x5c);
	*p = 0;
	p = fcn_0064d1a0((char*) 0x7e22c0, 0x5c) + 1;
	strcpy(p, "game.INI");

	main_LoadMessageFilterMask((char*) 0x7e22c0);

	GetPrivateProfileStringA("Network", "Server", "Server\\Server.dll", (char*) 0x7e1be0, 0x104, (char*) 0x7e22c0);
	strcpy((char*) 0x7e25e0, (char*) 0x7e1be0);
	p = fcn_0064d1a0((char*) 0x7e25e0, 0x5c);
	*p = 0;
	_strupr(command);

	*(int*) 0x7747e4 = GetPrivateProfileIntA("Gfx", "TextureDivider", 0, (char*) 0x7e22c0);
	*(int*) 0x774930 = GetPrivateProfileIntA("Sound", "msx", 0, (char*) 0x7e22c0);
	*(int*) 0x6a3444 = GetPrivateProfileIntA("Sound", "ambient", 0, (char*) 0x7e22c0);
	*(int*) 0x774934 = GetPrivateProfileIntA("Sound", "sfx", 0, (char*) 0x7e22c0);
	*(int*) 0x774938 = GetPrivateProfileIntA("Sound", "weather", 1, (char*) 0x7e22c0);

	GetPrivateProfileStringA("General", "Bildmodus", "FULLSCREEN", text, 0x100, (char*) 0x7e22c0);
	_strupr(text);
	windowed = (memcmp(text, (void*) 0x6a46cc, 0xd) == 0);
	if (strstr(command, (char*) 0x6a46cc) != 0)
		windowed = 1;
	if (strstr(command, (char*) 0x6a46f0) != 0)
		windowed = 0;

	GetPrivateProfileStringA("General", "GfxPath", "\\project\\gfx\\", (char*) 0x6a3448, 0x104, (char*) 0x7e22c0);
	GetPrivateProfileStringA("General", "GamePath", "\\project\\game\\", (char*) 0x6a3550, 0x104, (char*) 0x7e22c0);
	GetPrivateProfileStringA("General", "MoviePath", "\\project\\movie\\", (char*) 0x6a3658, 0x104, (char*) 0x7e22c0);
	GetPrivateProfileStringA("General", "Language", "german", (char*) 0x679888, 0x40, (char*) 0x7e22c0);
	main_SetLanguageByName((char*) 0x679888);
	*(int*) 0x77492c = GetPrivateProfileIntA("General", "show_intro", 0, (char*) 0x7e22c0);
	g_77534c = (unsigned char) GetPrivateProfileIntA("Gfx", "cur_res", 0, (char*) 0x7e22c0);
	i = g_77534c;
	q = (char*) 0x6acf68 + i * 8;
	*(int*) 0x6acf80 = *(int*) q;
	*(int*) 0x6acf84 = *(int*) (q + 4);
	if (strstr(command, (char*) 0x6a4648) != 0)
		*(int*) 0x7747fc = 1;

	GetPrivateProfileStringA("General", "Stadt", "Augsburg", (char*) 0x7e1d00, 0x40, (char*) 0x7e22c0);
	GetPrivateProfileStringA("Network", "Host", "128.0.0.1", (char*) 0x7e2000, 0x80, (char*) 0x7e22c0);
	*(int*) 0x7e2510 = GetPrivateProfileIntA("Network", "Port", 0x1d6b, (char*) 0x7e22c0);

	p = strstr(command, (char*) 0x6a4618);
	if (p != 0) {
		p += 7;
		e = fcn_0064e790(p, 0x22);
		q = (char*) 0x7e1d00;
		if (e != 0) {
			while (e > p)
				*q++ = *p++;
		}
		*q = 0;
	}

	p = strstr(command, (char*) 0x6a4610);
	if (p != 0) {
		p += 7;
		e = fcn_0064e790(p, 0x22);
		q = (char*) 0x774828;
		if (e != 0) {
			while (p < e)
				*q++ = *p++;
		}
		*q = 0;
	}

	p = strstr(command, (char*) 0x6a4608);
	if (p != 0) {
		p += 4;
		e = fcn_0064e790(p, 0x22);
		q = (char*) 0x7e2000;
		if (e != 0) {
			while (p < e)
				*q++ = *p++;
		}
		*q = 0;
		server = 1;
	} else {
		n = server;
	}

	p = strstr(command, (char*) 0x6a4600);
	if (p != 0) {
		p += 6;
		e = fcn_0064e790(p, 0x22);
		if (e != 0 && p < e) {
			i = e - p;
			memcpy(pbuf, p, i);
			pbuf[i] = 0;
		} else {
			pbuf[0] = 0;
		}
		*(int*) 0x7e2510 = atoi(pbuf);
	}

	if (main_CheckExistingInstance(&mutex) != 0)
		exit(1);

	if (main_CreateWindow((HINSTANCE) instance, show, windowed) == 0) {
		main_ShutdownEngine();
		return 0;
	}
	if (main_InitRuntime() == 0) {
		main_ShutdownEngine();
		return 0;
	}
	if (*(int*) 0x77492c != 0)
		main_PlayIntroMovies();
	if (main_CreateGameWindowAndDevice(windowed) == 0) {
		main_ShutdownEngine();
		return 0;
	}
	if (main_OpenEngine() == 0) {
		main_ShutdownEngine();
		return 0;
	}

	mode = 9;
	val = 0x59a;
	do {
		if (*(int*) 0x7747ec != 0) {
			n = 0x38;
			if (*(char*) 0x774828 != 0) {
				for (i = 0; i < 0x5f; i++) {
					if (fcn_0065f220((char*) 0x774828, *(char**) (0x14a57e0 + i * 4)) == 0) {
						n = i;
						break;
					}
				}
			}
			*(int*) 0x7747b0 = mode;
			*(char*) 0x7e23e0 = (char) (gm_RandomMod(0x5f) + 1);
			*(char*) 0x7e23e1 = (char) (gm_RandomMod(0x5f) + 1);
			*(char*) 0x7e23e3 = (char) n;
			*(char*) 0x7e23e2 = 0x12;
			*(int*) 0x7e23e4 = val;
			*(char*) 0x7e23e8 = 0;
			*(char*) 0x7e23e9 = 1;
			strcpy((char*) 0x7e23ea, "Tobias");
			strcpy((char*) 0x7e240a, "Severin");
			*(int*) 0x7e2468 = gm_FindHeadIconIndex((char*) 0x6a3db4) + 0x639;
			p = (char*) gm_GetStatRecord((Rec6*) (pbuf + 4), (int) *(unsigned char*) 0x7e23e3);
			*(int*) 0x7e2430 = *(int*) p;
			*(short*) pbuf = *(short*) (p + 4);
			*(char*) 0x7e2434 = (char) *(short*) pbuf;
			*(char*) 0x7e2433 = 0xa8;
			*(char*) 0x7e2430 = 0;
			*(char*) 0x7e2431 = 0;
			hst_SetHistoryScrollModeFlag(1);
		} else if (server != 0) {
			*(int*) 0x7747b0 = 5;
		} else {
			main_Menue();
			if (*(int*) 0x77495c != 0) {
				main_ShutdownSubsystems();
				main_PumpWindowMessages();
				if (main_CreateGameWindowAndDevice(windowed) == 0) {
					main_ShutdownEngine();
					return 0;
				}
				*(int*) 0x77495c = server;
				main_PumpWindowMessages();
			}
		}
		*(int*) 0x774958 = 1;
		if (*(int*) 0x7747b0 != 0 && *(int*) 0x77496c == 0) {
			do {
				main_RunGameLoop(0);
			} while (*(int*) 0x774958 != 0);
		}
		if (*(int*) 0x7747ec != 0 || server != 0)
			*(int*) 0x77496c = 1;
		*(int*) 0x774654 = 0;
		*(int*) 0x774650 = 0;
	} while (*(int*) 0x77496c == 0);

	main_ShutdownEngine();
	if (*(int*) 0x774974 != 0)
		main_SetScreensaverActive((void*) 1);
	return 1;
}
