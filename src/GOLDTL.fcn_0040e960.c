extern char* g_6b7e98;
/* ADDRESS: GOLD 0x005f26a4 */
extern char g_676724[];



void __cdecl fcn_00438b40(char*, char*);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040e960(char** a1, int* a2, int* a3, int* a4)
{
	if (*a1 != 0) {
		*(int*) (*a1 + 0x4c) = *a2;
		*(int*) (*a1 + 0x50) = *a3;
		*(int*) (*a1 + 0x54) = *a4;
		fcn_00438b40(*a1, *a1 + 0x4c);
		return 0;
	}
		fcn_00425bf0(g_6b7e98, *(int*) ((char*) g_6b7e98 + 0x118), g_676724);
	return 0;
}
