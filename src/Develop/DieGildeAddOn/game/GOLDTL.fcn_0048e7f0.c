unsigned short* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...);


/* ADDRESS: GOLDTL 0x0048e7f0 */
int __cdecl fcn_0048e7f0(char* e, unsigned short** out)
{
	unsigned short* r;

	if (e[2] == 3)
		return 0;
	r = gm_StartFilteredEntitySearch(2, 5, 0x21, 4, *(unsigned short*) e);
	if (out != 0)
		*out = r;
	if (r != 0)
		return 2;
	if (e[2] == 5)
		return 1;
	if ((e[2] == 2 || e[2] == 4) && (unsigned char) e[0xd] > 6)
		return 1;
	return 0;
}
