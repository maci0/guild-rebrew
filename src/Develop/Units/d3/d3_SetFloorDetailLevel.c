typedef struct Nibbles {
	unsigned char lo : 4;
	unsigned char hi : 4;
} Nibbles;
// SIZE 0x1

void __cdecl d3_UpdateFloorLighting(char* a);

/* ADDRESS: GOLDTL 0x004428d0 */
void __cdecl d3_SetFloorDetailLevel(char* floor, unsigned char level, char update)
{
	if (((Nibbles*) (floor + 0x8037))->lo != level) {
		((Nibbles*) (floor + 0x8037))->lo = level;
		if (update) {
			d3_UpdateFloorLighting(floor);
		}
	}
}
