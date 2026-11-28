#include <string.h>

/*
 * Versioned binary record loader for the "kugel" scene description.
 *
 * The stream is read sequentially and the version word decides which fields
 * exist. A leading name selects an object; optional byte/dword tables follow
 * for newer versions, then a record array of 0x158 bytes per entry. Each
 * record carries two equal handles, a two bit field packed across four bytes,
 * three floats and two 16 byte blocks, plus a trailing dword from the newest
 * format. The older formats scale the first block by dat_662a68 and default
 * the middle float to 63.0. Strings are read NUL terminated into 0x40 byte
 * slots.
 */

/* Same layout as the Col argument of fcn_0045c5b0. */
typedef struct FLOOR_COLOR_BITS {
	unsigned char a;
	unsigned char b;
	unsigned char c0 : 1;
	unsigned char c1 : 1;
	unsigned char c2 : 6;
	unsigned char d;
} FLOOR_COLOR_BITS;

typedef struct FLOOR_WATER_REC {
	int h0;
	int h1;
	FLOOR_COLOR_BITS bits;
	float f0c;
	float f10;
	float f14;
	float block[4];
	int extra[4];
	char pad[0x11c];
	int tail;
} FLOOR_WATER_REC;

typedef struct FLOOR_DESC {
	char name[0x40];
	int listB;
	int listD;
	char texture[0x40];
	int listE;
	int listC;
	float scale;
	float height;
	int count;
	int listA;
	FLOOR_WATER_REC* recs;
	char strings[8][0x40];
} FLOOR_DESC;

#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl ReportClientMessage(char*);
char* __cdecl vfs_ReadCString(char*, char*);
int __cdecl vfs_ReadByte(char*, char*);
int __cdecl fcn_004011f0(char*, int*);
int __cdecl vfs_ReadDword(char*, float*);
int __cdecl ReadVfsFourDwords(char*, void*);
int __cdecl vfs_ReadVec3(char*, void*);
int __cdecl bio_rd_array_quick(char*, int, int*);
void* __cdecl m_alloc(int, char*);
void __cdecl m_FreeTracked(void*);
int __cdecl d3_LoadOrReuseTexture(char*, FLOOR_COLOR_BITS, unsigned int, unsigned int);
int __cdecl d3_LoadTextureSurfaceTl(int);
char* __cdecl d3_LoadFloorPatch(char*);

/* ADDRESS: GOLDTL 0x00447e30 */
int __cdecl d3_int_io_LoadFloor(char* stream, unsigned int version)
{
	FLOOR_DESC desc;
	char recName[0x40];
	char skip[0x100];
	char flag;
	int i;
	int saved;
	int last;
	int tri[3];
	int handle;
	int mask;

	char* obj;
	char kind;

	char b1;
	char b2;
	FLOOR_COLOR_BITS bits;
	void* fill_dst;
	int fill_size;


	last = 0;
	mask = 0;
	obj = 0;
	if (version >= 0x3a6c0009) {
		fill_dst = &desc;
		fill_size = sizeof(desc);
		__asm {
			mov edi, fill_dst
			mov ebx, fill_size
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L447e30fill
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L447e30fill:
			add ecx, ebx
			rep stosb
		}
		vfs_ReadCString(stream, desc.name);
		if (desc.name[0] != 0 && version >= 0x3a6c00ad) {
			fcn_004011f0(stream, &desc.listA);
			bio_rd_array_quick(stream, desc.listA, &desc.listB);
			if (version >= 0x3a6c00bb) {
				bio_rd_array_quick(stream, desc.listA * 4, &desc.listC);
			}
		}
		if (version >= 0x3a6c00aa) {
			vfs_ReadByte(stream, &flag);
			if (flag != 0) {
				fcn_004011f0(stream, &desc.count);
				if (desc.count > 0) {
					if (version >= 0x3a6c00ad) {
						bio_rd_array_quick(stream, desc.listA, &desc.listD);
					}
					desc.recs = (FLOOR_WATER_REC*) m_alloc(desc.count * 0x158, (char*) 0x67ac08);
					saved = 0;

					while (saved < desc.count) {
						last = 0;

						vfs_ReadCString(stream, recName);
						vfs_ReadByte(stream, &kind);
						vfs_ReadByte(stream, &b1);
						vfs_ReadByte(stream, &b2);
						if (recName[0] != 0) {
							mask = ((b1 & 0x0f) << 2) | (b2 & 1);
							memset(&bits, 0, sizeof(bits)); bits.a = 0x7f; last = d3_LoadOrReuseTexture(recName, bits, mask, 0);
							if (last != 0) {
								d3_LoadTextureSurfaceTl(last);
							}
						}
						memset(&bits, 0, sizeof(bits));
						vfs_ReadByte(stream, &flag);
						bits.a = flag;
						vfs_ReadByte(stream, &flag);
						bits.b = flag;
						vfs_ReadByte(stream, &flag);
						bits.c0 = flag;
						vfs_ReadByte(stream, &flag);
						bits.c1 = flag;
						desc.recs[saved].h1 = last;
						desc.recs[saved].h0 = last;
						desc.recs[saved].bits = bits;
						if (version >= 0x3a6c00b6) {
							vfs_ReadDword(stream, &desc.recs[saved].f14);
						} else {
							desc.recs[saved].f14 = 63.0f;
						}
						vfs_ReadDword(stream, &desc.recs[saved].f0c);
						vfs_ReadDword(stream, &desc.recs[saved].f10);
						ReadVfsFourDwords(stream, desc.recs[saved].block);
						if (version < 0x3a6c00ac) {
							desc.recs[saved].block[0] *= 0.33333334f;
							desc.recs[saved].block[1] *= 0.33333334f;
							desc.recs[saved].block[2] *= 0.33333334f;
							desc.recs[saved].block[3] *= 0.33333334f;
						}
						ReadVfsFourDwords(stream, desc.recs[saved].extra);
						if (version >= 0x3a6c00b9) {
							fcn_004011f0(stream, &handle); desc.recs[saved].tail = handle;
						} else {
							desc.recs[saved].tail = 0;
						}
						saved++;

					}
				}
			}
		}
		vfs_ReadCString(stream, desc.texture);
		if (version >= 0x3a6c00ad && desc.texture[0] != 0) {
			bio_rd_array_quick(stream, desc.listA, &desc.listE);
		}
		if (version <= 0x3a6c000f) {
			for (i = 0; i < 5; i++) {
				vfs_ReadCString(stream, skip);
			}
		}
		if (version >= 0x3a6c00b0) {
			i = 8;
		} else {
			i = 6;
		}
		for (saved = 0; saved < i; saved++) {
			vfs_ReadCString(stream, desc.strings[saved]);
		}
		vfs_ReadDword(stream, &desc.scale);
		vfs_ReadDword(stream, &desc.height);
		if (version <= 0x3a6c000f) {
			for (i = 0; i < 0x100; i++) {
				vfs_ReadCString(stream, skip);
			}
		}
		obj = d3_LoadFloorPatch((char*) &desc);
		if (version >= 0x3a6c000e) {
			vfs_ReadVec3(stream, tri);
			if (obj != 0) {
				*(int*) (obj + 0x50) = tri[0];
				*(int*) (obj + 0x54) = tri[1];
				*(int*) (obj + 0x58) = tri[2];
			}
		}
		if (desc.recs != 0) {
			m_FreeTracked(desc.recs);
			desc.recs = 0;
		}
		if (desc.listE != 0) {
			m_FreeTracked((void*) desc.listE);
			desc.listE = 0;
		}
		if (desc.listD != 0) {
			m_FreeTracked((void*) desc.listD);
			desc.listD = 0;
		}
		if (desc.listB != 0) {
			m_FreeTracked((void*) desc.listB);
			desc.listB = 0;
		}
		if (desc.listC != 0) {
			m_FreeTracked((void*) desc.listC);
			desc.listC = 0;
		}
	} else {
		ReportClientMessage((char*) 0x67abe0);
	}
	return (int) obj;
}
