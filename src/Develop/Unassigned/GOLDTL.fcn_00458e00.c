void __cdecl fcn_004372d0(unsigned char, unsigned char, int, unsigned char, unsigned char);

/* ADDRESS: GOLDTL 0x00458e00 */
char __cdecl fcn_00458e00(char* a0, char* a1)
{
	void* obj;
	char* vt;
	float x;
	float y;
	float scale;
	float xstep;
	float ystep;
	unsigned char col[4];
	char* buf;
	int row;
	int col_idx;
	int shade;

	if (a0 != 0 && *(int*) (a0 + 0xc) > 0 && a1 != 0 && *(int*) (a1 + 0x1c) != 0) {
		scale = *(float*) a1 * *(float*) 0x6628cc * *(float*) 0x662dc0;
		if (((unsigned char*) a1)[0x2a] == 0) {
			return 1;
		}
		obj = *(void**) 0x6b5de0;
		vt = (char*) *(int*) obj;
		(*(void (__stdcall**) (void*, int, int)) (vt + 0xf4))(obj, 0,
			*(int*) (*(int*) (a1 + 0x1c) + 0x50));
		fcn_004372d0(((unsigned char*) a1)[0x2a],
			((unsigned char*) a1)[0x26] & 1, 0,
			(((unsigned char*) a1)[0x26] >> 1) & 1, 0);
		if (((unsigned char*) a1)[0x26] & 1) {
			shade = ((unsigned char*) a0)[0xb];
			col[2] = (unsigned char) ((((unsigned char*) a0)[0xa] * shade) >> 8);
			col[1] = (unsigned char) ((((unsigned char*) a0)[9] * shade) >> 8);
			col[0] = (unsigned char) ((((unsigned char*) a0)[8] * shade) >> 8);
		} else {
			*(unsigned int*) col =
				(((((unsigned char*) a1)[0x2a] << 8) | ((unsigned char*) a0)[0xa]) << 8
				| ((unsigned char*) a0)[9]) << 8 | ((unsigned char*) a0)[8];
		}
		xstep = (float) (*(int*) 0x1042578 - *(int*) 0x1042570) * *(float*) 0x662dbc;
		ystep = (float) (*(int*) 0x104257c - *(int*) 0x1042574) * *(float*) 0x6629d0;
		obj = *(void**) a0;
		(*(void (__stdcall**) (void*, int, int, void**, int)) (*(int*) obj + 0x2c))(obj, 0,
			*(int*) (a0 + 0xc) << 5, &buf, 0x2000);
		y = (float) *(int*) 0x1042574;
		for (row = 0; row < 0x30; row += 8) {
			x = (float) *(int*) 0x1042570;
			for (col_idx = 0; col_idx < 8; col_idx++) {
				if (a0[0x30 + row + col_idx] != 0) {
					*(float*) (buf + 0x20 * (row + col_idx)) = x;
					*(float*) (buf + 0x20 * (row + col_idx) + 4) = y;
					*(float*) (buf + 0x20 * (row + col_idx) + 8) = 1.0f;
					*(float*) (buf + 0x20 * (row + col_idx) + 0xc) = 1.0f;
					*(unsigned int*) (buf + 0x20 * (row + col_idx) + 0x10) =
						*(unsigned int*) col;
					buf[0x20 * (row + col_idx) + 0x17] = a0[0x60 + row + col_idx];
					*(float*) (buf + 0x20 * (row + col_idx) + 0x18) =
						(*(float*) (a0 + 0x9c + 0x10 * (row + col_idx)) + *(float*) (a0 + 0x14))
						* scale + *(float*) (a1 + 4);
					*(float*) (buf + 0x20 * (row + col_idx) + 0x1c) =
						*(float*) (a1 + 0x14)
						- *(float*) (a1 + 0x18)
						* *(float*) (a0 + 0x94 + 0x10 * (row + col_idx));
				}
				x += xstep;
			}
			y += ystep;
		}
		obj = *(void**) a0;
		(*(void (__stdcall**) (void*)) (*(int*) obj + 0x30))(obj);
		if (*(int*) (a0 + 0xc) != 0 && *(int*) (a0 + 0x10) != 0) {
			obj = *(void**) 0x6b5de0;
			vt = (char*) *(int*) obj;
			(*(void (__stdcall**) (void*, int, int, int, int, int)) (vt + 0x11c))(obj, 4,
				0, *(int*) (a0 + 0xc), 0, *(int*) (a0 + 0x10) / 3);
		}
		return 1;
	}
	return 0;
}
