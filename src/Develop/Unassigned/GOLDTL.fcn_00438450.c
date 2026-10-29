extern int g_6b8050;
extern int g_6b8008;
extern char* g_6b8014;
extern float g_662a34;
extern int g_10432a8;
extern int g_1042a04;

int __cdecl fcn_004382e0(unsigned int a0);
void __cdecl fcn_00438100(unsigned int a0, char* a1, int a2);
char __cdecl fcn_00438270(unsigned int a0, int a1, int a2);

/* ADDRESS: GOLDTL 0x00438450 */
unsigned char __cdecl fcn_00438450(char* o)
{
	unsigned char result;
	unsigned char sel;
	unsigned char flags;
	unsigned char anim;
	int v;
	int p;
	float* dst;
	float* src;
	int i;

	result = *(volatile unsigned char*) &o | 0x40;
	g_6b8050 = g_6b8050 + 1;
	v = fcn_004382e0((unsigned int) o);
	if (v != 0) {
		g_10432a8 = g_10432a8 + *(int*) (v + 0x314);
		g_1042a04 = g_1042a04 + *(int*) (v + 0x310);
		p = *(int*) (o + 0x1ec);
		*(int*) (o + 0x1cc) = v;
		sel = (*(unsigned char*) (o + 0x214) >> 2) & 1;
		flags = (unsigned char) ((sel << 3) ^ (*(unsigned char*) (o + 0x214) & 0xf3));
		*(unsigned char*) (o + 0x214) = flags;
		if (*(int*) (p + 0xb0) == g_6b8008) {
			anim = (unsigned char) (*(unsigned char*) (p + 0x163d) | 0x40);
			*(unsigned char*) (p + 0x163d) = anim;
			return anim;
		}
		if (sel != 0 || (flags & 0x10) != 0) {
			fcn_00438100((unsigned int) o, g_6b8014, 0);
			*(unsigned char*) (p + 0x163d) = (unsigned char) fcn_00438270((unsigned int) o, v, *(int*) (o + 0x1ec) + 0x48);
			*(int*) (v + 0x300) = 0;
			*(int*) (v + 0x304) = 0;
			*(int*) (v + 0x308) = 0;
			dst = (float*) (v + 0x284);
			src = (float*) (v + 8);
			for (i = 8; i != 0; i--) {
				dst[-1] = src[-2];
				dst[0] = src[-1];
				dst[1] = src[0];
				*(float*) (v + 0x300) = src[-2] + *(float*) (v + 0x300);
				*(float*) (v + 0x304) = dst[0] + *(float*) (v + 0x304);
				*(float*) (v + 0x308) = *(float*) (v + 0x308) + dst[1];
				src += 20;
				dst += 4;
			}
			*(float*) (v + 0x300) = *(float*) (v + 0x300) * g_662a34;
			*(float*) (v + 0x304) = *(float*) (v + 0x304) * g_662a34;
			*(float*) (v + 0x308) = *(float*) (v + 0x308) * g_662a34;
		}
		return *(unsigned char*) (p + 0x163d);
	}
	return (unsigned char) result;
}
unsigned char _dpad_10421a0[2148];
