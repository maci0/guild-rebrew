
/* ADDRESS: GOLDTL 0x00420200 */
void __cdecl msx_SetFadeDuration(int v)
{
	*(int*) 0x678168 = v;
}
