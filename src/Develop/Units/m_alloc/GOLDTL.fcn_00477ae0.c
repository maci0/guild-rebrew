#include <string.h>

void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl m_FreeTracked(void*);
int __cdecl fcn_00475780(char*, char*);
void __cdecl fcn_004757b0(char*, char, char, char);

/* Crop one 24-bit bitmap block: scan the cells against the hole colour for the
   used bounds, repaint both row markers, copy the bounding rows into the block
   header and return a right-sized copy. */
/* ADDRESS: GOLDTL 0x00477ae0 */
unsigned int* __cdecl fcn_00477ae0(int a0, int a1, unsigned int a2,
                                   unsigned int a3, char* a4, char a5, int a6)
{
	unsigned int* v6;
	unsigned int* v8;
	unsigned int col;
	unsigned int row;
	char* v7;
	char* v20;
	char v18;
	char v32;
	char v33;
	unsigned short xmin;
	unsigned short ymin;
	unsigned short xmax;
	unsigned short ymax;
	int step;
	int w;
	int len;
	unsigned int i;

	v18 = 0;
	v32 = 0;
	v33 = 0;
	xmax = 0;
	xmin = (unsigned short) a2;
	ymax = 0;
	ymin = (unsigned short) a3;
	v6 = (unsigned int*) m_alloc((a2 * 0xc + 4) * a3 + 0x32, (char*) 0x67d9a0);
	if (1 <= (int) a3) {
		step = a6 * 3;
		v7 = a4 + (a1 * a6 + a0) * 3;
		for (row = 0; (int) row < (int) a3; row++) {
			v20 = v7;
			for (col = 0; (int) col < (int) a2; col++) {
				if (fcn_00475780(v20, (char*) 0x100f1a0) &&
				    (int) col > (int) (xmax & 0xffff)) {
					xmax = (unsigned short) col;
				}
				if (fcn_00475780(v20, (char*) 0x100f1a0) &&
				    (int) col < (int) (xmin & 0xffff)) {
					xmin = (unsigned short) col;
				}
				if (fcn_00475780(v20, (char*) 0x100f1a0) &&
				    (int) row > (int) (ymax & 0xffff)) {
					ymax = (unsigned short) row;
				}
				if (fcn_00475780(v20, (char*) 0x100f1a0) &&
				    (int) row < (int) (ymin & 0xffff)) {
					ymin = (unsigned short) row;
				}
				v20 += 3;
			}
			v7 += step;
		}
	}
	if ((unsigned short) xmax < (unsigned short) xmin ||
	    (unsigned short) ymax < (unsigned short) ymin) {
		xmax = 0;
		xmin = 0;
		ymax = 0;
		ymin = 0;
	}
	*(unsigned short*) ((char*) v6 + 4) = xmin;
	*(unsigned short*) ((char*) v6 + 0xe) = xmin;
	*(unsigned short*) ((char*) v6 + 6) = (unsigned short) (xmax + 1);
	*(unsigned short*) ((char*) v6 + 8) = ymin;
	*(unsigned short*) ((char*) v6 + 0xa) = (unsigned short) (ymax + 1);
	*(unsigned short*) ((char*) v6 + 0x10) = ymin;
	*(unsigned short*) ((char*) v6 + 0x12) = (unsigned short) (xmax + 1);
	*(unsigned short*) ((char*) v6 + 0x14) = (unsigned short) (ymax + 1);
	if (fcn_00475780((char*) 0x67d95c, &v18) && 1 <= (int) a3) {
		step = a6 * 3;
		v7 = a4 + (a1 * a6 + a0) * 3;
		for (row = 0; (int) row < (int) a3; row++) {
			v20 = v7;
			for (col = 0; (int) col < (int) a2; col++) {
				if (!fcn_00475780(v20, (char*) 0x67d960)) {
					xmin = (unsigned short) col;
					ymin = (unsigned short) row;
					fcn_004757b0(v20, *(char*) 0x100f1a0,
					             *(char*) 0x100f1a1,
					             *(char*) 0x100f1a2);
				}
				if (!fcn_00475780(v20, (char*) 0x67d95c)) {
					xmax = (unsigned short) col;
					ymax = (unsigned short) row;
					fcn_004757b0(v20, *(char*) 0x100f1a0,
					             *(char*) 0x100f1a1,
					             *(char*) 0x100f1a2);
				}
				v20 += 3;
			}
			v7 += step;
		}
	}
	*(unsigned short*) ((char*) v6 + 0x16) = xmin;
	*(unsigned short*) ((char*) v6 + 0x18) = ymin;
	*(unsigned short*) ((char*) v6 + 0x1a) = xmax;
	*(unsigned short*) ((char*) v6 + 0x1c) = ymax;
	*(unsigned int*) v6 = 0x32;
	v8 = (unsigned int*) ((char*) v6 + 0x32);
	if (*(unsigned short*) ((char*) v6 + 0xa) != 0) {
		step = a6 * 3;
		v7 = a4 + (a1 * a6 + a0) * 3;
		for (i = 0; (int) i < (int) *(unsigned short*) ((char*) v6 + 0xa);
		     i++) {
			w = *(unsigned short*) ((char*) v6 + 6);
			len = w * 3;
			memcpy(v8, v7, len);
			*(unsigned int*) ((char*) v6 + 0x2e) += w;
			*(unsigned int*) v6 += len;
			v7 += step;
			v8 = (unsigned int*) ((char*) v8 + len);
		}
	}
	*(unsigned int*) ((char*) v6 + 0x2a) = 0;
	*(char*) ((char*) v6 + 0xd) = a5;
	*(unsigned int*) ((char*) v6 + 0x26) = 0xffffffff;
	v8 = (unsigned int*) m_alloc(*v6, (char*) 0x67d970);
	memcpy(v8, v6, *v6);
	m_FreeTracked(v6);
	return v8;
}
