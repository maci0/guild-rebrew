extern char g_774a80[];
extern char g_6b5c60[];



void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2c60(void* a1, int a2)
{
	char t;

	t = *(char*) ((char*) a1 + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(g_774a80, 0x4154, a2);
		fcn_00545d40(*(int*) ((char*) a1 + 4), -1, g_774a80, 0, 0x5fc, g_6b5c60);
	}
}
