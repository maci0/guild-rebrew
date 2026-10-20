#include <string.h>

#pragma intrinsic(memcpy, strcpy, strcmp)

char* __cdecl fcn_0041db70(unsigned int size, char* file);
void __cdecl fcn_0041ddd0(void* p);
int __cdecl fcn_0064d228(void);

extern char* g_1052ba4;
extern char g_1052a40[];

/* The reference frame keeps EBP; /O2 /Gd omits the frame pointer, so restore
 * it here instead of overriding the locked CFLAGS. */
#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x00433be0 */
char* __cdecl fcn_00433be0(char* a0, char* a1, char* a2, char* a3, char* a4, char* a5, char* a6, int a7)
{
	char* p;
	char* r;
	int i;
	int j;
	int k;
	char c;
	float dx;
	float dy;
	float dz;
	float minx;
	float miny;
	float minz;
	float maxx;
	float maxy;
	float maxz;
	float rx;
	float ry;
	float rz;
	float invx;
	float invy;
	float invz;

	if (a2 == 0) {
		return 0;
	}
	if (a0 == 0) {
		return 0;
	}
	if (a5 == 0) {
		if (a3 == 0) {
			return 0;
		}
		if (a4 == 0) {
			return 0;
		}
	}
	if (a7 <= 1) {
		return 0;
	}
	p = fcn_0041db70(0x16c, (char*) 0x67a1d4);
	*(int*) (p + 0x140) = *(int*) (a0 + 0x44);
	*(int*) (p + 0x148) = 2;
	for (k = 0; ; k++) {
		c = a6[k];
		p[k] = c;
		if (c == 0) {
			break;
		}
	}
	*(char**) (p + 0x15c) = fcn_0041db70(*(int*) (p + 0x148) * 0xc0, (char*) 0x67a1b4);
	**(int**) (p + 0x15c) = 0;
	*(int*) (*(int*) (p + 0x15c) + 4) = a7 * 3;
	*(int*) (*(int*) (p + 0x15c) + 0x20) = *(int*) (a2 + 0x20);
	*(int*) (*(int*) (p + 0x15c) + 0x24) = *(int*) (a2 + 0x24);
	*(int*) (*(int*) (p + 0x15c) + 0x28) = *(int*) (a2 + 0x28);
	*(int*) (*(int*) (p + 0x15c) + 0x2c) = *(int*) (a2 + 0x2c);
	*(int*) (*(int*) (p + 0x15c) + 0x30) = *(int*) (a2 + 0x30);
	*(int*) (*(int*) (p + 0x15c) + 0x34) = *(int*) (a2 + 0x34);
	if (*(int*) (a2 + 0xbc) != 0) {
		*(char**) (*(int*) (p + 0x15c) + 0xbc) =
		    fcn_0041db70(*(int*) (p + 0x140) * 0xc, (char*) 0x67a194);
		memcpy(*(char**) (*(int*) (p + 0x15c) + 0xbc), *(char**) (a2 + 0xbc),
		    *(int*) (p + 0x140) * 0xc);
		*(char**) (*(int*) (p + 0x15c) + 0x17c) =
		    fcn_0041db70(*(int*) (p + 0x140) * 0xc, (char*) 0x67a174);
	}
	if (*(int*) (a2 + 0xb4) != 0) {
		*(char**) (*(int*) (p + 0x15c) + 0xb4) =
		    fcn_0041db70(*(int*) (p + 0x140) * 3, (char*) 0x67a154);
		memcpy(*(char**) (*(int*) (p + 0x15c) + 0xb4), *(char**) (a2 + 0xb4),
		    *(int*) (p + 0x140) * 3);
		*(int*) (*(int*) (p + 0x15c) + 8) = *(int*) (a2 + 8);
		*(int*) (*(int*) (p + 0x15c) + 0xc) = *(int*) (a2 + 0xc);
		*(int*) (*(int*) (p + 0x15c) + 0x10) = *(int*) (a2 + 0x10);
		*(int*) (*(int*) (p + 0x15c) + 0x14) = *(int*) (a2 + 0x14);
		*(int*) (*(int*) (p + 0x15c) + 0x18) = *(int*) (a2 + 0x18);
		*(int*) (*(int*) (p + 0x15c) + 0x1c) = *(int*) (a2 + 0x1c);
		*(char**) (*(int*) (p + 0x15c) + 0x174) =
		    fcn_0041db70(*(int*) (p + 0x140) * 3, (char*) 0x67a134);
	}
	*(int*) (*(int*) (p + 0x15c) + 0xc0) = a7;
	*(int*) (*(int*) (p + 0x15c) + 0xc4) = a7 * 3;
	*(int*) (p + 0x144) = *(int*) (a1 + 0x144);
	for (i = 0; i < *(int*) (p + 0x144); i++) {
		for (k = 0; ; k++) {
			c = a1[0x40 + i * 0x40 + k];
			p[0x40 + i * 0x40 + k] = c;
			if (c == 0) {
				break;
			}
		}
		*(int*) (*(int*) (p + 0x15c) + 0x54 + i * 0x18) = *(int*) (a2 + 0x54 + i * 0x18);
		*(int*) (*(int*) (p + 0x15c) + 0x58 + i * 0x18) = *(int*) (a2 + 0x58 + i * 0x18);
		*(int*) (*(int*) (p + 0x15c) + 0x5c + i * 0x18) = *(int*) (a2 + 0x5c + i * 0x18);
		*(int*) (*(int*) (p + 0x15c) + 0x60 + i * 0x18) = *(int*) (a2 + 0x60 + i * 0x18);
		*(int*) (*(int*) (p + 0x15c) + 0x64 + i * 0x18) = *(int*) (a2 + 0x64 + i * 0x18);
		*(int*) (*(int*) (p + 0x15c) + 0x68 + i * 0x18) = *(int*) (a2 + 0x68 + i * 0x18);
	}
	if (a5 != 0) {
		for (i = 0; i < *(int*) (p + 0x144); i++) {
			for (j = 0; j < 4; j++) {
				if (strcmp(p + 0x40 + i * 0x40, a5 + 0x74 + j * 0x58) == 0) {
					*(int*) (*(int*) (p + 0x15c) + 0x114 + i * 0x18) =
					    *(int*) (a5 + 0xb4 + j * 0x58);
					*(int*) (*(int*) (p + 0x15c) + 0x118 + i * 0x18) =
					    *(int*) (a5 + 0xb8 + j * 0x58);
					*(int*) (*(int*) (p + 0x15c) + 0x11c + i * 0x18) =
					    *(int*) (a5 + 0xbc + j * 0x58);
					*(int*) (*(int*) (p + 0x15c) + 0x120 + i * 0x18) =
					    *(int*) (a5 + 0xc0 + j * 0x58);
					*(int*) (*(int*) (p + 0x15c) + 0x124 + i * 0x18) =
					    *(int*) (a5 + 0xc4 + j * 0x58);
					*(int*) (*(int*) (p + 0x15c) + 0x128 + i * 0x18) =
					    *(int*) (a5 + 0xc8 + j * 0x58);
				}
			}
		}
		*(float*) (*(int*) (p + 0x15c) + 0xe0) =
		    *(float*) (a5 + 0x50) - *(float*) (a0 + 0x50);
		*(float*) (*(int*) (p + 0x15c) + 0xe4) =
		    *(float*) (a5 + 0x54) - *(float*) (a0 + 0x54);
		*(float*) (*(int*) (p + 0x15c) + 0xe8) =
		    *(float*) (a5 + 0x58) - *(float*) (a0 + 0x58);
		*(int*) (*(int*) (p + 0x15c) + 0xe4) = 0;
		*(float*) (*(int*) (p + 0x15c) + 0xec) =
		    *(float*) (a5 + 0x5c) - *(float*) (a0 + 0x5c);
		*(float*) (*(int*) (p + 0x15c) + 0xf0) =
		    *(float*) (a5 + 0x60) - *(float*) (a0 + 0x60);
		*(float*) (*(int*) (p + 0x15c) + 0xf4) =
		    *(float*) (a5 + 0x64) - *(float*) (a0 + 0x64);
		if (*(int*) (a2 + 0xbc) != 0) {
			for (i = 0; i < *(int*) (p + 0x140); i++) {
				*(float*) (*(int*) (*(int*) (p + 0x15c) + 0x17c) + i * 0xc) =
				    *(float*) (*(int*) (a5 + 0x27c) + i * 0xc) -
				    *(float*) (*(int*) (a0 + 0x27c) + i * 0xc);
				*(float*) (*(int*) (*(int*) (p + 0x15c) + 0x17c) + i * 0xc + 4) =
				    *(float*) (*(int*) (a5 + 0x27c) + i * 0xc + 4) -
				    *(float*) (*(int*) (a0 + 0x27c) + i * 0xc + 4);
				*(float*) (*(int*) (*(int*) (p + 0x15c) + 0x17c) + i * 0xc + 8) =
				    *(float*) (*(int*) (a5 + 0x27c) + i * 0xc + 8) -
				    *(float*) (*(int*) (a0 + 0x27c) + i * 0xc + 8);
			}
		}
		if (*(int*) (a2 + 0xb4) != 0) {
			r = fcn_0041db70(*(int*) (p + 0x140) << 4, (char*) 0x67a110);
			minx = 1e10f;
			miny = 1e10f;
			minz = 1e10f;
			maxx = -1e10f;
			maxy = -1e10f;
			maxz = -1e10f;
			for (i = 0; i < *(int*) (p + 0x140); i++) {
				dx = *(float*) (*(int*) (a5 + 0x27c) + i * 0xc) -
				    *(float*) (*(int*) (a0 + 0x27c) + i * 0xc);
				dy = *(float*) (*(int*) (a5 + 0x27c) + i * 0xc + 4) -
				    *(float*) (*(int*) (a0 + 0x27c) + i * 0xc + 4);
				dz = *(float*) (*(int*) (a5 + 0x27c) + i * 0xc + 8) -
				    *(float*) (*(int*) (a0 + 0x27c) + i * 0xc + 8);
				*(float*) (r + i * 0x10) = dx;
				*(float*) (r + i * 0x10 + 4) = dy;
				*(float*) (r + i * 0x10 + 8) = dz;
				if (dx <= minx) {
					minx = dx;
				}
				if (dy <= miny) {
					miny = dy;
				}
				if (dz <= minz) {
					minz = dz;
				}
				if (dx >= maxx) {
					maxx = dx;
				}
				if (dy >= maxy) {
					maxy = dy;
				}
				if (dz >= maxz) {
					maxz = dz;
				}
			}
			*(float*) (*(int*) (p + 0x15c) + 0xc8) = minx;
			*(float*) (*(int*) (p + 0x15c) + 0xcc) = miny;
			*(float*) (*(int*) (p + 0x15c) + 0xd0) = minz;
			rx = maxx - minx;
			ry = maxy - miny;
			rz = maxz - minz;
			*(float*) (*(int*) (p + 0x15c) + 0xd4) = rx * *(float*) 0x662c30;
			*(float*) (*(int*) (p + 0x15c) + 0xd8) = ry * *(float*) 0x662c30;
			*(float*) (*(int*) (p + 0x15c) + 0xdc) = rz * *(float*) 0x662c30;
			invx = *(float*) 0x6628a0 / rx;
			invy = *(float*) 0x6628a0 / ry;
			invz = *(float*) 0x6628a0 / rz;
			for (i = 0; i < *(int*) (p + 0x140); i++) {
				*(unsigned char*) (*(int*) (*(int*) (p + 0x15c) + 0x174) + i * 3) =
				    (unsigned char) ((*(float*) (r + i * 0x10) - minx) *
					*(float*) 0x6628a4 * invx);
				*(unsigned char*) (*(int*) (*(int*) (p + 0x15c) + 0x174) + i * 3 + 1) =
				    (unsigned char) ((*(float*) (r + i * 0x10 + 4) - miny) *
					*(float*) 0x6628a4 * invy);
				*(unsigned char*) (*(int*) (*(int*) (p + 0x15c) + 0x174) + i * 3 + 2) =
				    (unsigned char) ((*(float*) (r + i * 0x10 + 8) - minz) *
					*(float*) 0x6628a4 * invz);
			}
			fcn_0041ddd0(r);
		}
	}
	else {
		for (i = 0; i < *(int*) (p + 0x144); i++) {
			for (j = 0; j < 4; j++) {
				if (strcmp(p + 0x40 + i * 0x40, a3 + 0x40 + j * 0x40) == 0) {
					*(int*) (*(int*) (p + 0x15c) + 0x114 + i * 0x18) =
					    *(int*) (a4 + 0x54 + j * 0x18);
					*(int*) (*(int*) (p + 0x15c) + 0x118 + i * 0x18) =
					    *(int*) (a4 + 0x58 + j * 0x18);
					*(int*) (*(int*) (p + 0x15c) + 0x11c + i * 0x18) =
					    *(int*) (a4 + 0x5c + j * 0x18);
					*(int*) (*(int*) (p + 0x15c) + 0x120 + i * 0x18) =
					    *(int*) (a4 + 0x60 + j * 0x18);
					*(int*) (*(int*) (p + 0x15c) + 0x124 + i * 0x18) =
					    *(int*) (a4 + 0x64 + j * 0x18);
					*(int*) (*(int*) (p + 0x15c) + 0x128 + i * 0x18) =
					    *(int*) (a4 + 0x68 + j * 0x18);
				}
			}
		}
		*(int*) (*(int*) (p + 0x15c) + 0xe0) = *(int*) (a4 + 0x20);
		*(int*) (*(int*) (p + 0x15c) + 0xe4) = *(int*) (a4 + 0x24);
		*(int*) (*(int*) (p + 0x15c) + 0xe8) = *(int*) (a4 + 0x28);
		*(int*) (*(int*) (p + 0x15c) + 0xec) = *(int*) (a4 + 0x2c);
		*(int*) (*(int*) (p + 0x15c) + 0xf0) = *(int*) (a4 + 0x30);
		*(int*) (*(int*) (p + 0x15c) + 0xf4) = *(int*) (a4 + 0x34);
		if (*(int*) (a2 + 0xbc) != 0) {
			memcpy(*(char**) (*(int*) (p + 0x15c) + 0x17c), *(char**) (a4 + 0xbc),
			    *(int*) (p + 0x140) * 0xc);
		}
		if (*(int*) (a2 + 0xb4) != 0) {
			memcpy(*(char**) (*(int*) (p + 0x15c) + 0x174), *(char**) (a4 + 0xb4),
			    *(int*) (p + 0x140) * 3);
			*(int*) (*(int*) (p + 0x15c) + 0xc8) = *(int*) (a4 + 8);
			*(int*) (*(int*) (p + 0x15c) + 0xcc) = *(int*) (a4 + 0xc);
			*(int*) (*(int*) (p + 0x15c) + 0xd0) = *(int*) (a4 + 0x10);
			*(int*) (*(int*) (p + 0x15c) + 0xd4) = *(int*) (a4 + 0x14);
			*(int*) (*(int*) (p + 0x15c) + 0xd8) = *(int*) (a4 + 0x18);
			*(int*) (*(int*) (p + 0x15c) + 0xdc) = *(int*) (a4 + 0x1c);
		}
	}
	*(char**) (p + 0x164) = g_1052ba4;
	g_1052ba4 = p;
	*(char**) (p + 0x160) = g_1052a40;
	*(char**) (*(char**) (p + 0x164) + 0x160) = p;
	return p;
}
#pragma optimize("", on)
