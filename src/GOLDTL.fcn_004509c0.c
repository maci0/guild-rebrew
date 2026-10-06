extern char* g_6b86e8;
extern int g_6b8708;
extern int g_6b8704;

void __cdecl fcn_004508a0(char* p);

// FUNCTION: GOLDTL 0x4509c0
void __cdecl fcn_004509c0(void)
{
	char* p;

	for (p = g_6b86e8; p != 0 && g_6b8708 < g_6b8704; p = *(char**) (p + 0x1f0)) {
		if (*(int*) (p + 0x218) == 6) {
			fcn_004508a0(p);
		}
	}
}
