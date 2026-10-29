typedef struct Tint {
	unsigned char level;  /* 0x0 */
	unsigned char pad1;   /* 0x1 */
	unsigned char pad2_0 : 1;   /* 0x2 bit 0 */
	unsigned char flag   : 1;   /* 0x2 bit 1 */
	unsigned char pad2_hi : 6;  /* 0x2 bits 2-7 */
	unsigned char pad3;   /* 0x3 */
} Tint;

int __cdecl fcn_0045c5b0(char* name, Tint tint, int a, int b);
void __cdecl fcn_0045ce90(int h);

/* Loads a texture/animation with a default tint: level 0x7f and the bit-1
 * bitfield of byte 2 set from the flag argument, then frees the handle.
 * The reference reads, masks and rewrites byte 2 in place (add cl,cl / xor /
 * and cl,2 / xor), which is cl's one-bit bitfield assignment, not a whole-byte
 * xor; keep the bitfield in Tint. */
/* ADDRESS: GOLDTL 0x0047ce00 */
int __cdecl fcn_0047ce00(char* name, unsigned char flag)
{
	Tint tint;
	int h;

	*(int*) &tint = 0;
	tint.level = 0x7f;
	tint.flag = flag;
	h = fcn_0045c5b0(name, tint, 0, 0);
	if (h != 0) {
		fcn_0045ce90(h);
	}
	return h;
}
