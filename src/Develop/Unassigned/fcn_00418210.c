#include <math.h>

int __cdecl fcn_0064d3f8(void);

/* ADDRESS: GOLDTL 0x00418210 */
int __cdecl fcn_00418210(char* obj, int now)
{
	int flags;
	unsigned int n;
	float half;
	float f;
	int color;
	int mask;
	int i;
	int alive;
	int r;
	unsigned char* e;
	char* p;
	float dt;
	float len;

	flags = *(int*) (obj + 0x20);
	if (flags & 1) {
		*(int*) (obj + 0x20) = flags & ~1;
		n = 1;
		color = *(int*) (obj + 0x24);
		e = *(unsigned char**) (obj + 0xdc);
		mask = ((unsigned char*) &color)[3];
		if (e != 0 && e[0x5c] > 0) {
			n = (unsigned char) e[0x5c];
		}
		p = *(char**) (obj + 0x28);
		for (i = 0; i < *(int*) (obj + 0xd8); i++, p += 0x54) {
			if ((*(unsigned char*) (p + 0x51) & 1) == 0) {
				r = fcn_0064d3f8();
				*(unsigned char*) (p + 0x4e) = (unsigned char)
				    ((r & mask) + ((unsigned char*) &color)[2]);
				r = fcn_0064d3f8();
				*(unsigned char*) (p + 0x4d) = (unsigned char)
				    ((r & mask) + ((unsigned char*) &color)[1]);
				r = fcn_0064d3f8();
				*(unsigned char*) (p + 0x4c) = (unsigned char)
				    ((r & mask) + ((unsigned char*) &color)[0]);
				*(unsigned char*) (p + 0x50) =
				    (unsigned char) (i % n);
				r = fcn_0064d3f8();
				*(float*) (p + 0x38) = (float) (((float) r
				    * 3.0518509e-05f) * 4.0) - 2.0f;
				r = fcn_0064d3f8();
				*(float*) (p + 0x3c) = ((float) r
				    * 3.0518509e-05f) * 1.5f;
				r = fcn_0064d3f8();
				*(float*) (p + 0x40) = (float) (((float) r
				    * 3.0518509e-05f) * 4.0) - 2.0f;
				r = fcn_0064d3f8();
				*(float*) p = ((float) r * 3.0518509e-05f)
				    * (*(float*) (obj + 0x10) * 2.0f)
				    - *(float*) (obj + 0x10);
				r = fcn_0064d3f8();
				*(float*) (p + 4) = ((float) r * 3.0518509e-05f)
				    * *(float*) (obj + 0x18)
				    + *(float*) (obj + 0x14);
				r = fcn_0064d3f8();
				*(float*) (p + 8) = ((float) r * 3.0518509e-05f)
				    * (*(float*) (obj + 0x10) * 2.0f)
				    - *(float*) (obj + 0x10);
				len = (float) sqrt((double)
				    (*(float*) p * *(float*) p
				    + *(float*) (p + 8) * *(float*) (p + 8)));
				if (len > *(float*) (obj + 0x10)
				    || len < *(float*) (obj + 0x10) * 0.4) {
					half = *(float*) (obj + 0x10)
					    * 0.25f;
					r = fcn_0064d3f8();
					f = ((float) r * 3.0518509e-05f)
					    * (half * 2.0f) - half
					    + *(float*) (obj + 0x10);
					f = f / len;
					*(float*) p = f * *(float*) p;
					*(float*) (p + 8) =
					    f * *(float*) (p + 8);
				}
				r = fcn_0064d3f8();
				*(float*) (p + 0x10) =
				    (float) ((r & 0x3f) + 0xc0);
				r = fcn_0064d3f8();
				{
					unsigned char fb;
					int nnow;
					float fv;

					fb = *(unsigned char*) (p + 0x51);
					nnow = now;
					fv = ((float) r * 3.0518509e-05f)
					    * (*(float*) obj * 2.0f)
					    - *(float*) obj
					    + *(float*) (obj + 0xe4);
					*(int*) (p + 0x30) = nnow;
					*(unsigned char*) (p + 0x51) = (unsigned char) (fb | 1);
					*(float*) (p + 0x48) = fv;
				}
			}
		}
	}
	p = *(char**) (obj + 0x28);
	alive = 0;
	for (i = 0; i < *(int*) (obj + 0xd8); i++, p += 0x54) {
		if (*(unsigned char*) (p + 0x51) & 1) {
			dt = (float) (unsigned int)
			    (now - *(int*) (p + 0x30))
			    * 0.33333334f;
			*(int*) (p + 0x30) = now;
			*(float*) (p + 0x38) += dt * *(float*) p;
			*(float*) (p + 0x3c) += dt * *(float*) (p + 4);
			*(float*) (p + 0x40) += dt * *(float*) (p + 8);
			if (*(float*) (p + 0x3c) < *(float*) (obj + 0xc)) {
				*(float*) (p + 0x3c) = *(float*) (obj + 0xc);
				*(float*) p = *(float*) p
				    - *(float*) p * 0.29f;
				*(float*) (p + 4) = *(float*) (p + 4)
				    * -0.34f;
				*(float*) (p + 8) = *(float*) (p + 8)
				    - *(float*) (p + 8) * 0.31f;
				len = (float) fabs((double) *(float*) (p + 4));
				if (len < 0.2) {
					*(float*) p = 0.0f;
					*(float*) (p + 4) = 0.0f;
					*(float*) (p + 8) = 0.0f;
				}
			} else {
				if (*(float*) (p + 4) != 0.0f) {
					*(float*) (p + 4) = *(float*) (p + 4)
					    - dt * *(float*) (obj + 4);
				}
			}
			f = dt * *(float*) (obj + 8);
			*(float*) (p + 0x10) = *(float*) (p + 0x10) - f;
			if (*(float*) (p + 0x10) > 0.0) {
				*(unsigned char*) (p + 0x4f) =
				    (unsigned char) (int)
				    *(float*) (p + 0x10);
			} else {
				*(unsigned char*) (p + 0x51) &=
				    (unsigned char) ~1;
			}
		}
		if (!(*(unsigned char*) (p + 0x51) & 1)) {
			alive++;
		}
	}
	if (alive >= *(int*) (obj + 0xd8)
	    && (*(int*) (obj + 0x20) & 2) == 0) {
		return 0;
	}
	return 1;
}
