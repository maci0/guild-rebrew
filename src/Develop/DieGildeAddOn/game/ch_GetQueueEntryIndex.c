extern char* g_6b5c20;

/* ADDRESS: GOLDTL 0x0051fd00 */
unsigned int __cdecl ch_GetQueueEntryIndex(unsigned int action)
{
	unsigned int idx;

	if (action != 0) {
		idx = (action - (unsigned int) g_6b5c20) / 0x194u;
	} else {
		idx = 0xffffffffu;
	}
	return idx;
}
