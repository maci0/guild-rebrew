extern char* g_6b7e94;

extern int __cdecl fcn_00428720(char*);

/* ADDRESS: GOLDTL 0x004287c0 */
void __cdecl fcn_004287c0(void)
{
	int i;
	char* p;

	for (i = 0; i < 0x64c00; i += 0xc98) {
		p = g_6b7e94 + i;
		if (*(unsigned char*) p != 0 || *(int*) (p + 0x100) != -1) {
			fcn_00428720(p);
		}
	}
}
