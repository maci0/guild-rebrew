#include <string.h>

struct VFS_DIR;
extern struct VFS_DIR* g_6b7fdc;
extern int g_6b7f98;

extern int __cdecl CloseVfsStream(void* stream);
extern int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);
extern int __cdecl vfs_fseek(char* stream, int offset, int origin);
extern void* __cdecl vfs_Tfopen(char* path, char* mode, struct VFS_DIR* root);
extern void* __cdecl m_alloc(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* ptr);
extern int __cdecl fcn_0064d41a(char* buf, const char* fmt, ...);
extern int __cdecl fcn_0041d9e0(char* text);

/* Loader of one text table set: finds the next free name slot, opens the
 * record file for it, then reads counts, pointer tables and record payloads
 * into the slot. Native body ends at 0x42dabe (extent 0x240). */
/* ADDRESS: GOLDTL 0x0042d880 */
unsigned int __cdecl fcn_0042d880(char* name)
{
	int a;
	int b;
	void* table;
	int* pcount;
	int* pc;
	char path[0x104];
	char msg[0x100];
	char* rec;
	void* stream;
	int count;
	int i;

	a = 0;
	b = 0;
	count = 0;
	rec = (char*) 0x149d120;
	while (*rec != 0) {
		rec += 0x74;
		count++;
		if ((int) rec >= 0x14a0b20)
			return 0;
	}
	if (count >= 0x80)
		return 0;
	fcn_0064d41a(path, "textbin_%s\\%s.res", "german", name);
	stream = vfs_Tfopen(path, "rb", g_6b7fdc);
	if (stream == 0) {
		fcn_0064d41a(msg, "Could not open textfile:%s", path);
		fcn_0041d9e0(msg);
		return 0;
	}
	vfs_fseek(stream, 0, 0);
	rec = (char*) (0x149d120 + count * 0x74);
	pc = (int*) (rec + 0x60);
	strcpy(rec, name);
	vfs_ReadData((char*) &a, 4, 1, stream);
	vfs_ReadData((char*) pc, 4, 1, stream);
	pcount = (int*) (rec + 0x64);
	vfs_ReadData((char*) pcount, 4, 1, stream);
	table = m_alloc(a * 4, "txt_txt:txt_loadTextFile:PointerTable");
	vfs_ReadData(table, 4, a, stream);
	for (i = 0; i < a; i++)
		vfs_ReadData((char*) ((*(int*) (rec + 0x60) + i) * 0x50 + 0x1053000),
		    0x50, 1, stream);
	for (i = 0; i < a; i++)
		vfs_ReadData((char*) ((*(int*) (rec + 0x60) + i) * 4 + 0x11bb000),
		    1, 1, stream);
	vfs_ReadData((char*) &b, 4, 1, stream);
	*(int*) (rec + 0x68) = (int) m_alloc(b, "txt_txt:txt_loadTextFile:Pointer");
	vfs_ReadData((char*) *(int*) (rec + 0x68), b, 1, stream);
	for (i = 0; i < a; i++)
		*(int*) ((*pc) * 4 + 0x14a5320 + i * 4) =
		    *(int*) ((char*) table + i * 4) + *(int*) (rec + 0x68);
	if (g_6b7f98 + 1 < *pcount)
		g_6b7f98 = *pcount + 1;
	CloseVfsStream(stream);
	m_FreeTracked(table);
	return 1;
}
