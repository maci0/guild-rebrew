

extern char d3_Universes[];

/* ADDRESS: GOLDDE 0x00411900 */
int __cdecl d3_GetContextIndex(char* p)
{
	int r;

	r = (unsigned int) (p - d3_Universes) / 988;
	if (r < 0 || r > 0x3f) {
		r = -1;
	}
	return r;
}
