/* Network-session start: waits for the network state, validates the city path,
 * loads the network scene, writes the game.INI network entry, connects and
 * retries until the session exists, then hands the session to the game and
 * tears the scene down. Returns 1 when the city path check fails, 2 when the
 * network scene check fails, 0 after a completed startup. */
extern signed char g_6a3440; extern unsigned char g_6a375c; extern int d3_CurrentContextIndex; extern int g_77250c; extern unsigned char g_773d75; extern int g_77494c; extern char g_868060[];
#pragma intrinsic(strcpy)

int __cdecl sprintf(char *buf, const char *fmt, ...);
char *__cdecl strrchr(const char *s, int c);
char *__cdecl strcpy(char *dst, const char *src);

__declspec(dllimport) unsigned long __stdcall GetModuleFileNameA(void *module, char *name, unsigned long size);
__declspec(dllimport) int __stdcall WritePrivateProfileStringA(const char *sec, const char *key,
                                                              const char *value, const char *file);
__declspec(dllimport) unsigned long __stdcall timeGetTime(void);

void __cdecl d2_ShowNetworkLoadStatus(unsigned int a0);
void __cdecl gm_InitCityAndTradeState(char a0);
void __cdecl init_LocalData(void);
void __cdecl gm_RestockTownMarket(char a0);
int __cdecl ls_SendGame(char *path);
int __cdecl ls_WaitAndLoadNetSave(void);
void __cdecl main_PumpWindowMessages(void);
void __cdecl cm_StepCommandQueue(void);
void __cdecl sv_WaitForNetworkSync(int id);
void __cdecl gm_UpdateMarketStockSlots(int i);
void __cdecl cm_SendRandomMarktSlotDelta(int i);
int __cdecl fcn_0050b750(int timeout, char who);
int __cdecl d3_FindFreeSceneContext(void);
int __cdecl d3_SelectSceneContext(int a0, int a1);
int __cdecl fcn_00442e30(void);
int __cdecl d3_LoadScene(char *name, int a1, int a2);
int __cdecl d2_SetFormVisibility(int a0, int a1);
int __cdecl d2_ClearSurface(int a0);
int __cdecl gm_RandomMod(unsigned short a0);
int __cdecl d2_SetBackdropResource(int a0);
int __cdecl d2_RenderAndPresentFrame(void);
void __cdecl cm_RequestSysMessage(char id, char *args);
int __cdecl cm_SendAllocClientSpieler(int a0, int a1, short a2, char a3, int a4,
                         char a5, char a6, char *a7, char *a8);
int __cdecl cm_GetCommandStatus(int i);
int __cdecl cm_GetCommandResult(int i);
int __cdecl gm_AllocRandomMissionJob(int a0, int a1, int a2);
int __cdecl d2_ShowMissionForEntity(int a0);
int __cdecl cm_RequestMoveCredits(int a0, int a1, char a2, int a3);
void __cdecl cm_SetGameSpeedSetting(int a0);

/* ADDRESS: GOLDTL 0x005145a0 */
int __cdecl ls_StartNetworkGame(char *path)
{
    char text[512];
    char file[260];
    int msg[31];    /* 0x7c-byte message block for fcn_004c5790; only [0]/[1] set */
    int flag;
    int session;
    int handle;
    int stamp;
    int result;
    int engine;
    int i;
    char *p;

    sprintf(text, *(char **) 0x14ac600, *(unsigned char *) &g_6a375c);
    d2_ShowNetworkLoadStatus((unsigned int) text);
    *(int *) &g_77494c = 0;
    do {
        main_PumpWindowMessages();
        cm_StepCommandQueue();
    } while (*(int *) &g_77494c == 0);
    if (*(int *) &g_77494c & 1) {
        if (*path == 0)
            sprintf(path, "%s/AUGSBURG.NET", "gamedata/cities");
        d2_ShowNetworkLoadStatus(*(unsigned int *) 0x14ac5f0);
        if (ls_SendGame(path) == 0)
            return 1;
    }
    flag = *(int *) &g_77494c & 1;
    d2_ShowNetworkLoadStatus(*(unsigned int *) 0x14ac5f4);
    if (ls_WaitAndLoadNetSave() == 0)
        return 2;
    GetModuleFileNameA(*(void **) 0x7e1f80, file, 0x104);
    p = strrchr(file, '\\');
    strcpy(p, "\\game.INI");
    engine = d3_CurrentContextIndex;
    *(int *) 0x7725c8 = 0;
    d3_SelectSceneContext(d3_FindFreeSceneContext(), 0);
    d3_LoadScene("scenes/*network.ed3", 0, 0);
    d2_SetFormVisibility(*(int *) 0x7e1d40, 0);
    *(int *) 0x7725c8 = 1;
    fcn_00442e30();
    d3_SelectSceneContext(engine, 0);
    d2_SetFormVisibility(*(int *) 0x7e1d40, 1);
    WritePrivateProfileStringA("Network", "Name", (char *) 0x7e23ea, file);
    WritePrivateProfileStringA("Network", "Familienname", (char *) 0x7e240a, file);
    d2_ClearSurface(*(int *) &g_77250c);
    d2_SetBackdropResource(((unsigned short) gm_RandomMod(2) != 1) ? 0x791 : 0x78e);
    d2_RenderAndPresentFrame();
    if (*(int *) &g_77494c & 1) {
        msg[0] = *(unsigned char *) &g_6a375c;
        cm_RequestSysMessage(6, (char *) msg);
    }
    session = cm_SendAllocClientSpieler(0xffff, 0xffff, *(unsigned char *) 0x7e23e2,
                           *(unsigned char *) 0x7e23e3,
                           *(int *) 0x7e23e4 + 0x59a,
                           *(unsigned char *) 0x7e23e8,
                           *(unsigned char *) 0x7e23e9,
                           (char *) 0x7e23ea, (char *) 0x7e240a);
    while (session == -1) {
        main_PumpWindowMessages();
        cm_StepCommandQueue();
        session = cm_SendAllocClientSpieler(0xffff, 0xffff, *(unsigned char *) 0x7e23e2,
                               *(unsigned char *) 0x7e23e3,
                               *(int *) 0x7e23e4 + 0x59a,
                               *(unsigned char *) 0x7e23e8,
                               *(unsigned char *) 0x7e23e9,
                               (char *) 0x7e23ea, (char *) 0x7e240a);
    }
    while (cm_GetCommandStatus(session) == 0) {
        main_PumpWindowMessages();
        cm_StepCommandQueue();
    }
    handle = cm_GetCommandResult(session);
    if (*(int *) &g_77494c & 1) {
        *(unsigned char *) &g_6a3440 = 0xff;
        msg[0] = -1;
        stamp = (int) timeGetTime();
        *(int *) 0x7e1f60 = stamp;
        msg[1] = stamp;
        cm_RequestSysMessage(9, (char *) msg);
    }
    while (*(unsigned char *) &g_6a3440 == 0xfe) {
        main_PumpWindowMessages();
        cm_StepCommandQueue();
    }
    if (*(unsigned char *) &g_6a3440 != 0xff) {
        if (*(unsigned char *) &g_6a3440 != 5)
            *(int *) 0x7e1f60 = (int) timeGetTime();
        gm_AllocRandomMissionJob(*(int *) (handle + 4), *(signed char *) &g_6a3440, 1);
    }
    result = fcn_0050b750(*(int *) 0x7747fc == 0 ? 2000 : 500000,
                          *(unsigned char *) &g_773d75);
    cm_RequestMoveCredits(*(int *) (handle + 4), -1, *(unsigned char *) &g_773d75,
                 result);
    while ((*(int *) &g_77494c & 4) == 0) {
        main_PumpWindowMessages();
        cm_StepCommandQueue();
    }
    if (flag != 0) {
        d2_ShowNetworkLoadStatus(*(unsigned int *) 0x14ac5f8);
        gm_InitCityAndTradeState(*(unsigned char *) &g_773d75);
    }
    sv_WaitForNetworkSync(0x24087);
    d2_ShowNetworkLoadStatus(*(unsigned int *) 0x14ac5fc);
    init_LocalData();
    sv_WaitForNetworkSync(0x24087);
    if (flag != 0) {
        gm_RestockTownMarket(*(unsigned char *) &g_773d75);
        i = 0;
        p = (char *) &g_868060;
        do {
            if (*p == 0)
                break;
            gm_UpdateMarketStockSlots(i);
            cm_SendRandomMarktSlotDelta(i);
            p += 0x2f4;
            i++;
        } while ((int) p < 0x868c30);
        cm_SetGameSpeedSetting(2);
    }
    *(int *) 0x7725c8 = 0;
    if (*(signed char *) &g_6a3440 > -1 && *(signed char *) &g_6a3440 < 6) {
        engine = d3_CurrentContextIndex;
        d3_SelectSceneContext(d3_FindFreeSceneContext(), 0);
        d3_LoadScene("scenes/*network.ed3", 0, 0);
        d2_ShowMissionForEntity(*(int *) (handle + 4));
        fcn_00442e30();
        d3_SelectSceneContext(engine, 0);
    }
    return 0;
}
