
extern char* g_6b7ebc;
extern char* g_6b7e98;
char* __cdecl CreateAnimationEvent(char* owner, char* name);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040d790(char** a, char** v)
{
	char* r;

	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) fcn_0040d790) {
		if (*(int*) (*a + 0x128) != 0) {
			*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040d790;
		}
		return 0;
	}
	if (*a == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 1;
	}
	r = CreateAnimationEvent(*a, *v);
	if (r != 0) {
		*(int*) (r + 0x18c) |= 1;
	}
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040d790;
	}
	return 0;
}
