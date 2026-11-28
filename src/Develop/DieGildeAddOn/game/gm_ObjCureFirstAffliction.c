


void __cdecl cm_RequestChangeBits(int, int, int, int, int);

/* ADDRESS: GOLDDE 0x005be300 */
int __cdecl gm_ObjCureFirstAffliction(char* entity)
{
	int afflictions;
	int clear_mask;

	afflictions = *(int*) (entity + 0x2c);
	if (afflictions != 0) {
		clear_mask = 0;
		if (afflictions & 0xf) {
			clear_mask = 7;
		}
		else if (afflictions & 0xf0) {
			clear_mask = 0x30;
		}
		else if (afflictions & 0xf00) {
			clear_mask = 0x300;
		}
		else if (afflictions & 0x3000) {
			clear_mask = 0x1000;
		}
		else if (afflictions & 0x1c000) {
			clear_mask = 0xc000;
		}
		else if (afflictions & 0xe0000) {
			clear_mask = 0x20000;
		}
		else if (afflictions & 0x700000) {
			clear_mask = 0x100000;
		}
		else if (afflictions & 0x1800000) {
			clear_mask = 0x800000;
		}
		else if (afflictions & 0x1e000000) {
			clear_mask = 0x6000000;
		}
		cm_RequestChangeBits(*(int*) (entity + 4), 0x2c, 4, 0, clear_mask);
	}
	return 1;
}
