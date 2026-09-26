// GLOBAL: GOLDTL 0x6b7fac
extern int g_6b7fac;
// GLOBAL: GOLD 0x6333cc
extern int g_6b7fac;
// FUNCTION: GOLD 0x0040af50
// SIZE: 58
// FUNCTION: GOLDTL 0x40bd80
// SIZE: 58

void __cdecl fcn_004050c0(void*);

void __cdecl fcn_0040bd80(char* a1)
{
	if (*(int*) (a1 + 0xc) == 0) {
		*(int*) (a1 + 0x34) = *(int*) ((char*)&g_6b7fac);
	}
	if (*(unsigned int*) ((char*)&g_6b7fac) > (unsigned int) (*(int*) (a1 + 0x34) + *(int*) (a1 + 0x30)) ||
	    *(unsigned char*) (a1 + 0x190) != 0) {
		fcn_004050c0(a1);
	}
}
