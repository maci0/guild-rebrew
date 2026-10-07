extern char g_7f4ca4[];
// GLOBAL: GOLDTL 0x774970
extern unsigned short g_774970;
// GLOBAL: GOLD 0x6f25b8
extern unsigned short g_774970;
// FUNCTION: GOLD 0x004c3f90
// FUNCTION: GOLDTL 0x4c4900

int __cdecl fcn_004c5790(int, void*);

void __cdecl fcn_0053d690(void)
{
	char buf[0x7c];
	*(int*) buf = *(int*) (g_7f4ca4 + (unsigned int) (unsigned short) *(unsigned short*) ((char*)&g_774970) * 135 * 4);
	fcn_004c5790(0x13, &buf);
}
