

extern char* g_6b7ebc;
extern char* g_6b7e98;
int __cdecl m_is_tracked(char* p);
void __cdecl fcn_0040b920(char* a, char* b);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040cba0(char** a, char** b)
{
	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) fcn_0040cba0) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040cba0;
		}
		return 0;
	}
	if (*b == 0 || *a == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	if (!m_is_tracked(*b)) {
		return 0;
	}
	if (!m_is_tracked(*a)) {
		return 0;
	}
	fcn_0040b920(*a, *b);
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040cba0;
	}
	return 1;
}
