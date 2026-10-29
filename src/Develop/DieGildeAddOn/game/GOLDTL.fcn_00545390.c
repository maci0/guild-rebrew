extern char g_6a56d0[];
extern char g_7f4cd0[];


void __cdecl fcn_0064d41a(void*, void*, int, void*);

void __cdecl he_AllocNone(void* a1)
{
	char buf[0x100];
	unsigned int idx;

	idx = *(unsigned short*) ((char*) a1 + 8);
	fcn_0064d41a(buf, g_6a56d0, *(unsigned char*) a1, g_7f4cd0 + idx * 0x21c);
}
