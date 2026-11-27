/* ADDRESS: GOLD 0x0047cb60 */
int __cdecl d2_GetResourceBankEntry(int obj, unsigned int idx)
{
	if (obj == 0) {
		return 0;
	}
	return *(int*) (obj + 0x45 + (idx & 0xffff) * 4) + obj;
}
