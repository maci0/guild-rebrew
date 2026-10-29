#include <stdio.h>

typedef struct {
	char name[0x60];
	int first;
	int count;
	char* text;
	char pad6c[8];
} TextBank_42d6b0;
// SIZE 0x74

extern char g_149d120[][0x74];
extern char g_1053000[][0x50];
extern int g_11bb000[];
extern char* g_14a5320[];
typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* g_6b7fdc;

int __cdecl fcn_0042d630(const char* name);
void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
void __cdecl fcn_00430a80(void* f, int off, int whence);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* f);
void __cdecl CloseVfsStream(void* f);
int* __cdecl m_alloc(int size, const char* tag);
void __cdecl m_FreeTracked(void* p);


/* Reloads a text bank from its language resource file. */
/* ADDRESS: GOLDTL 0x0042d6b0 */
int __cdecl fcn_0042d6b0(const char* name)
{
	int idx;
	void* f;
	int i;
	int n;
	int size;
	int* ofs;
	char path[0x100];

	idx = fcn_0042d630(name);
	if (idx == -1) {
		return 0;
	}
	sprintf(path, "textbin_%s\\%s.res", "german", ((TextBank_42d6b0*)g_149d120)[idx].name);
	f = vfs_Tfopen(path, "rb", g_6b7fdc);
	if (f == 0) {
		return 0;
	}
	fcn_00430a80(f, 0, 0);
	vfs_ReadData((char*)&n, 4, 1, f);
	vfs_ReadData((char*)&((TextBank_42d6b0*)g_149d120)[idx].first, 4, 1, f);
	vfs_ReadData((char*)&((TextBank_42d6b0*)g_149d120)[idx].count, 4, 1, f);
	ofs = m_alloc(n * 4, "txt_txt:txt_ReloadTextFile:PointerTable");
	vfs_ReadData((char*)ofs, n * 4, 1, f);
	for (i = 0; i < n; i++) {
		vfs_ReadData(g_1053000[((TextBank_42d6b0*)g_149d120)[idx].first + i], 0x50, 1, f);
	}
	for (i = 0; i < n; i++) {
		vfs_ReadData((char*)&g_11bb000[((TextBank_42d6b0*)g_149d120)[idx].first + i], 1, 1, f);
	}
	vfs_ReadData((char*)&size, 4, 1, f);
	((TextBank_42d6b0*)g_149d120)[idx].text = (char*) m_alloc(size, "txt_txt:txt_ReloadTextFile:Pointer");
	vfs_ReadData(((TextBank_42d6b0*)g_149d120)[idx].text, size, 1, f);
	for (i = 0; i < n; i++) {
		g_14a5320[((TextBank_42d6b0*)g_149d120)[idx].first + i] = ((TextBank_42d6b0*)g_149d120)[idx].text + ofs[i];
	}
	CloseVfsStream(f);
	m_FreeTracked(ofs);
	return 1;
}
