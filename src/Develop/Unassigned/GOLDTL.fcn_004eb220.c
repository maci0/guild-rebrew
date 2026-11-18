
/* ADDRESS: GOLDTL 0x004eb220 */
int __cdecl fcn_004eb220(char* entity)
{
	unsigned char kind;
	int level;

	kind = *(unsigned char*) (entity + 0x169);
	if (kind < 0x1e || kind > 0x21) {
		return 0;
	}
	if ((*(int*) (entity + 0x1c8) & 0x4000000) != 0) {
		return -1;
	}
	level = *(int*) (entity + 0x194);
	if (level < 3) {
		return -2;
	}
	return 1;
}
