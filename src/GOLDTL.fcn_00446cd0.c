typedef struct
{
	int k;
	int a;
	int b;
} fcn_00446cd0_Key;
// SIZE 0xc

typedef struct
{
	int pos[3];
	int dir[3];
	fcn_00446cd0_Key keys[6];
} fcn_00446cd0_Cam;
// SIZE 0x60

extern struct VFS_DIR* g_6b7fdc;
extern char s_6790b0[];
extern int g_6b86d4;
#include "client_types.h"
extern VECTOR3 g_67bbdc;
extern VECTOR3 g_6b86c4;
extern int g_6b805c;
extern float g_10425fc;
extern float g_104329c;
extern char g_1041d80[];
extern int g_67a370;

void* __cdecl fcn_0042ff50(const char* name, const char* mode, struct VFS_DIR* root);
void __cdecl fcn_00401360(void* s, int v);
void __cdecl fcn_00401260(void* s, int v);
void __cdecl fcn_004012f0(void* s, int* v);
void __cdecl fcn_004379a0(int list, int a, int kind, void* fn, void* ctx);
void __cdecl fcn_00446c60(void);
void __cdecl fcn_00401210(void* s, int v);
#include "Develop/Units/vfs/vfs.h"

/* ADDRESS: GOLDTL 0x00446cd0 */
void __cdecl fcn_00446cd0(char* name, void* stream)
{
	void* s;
	int i;
	int j;

	s = stream;
	if (s == 0) {
		s = fcn_0042ff50(name, s_6790b0, g_6b7fdc);
		if (s == 0) {
			return;
		}
	}
	g_6b86d4++;
	fcn_00401360(s, 0x3a6c00bb);
	fcn_00401260(s, 0);
	fcn_004012f0(s, ((int*)&g_67bbdc));
	fcn_004012f0(s, ((int*)&g_6b86c4));
	fcn_00401360(s, g_6b805c);
	fcn_00401260(s, (*(int*)&g_10425fc));
	fcn_00401260(s, (*(int*)&g_104329c));
	for (i = 0; i < 7; i++) {
		fcn_004012f0(s, ((fcn_00446cd0_Cam*)g_1041d80)[i].pos);
		fcn_004012f0(s, ((fcn_00446cd0_Cam*)g_1041d80)[i].dir);
		for (j = 0; j < 6; j++) {
			fcn_00401360(s, ((fcn_00446cd0_Cam*)g_1041d80)[i].keys[j].k);
			fcn_00401260(s, ((fcn_00446cd0_Cam*)g_1041d80)[i].keys[j].a);
			fcn_00401260(s, ((fcn_00446cd0_Cam*)g_1041d80)[i].keys[j].b);
		}
	}
	fcn_004379a0(g_67a370, 0, 0x18, (void*) fcn_00446c60, s);
	fcn_00401210(s, 0);
	if (stream == 0) {
		CloseVfsStream(s);
	}
	g_6b86d4--;
}
