
/* ADDRESS: GOLDTL 0x00573de0 */
char __cdecl d3_CollectObjectCallback(int v, int* list)
{
	list[list[0x41] + 1] = v;
	return ++list[0x41] < 0x40;
}
