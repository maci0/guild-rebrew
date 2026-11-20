extern int g_6b8050;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* d3_ActiveCamera;
extern float g_662a34;
extern int g_10432a8;
extern int g_1042a04;

int __cdecl fcn_004382e0(unsigned int a0);
void __cdecl d3_UpdateObjectCameraTransform(unsigned int a0, char* a1, int a2);
char __cdecl fcn_00438270(unsigned int a0, int a1, int a2);

/* ADDRESS: GOLDTL 0x00438450 */
unsigned char __cdecl fcn_00438450(char* o)
{
	unsigned char result;
	unsigned char sel;
	unsigned char flags;
	unsigned char anim;
	int transformObject;
	int p;
	float* dst;
	float* src;
	int i;

	result = *(unsigned char*) &o | 0x40;
	g_6b8050 = g_6b8050 + 1;
	transformObject = fcn_004382e0((unsigned int) o);
	if (transformObject != 0) {
		g_10432a8 = g_10432a8 + *(int*) (transformObject + 0x314);
		g_1042a04 = g_1042a04 + *(int*) (transformObject + 0x310);
		p = *(int*) (o + 0x1ec);
		*(int*) (o + 0x1cc) = transformObject;
		sel = (*(unsigned char*) (o + 0x214) >> 2) & 1;
		flags = (unsigned char) (((sel & 1) << 3) ^ (*(unsigned char*) (o + 0x214) & 0xf3));
		*(unsigned char*) (o + 0x214) = flags;
		if (*(int*) (p + 0xb0) == g_6b8008) {
			anim = (unsigned char) (*(unsigned char*) (p + 0x163d) | 0x40);
			*(unsigned char*) (p + 0x163d) = anim;
			return anim;
		}
		if (sel != 0 || (flags & 0x10) != 0) {
			d3_UpdateObjectCameraTransform((unsigned int) o, d3_ActiveCamera, 0);
			*(unsigned char*) (p + 0x163d) = (unsigned char) fcn_00438270((unsigned int) o, transformObject, *(int*) (o + 0x1ec) + 0x48);
			*(int*) (transformObject + 0x300) = 0;
			*(int*) (transformObject + 0x304) = 0;
			*(int*) (transformObject + 0x308) = 0;
			dst = (float*) (transformObject + 0x284);
			src = (float*) (transformObject + 8);
			for (i = 8; i != 0; i--) {
				dst[-1] = src[-2];
				dst[0] = src[-1];
				dst[1] = src[0];
				*(float*) (transformObject + 0x300) = src[-2] + *(float*) (transformObject + 0x300);
				*(float*) (transformObject + 0x304) = dst[0] + *(float*) (transformObject + 0x304);
				*(float*) (transformObject + 0x308) = *(float*) (transformObject + 0x308) + dst[1];
				src += 20;
				dst += 4;
			}
			*(float*) (transformObject + 0x300) = *(float*) (transformObject + 0x300) * 0.125f;
			*(float*) (transformObject + 0x304) = *(float*) (transformObject + 0x304) * 0.125f;
			*(float*) (transformObject + 0x308) = *(float*) (transformObject + 0x308) * 0.125f;
		}
		return *(unsigned char*) (p + 0x163d);
	}
	return (unsigned char) result;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_10421a0[2148];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_10421a4[28];
unsigned char _dpad_10421c4[348];
unsigned char _dpad_1042328[24];
unsigned char _dpad_1042344[500];
unsigned char _dpad_104253c[27];
unsigned char _dpad_104255b[21];
unsigned char _dpad_1042590[16];
unsigned char _dpad_10425ec[4];
unsigned char _dpad_10425f4[8];
unsigned char _dpad_1042600[1028];
#endif
