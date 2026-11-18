extern char g_774a80[];
extern char g_6ab49c[];


int  __cdecl fcn_0051e070(void);
void __cdecl io_FormatTextBuffer(void*, int, int, int, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2cb0(void* entity, void* otherEntity, int a3, int a4, int a5, int a6)
{
	char t;

	t = *(char*) ((char*) entity + 2);
	if (t == 6 || t == 7) {
		switch (fcn_0051e070()) {
		case 0:
		case 2:
			io_FormatTextBuffer(g_774a80, 0x414e, *(unsigned short*) otherEntity, a3,
			    *(int*) (0x665f78 + a4 * 4), a5, a6);
			break;
		case 1:
			io_FormatTextBuffer(g_774a80, 0x414e, *(unsigned short*) otherEntity,
			    *(int*) (0x665f78 + a4 * 4), a3, a5, a6);
			break;
		}
		fcn_00545d40(*(int*) ((char*) entity + 4), -1, g_774a80, 0, 0x5fc, g_6ab49c);
	}
}
