extern char* g_6b7e94;
// FUNCTION: GOLD 0x0042b010
// FUNCTION: GOLDTL 0x4298e0

void __cdecl fcn_00429d30(void*);

void __cdecl fcn_004298e0(void)
{
	int o;
	char* p;

	for (o = 0; o < 0x64c00; o += 0xc98) {
		p = (char*) (*(int*) ((char*)&g_6b7e94) + o);
		if (*(unsigned char*) p != 0 || *(int*) (p + 0x100) != -1) {
			fcn_00429d30(p);
		}
	}
}
