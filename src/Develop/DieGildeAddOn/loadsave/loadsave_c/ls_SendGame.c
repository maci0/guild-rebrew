


#include <windows.h>

extern char g_6a24d0[];
typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* g_6b7fdc;
#include "Develop/DieGildeAddOn/game/game_data.h"

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
void __cdecl vfs_fseek(void*, int, int);
int __cdecl fcn_00430c50(void*);
char* __cdecl m_alloc(int, char*);
#include "Develop/Units/vfs/vfs.h"
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);
void __cdecl m_FreeTracked(char*);
void __cdecl cm_RequestSendGameHeader(int);
int __cdecl cm_SendLoadChunk(char*);
void __cdecl main_PumpWindowMessages(void);
void __cdecl cm_StepCommandQueue(void);

int __cdecl ls_SendGame(char* path)
{
	int n;
	void* h;
	int size;
	int total;
	char* buf;
	char* p;
	int sent;

	n = 0;
	h = vfs_Tfopen(path, g_6a24d0, g_6b7fdc);
	if (h == 0) {
		return 0;
	}
	vfs_fseek(h, 0, 2);
	size = fcn_00430c50(h);
	total = (size / 128 + 1) * 128;
	vfs_fseek(h, 0, 0);
	buf = m_alloc(total, "ls_SendGame");
	if (buf == 0) {
		CloseVfsStream(h);
		return 0;
	}
	if (vfs_ReadData(buf, size, 1, h) == -1) {
		m_FreeTracked(buf);
		CloseVfsStream(h);
		return 0;
	}
	cm_RequestSendGameHeader(total);
	p = buf;
	sent = 0;
	while (sent < total) {
		if (cm_SendLoadChunk(p) != -1) {
			p += 0x80;
			sent += 0x80;
			if (n++ % 16 == 0) {
				Sleep(15);
			}
		}
		main_PumpWindowMessages();
		cm_StepCommandQueue();
	}
	while (g_1005760 != 0) {
		main_PumpWindowMessages();
		cm_StepCommandQueue();
	}
	m_FreeTracked(buf);
	CloseVfsStream(h);
	return 1;
}
