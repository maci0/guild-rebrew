/* Decoder-shaped routine: builds an eight-entry float palette from the two
   leading bytes of the source record (scaled by the constant at 0x662c30),
   then expands the two 24-bit packed indices in bytes 2..7 through that
   palette into the two 16-byte-stride float arrays at out+0xc / out+0x8c. */

extern int __cdecl fcn_00633144(void* out, void* src);

/* ADDRESS: GOLDTL 0x00633305 */
int __cdecl fcn_00633305(unsigned char* out, unsigned char* src)
{
	float f[8];
	float scale;
	unsigned v;
	int i;
	int r;

	r = fcn_00633144(out, src + 8);
	if (r < 0) {
		return r;
	}
	scale = *(float*) 0x662c30;
	f[0] = (float) src[0] * scale;
	f[1] = (float) src[1] * scale;
	if (src[0] > src[1]) {
		for (i = 1; i < 7; i++) {
			f[i + 1] = ((float) (7u - (unsigned) i) * f[0] + (float) (unsigned) i * f[1]) * *(float*) 0x662dbc;
		}
	} else {
		for (i = 1; i < 5; i++) {
			f[i + 1] = ((float) (5u - (unsigned) i) * f[0] + (float) (unsigned) i * f[1]) * *(float*) 0x6629d0;
		}
		f[6] = 0.0f;
		f[7] = 1.0f;
	}
	v = (unsigned) src[2] | ((unsigned) src[3] << 8) | ((unsigned) src[4] << 16);
	for (i = 0; i < 8; i++) {
		*(float*) ((char*) out + 0xc + i * 0x10) = f[v & 7];
		v >>= 3;
	}
	v = (unsigned) src[5] | ((unsigned) src[6] << 8) | ((unsigned) src[7] << 16);
	for (i = 0; i < 8; i++) {
		*(float*) ((char*) out + 0x8c + i * 0x10) = f[v & 7];
		v >>= 3;
	}
	return 0;
}
