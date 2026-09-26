// GLOBAL: GOLDTL 0x7746cc
extern char* g_7746cc;
// GLOBAL: GOLD 0x6f2310
extern char* g_7746cc;
// FUNCTION: GOLD 0x00577590
// SIZE: 67
// FUNCTION: GOLDTL 0x57fb60
// SIZE: 67

extern int* g_665f08;

int __cdecl fcn_0057fb60(void)
{
	unsigned short* p;
	unsigned short k;
	int v;

	p = ((unsigned short*)g_7746cc);
	if (p != 0) {
		k = *p;
		v = k;
		if (v >= 0x92 && (v <= 0x97 || v == 0x2db) &&
		    *(int*) ((int) g_665f08 + 0x38) == 0) {
			return k != 0x92;
		}
	}
	return -1;
}
