// FUNCTION: GOLDTL 0x4e5980

extern void* g_14d0020[];

void __cdecl fcn_00538060(void);
int __cdecl fcn_0042df30(void (__cdecl*)(void), int);
void __cdecl fcn_00405540(char*, int);

void __cdecl fcn_004e5980(void)
{
	char** p;

	fcn_0042df30(fcn_00538060, 1);
	for (p = ((char**)g_14d0020); (int) p < (int) (((char**)g_14d0020) + 0x300); p++) {
		if (*p != 0 && (*(unsigned char*) (*p + 0x8c) & 4) == 0) {
			fcn_00405540(*p, 1);
		}
	}
}
