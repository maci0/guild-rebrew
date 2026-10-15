#ifndef REBREW_SERVER
#include <string.h>
#include "ch_script.h"
#include "ch_motion.h"
#include "Develop/Units/m_alloc/m_alloc_checks.h"

char* __cdecl fcn_0040b730(char*, char*);
void __cdecl fcn_00425bf0(char*, unsigned int, const char*);
int __cdecl fcn_00429ed0(const char*, void*, int, int, ...);

/* ADDRESS: GOLDTL 0x0040cae0 */
/* ADDRESS: GOLD 0x0040bbc0 */
int __cdecl WalkToDummy(char** character, char** dummy)
{
    if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) WalkToDummy) {
        if (*(void**) (*character + 0x128) != 0) {
            *(void**) (g_6b7e98 + 0xc60) = (void*) WalkToDummy;
            return 0;
        }
    } else {
        if (*dummy != 0 && *character != 0) {
            if (m_is_tracked(*dummy) && m_is_tracked(*character)) {
                fcn_0040b730(*character, *dummy);
                if (*(int*) (g_6b7e98 + 0xc84) == 1) {
                    *(void**) (g_6b7e98 + 0xc60) = (void*) WalkToDummy;
                }
                return 1;
            }
        } else {
            fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118),
                "WalkToDummy(): invalid character or dummy");
        }
    }
    return 0;
}

/* ADDRESS: GOLDTL 0x0040d980 */
/* ADDRESS: GOLD 0x0040ca60 */
int __cdecl MoveCharacterCamera(char** character, char** view, int* mode)
{
    char* object;
    char* name;

    object = *character;
    if (object == 0) {
        fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118),
            "MoveCharacterCamera(): Invalid character");
        return 1;
    }
    name = *view;
    if (strcmp(name, "CLOSEUP") == 0) {
        fcn_004056f0(object, 0, *mode);
        return 0;
    }
    if (strcmp(name, "LEFT_SHOULDER") == 0) {
        fcn_004056f0(object, 1, *mode);
        return 0;
    }
    if (strcmp(name, "RIGHT_SHOULDER") == 0) {
        fcn_004056f0(object, 2, *mode);
        return 0;
    }
    if (strcmp(name, "EGO") == 0) {
        fcn_004056f0(object, 3, *mode);
    }
    return 0;
}

/* One unused object argument is inferred from the native script registration. */
/* ADDRESS: GOLDTL 0x0040dac0 */
int __cdecl fcn_0040dac0(char** character)
{
    return 0;
}

/* Inferred name and source placement; native recipes are identical in both clients. */
/* ADDRESS: GOLDTL 0x0040e1a0 */
/* ADDRESS: GOLD 0x0040d270 */
void __cdecl ch_RegisterScriptCommands(void)
{
    fcn_00429ed0("CreateCharacter", (void*) fcn_0040c930, 1, 4, 6, 7, 7, 7);
    fcn_00429ed0("CreateCharacterAtDummy", (void*) CreateCharacterAtDummy, 1, 3, 6, 1, 6);
    fcn_00429ed0("KillCharacter", (void*) fcn_0040cad0, 5, 1, 1);
    fcn_00429ed0("WalkToDummy", (void*) WalkToDummy, 5, 2, 1, 1);
    fcn_00429ed0("WalkToDummyRotate", (void*) fcn_0040cba0, 5, 2, 1, 1);
    fcn_00429ed0("WalkToDummyVerified", (void*) fcn_0040cd20, 5, 3, 1, 1, 1);
    fcn_00429ed0("WalkToDummyRotateVerified", (void*) fcn_0040cc60, 5, 3, 1, 1, 1);
    fcn_00429ed0("PlayAnimation", (void*) fcn_0040cde0, 5, 3, 1, 6, 1);
    fcn_00429ed0("PlayAnimationSound", (void*) PlayCharacterAniSound, 5, 5, 1, 6, 1, 1, 6);
    fcn_00429ed0("PlayAnimationScript", (void*) PlayCharacterAniScript, 5, 5, 1, 6, 1, 1, 6);
    fcn_00429ed0("PlayAnimationScriptInt", (void*) PlayCharacterAniScriptInt, 5, 6, 1, 6, 1, 1, 6, 1);
    fcn_00429ed0("GetCharacterHandle", (void*) fcn_0040d250, 1, 1, 6);
    fcn_00429ed0("TakeObject", (void*) fcn_0040d2b0, 1, 4, 1, 6, 1, 1);
    fcn_00429ed0("TakeObjectLeft", (void*) fcn_0040d360, 1, 4, 1, 6, 1, 1);
    fcn_00429ed0("TakeObjectScript", (void*) TakeObjectScript, 1, 6, 1, 6, 1, 1, 1, 6);
    fcn_00429ed0("GiveObject", (void*) fcn_0040d550, 1, 2, 1, 6);
    fcn_00429ed0("DropObject", (void*) fcn_0040d580, 1, 4, 1, 6, 1, 1);
    fcn_00429ed0("DropObjectLeft", (void*) fcn_0040d640, 1, 4, 1, 6, 1, 1);
    fcn_00429ed0("SitDown", (void*) fcn_0040d700, 1, 2, 1, 6);
    fcn_00429ed0("SitDownAtOnce", (void*) fcn_0040d790, 1, 2, 1, 6);
    fcn_00429ed0("GetUp", (void*) fcn_0040d830, 1, 2, 1, 6);
    fcn_00429ed0("SetCharacterCamera", (void*) SetCharacterCamera, 5, 2, 1, 6);
    fcn_00429ed0("MoveCharacterCamera", (void*) MoveCharacterCamera, 5, 3, 1, 6, 1);
    fcn_00429ed0("PreloadAnimation", (void*) fcn_0040da60, 5, 5, 1, 6, 6, 6, 6);
    fcn_00429ed0("PreloadSitMesh", (void*) fcn_0040dac0, 5, 1, 1);
    fcn_00429ed0("CharacterIdle", (void*) fcn_0040dad0, 1, 1, 1);
    fcn_00429ed0("StopCharacter", (void*) fcn_0040db10, 5, 1, 1);
    fcn_00429ed0("KillCharacterAnimations", (void*) fcn_0040db50, 5, 1, 1);
    fcn_00429ed0("DummyBlocked", (void*) fcn_0040dbb0, 1, 2, 1, 1);
    fcn_00429ed0("CharacterCount", (void*) fcn_0040cd70, 1, 0);
    fcn_00429ed0("LookAtCharacter", (void*) fcn_0040dcd0, 5, 2, 1, 1);
    fcn_00429ed0("LookAtObject", (void*) fcn_0040ddc0, 5, 2, 1, 1);
    fcn_00429ed0("SetCharacterToDummy", (void*) fcn_0040de40, 5, 2, 1, 1);
    fcn_00429ed0("CharacterSitting", (void*) CharacterSitting, 5, 1, 1);
    fcn_00429ed0("GetCharacterSubObjectHandle", (void*) fcn_0040df40, 5, 2, 1, 6);
    fcn_00429ed0("SetCharacterStepSample", (void*) fcn_0040df90, 5, 1, 6);
    fcn_00429ed0("SetLowPoly", (void*) fcn_0040dfb0, 5, 2, 1, 1);
    fcn_00429ed0("AttachObject", (void*) fcn_0040e000, 5, 3, 1, 6, 6);
    fcn_00429ed0("SetCharacterTransperancy", (void*) fcn_0040e080, 5, 2, 1, 1);
    fcn_00429ed0("CharacterSitsDown", (void*) CharacterSitsDown, 5, 1, 1);
    fcn_00429ed0("FindInCharacterName", (void*) fcn_0040e150, 1, 2, 1, 6);
}

#endif
