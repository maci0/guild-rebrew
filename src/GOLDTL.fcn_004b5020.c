typedef struct {
	unsigned char kind;
	char pad1[0x21b];
} fcn_004b5020_slot;
// SIZE 0x21c

extern fcn_004b5020_slot g_7f4ca2[];

char* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...);
char* __cdecl gm_AddObjekt(void);

// FUNCTION: GOLD 0x4b4eb0
// SIZE: 80
// FUNCTION: GOLDTL 0x4b5020
// SIZE: 68

int __cdecl fcn_004b5020(void)
{
	char* p;
	unsigned short h;

	for (p = gm_StartFilteredEntitySearch(1, 6); p != 0; p = gm_AddObjekt()) {
		h = *(unsigned short*) (p + 0x27);
		if (h != 0xffff && g_7f4ca2[h].kind == 5)
			return 0;
	}
	return 1;
}
