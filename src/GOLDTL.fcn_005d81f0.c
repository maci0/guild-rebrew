#include <string.h>

extern char* __cdecl fcn_00508e40(int);
extern char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern void __cdecl fcn_004c6ae0(int, int);
extern int __cdecl fcn_004c5420(int, int, int, int, int);
extern void __cdecl fcn_0051af00(char*, int, ...);
extern void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
extern void __cdecl fcn_005099e0(char*, int);
extern void __cdecl fcn_004c57e0(int, int);
extern char* __cdecl fcn_005bdc30(int, int*, char*, int, int);
extern int __cdecl fcn_00470820(int, int, char*);
extern void __cdecl fcn_00473a90(int, int);
extern void __cdecl fcn_00471b60(int);
extern void __cdecl fcn_004727a0(int, int);
extern int __cdecl fcn_00519190(int, int, int, int);
extern int __cdecl fcn_00472250(int, int, int);
extern int __cdecl fcn_00525f60(char*, int);
extern int __cdecl fcn_004c4450(int);
extern void __cdecl fcn_00535960(void);
extern void __cdecl fcn_00526120(char*, int);
extern int __cdecl gm_RandomMod(int);
extern int __cdecl fcn_005373e0(int, int);
extern void __cdecl fcn_00471e30(int);

/* Validates the current entity action against its target and executes the
 * action's announce/notify path; returns one of the 0x10/0x20/0x60/0x81 codes. */
/* ADDRESS: GOLDTL 0x005d81f0 */
unsigned int __cdecl fcn_005d81f0(char* a0, int* a1)
{
	unsigned int found[4];
	char text[512];
	char name[256];
	char* ent;
	char* other;
	char* rec;
	int state;
	int id;
	int saved;
	int i;
	int j;
	int count;
	int kid;
	int ret;
	int thr;
	unsigned int r;

	ret = 0;
	saved = -1;
	if (*(unsigned char*) (a0 + 2) != 6) {
		if (*(int*) (a0 + 0x194) <= 4)
			return 0x20;
		if (*a1 != 3 || (*(unsigned char*) (a0 + 0x1c8) & 0x80) != 0) {
			if (*a1 != 4)
				return 0x60;
			other = (char*) a1[0x87];
			if (other == 0)
				return 0x60;
			if ((*(unsigned char*) (other + 0x1c8) & 0x80) != 0)
				return 0x60;
		} else {
			other = a0;
		}
		ent = fcn_00508e40(a1[0x85]);
		rec = gm_StartFilteredEntitySearch(1, 1, a1[0x86]);
		if (ent != 0 && rec != 0) {
			fcn_004c6ae0(*(int*) (a0 + 4), -5);
			fcn_004c5420(*(int*) (other + 4), 0x1c8, 4, 0x80, 0);
			if (*(unsigned char*) ((*(unsigned short*) (rec + 0x27)) * 0x21c + 0x7f4ca2) == 6 ||
			    *(unsigned char*) ((*(unsigned short*) (rec + 0x27)) * 0x21c + 0x7f4ca2) == 7) {
				fcn_0051af00(text, 0x1ddf, *(unsigned short*) a0, rec, *ent);
				fcn_00545d40(*(unsigned short*) (rec + 0x27), *(unsigned short*) (rec + 0x27),
					text, 0, 0x5fb, (char*) 0x6a59fc);
			}
			fcn_005099e0(ent, *(int*) 0x773da8);
			fcn_004c57e0(*(int*) (ent + 4), 1);
			return 0x10;
		}
		return 0x60;
	}
	for (i = 0; i < 4; i++)
		found[i] = 0;
	if (*a1 != 3) {
		if (*a1 != 4)
			return 0x60;
		other = (char*) a1[0x87];
		if (other == 0)
			return 0x60;
	} else {
		other = a0;
	}
	if (*(unsigned char*) (other + 0x1c8) <= 0xff) {
		fcn_0051af00(name, 0x1ce0);
		fcn_00526120(name, 0);
		return 0x81;
	}
	found[1] = 0x410;
	found[2] = *(unsigned int*) 0x666018;
	found[3] = *(unsigned int*) 0x66601c;
	found[0] = 0;
	fcn_0051af00(name, 0x9b);
	rec = fcn_005bdc30(1, (int*) found, name, 0, 0);
	if (rec == 0)
		return 0;
	if (*(unsigned short*) (rec + 0x27) == 0xffff)
		return 0;
	state = (*(unsigned short*) (rec + 0x27)) * 0x21c;
	j = fcn_00470820(0, 0, (char*) 0x6acd8c);
	fcn_00473a90(0, 0);
	fcn_00471b60(j);
	fcn_004727a0(j, 1);
	i = fcn_00519190(0x1ddd, 5, *(unsigned short*) (state + 0x7f4ca0), rec);
	kid = fcn_00472250(j, 1, i);
	i = fcn_00472250(j, 1, i + 1);
	*(int*) 0x100f1dc = -1;
	for (;;) {
		if (*(int*) 0x100f1dc != -1) {
			if (*(int*) 0x67d370 != kid) {
				if (*(int*) 0x67d370 == i)
					*(int*) 0x774654 = 1;
			} else {
				count = fcn_00525f60(a0, 5);
				if (count != 0) {
					fcn_004c6ae0(*(int*) (a0 + 4), -5);
					thr = fcn_004c5420(*(int*) (other + 4), 0x1c8, 4, 0x80, 0);
					count = fcn_004c4450(thr);
					while (count == 0) {
						fcn_00535960();
						count = fcn_004c4450(thr);
					}
					fcn_0051af00(text, 0x1dde);
					fcn_00526120(text, 0);
					r = gm_RandomMod(0x300) & 0xffff;
					count = 0x300;
					do {
						ent = (char*) ((r & 0xffff) * 0x21c + 0x7f4ca0);
						if (*(short*) (ent + 0x27) != -1 &&
						    *(int*) (ent + 0x6c) == rec &&
						    *(unsigned char*) (ent + 2) == 0) {
							other = ent;
							if (*(unsigned char*) ((state + 0x7f4ca2)) == 6 ||
							    *(unsigned char*) ((state + 0x7f4ca2)) == 7) {
								fcn_0051af00(text, 0x1ddf, *(unsigned short*) a0, rec,
									*(unsigned short*) other);
								fcn_00545d40(*(unsigned int*) (state + 0x7f4ca4),
									*(unsigned int*) (state + 0x7f4ca4), text, 0, 0x5fb,
									(char*) 0x6a59fc);
							}
							fcn_005099e0(other, *(int*) 0x773da8);
							fcn_004c57e0(*(int*) (state + 0x7f4ca4), 1);
							ret = 0x81;
							*(int*) 0x774654 = 1;
							break;
						}
						count -= 1;
						r = (r + 1) % 0x300;
					} while (count != 0);
					if (ret == 0)
						ret = 0x81;
					*(int*) 0x774654 = 1;
				}
			}
		}
		if (*(int*) 0x14ce8e0 != 0)
			*(int*) 0x774654 = 1;
		if (fcn_005373e0(0x5d81f0, 0x657c7) == 0) {
			fcn_00471e30(j);
			return ret;
		}
	}
}
