/* ADDRESS: GOLDTL 0x0040f530 */
int __cdecl SetNoTextures(int *value)
{
	*(int *) 0x6b8019 = *value;
	return 1;
}
