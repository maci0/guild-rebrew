#include <math.h>
#include <string.h>

extern void* g_6b7fdc;

void* __cdecl vfs_Tfopen(char*, char*, void*);
void __cdecl fcn_0044e190(void*, void*);
void __cdecl CloseVfsStream(void*);
void* __cdecl m_alloc(int, char*);
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_0044f8e0(char*);
void __cdecl fcn_0044f7e0(char*);
int __cdecl fcn_0044fba0(char*, char*);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
int __cdecl vfs_ReadData(char*, int, int, char*);
unsigned int __cdecl vfs_fwrite(void*, int, int, char*);
int __cdecl vfs_fseek(char*, int, int);
int __cdecl vfs_ftell(char*);
void __cdecl fcn_00401210(void*, char);
void __cdecl fcn_00401230(void*, void*);
void __cdecl fcn_00401260(void*, int);
void __cdecl fcn_004012f0(void*, void*);
void __cdecl fcn_00401360(void*, int);

/* SIZE 0x18 */
typedef struct FL_POI {
	float pos[3];
	float unbekannt[3];
} FL_POI;

/* SIZE 0x38 */
typedef struct FL_POL {
	float ecke[3][2];
	int idx[3];
	int material_tmp;
	int material;
	float normal[3];
} FL_POL;

/* SIZE 0x58 */
typedef struct FL_BONE {
	char name[0x40];
	float a[3];
	float b[3];
} FL_BONE;

/* SIZE 0xe0 - material entry. The three name blocks and the packed flag
 * bytes at 0xc0 keep offset names; their original meanings are unidentified. */
typedef struct FL_MAT {
	char str00[0x40];
	char str40[0x40];
	char str80[0x40];
	unsigned char b_c0;
	unsigned char b_c1;
	unsigned char b_c2;
	unsigned char b_c3;
	unsigned char b_c4;
	unsigned char b_c5;
	unsigned char b_c6;
	unsigned char b_c7;
	unsigned char b_c8;
	unsigned char b_c9;
	char pad_ca[2];
	float f_cc;
	float f_d0;
	float f_d4;
	float f_d8;
	float winkel;
} FL_MAT;

/* SIZE 0x198 - chunk description decoded by fcn_0044e190 */
typedef struct FL_INFO {
	char pad00[1];
	char f01;
	char pad02[0xa];
	int anzahl_mat;
	FL_MAT* mat;
	char pad14[8];
	int anzahl_pol;
	FL_POL* pol;
	char pad24[8];
	int anzahl_poi;
	FL_POI* poi;
	int anzahl_bone;
	FL_BONE bone[4];
} FL_INFO;

/* SIZE 0x2a4 - chunk object: 0x40-byte header followed by the model arrays */
typedef struct FL_OBJ {
	char kopf[0x40];
	FL_POI* poi;
	int anzahl_poi;
	FL_POL* pol;
	int anzahl_pol;
	char pad50[0x184];
	float radius;
	char pad1d8[0xc];
	int anzahl_mat;
	int f1e8;
	char pad1ec[0xb8];
} FL_OBJ;

/* Attested by its allocator tags ("d3_io_fl:AddFLChunk"), which also name the
 * chunk sections: obj, poi, pol, TempMat[ReOrder], RemoveDoubleMaterials.
 * Reads a fast chunk, merges duplicate points when asked, rotates the point
 * and face-corner data through the material transforms, then writes the
 * chunk back through the 0x4012xx bit-stream helpers. */
#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0044fc70 */
void __cdecl d3_AddFLChunk(char* name, char flag)
{
	FL_INFO info;
	char pfad[0x110];
	FL_OBJ* obj;
	void* stream;
	unsigned char* marker;
	FL_MAT* tmpmat;
	FL_MAT* mat;
	FL_POL* pol;
	int i;
	int j;
	int k;
	int n;
	int material;
	int dstoff;
	int len;
	int newcount;
	char* buf;
	float sina;
	float cosa;
	float sinb;
	float cosb;
	float vx;
	float vy;
	float vz;
	float x1;
	float z1;
	float tmp[3];

	strcpy(pfad, name);
	memset(&info, 0, sizeof(info));
	stream = vfs_Tfopen(name, "rb", g_6b7fdc);
	if (stream == 0) {
		return;
	}
	fcn_0044e190(stream, &info);
	if (info.anzahl_pol <= 0 || info.anzahl_poi <= 0) {
		CloseVfsStream(stream);
		return;
	}
	obj = (FL_OBJ*) m_alloc(0x2a4, "d3_io_fl:AddFLChunk(obj)");
	if (info.f01 == 0 && flag != 0) {
		for (i = 0; i < info.anzahl_poi; i++) {
			for (j = 0; j < info.anzahl_poi; j++) {
				if (i == j) {
					continue;
				}
				if (!CompareVector3WithinTolerance(info.poi[i].pos, info.poi[j].pos, 0.001f)) {
					continue;
				}
				for (k = 0; k < info.anzahl_pol; k++) {
					for (n = 0; n < 3; n++) {
						material = info.pol[k].idx[n];
						if (material == j) {
							material = i;
						} else if (material > j) {
							material--;
						}
						info.pol[k].idx[n] = material;
					}
				}
				info.anzahl_poi--;
				memmove(&info.poi[j], &info.poi[j + 1], (info.anzahl_poi - j) * sizeof(FL_POI));
				j--;
			}
		}
	}
	obj->anzahl_poi = info.anzahl_poi;
	obj->poi = (FL_POI*) m_alloc((info.anzahl_poi * 3 + 0x18) * 8, "d3_io_fs:AddFLChunk(poi)");
	sina = (float) sin(-1.5707963705062866);
	cosa = (float) cos(-1.5707963705062866);
	sinb = (float) sin(3.1415927410125732);
	cosb = (float) cos(3.1415927410125732);
	for (i = 0; i < obj->anzahl_poi; i++) {
		vx = info.poi[i].pos[0];
		vy = cosa * info.poi[i].pos[1] - sina * info.poi[i].pos[2];
		vz = sina * info.poi[i].pos[1] + cosa * info.poi[i].pos[2];
		x1 = vx * cosb + vz * sinb;
		z1 = vz * cosb - vx * sinb;
		obj->poi[i].pos[0] = x1 * -1.0 * cosb + z1 * sinb;
		obj->poi[i].pos[1] = vy;
		obj->poi[i].pos[2] = z1 * cosb - x1 * sinb;
	}
	if (info.anzahl_mat > 0) {
		marker = (unsigned char*) m_alloc(info.anzahl_mat, "d3_io_fs:RemoveDoubleMaterials");
		for (j = 1; j < info.anzahl_mat; j++) {
			if (marker[j - 1] != 0) {
				continue;
			}
			marker[j - 1] = 1;
			for (i = j; i < info.anzahl_mat; i++) {
				if (memcmp(&info.mat[j - 1], &info.mat[i], sizeof(FL_MAT)) != 0) {
					continue;
				}
				for (n = 0; n < info.anzahl_pol; n++) {
					if (info.pol[n].material == j) {
						info.pol[n].material = j - 1;
					}
				}
				marker[j] = 1;
			}
		}
		memset(marker, 0, info.anzahl_mat);
		for (i = 0; i < info.anzahl_pol; i++) {
			material = info.pol[i].material;
			if (material >= 0) {
				marker[material] = 1;
			}
		}
		i = 0;
		while (i < info.anzahl_mat) {
			if (marker[i] != 0) {
				i++;
				continue;
			}
			for (n = 0; n < info.anzahl_pol; n++) {
				if (info.pol[n].material > i) {
					info.pol[n].material--;
				}
			}
			info.anzahl_mat--;
			memmove(&info.mat[i], &info.mat[i + 1], (info.anzahl_mat - i) * sizeof(FL_MAT));
			memmove(&marker[i], &marker[i + 1], info.anzahl_mat - i);
		}
		m_FreeTracked(marker);
	}
	obj->anzahl_pol = info.anzahl_pol;
	obj->pol = (FL_POL*) m_alloc(info.anzahl_pol * 0x38, "d3_io_fs:AddFLChunk(pol)");
	memcpy(obj->pol, info.pol, info.anzahl_pol * sizeof(FL_POL));
	marker = (unsigned char*) m_alloc(info.anzahl_mat, "d3_io_fs:Materials(bool)");
	tmpmat = (FL_MAT*) m_alloc(info.anzahl_mat * 0xe0, "d3_io_fs:TempMat[ReOrder]");
	memcpy(tmpmat, info.mat, info.anzahl_mat * sizeof(FL_MAT));
	dstoff = 0;
	newcount = 0;
	for (i = 0; i < obj->anzahl_pol; i++) {
		material = info.pol[i].material;
		if (material < 0) {
			continue;
		}
		if (marker[material] != 0) {
			continue;
		}
		marker[material] = 1;
		for (n = 0; n < obj->anzahl_pol; n++) {
			if (info.pol[n].material == material) {
				obj->pol[n].material = newcount;
			}
		}
		memcpy((char*) info.mat + dstoff, &tmpmat[material], sizeof(FL_MAT));
		dstoff += sizeof(FL_MAT);
		newcount++;
	}
	m_FreeTracked(tmpmat);
	m_FreeTracked(marker);
	for (i = 0; i < obj->anzahl_pol; i++) {
		material = obj->pol[i].material;
		if (material < 0) {
			continue;
		}
		mat = &info.mat[material];
		for (n = 0; n < 3; n++) {
			pol = &obj->pol[i];
			x1 = pol->ecke[n][0] * mat->f_cc + 0.5f - mat->f_cc * 0.5f;
			z1 = pol->ecke[n][1] * mat->f_d0 + 0.5f - mat->f_d0 * 0.5f;
			pol->ecke[n][0] = (float) cos(mat->winkel) * x1 - (float) sin(mat->winkel) * z1 + mat->f_d4;
			pol->ecke[n][1] = (float) cos(mat->winkel + 3.1415927f) * z1 + (float) sin(mat->winkel + 3.1415927f) * x1 + mat->f_d8;
		}
	}
	obj->anzahl_mat = info.anzahl_mat;
	obj->f1e8 = 0;
	fcn_0044f8e0((char*) obj);
	fcn_0044f7e0((char*) obj);
	len = vfs_ftell(stream);
	vfs_fseek(stream, 0, 0);
	buf = (char*) m_alloc(len, "d3_io_fl:NotMyChunkBufferStart");
	vfs_ReadData(buf, len, 1, stream);
	CloseVfsStream(stream);
	stream = vfs_Tfopen(pfad, "wb", g_6b7fdc);
	vfs_fwrite(buf, len, 1, stream);
	m_FreeTracked(buf);
	fcn_00401210(stream, 0x2d);
	fcn_00401360(stream, fcn_0044fba0((char*) obj, (char*) &info));
	fcn_00401360(stream, 0xfab50005);
	fcn_00401360(stream, obj->anzahl_mat);
	fcn_00401360(stream, obj->anzahl_poi);
	fcn_00401360(stream, obj->anzahl_pol);
	for (i = 0; i < obj->anzahl_poi + 8; i++) {
		fcn_004012f0(stream, obj->poi[i].pos);
		fcn_004012f0(stream, obj->poi[i].unbekannt);
	}
	fcn_00401260(stream, *(int*) &obj->radius);
	for (i = 0; i < obj->anzahl_pol; i++) {
		pol = &obj->pol[i];
		fcn_00401360(stream, pol->idx[0]);
		fcn_00401360(stream, pol->idx[1]);
		fcn_00401360(stream, pol->idx[2]);
		tmp[0] = pol->ecke[0][0];
		tmp[1] = pol->ecke[1][0];
		tmp[2] = pol->ecke[2][0];
		fcn_004012f0(stream, tmp);
		tmp[0] = pol->ecke[0][1];
		tmp[1] = pol->ecke[1][1];
		tmp[2] = pol->ecke[2][1];
		fcn_004012f0(stream, tmp);
		fcn_004012f0(stream, pol->normal);
		if (obj->anzahl_mat > 0xfe) {
			fcn_00401360(stream, pol->material);
		} else {
			fcn_00401210(stream, pol->material == -1 ? (char) 0xff : (char) pol->material);
		}
	}
	for (i = 0; i < obj->anzahl_mat; i++) {
		mat = &info.mat[i];
		fcn_00401230(stream, mat->str00);
		fcn_00401230(stream, mat->str80);
		fcn_00401230(stream, mat->str40);
		fcn_00401210(stream, (char) mat->b_c0);
		fcn_00401210(stream, (char) mat->b_c1);
		fcn_00401210(stream, (char) (((((mat->b_c3 << 4) | mat->b_c6) << 1) | mat->b_c5) << 1 | mat->b_c2));
		fcn_00401210(stream, (char) ((mat->b_c7 & 0xfe) | mat->b_c4));
		fcn_00401210(stream, (char) mat->b_c8);
		fcn_00401210(stream, (char) mat->b_c9);
	}
	fcn_00401360(stream, info.anzahl_bone);
	for (i = 0; i < info.anzahl_bone; i++) {
		fcn_00401230(stream, info.bone[i].name);
		fcn_004012f0(stream, info.bone[i].a);
		fcn_004012f0(stream, info.bone[i].b);
	}
	fcn_00401210(stream, 0x2f);
	vfs_ftell(stream);
	CloseVfsStream(stream);
	if (info.anzahl_mat > 0 && info.mat != 0) {
		m_FreeTracked(info.mat);
		info.mat = 0;
	}
	if (obj->anzahl_pol > 0 && obj->pol != 0) {
		m_FreeTracked(obj->pol);
		obj->pol = 0;
	}
	if (info.anzahl_pol > 0 && info.pol != 0) {
		m_FreeTracked(info.pol);
		info.pol = 0;
	}
	if (obj->anzahl_poi > 0 && obj->poi != 0) {
		m_FreeTracked(obj->poi);
		obj->poi = 0;
	}
	if (info.anzahl_poi > 0 && info.poi != 0) {
		m_FreeTracked(info.poi);
		info.poi = 0;
	}
	m_FreeTracked(obj);
}
#pragma optimize("", on)
