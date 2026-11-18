extern char* g_5fb5b0;
extern int g_fb9598, g_fb98f4;

/* ADDRESS: GOLD 0x004556d0 */
void __cdecl fcn_004556d0(char* node)
{
	char* prev;
	char* owner;

	prev = *(char**) (node + 0x318);
	owner = *(char**) (node + 0x2f0);
	if (prev == (char*) 0xfb95e0) {
		*(int*) (owner + 0xa4) = *(int*) (node + 0x314);
	} else {
		*(int*) (prev + 0x314) = *(int*) (node + 0x314);
	}
	prev = *(char**) (node + 0x314);
	if (prev == (char*) 0xfb9280) {
		*(int*) (owner + 0xa8) = *(int*) (node + 0x318);
	} else {
		*(int*) (prev + 0x318) = *(int*) (node + 0x318);
	}
	if (owner == g_5fb5b0) {
		g_fb98f4 = *(int*) (owner + 0xa4);
		g_fb9598 = *(int*) (owner + 0xa8);
	}
}
