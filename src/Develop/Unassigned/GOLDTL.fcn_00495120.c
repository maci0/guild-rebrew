
/* ADDRESS: GOLDTL 0x00495120 */
void __cdecl fcn_00495120(int v)
{
	int i;

	i = *(int*) 0x1008524;
	((int*) 0x100af80)[i] = v;
	*(int*) 0x1008524 = i + 1;
}
