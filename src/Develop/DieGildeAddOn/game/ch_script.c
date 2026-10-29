#ifndef REBREW_SERVER
#include <string.h>
#include "ch_script.h"
#include "ch_motion.h"
#include "Develop/Units/m_alloc/m_alloc_checks.h"

char* __cdecl fcn_0040b730(char*, char*);
void __cdecl fcn_00425bf0(char*, unsigned int, const char*);
int __cdecl evt_ImportCommand(const char*, void*, int, int, ...);

/* ADDRESS: GOLDTL 0x0040cae0 */
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
void __cdecl ch_RegisterScriptCommands(void)
{
    evt_ImportCommand("CreateCharacter", (void*) fcn_0040c930, 1, 4, 6, 7, 7, 7);
    evt_ImportCommand("CreateCharacterAtDummy", (void*) CreateCharacterAtDummy, 1, 3, 6, 1, 6);
    evt_ImportCommand("KillCharacter", (void*) fcn_0040cad0, 5, 1, 1);
    evt_ImportCommand("WalkToDummy", (void*) WalkToDummy, 5, 2, 1, 1);
    evt_ImportCommand("WalkToDummyRotate", (void*) fcn_0040cba0, 5, 2, 1, 1);
    evt_ImportCommand("WalkToDummyVerified", (void*) fcn_0040cd20, 5, 3, 1, 1, 1);
    evt_ImportCommand("WalkToDummyRotateVerified", (void*) fcn_0040cc60, 5, 3, 1, 1, 1);
    evt_ImportCommand("PlayAnimation", (void*) fcn_0040cde0, 5, 3, 1, 6, 1);
    evt_ImportCommand("PlayAnimationSound", (void*) PlayCharacterAniSound, 5, 5, 1, 6, 1, 1, 6);
    evt_ImportCommand("PlayAnimationScript", (void*) PlayCharacterAniScript, 5, 5, 1, 6, 1, 1, 6);
    evt_ImportCommand("PlayAnimationScriptInt", (void*) PlayCharacterAniScriptInt, 5, 6, 1, 6, 1, 1, 6, 1);
    evt_ImportCommand("GetCharacterHandle", (void*) fcn_0040d250, 1, 1, 6);
    evt_ImportCommand("TakeObject", (void*) fcn_0040d2b0, 1, 4, 1, 6, 1, 1);
    evt_ImportCommand("TakeObjectLeft", (void*) fcn_0040d360, 1, 4, 1, 6, 1, 1);
    evt_ImportCommand("TakeObjectScript", (void*) TakeObjectScript, 1, 6, 1, 6, 1, 1, 1, 6);
    evt_ImportCommand("GiveObject", (void*) fcn_0040d550, 1, 2, 1, 6);
    evt_ImportCommand("DropObject", (void*) fcn_0040d580, 1, 4, 1, 6, 1, 1);
    evt_ImportCommand("DropObjectLeft", (void*) fcn_0040d640, 1, 4, 1, 6, 1, 1);
    evt_ImportCommand("SitDown", (void*) fcn_0040d700, 1, 2, 1, 6);
    evt_ImportCommand("SitDownAtOnce", (void*) fcn_0040d790, 1, 2, 1, 6);
    evt_ImportCommand("GetUp", (void*) fcn_0040d830, 1, 2, 1, 6);
    evt_ImportCommand("SetCharacterCamera", (void*) SetCharacterCamera, 5, 2, 1, 6);
    evt_ImportCommand("MoveCharacterCamera", (void*) MoveCharacterCamera, 5, 3, 1, 6, 1);
    evt_ImportCommand("PreloadAnimation", (void*) fcn_0040da60, 5, 5, 1, 6, 6, 6, 6);
    evt_ImportCommand("PreloadSitMesh", (void*) fcn_0040dac0, 5, 1, 1);
    evt_ImportCommand("CharacterIdle", (void*) fcn_0040dad0, 1, 1, 1);
    evt_ImportCommand("StopCharacter", (void*) fcn_0040db10, 5, 1, 1);
    evt_ImportCommand("KillCharacterAnimations", (void*) fcn_0040db50, 5, 1, 1);
    evt_ImportCommand("DummyBlocked", (void*) fcn_0040dbb0, 1, 2, 1, 1);
    evt_ImportCommand("CharacterCount", (void*) fcn_0040cd70, 1, 0);
    evt_ImportCommand("LookAtCharacter", (void*) fcn_0040dcd0, 5, 2, 1, 1);
    evt_ImportCommand("LookAtObject", (void*) fcn_0040ddc0, 5, 2, 1, 1);
    evt_ImportCommand("SetCharacterToDummy", (void*) fcn_0040de40, 5, 2, 1, 1);
    evt_ImportCommand("CharacterSitting", (void*) CharacterSitting, 5, 1, 1);
    evt_ImportCommand("GetCharacterSubObjectHandle", (void*) fcn_0040df40, 5, 2, 1, 6);
    evt_ImportCommand("SetCharacterStepSample", (void*) fcn_0040df90, 5, 1, 6);
    evt_ImportCommand("SetLowPoly", (void*) fcn_0040dfb0, 5, 2, 1, 1);
    evt_ImportCommand("AttachObject", (void*) fcn_0040e000, 5, 3, 1, 6, 6);
    evt_ImportCommand("SetCharacterTransperancy", (void*) fcn_0040e080, 5, 2, 1, 1);
    evt_ImportCommand("CharacterSitsDown", (void*) CharacterSitsDown, 5, 1, 1);
    evt_ImportCommand("FindInCharacterName", (void*) fcn_0040e150, 1, 2, 1, 6);
}

#endif
