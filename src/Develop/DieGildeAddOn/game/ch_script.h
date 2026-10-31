#ifndef CH_SCRIPT_H
#define CH_SCRIPT_H

/* Inferred declaration home; signatures follow the native callback providers. */
char* __cdecl fcn_0040c930(char** a, float* b, float* c, float* d);
char* __cdecl CreateCharacterAtDummy(char** file, char** dummy, char** name);
int __cdecl fcn_0040cad0(char** a);
int __cdecl WalkToDummy(char** character, char** dummy);
int __cdecl fcn_0040cba0(char** a, char** b);
int __cdecl fcn_0040cd20(char** a, char** b, int* c);
int __cdecl fcn_0040cc60(char** a, char** b, int* c);
int __cdecl fcn_0040cde0(char** a, char** name, int* param);
int __cdecl PlayCharacterAniSound(char** ch, char** ani, int* kind, unsigned char* level, char** sound);
int __cdecl PlayCharacterAniScript(char** ch, char** script, int* kind, unsigned char* level, char** func);
int __cdecl PlayCharacterAniScriptInt(char** ch, char** script, int* kind, unsigned char* level, char** func, int* param);
int __cdecl fcn_0040d250(int* a1);
int __cdecl fcn_0040d2b0(char** a, char** name, int* param, char** src);
int __cdecl fcn_0040d360(char** a, char** name, int* param, char** src);
int __cdecl TakeObjectScript(char** ch, char** ani, int* kind, char** dummy, unsigned char* level, char** func);
int __cdecl fcn_0040d550(int* a1, int* a2);
int __cdecl fcn_0040d580(char** a, char** name, int* param, char** name2);
int __cdecl fcn_0040d640(char** a, char** name, int* param, char** name2);
int __cdecl fcn_0040d700(char** a, char** v);
int __cdecl fcn_0040d790(char** a, char** v);
int __cdecl fcn_0040d830(char** a, int* v);
int __cdecl SetCharacterCamera(char** ch, char** view);
int __cdecl MoveCharacterCamera(char** character, char** view, int* mode);
int __cdecl fcn_0040da60(void** a1, int* a2, int* a3, int* a4, int* a5);
int __cdecl fcn_0040dac0(char** character);
int __cdecl CharacterIdle(int** charakter_argument);
int __cdecl fcn_0040db10(void* a1);
int __cdecl fcn_0040db50(char** a1);
char* __cdecl fcn_0040dbb0(char** a, int* range);
int __cdecl fcn_0040cd70(void);
int __cdecl fcn_0040dcd0(char** a, char** b);
int __cdecl fcn_0040ddc0(char** a, char** b);
int __cdecl fcn_0040de40(char** a, char** b);
int __cdecl CharacterSitting(char** object);
int __cdecl fcn_0040df40(char** a1, int* a2);
int __cdecl fcn_0040df90(char** p);
int __cdecl fcn_0040dfb0(char** pp, int* on);
int __cdecl fcn_0040e000(char** a, const char* name, int* v);
int __cdecl fcn_0040e080(char** a, unsigned char* v);
int __cdecl CharacterSitsDown(char** object);
int __cdecl fcn_0040e150(char** a1, int* a2);

void __cdecl ch_RegisterScriptCommands(void);

#endif
