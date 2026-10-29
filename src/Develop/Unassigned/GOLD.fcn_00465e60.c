/* ADDRESS: GOLD 0x00465e60 */
void __cdecl fcn_00465e60(char *p)
{
	int i;

	for (i = 0; i < 0x11e; i++)
		*(unsigned short *) (p + 0x8c + i * 4) = 0;
	for (i = 0; i < 0x1e; i++)
		*(unsigned short *) (p + 0x980 + i * 4) = 0;
	for (i = 0; i < 0x13; i++)
		*(unsigned short *) (p + 0xa74 + i * 4) = 0;
	*(int *) (p + 0x16a4) = 0;
	*(int *) (p + 0x16a0) = 0;
	*(int *) (p + 0x16a8) = 0;
	*(int *) (p + 0x1698) = 0;
	*(unsigned short *) (p + 0x48c) = 1;
}
