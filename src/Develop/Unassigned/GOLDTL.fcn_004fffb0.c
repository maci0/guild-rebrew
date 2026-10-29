extern char g_7f4caa[];
extern char g_7f4caa[];
extern char g_7f4cc0[];
extern char g_7f4cc0[];

/* ADDRESS: GOLD 0x004fd7e0 */
/* ADDRESS: GOLDTL 0x004fffb0 */
int __cdecl fcn_004fffb0(int a1)
{
	unsigned short w;
	unsigned int i;
	int v;

	i = (unsigned int) a1 & 0xffff;
	w = *(unsigned short*) (g_7f4caa + i * 540);
	v = w;
	return v < *(float*) (g_7f4cc0 + i * 540);
}
