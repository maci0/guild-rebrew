


/* fcn_005743b0: return fcn_005463a0(2, 0, 0x9f, 2, *(unsigned short*)a) != 0. */

int __cdecl he_StartHandlungSearch(int, int, int, int, int);

/* ADDRESS: GOLDDE 0x00562720 */
int __cdecl he_HasZigeunerAction0x9f(char* entity)
{
	return he_StartHandlungSearch(2, 0, 0x9f, 2, *(unsigned short*) entity) != 0;
}

