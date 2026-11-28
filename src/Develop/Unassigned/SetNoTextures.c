/* ADDRESS: GOLDTL 0x0040f530 */
/* ADDRESS: GOLDDE 0x0040e330 */
int __cdecl SetNoTextures(int *value)
{
	*(int *) 0x6b8019 = *value;
	return 1;
}
