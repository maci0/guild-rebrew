


char* __cdecl gm_QueryEntities(int, int, int, ...);

/* ADDRESS: GOLDDE 0x0055c3d0 */
int __cdecl ahm_HasActiveLabFeature(char* e, unsigned short t)
{
	char* r;

	if (t == 0x24b || t == 0x256 || t == 0x266) {
		r = gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, t);
		if (r != 0 && *(int*) (r + 0x1c) > 0) {
			return 1;
		}
	}
	return 0;
}
