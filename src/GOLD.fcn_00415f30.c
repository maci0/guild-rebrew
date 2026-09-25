#include <math.h>

// SIZE 0x54
struct key_415f30 {
	char pad0[0x10];
	float dir[3];
	char pad1c[0x14];
	unsigned int start;
	char pad34[4];
	float out[3];
	char pad44[4];
	float gain;
	char pad4c[3];
	unsigned char level;
	char pad50[4];
};

// SIZE 0xe8
struct track_415f30 {
	char pad0[8];
	float lift;
	char padc[0x14];
	unsigned int length;
	char pad24[4];
	struct key_415f30* keys;
	char pad2c[0xa4];
	int count;
	char padd4[0x10];
	float volume;
};

// FUNCTION: GOLD 0x415f30
// SIZE: 266
int __cdecl fcn_00415f30(struct track_415f30* tr, unsigned int t)
{
	struct key_415f30* k;
	float f;
	int i;

	k = tr->keys;
	f = (float) (t - k->start) / (float) tr->length;
	if (f >= 0.0 && f <= 1.0) {
		f = 1.0f - ((float) cos((f + 1.0f) * 1.5707964f) + 1.0f);
		for (i = 0; i < tr->count; i++) {
			k[i].out[0] = f * k[i].dir[0];
			k[i].out[1] = (k[i].dir[1] + tr->lift) * f;
			k[i].out[2] = f * k[i].dir[2];
			k[i].gain = (f * 0.4f + 1.0f) * tr->volume;
			k[i].level = (unsigned char) ((1.0f - f) * 255.0f);
		}
	}
	return t < tr->keys->start + tr->length;
}
