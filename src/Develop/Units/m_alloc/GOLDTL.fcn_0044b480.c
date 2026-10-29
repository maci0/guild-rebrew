#include <string.h>
#include <math.h>

extern void* __cdecl m_alloc(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* ptr);
void* __cdecl vfs_Tfopen(const char*, const char*, void*);
void __cdecl CloseVfsStream(void*);
void __cdecl fcn_0044a770(void*, int);
void __cdecl fcn_0044e190(void*, void*);
char __cdecl fcn_0044f0e0(char*);
void __cdecl fcn_0044fc70(char*, char);
int __cdecl fcn_00451840(float*, float*, float);
int __cdecl fcn_0045c5b0(char*, int, int, int);
int __cdecl fcn_0064d470(char*, char*);
char* __cdecl fcn_0064d530(char*, const char*, unsigned int);
void* __cdecl fcn_0064d740(void*, const void*, unsigned int);
char* __cdecl fcn_0066080a(char*);

/* Texture record of the .BGF chunk block, native stride 0xe0. */
typedef struct BGF_TEX {
	char name_000[0x40];
	char name_040[0x40];
	char name_080[0x40];
	unsigned char typ_0c0;
	unsigned char idx_0c1;
	unsigned char f_0c2;
	unsigned char f_0c3;
	unsigned char f_0c4;
	unsigned char f_0c5;
	unsigned char f_0c6;
	unsigned char f_0c7;
	unsigned char f_0c8;
	unsigned char f_0c9;
	char unbekannt_0ca[2];
	float f_0cc;
	float f_0d0;
	float f_0d4;
	float f_0d8;
	float f_0dc;
} BGF_TEX;

/* Polygon record, native stride 0x38. */
typedef struct BGF_POL {
	float uv[6];
	int ecken[3];
	int idx_024;
	int material;
	char unbekannt_02c[0x0c];
} BGF_POL;

/* Point record, native stride 0x18. */
typedef struct BGF_POI {
	float x;
	float y;
	float z;
	char unbekannt_00c[0x0c];
} BGF_POI;

/* Named part record, native stride 0x58. */
typedef struct BGF_TEIL {
	char name[0x40];
	int wert[6];
} BGF_TEIL;

/* Chunk header block filled by the .BGF chunk table reader. */
typedef struct BGF_HEADER {
	unsigned char typ;
	unsigned char flags;
	char unbekannt_002[0x0a];
	int anzahl_tex;
	BGF_TEX* tex;
	char unbekannt_014[0x08];
	int anzahl_pol;
	BGF_POL* pol;
	char unbekannt_024[0x08];
	int anzahl_poi;
	BGF_POI* poi;
	int anzahl_teil;
	BGF_TEIL teil[4];
} BGF_HEADER;

/* Object built by this loader, native size 0x2a4. */
typedef struct BGF_OBJ {
	char name[0x40];
	float* punkte;
	int anzahl_punkte;
	BGF_POL* polys;
	int anzahl_polys;
	char unbekannt_050[0x24];
	BGF_TEIL teile[4];
	char unbekannt_1d4[0x10];
	int anzahl_texnamen;
	int tex_stride;
	char unbekannt_1ec[0x14];
	char* texnamen;
	char unbekannt_204[0x9d];
	unsigned char flags;
	char unbekannt_2a2[2];
} BGF_OBJ;

BGF_OBJ* __cdecl fcn_0044f250(char*, char*, char*, int, int);

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0044b480 */
BGF_OBJ* __cdecl fcn_0044b480(char* name, char* a1, char* nametab, int namestep,
	int namecount)
{
	char buf[0x120];
	BGF_HEADER hdr;
	BGF_OBJ* obj;
	BGF_TEX* tex;
	void* stream;
	void* r;
	char* seen;
	char* snapshot;
	char* list;
	char* dst;
	char* p;
	char ok;
	int res;
	int i;
	int j;
	int k;
	int m;
	int n;
	int off;
	int off2;
	int newn;
	int copyoff;
	int idx;
	int info;
	int c1;
	int c2;
	float ax;
	float ay;
	float az;
	float ca;
	float sa;
	float cb;
	float sb;
	float fu;
	float fv;
	float fw;
	float ft;
	float fk;

	res = 0;
	strcpy(buf, name);
	fcn_0066080a(buf);
	if (!fcn_0064d470(buf, (char*) 0x67af00)) {
		return 0;
	}
	ok = fcn_0044f0e0(buf);
	obj = fcn_0044f250(buf, a1, nametab, namestep, namecount);
	if (obj == 0) {
		fcn_0044fc70(buf, ok);
		obj = fcn_0044f250(buf, a1, nametab, namestep, namecount);
		res = (int) obj;
	}
	if (obj != 0) {
		obj->flags = (obj->flags & 0xfd) | ((ok == 0) << 1);
		fcn_0044a770(obj, 0);
		return obj;
	}
	memset(&hdr, 0, sizeof(hdr));
	stream = vfs_Tfopen(buf, (char*) 0x6750e8, *(void**) 0x6b7fdc);
	if (stream == 0) {
		return (BGF_OBJ*) res;
	}
	fcn_0044e190(stream, &hdr);
	CloseVfsStream(stream);
	if (hdr.anzahl_pol <= 0 || hdr.anzahl_poi <= 0) {
		goto cleanup;
	}
	obj = m_alloc(0x2a4, (char*) 0x67afe0);
	res = (int) obj;
	fcn_0064d530(obj->name, a1, 0x3f);
	obj->name[0x3f] = 0;
	obj->flags = (obj->flags & 0xfd) | ((hdr.flags & 1) << 1);

	/* Drop duplicate points and renumber every polygon corner. */
	if (hdr.flags == 0) {
		i = 0;
		off = 0;
		while (i < hdr.anzahl_poi) {
			j = 0;
			off2 = 0;
			while (j < hdr.anzahl_poi) {
				if (i != j && fcn_00451840((float*) ((char*) hdr.poi + off),
					(float*) ((char*) hdr.poi + off2), 0.001f)) {
					for (k = 0; k < hdr.anzahl_pol; k++) {
						for (m = 0; m < 3; m++) {
							n = hdr.pol[k].ecken[m];
							if (n == j) {
								hdr.pol[k].ecken[m] = i;
							}
							else if (n > j) {
								hdr.pol[k].ecken[m] = n - 1;
							}
						}
					}
					hdr.anzahl_poi--;
					fcn_0064d740((char*) hdr.poi + off,
						(char*) hdr.poi + off + 0x18,
						(hdr.anzahl_poi - i) * 0x18);
				}
				else {
					j++;
					off2 += 0x18;
				}
			}
			i++;
			off += 0x18;
		}
	}

	/* Build the transformed point array, three floats per point. */
	obj->anzahl_punkte = hdr.anzahl_poi;
	obj->punkte = m_alloc((hdr.anzahl_poi * 3 + 0x18) * 8, (char*) 0x67afcc);
	sb = (float) sin(*(double*) 0x662d08);
	cb = (float) cos(*(double*) 0x662d08);
	sa = (float) sin(*(double*) 0x662cc8);
	ca = (float) cos(*(double*) 0x662cc8);
	for (i = 0; i < obj->anzahl_punkte; i++) {
		off = i * 0x18;
		ax = *(float*) ((char*) hdr.poi + off);
		ay = *(float*) ((char*) hdr.poi + off + 4);
		az = *(float*) ((char*) hdr.poi + off + 8);
		fu = cb * ay - sb * az;
		fv = cb * az + sb * ay;
		fw = ca * fv - ax * sa;
		ft = (sa * fv + ca * ax) * *(float*) 0x662a94;
		obj->punkte[i * 6] = ca * ft + fw * sa;
		obj->punkte[i * 6 + 1] = fu;
		obj->punkte[i * 6 + 2] = fw * ca - ft * sa;
	}

	/* Drop duplicate texture records, remapping polygon materials. */
	if (hdr.anzahl_tex > 0) {
		seen = m_alloc(hdr.anzahl_tex, (char*) 0x67afb0);
		if (hdr.anzahl_tex > 0) {
			n = 1;
			off = 0;
			do {
				if (seen[n - 1] == 0) {
					seen[n - 1] = 1;
					if (n < hdr.anzahl_tex) {
						off2 = off + 0xe0;
						for (j = n; j < hdr.anzahl_tex; j++) {
							if (memcmp((char*) hdr.tex + off,
								(char*) hdr.tex + off2, 0xe0) == 0) {
								for (k = 0; k < hdr.anzahl_pol; k++) {
									if (hdr.pol[k].material == j) {
										hdr.pol[k].material = n - 1;
									}
								}
								seen[j] = 1;
							}
							off2 += 0xe0;
						}
					}
				}
				n++;
				off += 0xe0;
			} while (n - 1 < hdr.anzahl_tex);
		}
		m_FreeTracked(seen);

		/* Drop texture records no polygon refers to. */
		list = m_alloc(hdr.anzahl_tex, (char*) 0x67af94);
		n = hdr.anzahl_tex;
		if (hdr.anzahl_pol > 0) {
			for (k = 0; k < hdr.anzahl_pol; k++) {
				idx = hdr.pol[k].material;
				if (idx >= 0) {
					list[idx] = 1;
				}
			}
		}
		i = 0;
		off = 0;
		while (i < n) {
			if (list[i] == 0) {
				for (k = 0; k < hdr.anzahl_pol; k++) {
					if (hdr.pol[k].material > i) {
						hdr.pol[k].material--;
					}
				}
				n--;
				fcn_0064d740((char*) hdr.tex + off,
					(char*) hdr.tex + off + 0xe0, (n - i) * 0xe0);
				fcn_0064d740(list + i, list + i + 1, n - i);
			}
			else {
				i++;
				off += 0xe0;
			}
		}
		hdr.anzahl_tex = n;
		m_FreeTracked(list);
	}

	obj->anzahl_polys = hdr.anzahl_pol;
	obj->polys = m_alloc(hdr.anzahl_pol * 0x38, (char*) 0x67af80);
	memcpy(obj->polys, hdr.pol, hdr.anzahl_pol * 0x38);

	/* Compact the used texture records to the front of the header block. */
	seen = m_alloc(hdr.anzahl_tex, (char*) 0x67af68);
	snapshot = m_alloc(hdr.anzahl_tex * 0xe0, (char*) 0x67af50);
	memcpy(snapshot, hdr.tex, hdr.anzahl_tex * 0xe0);
	newn = 0;
	copyoff = 0;
	for (k = 0; k < obj->anzahl_polys; k++) {
		idx = hdr.pol[k].material;
		if (idx >= 0 && seen[idx] == 0) {
			seen[idx] = 1;
			for (m = 0; m < obj->anzahl_polys; m++) {
				if (hdr.pol[m].material == idx) {
					obj->polys[m].material = newn;
				}
			}
			memcpy((char*) hdr.tex + copyoff, snapshot + idx * 0xe0, 0xe0);
			newn++;
			copyoff += 0xe0;
		}
	}
	m_FreeTracked(snapshot);
	m_FreeTracked(seen);

	/* Rotate the two components of every polygon corner pair. */
	for (i = 0; i < obj->anzahl_polys; i++) {
		idx = obj->polys[i].material;
		if (idx < 0) {
			continue;
		}
		tex = hdr.tex + idx;
		for (m = 0; m < 3; m++) {
			ax = obj->polys[i].uv[m * 2];
			ay = obj->polys[i].uv[m * 2 + 1];
			fu = ax * tex->f_0cc + *(float*) 0x6628cc
				- tex->f_0cc * *(float*) 0x6628cc;
			fv = ay * tex->f_0d0 + *(float*) 0x6628cc
				- tex->f_0d0 * *(float*) 0x6628cc;
			fw = tex->f_0dc;
			obj->polys[i].uv[m * 2] = (float) cos(fw) * fu
				- (float) sin(fw) * fv + tex->f_0d4;
			fk = tex->f_0dc + *(float*) 0x6628fc;
			obj->polys[i].uv[m * 2 + 1] = (float) cos(fk) * fv
				+ (float) sin(fk) * fu + tex->f_0d8;
		}
	}

	/* Name table: caller supplied one wins only when the counts agree. */
	if (nametab != 0 && namestep > 0 && namecount == hdr.anzahl_tex) {
		obj->anzahl_texnamen = namecount;
		obj->tex_stride = namestep;
		obj->texnamen = nametab;
	}
	else {
		obj->anzahl_texnamen = hdr.anzahl_tex;
		obj->tex_stride = 1;
		obj->texnamen = m_alloc(hdr.anzahl_tex << 6, (char*) 0x67af38);
		dst = obj->texnamen;
		for (i = 0; i < hdr.anzahl_tex; i++) {
			p = (char*) hdr.tex + i * 0xe0;
			if (p[0x80]) {
				strcpy(dst, p + 0x80);
			}
			else if (p[0]) {
				strcpy(dst, p);
			}
			else if (p[0x40]) {
				strcpy(dst, p + 0x40);
			}
			dst += 0x40;
		}
	}

	list = m_alloc(obj->anzahl_polys, (char*) 0x67af20);
	info = 0;
	((unsigned char*) &info)[0] = 0xff;
	for (i = 0; i < obj->anzahl_texnamen; i++) {
		tex = hdr.tex + i;
		if (tex->typ_0c0 != 0) {
			((unsigned char*) &info)[0] = tex->idx_0c1;
			if (tex->typ_0c0 == 2) {
				((unsigned char*) &info)[2] |= 1;
			}
		}
		((unsigned char*) &info)[1] = tex->f_0c7;
		((unsigned char*) &info)[2] = (((unsigned char*) &info)[2] & 0xfd)
			| ((tex->f_0c2 & 1) << 1);
		c2 = (tex->f_0c8 << 4) | tex->f_0c9;
		c1 = (((tex->f_0c3 << 4) | tex->f_0c6) << 1) | tex->f_0c5;
		c1 <<= 1;
		if (tex->name_080[0] != 0) {
			c1 |= 1;
		}
		r = (void*) fcn_0045c5b0(obj->texnamen + i * 0x40, info, c1, c2);
		if (r != 0) {
			idx = ((int) r - *(int*) 0x104049c) / 0x70;
		}
		else {
			idx = -1;
		}
		for (k = 0; k < obj->anzahl_polys; k++) {
			if (list[k] == 0 && obj->polys[k].material == i) {
				obj->polys[k].idx_024 = idx;
				list[k] = 1;
			}
		}
	}
	m_FreeTracked(list);

	for (i = 0; i < hdr.anzahl_teil; i++) {
		fcn_0064d530(obj->teile[i].name, hdr.teil[i].name, 0x3f);
		obj->teile[i].name[0x3f] = 0;
		obj->teile[i].wert[0] = hdr.teil[i].wert[0];
		obj->teile[i].wert[1] = hdr.teil[i].wert[1];
		obj->teile[i].wert[2] = hdr.teil[i].wert[2];
		obj->teile[i].wert[3] = hdr.teil[i].wert[3];
		obj->teile[i].wert[4] = hdr.teil[i].wert[4];
		obj->teile[i].wert[5] = hdr.teil[i].wert[5];
	}
	fcn_0044a770(obj, 1);

cleanup:
	if (hdr.anzahl_tex > 0 && hdr.tex != 0) {
		m_FreeTracked(hdr.tex);
	}
	if (hdr.anzahl_pol > 0 && hdr.pol != 0) {
		m_FreeTracked(hdr.pol);
	}
	if (hdr.anzahl_poi > 0 && hdr.poi != 0) {
		m_FreeTracked(hdr.poi);
	}
	return (BGF_OBJ*) res;
}
#pragma optimize("", on)
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")
unsigned char _tlead_GOLDTL_fcn_0044b480[256] = {
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90
};
