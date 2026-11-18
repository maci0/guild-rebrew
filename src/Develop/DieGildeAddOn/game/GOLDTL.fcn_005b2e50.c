extern int g_665f78[];
extern int g_665f78[];
extern char g_774a80[];
extern char g_6b5c60[];



int  __cdecl fcn_0051e070(void);
void __cdecl io_FormatTextBuffer(void*, int, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2e50(void* entity, void* otherEntity, int a3, int tableIndex)
{
	char t;

	t = *(char*) ((char*) entity + 2);
	if (t == 6 || t == 7) {
		switch (fcn_0051e070()) {
		case 0:
		case 2:
			io_FormatTextBuffer(g_774a80, 0x4150, *(unsigned short*) otherEntity, a3,
			    g_665f78[tableIndex]);
			break;
		case 1:
			io_FormatTextBuffer(g_774a80, 0x4150, *(unsigned short*) otherEntity,
			    g_665f78[tableIndex], a3);
			break;
		}
		fcn_00545d40(*(int*) ((char*) entity + 4), -1, g_774a80, 0, 0x5fc, g_6b5c60);
	}
}
