/* ADDRESS: GOLD 0x00438c30 */
char* __cdecl fcn_00438c30(char* node)
{
	int mode;

	mode = *(int*) (node + 0x1f8);
	node = *(char**) (node + 0x1f0);
	if (mode == 0) {
		while (node != 0 && (node[0x210] & 1) == 0) {
			node = *(char**) (node + 0x1f0);
		}
	}
	return node;
}
