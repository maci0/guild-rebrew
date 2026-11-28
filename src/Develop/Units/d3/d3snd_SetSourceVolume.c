
/* ADDRESS: GOLDTL 0x004193c0 */
/* ADDRESS: GOLDDE 0x00417100 */
void __cdecl d3snd_SetSourceVolume(char* p, int v)
{
	*(int*) (p + 0x40) = v;
}
