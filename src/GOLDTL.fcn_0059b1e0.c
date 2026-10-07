// FUNCTION: GOLDTL 0x0059b1e0

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

extern char* g_99ec10;
extern char g_6aa380[];

int __cdecl fcn_0064d41a(char*, const char*, ...);

void __cdecl fcn_0059b1e0(char* node, int depth)
{
	char buf[0x200];
	char* c;

	if (node != 0) {
		memset(buf, ' ', sizeof(buf));
		fcn_0064d41a(buf + depth * 2, g_6aa380, g_99ec10 + *(unsigned short*) node * 65 + 1,
		    *(int*) (node + 0xe));
		for (c = *(char**) (node + 0x14); c != 0; c = *(char**) (c + 0x3f)) {
			fcn_0059b1e0(c, depth + 1);
		}
	}
}
