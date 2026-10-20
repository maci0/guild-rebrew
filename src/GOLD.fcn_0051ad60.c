extern unsigned int g_6b5c20;

/* ADDRESS: GOLD 0x0051ad60 */
unsigned int __cdecl fcn_0051ad60(unsigned int action)
{
	unsigned int idx;

	if (action != 0) {
		idx = (action - g_6b5c20) / 0x194u;
	} else {
		idx = 0xffffffffu;
	}
	return idx;
}
