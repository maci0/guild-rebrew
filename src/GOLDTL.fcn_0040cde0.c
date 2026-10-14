


extern char* g_6b7ebc;
extern char* g_6b7e98;
int __cdecl fcn_00406340(char* e, char* name, int param);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040cde0(char** a, char** name, int* param)
{
	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) fcn_0040cde0) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040cde0;
		}
		return 0;
	}
	if (*a == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 1;
	}
	fcn_00406340(*a, *name, *param);
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040cde0;
	}
	return 0;
}
