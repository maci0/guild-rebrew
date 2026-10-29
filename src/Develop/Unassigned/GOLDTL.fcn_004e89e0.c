extern unsigned short g_7f4c04;

#ifdef REBREW_GOLD
#define BASE_A 0x925134
#define END_A  0x925524
#define BASE_B 0x92512c
#define END_B  0x92551c
#else
#define BASE_A 0x9a9234
#define END_A  0x9a9624
#define BASE_B 0x9a922c
#define END_B  0x9a961c
#endif

/* ADDRESS: GOLDTL 0x004e89e0 */
void __cdecl fcn_004e89e0(char* obj, int flag)
{
	int a;
	int v;
	unsigned short w;

	w = g_7f4c04;
	a = BASE_A;
	do {
		v = *(int*) (obj + 4);
		if (*(int*) (a - 0x10) == v && flag != 0) {
			*(int*) (a - 0x10) = -1;
			*(int*) (a - 8) = 0;
			*(unsigned char*) (a - 4) = (unsigned char) ((w > 0xb) + 3);
		} else if (*(int*) a == v) {
			*(unsigned char*) (a - 4) = 1;
		} else {
			a += 0x18;
			continue;
		}
		*(int*) a = -1;
		a += 0x18;
	} while (a < END_A);
	if (*(unsigned char*) (obj + 0x168) != 0) {
		a = BASE_B;
		do {
			if (*(unsigned char*) (a - 4) == *(unsigned char*) (obj + 0x168) && *(int*) a > 0) {
				*(int*) a = *(int*) a - 1;
			}
			a += 0x18;
		} while (a < END_B);
	}
	*(unsigned char*) (obj + 0x168) = 0;
	if (flag != 0) {
		*(unsigned char*) (obj + 0x166) = 0;
		*(unsigned char*) (obj + 0x169) = 0;
	}
}
