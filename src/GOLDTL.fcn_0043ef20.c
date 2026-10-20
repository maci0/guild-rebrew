#include <math.h>
#include <string.h>

/* Compiler float/double pools and lighting constants. */
extern float g_6628a0; /* 1.0f */
extern float g_6628a8; /* 0.0f */
extern float g_6628cc;
extern float g_662c30;
extern float g_662ca8;
extern double g_662ca0;
extern float g_662d40[3];
extern float g_67bbdc;
extern float g_67bbe0;
extern float g_67bbe4;
extern float g_6b86c4;
extern float g_6b86c8;
extern float g_6b86cc;
extern float g_1040d00[0x400];
extern int g_67a370;

void __cdecl fcn_0043bf20(char* a);
void __cdecl fcn_00455140(char* node, float* in, float* out);
char __cdecl fcn_004379a0(char* scene, char* node, unsigned int flags,
                          char (__cdecl* cb)(char*, void*), void* ctx);
char __cdecl fcn_0043ed30(char* node, void* ctx);

typedef void (__cdecl* LightLock)(char*, int, char**);
typedef void (__cdecl* LightUnlock)(char*);

/* Iterator context: the handle lives at ctx+0, the first hit at ctx+4. */
typedef struct LightIter {
	char* obj;
	void* item;
} LightIter;

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0043ef20 */
void __cdecl fcn_0043ef20(char* a0)
{
	char* lum;
	char* bmp;
	char* prevRow;
	char* curRow;
	char* dst;
	char* cellp;
	char* planep;
	char* obj;
	unsigned char b0;
	int w;
	int rowOff;
	int i;
	int j;
	int k;
	int y;
	int x;
	int c1;
	int c2;
	int d1;
	int d2;
	int red;
	int grn;
	int blu;
	int idx;
	unsigned int texel;
	unsigned int n;
	unsigned int t;
	unsigned int val;
	float u[3];
	float f27;
	float grad;
	float ka;
	float kb;
	float kaa;
	float s1;
	float s2;
	float nrm;
	float tot;
	float shade;
	float chan;
	LightIter it;

	if ((*(unsigned char*) (a0 + 0x8036) & 2) == 0 && *(int*) (a0 + 0x1c) != 0) {
		fcn_0043bf20(a0);
		w = *(int*) a0;
		memset(*(void**) (a0 + 0x1c), 0, w * w);
		it.obj = a0;
		it.item = 0;
		fcn_004379a0((char*) g_67a370, 0, 0xe, fcn_0043ed30, &it);
		if (it.item != 0) {
			char* e;

			e = (char*) it.item;
			f27 = *(float*) (e + 0x94) * g_6628cc;
			*(float*) (a0 + 0x90) = *(float*) (e + 0x5c) * g_662c30;
			*(float*) (a0 + 0x94) = *(float*) (e + 0x60) * g_662c30;
			*(float*) (a0 + 0x98) = *(float*) (e + 0x64) * g_662c30;
			fcn_00455140(e, g_662d40, u);
			grad = *(float*) (a0 + 0x78) * *(float*) (a0 + 0x84);
			grad += grad;
			lum = *(char**) (a0 + 0x10);
			bmp = *(char**) (a0 + 0x1c);
			ka = *(float*) (a0 + 0x78) * *(float*) (a0 + 0x60) * g_662ca8;
			kb = *(float*) (a0 + 0x84) * *(float*) (a0 + 0x60);
			kb += kb;
			if (w > 0) {
				kaa = ka * ka;
				rowOff = 0;
				y = 1;
				do {
					prevRow = (char*) (((y - 2) & (w - 1)) * w) + (int) lum;
					curRow = (char*) ((y & (w - 1)) * w) + (int) lum;
					x = 0;
					do {
						c1 = (int) (unsigned char) lum[rowOff + ((x - 1) & (w - 1))];
						c2 = (int) (unsigned char) lum[rowOff + ((x + 1) & (w - 1))];
						d1 = c2 - c1;
						d2 = (int) (unsigned char) curRow[x] - (int) (unsigned char) prevRow[x];
						s1 = (float) d1 * grad;
						s2 = (float) d2 * kb;
						nrm = g_6628a0 / (float) sqrt(s2 * s2 + s1 * s1 + kaa);
						tot = u[0] * (nrm * s1) + u[1] * (ka * nrm) + u[2] * (nrm * s2);
						if (tot > g_6628a8) {
							idx = (int) (tot * g_662ca0);
							chan = f27 * g_1040d00[idx];
							val = (unsigned int) (int) chan;
							if (val > 0x7f) {
								val = 0x7f;
							}
							bmp[rowOff + x] = bmp[rowOff + x] | (unsigned char) val;
						}
						x++;
					} while (x < w);
					rowOff += w;
					y++;
				} while (y - 1 < w);
			}
		} else {
			*(int*) (a0 + 0x90) = 0x437f0000;
			*(int*) (a0 + 0x94) = 0x437f0000;
			*(int*) (a0 + 0x98) = 0x437f0000;
		}
		cellp = a0 + 0xc0;
		planep = cellp;
		i = 8;
		do {
			k = 8;
			do {
				j = 8;
				do {
					if (*(unsigned int*) cellp > 0) {
						obj = *(char**) (cellp - 0xc);
						(*(LightLock**) obj)[0xe](obj, 0x2000, &dst);
						n = *(unsigned int*) cellp;
						t = 0;
						if (n > 0) {
							do {
								texel = *(unsigned int*) (*(int*) (cellp - 0x1c) + (int) t * 4) & 0xffffff;
								*(float*) dst = (float) (unsigned int) (texel % (unsigned int) w) *
								                *(float*) (a0 + 0x60);
								*(float*) (dst + 4) = (float) lum[texel] * *(float*) (a0 + 0x84);
								*(float*) (dst + 8) = (float) (unsigned int) (texel / (unsigned int) w) *
								                *(float*) (a0 + 0x78);
								b0 = (unsigned char) bmp[texel];
								shade = (float) (int) (b0 & 0x7f);
								shade += shade;
								if ((signed char) b0 < 0) {
									red = (int) (shade * *(float*) (a0 + 0x90) + g_67bbdc + g_6b86c4);
									if ((unsigned int) red > 0xff) {
										red = 0xff;
									}
									grn = (int) (shade * *(float*) (a0 + 0x94) + g_67bbe0 + g_6b86c8);
									if ((unsigned int) grn > 0xff) {
										grn = 0xff;
									}
									blu = (int) (shade * *(float*) (a0 + 0x98) + g_67bbe4 + g_6b86cc);
									if ((unsigned int) blu > 0xff) {
										blu = 0xff;
									}
								} else {
									red = (int) (shade * *(float*) (a0 + 0x90) + g_67bbdc);
									if ((unsigned int) red > 0xff) {
										red = 0xff;
									}
									red = red & 0xff;
									grn = (int) (shade * *(float*) (a0 + 0x94) + g_67bbe0);
									if ((unsigned int) grn > 0xff) {
										grn = 0xff;
									}
									grn = grn & 0xff;
									blu = (int) (shade * *(float*) (a0 + 0x98) + g_67bbe4);
									if ((unsigned int) blu > 0xff) {
										blu = 0xff;
									}
									blu = blu & 0xff;
								}
								*(unsigned int*) (dst + 0xc) = (texel & 0xff000000) + (unsigned int) blu +
								                               (unsigned int) (red * 0x100 + grn) * 0x100;
								*(int*) (dst + 0x10) = *(int*) (*(int*) (a0 + 0x20) + (int) texel * 8);
								*(int*) (dst + 0x14) = *(int*) (*(int*) (a0 + 0x20) + (int) texel * 8 + 4);
								dst += 0x18;
								t++;
							} while (t < n);
						}
						(*(LightUnlock**) obj)[0xf](obj);
					}
					if (*(unsigned int*) (cellp + 4) > 0) {
						obj = *(char**) (cellp - 8);
						(*(LightLock**) obj)[0xe](obj, 0x2000, &dst);
						n = *(unsigned int*) (cellp + 4);
						t = 0;
						if (n > 0) {
							do {
								texel = *(unsigned int*) (*(int*) (cellp - 0x18) + (int) t * 4) & 0xffffff;
								*(float*) dst = (float) (unsigned int) (texel % (unsigned int) w) *
								                *(float*) (a0 + 0x60);
								*(float*) (dst + 4) = (float) lum[texel] * *(float*) (a0 + 0x84);
								*(float*) (dst + 8) = (float) (unsigned int) (texel / (unsigned int) w) *
								                *(float*) (a0 + 0x78);
								b0 = (unsigned char) bmp[texel];
								shade = (float) (int) (b0 & 0x7f);
								shade += shade;
								if ((signed char) b0 < 0) {
									red = (int) (shade * *(float*) (a0 + 0x90) + g_67bbdc + g_6b86c4);
									if ((unsigned int) red > 0xff) {
										red = 0xff;
									}
									grn = (int) (shade * *(float*) (a0 + 0x94) + g_67bbe0 + g_6b86c8);
									if ((unsigned int) grn > 0xff) {
										grn = 0xff;
									}
									blu = (int) (shade * *(float*) (a0 + 0x98) + g_67bbe4 + g_6b86cc);
									if ((unsigned int) blu > 0xff) {
										blu = 0xff;
									}
								} else {
									red = (int) (shade * *(float*) (a0 + 0x90) + g_67bbdc);
									if ((unsigned int) red > 0xff) {
										red = 0xff;
									}
									red = red & 0xff;
									grn = (int) (shade * *(float*) (a0 + 0x94) + g_67bbe0);
									if ((unsigned int) grn > 0xff) {
										grn = 0xff;
									}
									grn = grn & 0xff;
									blu = (int) (shade * *(float*) (a0 + 0x98) + g_67bbe4);
									if ((unsigned int) blu > 0xff) {
										blu = 0xff;
									}
									blu = blu & 0xff;
								}
								*(unsigned int*) (dst + 0xc) = (texel & 0xff000000) + (unsigned int) blu +
								                               (unsigned int) (red * 0x100 + grn) * 0x100;
								*(int*) (dst + 0x10) = *(int*) (*(int*) (a0 + 0x20) + (int) texel * 8);
								*(int*) (dst + 0x14) = *(int*) (*(int*) (a0 + 0x20) + (int) texel * 8 + 4);
								dst += 0x18;
								t++;
							} while (t < n);
						}
						(*(LightUnlock**) obj)[0xf](obj);
					}
					cellp += 0x34;
					j--;
				} while (j);
				planep += 0x1f4;
				cellp = planep;
				k--;
			} while (k);
			cellp = planep;
			i--;
		} while (i);
	}
}
