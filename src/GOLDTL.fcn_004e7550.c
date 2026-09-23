// GLOBAL: GOLDTL 0x68d924
extern char g_68d924[];
// FUNCTION: GOLDTL 0x4e7550
// SIZE: 68

void __cdecl fcn_0064d41a(void*, void*, int, int, int, int, int);

void __cdecl fcn_004e7550(void* a1, void* a2)
{
	fcn_0064d41a(a2, g_68d924,
	    *(unsigned char*) ((char*) a1 + 0x80),
	    *(unsigned char*) ((char*) a1 + 0x81),
	    *(unsigned char*) ((char*) a1 + 0x82),
	    *(unsigned char*) ((char*) a1 + 0x83),
	    *(unsigned char*) ((char*) a1 + 0x84));
}
