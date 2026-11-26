extern char g_774a80[];
extern char g_6ab49c[];


int  __cdecl fcn_0051e070(void);
void __cdecl io_FormatTextBuffer(void*, int, int, int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_NotifyFriedhofEvent08(void* entity, void* otherEntity, int targetPtr, int actionKind, int amount, int bonus)
{
	char t;

	t = *(char*) ((char*) entity + 2);
	if (t == 6 || t == 7) {
		switch (fcn_0051e070()) {
		case 0:
		case 2:
			io_FormatTextBuffer(g_774a80, 0x414e, *(unsigned short*) otherEntity, targetPtr,
			    *(int*) (0x665f78 + actionKind * 4), amount, bonus);
			break;
		case 1:
			io_FormatTextBuffer(g_774a80, 0x414e, *(unsigned short*) otherEntity,
			    *(int*) (0x665f78 + actionKind * 4), targetPtr, amount, bonus);
			break;
		}
		he_PostEntityMessage(*(int*) ((char*) entity + 4), -1, g_774a80, 0, 0x5fc, g_6ab49c);
	}
}
