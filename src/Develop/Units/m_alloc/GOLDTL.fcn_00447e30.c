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
typedef struct Col447e30 {
	unsigned char a;
	unsigned char b;
	unsigned char c0 : 1;
	unsigned char c1 : 1;
	unsigned char c2 : 6;
	unsigned char d;
} Col447e30;

typedef struct S447e30Rec {
	int h0;
	int h1;
	Col447e30 bits;
	float f0c;
	float f10;
	float f14;
	float block[4];
	int extra[4];
	char pad[0x11c];
	int tail;
} S447e30Rec;

typedef struct S447e30Desc {
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
	S447e30Rec* recs;
	char strings[8][0x40];
} S447e30Desc;

extern float g_662a68;
int __cdecl ReportClientMessage(char*);
char* __cdecl fcn_004011a0(char*, char*);
int __cdecl fcn_00401180(char*, char*);
int __cdecl fcn_004011f0(char*, int*);
int __cdecl fcn_004011d0(char*, float*);
int __cdecl ReadVfsFourDwords(char*, void*);
int __cdecl fcn_00401280(char*, void*);
int __cdecl bio_rd_array_quick(char*, int, int*);
void* __cdecl m_alloc(int, char*);
void __cdecl m_FreeTracked(void*);
int __cdecl fcn_0045c5b0(char*, Col447e30, unsigned int, unsigned int);
int __cdecl fcn_0045ce90(int);
char* __cdecl fcn_0043fa10(char*);

/* ADDRESS: GOLDTL 0x00447e30 */
int __cdecl fcn_00447e30(char* stream, unsigned int version)
{
	S447e30Desc desc;
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
	Col447e30 bits;
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
		fcn_004011a0(stream, desc.name);
		if (desc.name[0] != 0 && version >= 0x3a6c00ad) {
			fcn_004011f0(stream, &desc.listA);
			bio_rd_array_quick(stream, desc.listA, &desc.listB);
			if (version >= 0x3a6c00bb) {
				bio_rd_array_quick(stream, desc.listA * 4, &desc.listC);
			}
		}
		if (version >= 0x3a6c00aa) {
			fcn_00401180(stream, &flag);
			if (flag != 0) {
				fcn_004011f0(stream, &desc.count);
				if (desc.count > 0) {
					if (version >= 0x3a6c00ad) {
						bio_rd_array_quick(stream, desc.listA, &desc.listD);
					}
					desc.recs = (S447e30Rec*) m_alloc(desc.count * 0x158, (char*) 0x67ac08);
					saved = 0;

					while (saved < desc.count) {
						last = 0;

						fcn_004011a0(stream, recName);
						fcn_00401180(stream, &kind);
						fcn_00401180(stream, &b1);
						fcn_00401180(stream, &b2);
						if (recName[0] != 0) {
							mask = ((b1 & 0x0f) << 2) | (b2 & 1);
							memset(&bits, 0, sizeof(bits)); bits.a = 0x7f; last = fcn_0045c5b0(recName, bits, mask, 0);
							if (last != 0) {
								fcn_0045ce90(last);
							}
						}
						memset(&bits, 0, sizeof(bits));
						fcn_00401180(stream, &flag);
						bits.a = flag;
						fcn_00401180(stream, &flag);
						bits.b = flag;
						fcn_00401180(stream, &flag);
						bits.c0 = flag;
						fcn_00401180(stream, &flag);
						bits.c1 = flag;
						desc.recs[saved].h1 = last;
						desc.recs[saved].h0 = last;
						desc.recs[saved].bits = bits;
						if (version >= 0x3a6c00b6) {
							fcn_004011d0(stream, &desc.recs[saved].f14);
						} else {
							desc.recs[saved].f14 = 63.0f;
						}
						fcn_004011d0(stream, &desc.recs[saved].f0c);
						fcn_004011d0(stream, &desc.recs[saved].f10);
						ReadVfsFourDwords(stream, desc.recs[saved].block);
						if (version < 0x3a6c00ac) {
							desc.recs[saved].block[0] *= g_662a68;
							desc.recs[saved].block[1] *= g_662a68;
							desc.recs[saved].block[2] *= g_662a68;
							desc.recs[saved].block[3] *= g_662a68;
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
		fcn_004011a0(stream, desc.texture);
		if (version >= 0x3a6c00ad && desc.texture[0] != 0) {
			bio_rd_array_quick(stream, desc.listA, &desc.listE);
		}
		if (version <= 0x3a6c000f) {
			for (i = 0; i < 5; i++) {
				fcn_004011a0(stream, skip);
			}
		}
		if (version >= 0x3a6c00b0) {
			i = 8;
		} else {
			i = 6;
		}
		for (saved = 0; saved < i; saved++) {
			fcn_004011a0(stream, desc.strings[saved]);
		}
		fcn_004011d0(stream, &desc.scale);
		fcn_004011d0(stream, &desc.height);
		if (version <= 0x3a6c000f) {
			for (i = 0; i < 0x100; i++) {
				fcn_004011a0(stream, skip);
			}
		}
		obj = fcn_0043fa10((char*) &desc);
		if (version >= 0x3a6c000e) {
			fcn_00401280(stream, tri);
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
