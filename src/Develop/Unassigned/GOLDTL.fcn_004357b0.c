#include <math.h>

// SIZE 0xc0
struct frame_4357b0 {
	char pad0[4];
	int length;
	char pad8[0xb8];
};

// SIZE 0x160
struct anim_4357b0 {
	char pad0[0x148];
	int count;
	char pad14c[0x10];
	struct frame_4357b0* frames;
};

// SIZE 0x70
struct blend_4357b0 {
	int cur;
	int next;
	int time;
	char padc[0x58];
	float weight;
	struct anim_4357b0* anim;
	char pad6c;
	unsigned char flags;
	char pad6e[2];
};

/* ADDRESS: GOLDTL 0x004357b0 */
void __cdecl fcn_004357b0(struct blend_4357b0* b, float* w0, float* w1)
{
	struct anim_4357b0* an;
	float step;
	float f;
	float a;
	float c;

	an = b->anim;
	if (b->flags & 2) {
		step = 1.0f / an->frames[b->next].length;
		f = b->time * step;
		if (b->flags & 4) {
			if (an->count <= 2) {
				if (b->next <= 0) {
					f = 1.0f - ((float) cos(f * 3.1415927f) + 1.0f) * 0.5f;
				} else if (b->cur >= an->count - 1) {
					f = 1.0f - ((float) cos((f + 1.0f) * 1.5707964f) + 1.0f);
				}
			} else {
				if (b->next <= 0) {
					f = 1.0f - (float) cos(f * 1.5707964f);
				} else if (b->cur >= an->count - 1) {
					f = 1.0f - ((float) cos((f + 1.0f) * 1.5707964f) + 1.0f);
				}
			}
		}
		c = f - step * b->weight;
		a = 1.0f - c;
	} else {
		step = 1.0f / an->frames[b->cur].length;
		f = b->time * step;
		if (b->flags & 4) {
			if (an->count <= 2 && b->cur + 1 >= an->count - 1) {
				f = 1.0f - ((float) cos(f * 3.1415927f) + 1.0f) * 0.5f;
			} else if (b->next >= an->count - 1) {
				f = 1.0f - ((float) cos((f + 1.0f) * 1.5707964f) + 1.0f);
			} else if (b->cur <= 0) {
				f = 1.0f - (float) cos(f * 1.5707964f);
			}
		}
		a = f + step * b->weight;
		c = 1.0f - a;
	}
	*w0 = a;
	*w1 = c;
}
