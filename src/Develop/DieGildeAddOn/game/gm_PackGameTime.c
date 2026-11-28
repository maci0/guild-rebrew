
/* ADDRESS: GOLDTL 0x00500d60 */
/* ADDRESS: GOLDDE 0x004ec4a0 */
void __cdecl gm_PackGameTime(int* src, char* dst)
{
	*(short*) (dst + 2) = (short) *src + 0x578;
	dst[1] = (char) (*src % 4) * 3 + 1;
	dst[0] = 1;
	dst[4] = ((char*) src)[4];
	dst[5] = ((char*) src)[6];
	*(int*) (dst + 6) = *(int*) ((char*) src + 0xa);
}
