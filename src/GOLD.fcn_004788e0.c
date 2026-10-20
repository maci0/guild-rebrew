/* ADDRESS: GOLD 0x004788e0 */
void __cdecl fcn_004788e0(int a)
{
	int* p;

	if (*(int*) 0xf8aa84 < 1)
		return;
	if (a < 0)
		return;
	p = (int*) (0xf8a680 + a * 16);
	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
	p[3] = 0;
	*(int*) 0xf8aa84 = *(int*) 0xf8aa84 - 1;
}
