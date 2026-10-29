


extern char* g_aed324;
extern char* g_aed200;

void __cdecl fcn_004c4aa0(char* node)
{
	char* prev;
	char* next;

	prev = *(char**) (node + 0x91);
	if (prev != 0) {
		*(char**) (prev + 0x95) = *(char**) (node + 0x95);
	} else {
		g_aed324 = *(char**) (node + 0x95);
	}
	next = *(char**) (node + 0x95);
	if (next != 0) {
		*(char**) (next + 0x91) = *(char**) (node + 0x91);
	}
	*(char**) (node + 0x91) = 0;
	*(char**) (node + 0x95) = g_aed200;
	g_aed200 = node;
}
