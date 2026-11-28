
/* ADDRESS: GOLDTL 0x00420200 */
/* ADDRESS: GOLDDE 0x0041d160 */
void __cdecl msx_SetFadeDuration(int v)
{
	*(int*) 0x678168 = v;
}
