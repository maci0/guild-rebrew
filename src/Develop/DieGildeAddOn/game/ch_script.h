#ifndef CH_SCRIPT_H
#define CH_SCRIPT_H

/* Inferred declaration home; signatures follow the native callback providers. */
char* __cdecl CreateCharacter(char** a, float* b, float* c, float* d);
char* __cdecl CreateCharacterAtDummy(char** file, char** dummy, char** name);
int __cdecl KillCharacter(char** a);
int __cdecl WalkToDummy(char** character, char** dummy);
int __cdecl WalkToDummyRotate(char** a, char** b);
int __cdecl WalkToDummyVerified(char** a, char** b, int* c);
int __cdecl WalkToDummyRotateVerified(char** a, char** b, int* c);
int __cdecl PlayAnimation(char** a, char** name, int* param);
int __cdecl PlayCharacterAniSound(char** ch, char** ani, int* kind, unsigned char* level, char** sound);
int __cdecl PlayCharacterAniScript(char** ch, char** script, int* kind, unsigned char* level, char** func);
int __cdecl PlayCharacterAniScriptInt(char** ch, char** script, int* kind, unsigned char* level, char** func, int* param);
int __cdecl GetCharacterHandle(int* a1);
int __cdecl TakeObject(char** a, char** name, int* param, char** src);
int __cdecl TakeObjectLeft(char** a, char** name, int* param, char** src);
int __cdecl TakeObjectScript(char** ch, char** ani, int* kind, char** dummy, unsigned char* level, char** func);
int __cdecl GiveObject(int* a1, int* a2);
int __cdecl DropObject(char** a, char** name, int* param, char** name2);
int __cdecl DropObjectLeft(char** a, char** name, int* param, char** name2);
int __cdecl SitDown(char** a, char** v);
int __cdecl SitDownAtOnce(char** a, char** v);
int __cdecl GetUp(char** a, int* v);
int __cdecl SetCharacterCamera(char** ch, char** view);
int __cdecl MoveCharacterCamera(char** character, char** view, int* mode);
int __cdecl PreloadAnimation(void** a1, int* a2, int* a3, int* a4, int* a5);
int __cdecl PreloadSitMesh(char** character);
int __cdecl CharacterIdle(int** charakter_argument);
int __cdecl StopCharacter(void* a1);
int __cdecl KillCharacterAnimations(char** a1);
char* __cdecl DummyBlocked(char** a, int* range);
int __cdecl fcn_0040cd70(void);
int __cdecl LookAtCharacter(char** a, char** b);
int __cdecl LookAtObject(char** a, char** b);
int __cdecl SetCharacterToDummy(char** a, char** b);
int __cdecl CharacterSitting(char** object);
int __cdecl GetCharacterSubObjectHandle(char** a1, int* a2);
int __cdecl SetCharacterStepSample(char** p);
int __cdecl SetLowPoly(char** pp, int* on);
int __cdecl AttachObject(char** a, const char* name, int* v);
int __cdecl SetCharacterTransperancy(char** a, unsigned char* v);
int __cdecl CharacterSitsDown(char** object);
int __cdecl FindInCharacterName(char** a1, int* a2);

void __cdecl ch_RegisterScriptCommands(void);

#endif
