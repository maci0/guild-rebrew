#include <string.h>

extern char g_10432c0[];
extern int g_6b8010;
extern int g_67530c;
extern int g_675310;

void __cdecl fcn_0041d9e0(const char* msg);
int __cdecl fcn_004050c0(char* obj);
char* __cdecl fcn_00445600(char* a, int b, char* c, char* d);
void __cdecl fcn_00455350(char* src, char* pos, float* out);
int __cdecl ch_MoveCharacter2Universe(char* obj, void* universe);
char __cdecl SelectTextureSet(void* obj, void* ctx, unsigned char a, char b);
void __cdecl CharacterClearSitting(unsigned char* ch);
void __cdecl ch_SetPosition(char* obj, float* position, int flag);
void __cdecl fcn_004432d0(int a, int b);
void __cdecl ch_SetVisible(char* obj, int shown);

/* ADDRESS: GOLDTL 0x00407390 */
void __cdecl ch_Move2Universe(char* a0)
{
	char* v4;
	char* v3;
	char* p;
	int v2;
	int v5;
	char v8[16];
	char name[0x80];

	v4 = a0;
	v2 = *(int*) (a0 + 0x30);
	v3 = *(char**) (a0 + 0x14);
	if (v2 < 0) {
		fcn_0041d9e0((char*) 0x675a40);
		fcn_004050c0(v4);
		return;
	}
	if ((v2 == 0 && *(int*) (v4 + 0x34) != -1)
		|| (v2 != 0 && *(int*) (v4 + 0x34) == -1)) {
		if (v2 != 0 || *(int*) (v4 + 0x34) == -1)
			fcn_0041d9e0((char*) 0x675950);
		else
			fcn_0041d9e0((char*) 0x6759c8);
		fcn_004050c0(v4);
		return;
	}
	v5 = (int) ch_MoveCharacter2Universe(v3, g_10432c0 + v2 * 0x3dc);
	if (v5 == 0) {
		fcn_0041d9e0((char*) 0x675918);
		fcn_004050c0(v4);
		return;
	}
	{
		int saved = g_6b8010;

		fcn_004432d0(*(int*) (v4 + 0x30), 1);
		if (*(int*) (v4 + 0x30) == 0) {
			if (g_67530c == *(int*) (v3 + 0x2c))
				SelectTextureSet(*(void**) (v3 + 0x34),
					(char*) *(int*) (*(int*) (v3 + 0x34) + 0x1ec) + 0xf4,
					0, 0);
		} else {
			if (g_67530c == *(int*) (v3 + 0x2c))
				SelectTextureSet(*(void**) (v3 + 0x34),
					(char*) *(int*) (*(int*) (v3 + 0x34) + 0x1ec) + 0xf4,
					*(unsigned char*) (v3 + 0x23a), 1);
		}
		CharacterClearSitting((unsigned char*) v3);
		if (*(char*) (v4 + 0x17c)) {
			ch_SetPosition(v3, (float*) (v4 + 0x180), 0);
		} else {
			if (*(char*) (v4 + 0xf0)) {
				strcpy(name, v4 + 0xf0);
			} else {
				strcpy(name, (char*) 0x675908);
			}
			p = fcn_00445600(0, 0x100, 0, name);
			if (p != 0 || (p = fcn_00445600(0, 0x100, 0, (char*) 0x675908)) != 0
				|| (p = fcn_00445600(0, 0x100, 0, (char*) 0x675908)) != 0) {
				fcn_00455350(p, p + 0x4c, (float*) v8);
				ch_SetPosition(v3, (float*) v8, 0);
			}
		}
		*(int*) (v3 + 0x2c) = *(int*) (v4 + 0x34);
		*(int*) (v3 + 0x30) = *(int*) (v4 + 0x38);
		*(int*) (v3 + 0x38) = 0;
		*(int*) (v3 + 0x3c) = 0;
		*(int*) (v3 + 0x40) = 0;
		ch_SetVisible(v3, 1);
		if (saved == *(int*) (v4 + 0x30)) {
			if ((*(int*) (v3 + 0x2c) != -1 && g_67530c != *(int*) (v3 + 0x2c))
				|| (g_675310 != -1 && g_675310 != *(int*) (v3 + 0x30)))
				ch_SetVisible(v3, 0);
		}
		if (*(int*) (v4 + 0x28) != 0
			&& *(char*) (*(int*) (v4 + 0x28) + 9) == 0x38)
			ch_SetVisible(v3, 0);
		fcn_004432d0(saved, 1);
		fcn_004050c0(v4);
	}
}
