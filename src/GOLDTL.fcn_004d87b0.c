// GLOBAL: GOLDTL 0x772ea4
extern int g_772ea4;
// FUNCTION: GOLDTL 0x4d87b0
// SIZE: 61

int __cdecl fcn_00508e40(int);
void __cdecl fcn_0051af00(void*, int, int);
void __cdecl fcn_00533a40(void*);

void __cdecl fcn_004d87b0(void* a1)
{
	char buf[0x100];

	g_772ea4 = fcn_00508e40(*(int*) a1);
	fcn_0051af00(buf, 0x11b7, *(unsigned short*) g_772ea4);
	fcn_00533a40(buf);
}
