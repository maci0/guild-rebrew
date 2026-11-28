
/* ADDRESS: GOLDTL 0x0047b620 */
/* ADDRESS: GOLDDE 0x0046a610 */
int __cdecl d2_GetBankEntry(char* p, int i)
{
	if (i >= *(unsigned short*) (p + 4)) {
		return 0;
	}
	return *(int*) (*(int*) (p + 0x18) + i * 4);
}
