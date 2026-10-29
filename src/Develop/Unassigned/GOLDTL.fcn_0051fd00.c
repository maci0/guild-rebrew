extern unsigned int g_6b5c20;

/* ADDRESS: GOLDTL 0x0051fd00 */
unsigned int __cdecl fcn_0051fd00(unsigned int action)
{
	unsigned int idx;

	if (action != 0) {
		idx = (action - g_6b5c20) / 0x194u;
	} else {
		idx = 0xffffffffu;
	}
	return idx;
}
