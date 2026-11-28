
/* ADDRESS: GOLDTL 0x004f17f0 */
/* ADDRESS: GOLDDE 0x004dd8e0 */
int __cdecl gv_MatchEntityGraveyardSlot(char* a1, char* a2)
{
	unsigned short v;

	v = *(unsigned short*) (a1 + 0x50);
	if (*(unsigned short*) (a2 + 8) == v && v != 0x7fff) {
		return 1;
	}
	return 0;
}
