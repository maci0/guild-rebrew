void __cdecl d3_SetRenderMaterialState(unsigned char, unsigned char, int, unsigned char, unsigned char);

/* ADDRESS: GOLDTL 0x00458e00 */
char __cdecl d3_RenderSkyLayer(char* dome, char* layer)
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
	float* uv;
	if (dome != 0 && *(int*) (dome + 0xc) > 0 && layer != 0 && *(int*) (layer + 0x1c) != 0) {
		scale = *(float*) layer * 0.5f;
		scale = scale * 0.31830987334251404f;
		if (((unsigned char*) layer)[0x2a] == 0) {
			return 1;
		}
		obj = *(void**) 0x6b5de0;
		vt = (char*) *(int*) obj;
		(*(void (__stdcall**) (void*, int, int)) (vt + 0xf4))(obj, 0,
			*(int*) (*(int*) (layer + 0x1c) + 0x50));
		d3_SetRenderMaterialState(((unsigned char*) layer)[0x2a],
			((unsigned char*) layer)[0x26] & 1, 0,
			(((unsigned char*) layer)[0x26] >> 1) & 1, 0);
		if (((unsigned char*) layer)[0x26] & 1) {
			shade = ((unsigned char*) dome)[0xb];
			col[2] = (unsigned char) ((((unsigned char*) dome)[0xa] * shade) >> 8);
			col[1] = (unsigned char) ((((unsigned char*) dome)[9] * shade) >> 8);
			col[0] = (unsigned char) ((((unsigned char*) dome)[8] * shade) >> 8);
		} else {
			*(unsigned int*) col =
				(((((unsigned char*) layer)[0x2a] << 8) | ((unsigned char*) dome)[0xa]) << 8
				| ((unsigned char*) dome)[9]) << 8 | ((unsigned char*) dome)[8];
		}
		xstep = (float) (*(int*) 0x1042578 - *(int*) 0x1042570) * 0.1428571492433548f;
		ystep = (float) (*(int*) 0x104257c - *(int*) 0x1042574) * 0.2f;
		obj = *(void**) dome;
		(*(void (__stdcall**) (void*, int, int, void**, int)) (*(int*) obj + 0x2c))(obj, 0,
			*(int*) (dome + 0xc) << 5, &buf, 0x2000);
		y = (float) *(int*) 0x1042574; uv = (float*) (dome + 0x94);
		row = 0; do {
			x = (float) *(int*) 0x1042570;
			for (col_idx = 8; col_idx != 0; col_idx--, row++) {
				if (dome[0x30 + row] != 0) {
					*(float*) (buf + 0x20 * (row)) = x;
					*(float*) (buf + 0x20 * (row) + 4) = y;
					*(float*) (buf + 0x20 * (row) + 8) = 1.0f;
					*(float*) (buf + 0x20 * (row) + 0xc) = 1.0f;
					*(unsigned int*) (buf + 0x20 * (row) + 0x10) =
						*(unsigned int*) col;
					buf[0x20 * (row) + 0x17] = dome[0x60 + row];
					*(float*) (buf + 0x20 * (row) + 0x18) =
						(uv[2] + *(float*) (dome + 0x14))
						* scale + *(float*) (layer + 4);
					*(float*) (buf + 0x20 * (row) + 0x1c) =
						-(*(float*) (layer + 0x18)
						* uv[0])
						+ *(float*) (layer + 0x14);
				}
				x += xstep; uv += 4;
			}
			y += ystep;
		} while (row < 0x30);
		obj = *(void**) dome;
		(*(void (__stdcall**) (void*)) (*(int*) obj + 0x30))(obj);
		if (*(int*) (dome + 0xc) != 0 && *(int*) (dome + 0x10) != 0) {
			obj = *(void**) 0x6b5de0;
			vt = (char*) *(int*) obj;
			(*(void (__stdcall**) (void*, int, int, int, int, int)) (vt + 0x11c))(obj, 4,
				0, *(int*) (dome + 0xc), 0, *(int*) (dome + 0x10) / 3);
		}
		return 1;
	}
	return 0;
}
