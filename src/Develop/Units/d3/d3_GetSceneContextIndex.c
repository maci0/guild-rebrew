extern char d3_Universes[];

/* ADDRESS: GOLD 0x00411be0 */
int __cdecl d3_GetSceneContextIndex(char* p)
{
	int r;

	r = (unsigned int) (p - d3_Universes) / 992;
	if (r < 0 || r > 0x3f) {
		r = -1;
	}
	return r;
}
