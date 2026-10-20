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
 * the middle float to 60.0. Strings are read NUL terminated into 0x40 byte
 * slots.
 */

typedef struct S447e30Rec {
	int h0;
	int h1;
	int bits;
	float f0c;
	float f10;
	float f14;
	float block[4];
	int extra[4];
	int pad[0x11c];
	int tail;
} S447e30Rec;

int __cdecl fcn_0041d9e0(char*);
char* __cdecl fcn_004011a0(char*, char*);
int __cdecl fcn_00401180(char*, char*);
int __cdecl fcn_004011f0(char*, int*);
int __cdecl fcn_004011d0(char*, float*);
int __cdecl fcn_004012b0(char*, void*);
int __cdecl fcn_00401280(char*, void*);
int __cdecl fcn_00401500(char*, int, int*);
void* __cdecl fcn_0041db70(int, char*);
void __cdecl fcn_0041ddd0(void*);
int __cdecl fcn_0045c5b0(char*, int, int, int);
int __cdecl fcn_0045ce90(int);
char* __cdecl fcn_0043fa10(char*);

/* ADDRESS: GOLDTL 0x00447e30 */
int __cdecl fcn_00447e30(char* stream, unsigned int version)
{
	char name[0x2a4];
	char recName[0x40];
	char skip[0x100];
	char strings[8][0x40];
	char flag;
	int listB;
	int listA;
	int listC;
	int listD;
	int listE;
	int count;
	int i;
	int saved;
	int last;
	int tri[3];
	int handle;
	int mask;
	S447e30Rec* recs;
	S447e30Rec* rec;
	char* obj;
	char kind;
	char b0;
	char b1;
	char b2;
	int bits;

	handle = 0;
	last = 0;
	listA = 0;
	listB = 0;
	listC = 0;
	listD = 0;
	listE = 0;
	mask = 0;
	recs = 0;
	obj = 0;
	if (version < 0x3a6c0009) {
		fcn_0041d9e0((char*) 0x67abe0);
		return 0;
	}
	memset(name, 0, 0x2a4);
	fcn_004011a0(stream, name);
	if (name[0] != 0 && version >= 0x3a6c00ad) {
		fcn_004011f0(stream, &listA);
		fcn_00401500(stream, listA, &listB);
		if (version >= 0x3a6c00bb) {
			fcn_00401500(stream, listA * 4, &listC);
		}
	}
	if (version >= 0x3a6c00aa) {
		fcn_00401180(stream, &flag);
		if (flag != 0) {
			fcn_004011f0(stream, &count);
			if (count > 0) {
				if (version >= 0x3a6c00ad) {
					fcn_00401500(stream, listA, &listD);
				}
				recs = (S447e30Rec*) fcn_0041db70(count * 0x158, (char*) 0x67ac08);
				saved = 0;
				rec = recs;
				while (saved < count) {
					last = 0;
					handle = 0;
					fcn_004011a0(stream, recName);
					fcn_00401180(stream, &kind);
					fcn_00401180(stream, &b1);
					fcn_00401180(stream, &b2);
					if (recName[0] != 0) {
						mask = ((b1 & 0x0f) << 2) | (b2 & 1);
						last = fcn_0045c5b0(recName, 0x7f, mask, 0);
						if (last != 0) {
							fcn_0045ce90(last);
						}
					}
					bits = 0;
					fcn_00401180(stream, &b0);
					((char*) &bits)[0] = b0;
					fcn_00401180(stream, &b1);
					((char*) &bits)[1] = b1;
					fcn_00401180(stream, &b2);
					((char*) &bits)[2] = (b2 & 1);
					fcn_00401180(stream, &b0);
					((char*) &bits)[2] |= (b0 & 1) << 1;
					rec->h0 = last;
					rec->h1 = last;
					rec->bits = bits;
					if (version >= 0x3a6c00b6) {
						fcn_004011d0(stream, &rec->f14);
					} else {
						rec->f14 = 60.0f;
					}
					fcn_004011d0(stream, &rec->f0c);
					fcn_004011d0(stream, &rec->f10);
					fcn_004012b0(stream, rec->block);
					if (version < 0x3a6c00ac) {
						rec->block[0] *= *(float*) 0x662a68;
						rec->block[1] *= *(float*) 0x662a68;
						rec->block[2] *= *(float*) 0x662a68;
						rec->block[3] *= *(float*) 0x662a68;
					}
					fcn_004012b0(stream, rec->extra);
					if (version >= 0x3a6c00b9) {
						fcn_004011f0(stream, &rec->tail);
					} else {
						rec->tail = 0;
					}
					saved++;
					rec++;
				}
			}
		}
	}
	fcn_004011a0(stream, name);
	if (version >= 0x3a6c00ad && name[0] != 0) {
		fcn_00401500(stream, listA, &listE);
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
		fcn_004011a0(stream, strings[saved]);
	}
	fcn_004011d0(stream, (float*) &last);
	fcn_004011d0(stream, (float*) &count);
	if (version <= 0x3a6c000f) {
		for (i = 0; i < 0x100; i++) {
			fcn_004011a0(stream, skip);
		}
	}
	obj = fcn_0043fa10(name);
	if (version >= 0x3a6c000e) {
		fcn_00401280(stream, tri);
		if (obj != 0) {
			*(int*) (obj + 0x50) = tri[0];
			*(int*) (obj + 0x54) = tri[1];
			*(int*) (obj + 0x58) = tri[2];
		}
	}
	if (recs != 0) {
		fcn_0041ddd0(recs);
		recs = 0;
	}
	if (listD != 0) {
		fcn_0041ddd0((void*) listD);
		listD = 0;
	}
	if (listB != 0) {
		fcn_0041ddd0((void*) listB);
		listB = 0;
	}
	if (listC != 0) {
		fcn_0041ddd0((void*) listC);
		listC = 0;
	}
	if (listE != 0) {
		fcn_0041ddd0((void*) listE);
		listE = 0;
	}
	return (int) obj;
}
