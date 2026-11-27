/* ADDRESS: GOLD 0x004ef710 */
int __cdecl gv_IsSameField(void* a0, void* a1)
{
	unsigned short id;

	id = *(unsigned short*) ((char*) a0 + 0x50);
	if (*(unsigned short*) ((char*) a1 + 8) == id && id != 0x7fff) {
		return 1;
	}
	return 0;
}
