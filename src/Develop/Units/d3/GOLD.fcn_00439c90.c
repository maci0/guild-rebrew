/* Clips the vertex list in the first list buffer against the planes of a0
 * (Sutherland-Hodgman), alternating the two list buffers at 0xfc4c60.
 * DATA TODO: 0x633454, 0x633458, 0xfc4c60 and 0xfc5360 have no data rows. */

typedef struct {
	float x;
	float y;
	float z;
	float w;
	char pad10[0x1c];
	float f2c;
	char pad30[0x10];
	unsigned char b40;
	unsigned char b41;
	unsigned char b42;
	unsigned char b43;
	char pad44[0xb];
	unsigned char b4f;
} D3_CLIP_VERTEX;

/* ADDRESS: GOLD 0x00439c90 */
int __cdecl fcn_00439c90(unsigned int* a0)
{
	D3_CLIP_VERTEX** cur;
	D3_CLIP_VERTEX** out;
	D3_CLIP_VERTEX* v;
	D3_CLIP_VERTEX* n;
	D3_CLIP_VERTEX* tmp;
	float* pl;
	float dc;
	float dn;
	float t;
	int inside;
	int next_inside;
	unsigned int pi;
	unsigned int k;

	*(int*) 0x633454 = 0;
	if (((unsigned int) a0 + 8 | *a0 | (unsigned int) a0) == 0) {
		return 0;
	}
	pi = 0;
	tmp = (D3_CLIP_VERTEX*) 0xfc5360;
	if (*a0 != 0) {
		pl = (float*) &a0[3];
		do {
			*(int*) 0x633454 = 0;
			cur = (D3_CLIP_VERTEX**) ((pi & 1) * 0x200 + 0xfc4c60);
			v = cur[0];
			cur[*(int*) 0x633458] = v;
			dc = v->x * pl[-1] + (v->y * pl[0] + v->z * pl[1]);
			out = (D3_CLIP_VERTEX**) (((pi - 1) & 1) * 0x200 + 0xfc4c60);
			inside = dc >= pl[2];
			k = 0;
			if (*(int*) 0x633458 != 0) {
				do {
					v = cur[0];
					n = cur[1];
					dn = n->y * pl[0] + (n->z * pl[1] + pl[-1] * n->x);
					next_inside = !(dn < pl[2]);
					if (inside) {
						*out++ = v;
						*(int*) 0x633454 = *(int*) 0x633454 + 1;
					}
					if (inside != next_inside) {
						t = (pl[2] - dc) / (dn - dc);
						tmp->x = (n->x - v->x) * t + v->x;
						tmp->y = (n->y - v->y) * t + v->y;
						tmp->z = (n->z - v->z) * t + v->z;
						tmp->w = (n->w - v->w) * t + v->w;
						tmp->f2c = (n->f2c - v->f2c) * t + v->f2c;
						tmp->b40 = (unsigned char) (int) ((float) ((int) n->b40 - (int) v->b40) * t + v->b40);
						tmp->b41 = (unsigned char) (int) ((float) ((int) n->b41 - (int) v->b41) * t + v->b41);
						tmp->b42 = (unsigned char) (int) ((float) ((int) n->b42 - (int) v->b42) * t + v->b42);
						tmp->b43 = (unsigned char) (int) ((float) ((int) n->b43 - (int) v->b43) * t + v->b43);
						tmp->b4f = (unsigned char) (int) ((float) ((int) n->b4f - (int) v->b4f) * t + v->b4f);
						*out++ = tmp;
						tmp++;
						*(int*) 0x633454 = *(int*) 0x633454 + 1;
					}
					dc = dn;
					k++;
					cur++;
					inside = next_inside;
				} while (k < *(unsigned int*) 0x633458);
			}
			*(int*) 0x633458 = *(int*) 0x633454;
			pi++;
			pl += 4;
		} while (pi < *a0);
	}
	return (int) ((pi & 1) * 0x200 + 0xfc4c60);
}
