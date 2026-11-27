#include <stdio.h>

extern void* __cdecl m_alloc(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* ptr);
extern int __cdecl ReportClientMessage(char* text);
unsigned int __cdecl vfs_ReadData(void* buffer, unsigned int size,
    unsigned int count, char* file);
char* __cdecl vfs_Tfopen(char* path, char* mode, void* root);
int __cdecl vfs_fseek(char* stream, int offset, int origin);
int __cdecl CloseVfsStream(char* stream);

/* Gold txt_loadTextFile (GOLDTL 0x42d880): loads one text table set into the
 * next free 0x74-byte name slot at 0x1431fc0. The VFS root 0x6333fc and the
 * highest id 0x6333b8 have no Gold data rows yet (DATA TODO). */
/* ADDRESS: GOLD 0x0042e530 */
unsigned int __cdecl txt_LoadTextPointerTable(char* name)
{
	int a;
	int b;
	void* table;
	int* pcount;
	int* pc;
	char path[0x104];
	char msg[0x100];
	char* rec;
	char* stream;
	int count;
	int i; char* q; char ch; int* dst; int base;

	i = 0;
	count = 0;
	a = 0;
	b = 0;
	rec = (char*) 0x1431fc0;
	do {
		if (*rec == 0)
			goto found;
		rec += 0x74;
		count++;
	} while ((int) rec < 0x14359c0);
	return 0;
found:
	if (count >= 0x80)
		return 0;
	sprintf(path, "textbin_%s\\%s.res", "german", name);
	stream = vfs_Tfopen(path, "rb", *(void**) 0x6333fc);
	if (stream == 0) {
		sprintf(msg, "Could not open textfile:%s", path);
		ReportClientMessage(msg);
		return 0;
	}
	vfs_fseek(stream, 0, 0);
	rec = (char*) (0x1431fc0 + count * 0x74);
	pc = (int*) (rec + 0x60);
	q = name; do { ch = *q; rec[q - name] = ch; q++; } while (ch);
	vfs_ReadData(&a, 4, 1, stream);
	vfs_ReadData(pc, 4, 1, stream);
	pcount = (int*) (rec + 0x64);
	vfs_ReadData(pcount, 4, 1, stream);
	table = m_alloc(a * 4, "txt_txt:txt_loadTextFile:PointerTable");
	vfs_ReadData(table, 4, a, stream);
	for (i = 0; i < a; i++)
		vfs_ReadData((char*) ((*pc + i) * 0x50 + 0xfe7e40),
		    0x50, 1, stream);
	for (i = 0; i < a; i++)
		vfs_ReadData((char*) ((*pc + i) * 4 + 0x114fe60),
		    1, 1, stream);
	vfs_ReadData(&b, 4, 1, stream);
	*(int*) (rec + 0x68) = (int) m_alloc(b, "txt_txt:txt_loadTextFile:Pointer");
	vfs_ReadData((char*) *(int*) (rec + 0x68), b, 1, stream);
	if (a > 0) { dst = (int*) ((*pc) * 4 + 0x143a1c0); base = *(int*) (rec + 0x68); for (i = 0; i < a; i++, dst++)
		*dst =
		    ((int*) table)[i] + base; }
	if (*pcount > *(int*) 0x6333b8 + 1)
		*(int*) 0x6333b8 = *pcount + 1;
	CloseVfsStream(stream);
	m_FreeTracked(table);
	return 1;
}
