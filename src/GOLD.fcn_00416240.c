// SIZE 0x54
struct key_416240 {
	float gain;
	float decay;
	char pad8[8];
	float dir[3];
	float peak;
	char pad20[0x10];
	unsigned int start;
	char pad34[4];
	float out[3];
	char pad44[0xb];
	unsigned char level;
	char pad50;
	unsigned char active : 1;
	char pad52[2];
};

// SIZE 0xd4
struct track_416240 {
	float scale;
	char pad4[0x1c];
	unsigned int length;
	char pad24[4];
	struct key_416240* keys;
	char pad2c[0xa4];
	int count;
};

// FUNCTION: GOLD 0x416240
// SIZE: 252
int __cdecl fcn_00416240(struct track_416240* tr, unsigned int t)
{
	struct key_416240* k;
	float f;
	int idle;
	int i;

	idle = 0;
	i = 0;
	k = tr->keys;
	for (; i < tr->count; i++, k++) {
		if (t >= k->start && t <= k->start + tr->length) {
			f = (float) (t - k->start) / (float) tr->length;
			k->out[0] = f * k->dir[0];
			k->out[1] = f * k->dir[1];
			k->out[2] = f * k->dir[2];
			if (f < k->peak) {
				k->level = (unsigned char) (k->gain * tr->scale * f);
			} else {
				k->level = (unsigned char) ((1.0 - (f - k->peak) * k->decay) * tr->scale);
			}
			k->active = 1;
		} else {
			k->active = 0;
		}
		if (!k->active) {
			idle++;
		}
	}
	return idle < tr->count;
}
