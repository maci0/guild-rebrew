extern int g_774654;
typedef unsigned char u8;
typedef unsigned short u16;

int __cdecl gm_CanEnterGebaeude(char*);
void __cdecl d2_ResetUiInputAndBounds(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl sv_ResetSelectionState(void);
void __cdecl fcn_005305a0(void);
int __cdecl sb_PlayVoice(int, void*, int, int, int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl sb_LoadBuildingVoiceBanks(char*);
int __cdecl fcn_00510c90(int);
void __cdecl d3_DeinitUniverse(int);
int __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_InitUniverse(int);
int __cdecl d3_TraverseSceneObjects(void*, int, int, void*);
void __cdecl ch_PreloadBuildingMotions(char*);
void __cdecl d3_UpdateBuildingView(char*, int);
void __cdecl d3_SetupInteriorScene(char*, char*);
void __cdecl d3_SetNodePosition(void*, void*);
void __cdecl d3_SetObjectRotation(void*, void*);
int __cdecl fcn_00504bd0(int);
int __cdecl CompareVector3WithinTolerance(float* a, float* b, float eps);
void __cdecl d2_DispatchTutorialInput(int, void*, int, int);
int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(void*);
void __cdecl evt_WaitForScriptExit(int);
void __cdecl d3_CleanupBuildingScene(char*);
void __cdecl d3snd_FreeObjectSoundBanks(void);
void __cdecl d3_ResetWorldSceneState(void);
void __cdecl fcn_00597fd0(void*);
void __cdecl d2_RunCharacterActionsHud(int, void*);
void __cdecl d2_RunSabotageActionsHud(int, void*);
void __cdecl d2_RunWeinschrankMenu(int, void*);
void __cdecl d2_RunRhetoricActionsHud(int, void*);
void __cdecl d2_RunSocialActionsHud(int, void*);
void __cdecl d2_RunGeliebteHud(int, void*);
void __cdecl d2_RunWirtshausTableMenu(int, void*);
void __cdecl d2_RunTutorialSchmiedeHud(int, void*);
void __cdecl d2_RunTischlereiInteriorHud(int, void*);
void __cdecl d2_RunMixingProductionMenu(int, void*);
void __cdecl d2_RunIdleBuildingInterior0xd6(int, void*);
void __cdecl d2_RunAlchemistCreatureHud(int, void*);
void __cdecl d2_RunSteinmetzMenu(int, void*);
void __cdecl d2_RunBankContactMenu(int, void*);
void __cdecl d2_RunKircheMenu(int, void*);
void __cdecl d2_RunKircheAltarMenu(int, void*);
void __cdecl d2_RunKerkerplanHotspot(int, void*);
void __cdecl d2_RunKerkermeisterMenu(int, void*);
void __cdecl d2_RunIdleBuildingInterior0xbb(int, void*);
void __cdecl d2_RunRaeuberlagerMenu(int, void*);
void __cdecl d2_RunIdleBuildingInterior0x4d(int, void*);
void __cdecl d2_RunWachstubeMenu(int, void*);
void __cdecl d2_RunWachstubeRegenMenu(int, void*);
void __cdecl d2_RunKerkerZelleMenu(int, void*);
void __cdecl d2_RunBeichtstuhlMenu(int, void*);
void __cdecl d2_RunParfumerieProductionMenu(int, void*);
void __cdecl d2_RunWirtshausContactMenu(int, void*);
void __cdecl d2_RunBrauenMenu(int, void*);
void __cdecl d2_RunRathausMenu(int, void*);
void __cdecl d2_RunRathausCouncilMenu(int, void*);
void __cdecl d2_RunStadtkasseMenu(int, void*);
void __cdecl d2_RunZunftLevel2Menu(int, void*);
void __cdecl d2_RunSchreibstubeMenu(int, void*);
void __cdecl d2_RunZunftPreismanipMenu(int, void*);
void __cdecl d2_RunZunftMenu(int, void*);
void __cdecl d2_RunWachhofRegenMenu(int, void*);
void __cdecl d2_RunZollamtMenu(int, void*);
void __cdecl d2_RunRazziaWacheMenu(int, void*);
void __cdecl d2_RunAlchemistMenu(int, void*);
void __cdecl d2_RunSchneiderMenu(int, void*);
void __cdecl d2_RunDomizilKabinettMenu(int, void*);
void __cdecl d2_RunDomizilKanoneMenu(int, void*);
extern unsigned int g_6a2520;
extern char g_6752a8[];
char* __cdecl strcpy(char*, const char*);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x005a76b0 */
int __cdecl gm_RunGebaeudeVisit(char* o, int p2)
{
    int r;
    int x;
    int i;
    int t;
    struct { float pos[4]; float rot[3]; } saved;
    char* msg;
    u8 c;

    r = -1;
    if (gm_CanEnterGebaeude(o) == 0) {
        *(int*) &g_7e2700 = 0;
        return 0;
    }
    d2_ResetUiInputAndBounds();
    main_RunFrameLoop((void*) 0x5a76b0, 0x20007);
    g_6a2520 = 0;
    sv_ResetSelectionState();
    fcn_005305a0();
    x = *(int*) &d3_CurrentContextIndex;
    *(int*) 0x7746d0 = 0;
    *(u16*) (o + 0x29) = (u16) p2;
    *(int*) &saved.pos[0] = *(int*) &g_7e3a40;
    *(int*) &saved.pos[1] = *(int*) &g_7e3a44;
    *(int*) &saved.pos[2] = *(int*) &g_7e3a48;
    *(int*) &saved.rot[0] = *(int*) &d3_CameraTargetRotation;
    *(int*) &saved.rot[1] = *(int*) &g_7e3a54;
    *(int*) &saved.rot[2] = *(int*) &g_7e3a58;
    if (p2 == 0)
        *(int*) &g_7746c4 = 0;
    if (*(u16*) (o + 0x27) == *(u16*) &g_774970)
        sb_PlayVoice(g_7747c8, (void*) 0x6aadc8, 1, 0x3f, 0x7f, 0, 0);
    else
        sb_PlayVoice(g_7747c8, (void*) 0x6aadac, 1, 0x3f, 0x7f, 0, 0);
    strcpy(g_6752a8, "normal_s");

    fcn_00502cd0(*(int*) (o + 0x5d), 1, 0, (int) *(u16*) (o + 0x29));
    sb_LoadBuildingVoiceBanks(o);

    do {
        g_774658 = g_774650 + 1;
        msg = (char*) fcn_00502cd0(*(int*) (o + 0x5d), 1, 0, (int) *(u16*) (o + 0x29));
        if (msg != 0) {
            c = ((u8*) &init_SceneContextIndices)[*(u16*) msg];
            if (c != 0xfe) {
                if (c == 0xff ||
                    *(signed char*) (0x1043695 + 0x3dc * (int) (signed char) c) != 0) {
                    d2_SuppressOverlay = 1;
                    main_RunFrameLoop((void*) 0, 0x603c7);
                    main_RunFrameLoop((void*) 0, 0x603c7);
                    fcn_00510c90((int) *(u16*) msg);
                    d2_SuppressOverlay = 0;
                }
                if (*(int*) &d3_CurrentContextIndex != 0)
                    d3_DeinitUniverse(3);
                *(int*) &g_7746c4 = (int) o;
                *(int*) &g_7746cc = (int) msg;
                *(int*) &g_6791c8 = *(int*) (msg + 2);
                g_67530c = *(int*) (o + 1);
                g_675310 = *(int*) (msg + 2);
                *(u16*) (o + 0x29) = *(u16*) msg;
                d3_SelectSceneContext((int) (signed char) ((u8*) &init_SceneContextIndices)[*(u16*) msg], 0);
                d3_InitUniverse(3);
                d3_TraverseSceneObjects((void*) *(int*) &g_67a370, 0, 0xe0, (void*) 0x456df0);
                ch_PreloadBuildingMotions(o);
                t = *(int*) &g_7746c4;
                d3_UpdateBuildingView((char*) t, (int) *(u16*) (t + 0x29));
                d3_SetupInteriorScene((char*) *(int*) &g_7746c4, (char*) *(int*) &g_7746cc);
                t = *(int*) &d3_ActiveCamera;
                d3_SetNodePosition((void*) t, (char*) t + 0x5c);
                t = *(int*) &d3_ActiveCamera;
                d3_SetObjectRotation((void*) t, (char*) t + 0x90);
                t = *(int*) &g_67a370;
                if (t != 0) {
                    i = *(int*) (t + 0x3c8);
                    if (i != 0) {
                        if (*(int*) (i + 0x210) != 0)
                            ((void (__cdecl*) (int, int, int, int)) *(int*) (i + 0x210))
                                (t, 4, i + 0x214, 0);
                    }
                }
                r = *(int*) &evt_LastGfxScriptId;
                if (*(u16*) (o + 0x27) != *(u16*) &g_774970) {
                    i = fcn_00504bd0((int) *(u8*) o);
                    if (i == 1 || i == 8) {
                        if (CompareVector3WithinTolerance((char*) *(void**) &d3_ActiveCamera + 0x114,
                                         (void*) &g_662d70, 0.1f) == 0) {
                            if (CompareVector3WithinTolerance((char*) *(void**) &d3_ActiveCamera + 0x120,
                                             (void*) &g_662d70, 0.1f) == 0) {
                                t = *(int*) &d3_ActiveCamera;
                                d3_SetNodePosition((void*) t, (char*) t + 0x114);
                                t = *(int*) &d3_ActiveCamera;
                                d3_SetObjectRotation((void*) t, (char*) t + 0x120);
                            }
                        }
                    }
                }
                t = *(int*) &d3_ActiveCamera;
                *(int*) &g_7e3a40 = *(int*) (t + 0x4c);
                *(int*) &g_7e3a44 = *(int*) (t + 0x50);
                *(int*) &g_7e3a48 = *(int*) (t + 0x54);
                *(int*) &d3_CameraTargetRotation = *(int*) (t + 0x84);
                *(int*) &g_7e3a54 = *(int*) (t + 0x88);
                *(int*) &g_7e3a58 = *(int*) (t + 0x8c);
                d3_CameraHorizontalIndex = 0;
                d3_CameraVerticalStep = 0;
            }
            d2_DispatchTutorialInput(0x19, msg, 0, 0);
            switch (*(u16*) msg) {
    case 0x13:
        d2_RunCharacterActionsHud(*(int*)&g_7746c4, msg);
        break;
    case 0x14:
        d2_RunSabotageActionsHud(*(int*)&g_7746c4, msg);
        break;
    case 0x16:
        d2_RunWeinschrankMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x15:
        d2_RunRhetoricActionsHud(*(int*)&g_7746c4, msg);
        break;
    case 0x17:
        d2_RunSocialActionsHud(*(int*)&g_7746c4, msg);
        break;
    case 0x18:
        d2_RunGeliebteHud(*(int*)&g_7746c4, msg);
        break;
    case 0x1f:
        d2_RunWirtshausTableMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x74:
        d2_RunTutorialSchmiedeHud(*(int*)&g_7746c4, msg);
        break;
    case 0x85:
        d2_RunTischlereiInteriorHud(*(int*)&g_7746c4, msg);
        break;
    case 0xcf:
        d2_RunMixingProductionMenu(*(int*)&g_7746c4, msg);
        break;
    case 0xd6:
        d2_RunIdleBuildingInterior0xd6(*(int*)&g_7746c4, msg);
        break;
    case 0xdd:
        d2_RunAlchemistCreatureHud(*(int*)&g_7746c4, msg);
        break;
    case 0x9b:
        d2_RunSteinmetzMenu(*(int*)&g_7746c4, msg);
        break;
    case 0xa5:
        d2_RunBankContactMenu(*(int*)&g_7746c4, msg);
        break;
    case 0xe5:
    case 0xe6:
        d2_RunKircheMenu(*(int*)&g_7746c4, msg);
        break;
    case 0xf0:
        d2_RunKircheAltarMenu(*(int*)&g_7746c4, msg);
        break;
    case 0xb7:
        d2_RunKerkerplanHotspot(*(int*)&g_7746c4, msg);
        break;
    case 0xba:
        d2_RunKerkermeisterMenu(*(int*)&g_7746c4, msg);
        break;
    case 0xbb:
        d2_RunIdleBuildingInterior0xbb(*(int*)&g_7746c4, msg);
        break;
    case 0x54:
        d2_RunRaeuberlagerMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x4d:
        d2_RunIdleBuildingInterior0x4d(*(int*)&g_7746c4, msg);
        break;
    case 0x5c:
        d2_RunWachstubeMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x60:
        d2_RunWachstubeRegenMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x65:
        d2_RunKerkerZelleMenu(*(int*)&g_7746c4, msg);
        break;
    case 0xf2:
        d2_RunBeichtstuhlMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x118:
        d2_RunParfumerieProductionMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x120:
        d2_RunWirtshausContactMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x12e:
        d2_RunBrauenMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x10e:
        d2_RunRathausMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x110:
        d2_RunRathausCouncilMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x114:
        d2_RunStadtkasseMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x137:
        d2_RunZunftLevel2Menu(*(int*)&g_7746c4, msg);
        break;
    case 0xf7:
        d2_RunSchreibstubeMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x138:
        d2_RunZunftPreismanipMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x139:
        d2_RunZunftMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x145:
        d2_RunWachhofRegenMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x146:
        d2_RunZollamtMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x14c:
        d2_RunRazziaWacheMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x24b:
        d2_RunAlchemistMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x29e:
        d2_RunSchneiderMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x266:
        d2_RunDomizilKabinettMenu(*(int*)&g_7746c4, msg);
        break;
    case 0x256:
        d2_RunDomizilKanoneMenu(*(int*)&g_7746c4, msg);
        break;
            default:
                fcn_00597fd0(msg);
                break;
            }
            d2_DispatchTutorialInput(0x1a, msg, 0, 0);
            *(int*) 0x7746d0 = (int) msg;
            if (r != -1) {
                msg = (char*) evt_FindScriptById(r);
                if (msg != 0) {
                    evt_RequestScriptExit(msg);
                    evt_WaitForScriptExit(*(int*) (msg + 0x100));
                }
            }
            t = *(int*) &g_67a370;
            if (t != 0) {
                i = *(int*) (t + 0x3c8);
                if (i != 0) {
                    if (*(int*) (i + 0x294) != 0) {
                        ((void (__cdecl*) (int, int, int, int)) *(int*) (i + 0x294))
                            (t, 5, i + 0x298, 0);
                    }
                }
            }
            i = *(int*) &evt_LastGfxScriptId;
            if (i != -1)
                evt_WaitForScriptExit(i);
            d3_CleanupBuildingScene(o);
            g_774670 = 1;
            if (*(int*) &g_7746c4 == 0) {
                g_774654 = 1;
                d3_DeinitUniverse(3);
            }
        }
    } while (main_RunFrameLoop((void*) 0x5a76b0, 0x67fff) != 0);

    sv_ResetSelectionState();
    fcn_005305a0();
    *(int*) &g_7ea360 = 0;
    d3snd_FreeObjectSoundBanks();
    d3_SelectSceneContext(x, 0);
    *(int*) &g_6791c8 = 0;
    g_67530c = -1;
    g_675310 = -1;
    *(int*) &g_7746c4 = 0;
    *(int*) &g_7746cc = 0;
    d3_ResetWorldSceneState();
    *(int*) &g_7e3a40 = *(int*) &saved.pos[0];
    *(int*) &g_7e3a44 = *(int*) &saved.pos[1];
    *(int*) &g_7e3a48 = *(int*) &saved.pos[2];
    *(int*) &d3_CameraTargetRotation = *(int*) &saved.rot[0];
    *(int*) &g_7e3a54 = *(int*) &saved.rot[1];
    *(int*) &g_7e3a58 = *(int*) &saved.rot[2];
    return sb_PlayVoice(g_7747c8, (void*) 0x6aad8c, 1, 0x3f, 0x7f, 0, 0);
}
