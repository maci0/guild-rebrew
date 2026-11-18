extern char g_7f4caa[];
extern char g_7f4cc0[];

/* ADDRESS: GOLD 0x004fd7e0 */
/* ADDRESS: GOLDTL 0x004fffb0 */
int __cdecl fcn_004fffb0(int index)
{
	unsigned short w;
	unsigned int slot;
	int v;

	slot = (unsigned int) index & 0xffff;
	w = *(unsigned short*) (g_7f4caa + slot * 540);
	v = w;
	return v < *(float*) (g_7f4cc0 + slot * 540);
}
