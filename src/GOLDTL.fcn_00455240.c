extern int g_6b8014;
// FUNCTION: GOLDTL 0x455240

void __cdecl fcn_004557c0(void*, int, int, void*);
void __cdecl fcn_004519d0(void*, int);

void __cdecl fcn_00455240(void* a1, int a2)
{
	char buf[0x40];

	fcn_004557c0(a1, (*(unsigned char*) ((char*) a1 + 0x214) & 0x20) ? 0 : g_6b8014,
	    1, buf);
	fcn_004519d0(buf, a2);
}
