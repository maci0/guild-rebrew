typedef struct Vec3i {
	int x;
	int y;
	int z;
} Vec3i;

/* ADDRESS: GOLDTL 0x00408250 */
/* ADDRESS: GOLDDE 0x004073f0 */
void __cdecl ch_CopyMapBounds(Vec3i* dst, Vec3i* src)
{
	*dst = *src;
}
