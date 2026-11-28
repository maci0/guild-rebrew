
/* ADDRESS: GOLDTL 0x004be320 */
/* ADDRESS: GOLDDE 0x004abea0 */
void __cdecl gm_GetChainNodeAtIndex(char* p, int count)
{
	int i;

	i = 0;
	while (p != 0 && count != i) {
		p = *(char**) (p + 0x3c);
		i++;
	}
}
