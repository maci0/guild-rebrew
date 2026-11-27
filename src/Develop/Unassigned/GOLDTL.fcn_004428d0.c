typedef struct Nibbles {
	unsigned char lo : 4;
	unsigned char hi : 4;
} Nibbles;
// SIZE 0x1

void __cdecl d3_UpdateFloorLighting(char* a);

/* ADDRESS: GOLDTL 0x004428d0 */
void __cdecl fcn_004428d0(char* a, unsigned char v, char update)
{
	if (((Nibbles*) (a + 0x8037))->lo != v) {
		((Nibbles*) (a + 0x8037))->lo = v;
		if (update) {
			d3_UpdateFloorLighting(a);
		}
	}
}
