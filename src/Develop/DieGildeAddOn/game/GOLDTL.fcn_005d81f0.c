#include <string.h>
#include "client_dialog_state.h"
#include "client_actions.h"

typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int pad14[15];
} Req5d81f0;

typedef struct {
	unsigned short id;
	unsigned char kind;
	unsigned char pad3;
	int handle;
	char pad8[0x164];
	char* rec;
	char pad170[0xac];
} Slot5d81f0;

extern __int64 g_666018;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern char g_7f4ca0[];

extern char* __cdecl gm_LookupEntityRecordById(int);
extern char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern void __cdecl fcn_004c6ae0(int, int);
extern int __cdecl fcn_004c5420(int, int, int, int, int);
extern void __cdecl io_FormatTextBuffer(char*, int, ...);
extern void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
extern void __cdecl fcn_005099e0(char*, int);
extern void __cdecl fcn_004c57e0(int, int);
extern char* __cdecl fcn_005bdc30(int, int*, char*, int, int);
extern int __cdecl fcn_00470820(int, int, char*);
extern void __cdecl d2_SetOverlayAnimation(int, int);
extern void __cdecl fcn_00471b60(int);
extern void __cdecl d2_SetForm(int, int);
extern int __cdecl io_AppendText(int, int, int, int);
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
	Req5d81f0 found;
	char text[512];
	char name[256];
	char* ent;
	char* other;
	char* rec;
	char* state_ptr;
	int i;
	int j;
	int count;
	int kid;
	int ret;
	int thr;
	int r;

	if (*(unsigned char*) (a0 + 2) != 6) {
		if (*(int*) (a0 + 0x194) < 5)
			return 0x20;
		if (*a1 == 3 && (*(int*) (a0 + 0x1c8) & 0x80) == 0) {
			other = a0;
		} else {
			if (*a1 != 4)
				goto fail60;
			other = (char*) a1[0x87];
			if (other == 0)
				goto fail60;
			if ((*(int*) (other + 0x1c8) & 0x80) != 0)
				goto fail60;
		}
		ent = gm_LookupEntityRecordById(a1[0x85]);
		if (ent == 0)
			goto fail60;
		rec = gm_StartFilteredEntitySearch(1, 1, a1[0x86]);
		if (rec == 0)
			goto fail60;
		fcn_004c6ae0(*(int*) (a0 + 4), -5);
		fcn_004c5420(*(int*) (other + 4), 0x1c8, 4, 0x80, 0);
		if (((Slot5d81f0*) g_7f4ca0)[*(unsigned short*) (rec + 0x27)].kind == 6 ||
		    ((Slot5d81f0*) g_7f4ca0)[*(unsigned short*) (rec + 0x27)].kind == 7) {
			io_FormatTextBuffer(text, 0x1ddf, *(unsigned short*) a0, rec, *(unsigned short*) ent);
			fcn_00545d40(*(unsigned short*) (rec + 0x27), *(unsigned short*) (rec + 0x27),
				text, 0, 0x5fb, (char*) 0x6a59fc);
		}
		fcn_005099e0(ent, (int) g_773da8);
		fcn_004c57e0(*(int*) (ent + 4), 1);
		return 0x10;
	}
	memset(&found, 0, sizeof(found));
	if (*a1 == 3) {
		other = a0;
	} else {
		if (*a1 != 4 || a1[0x87] == 0)
			goto fail60;
		other = (char*) a1[0x87];
	}
	if ((*(unsigned char*) (other + 0x1c8) & 0x80) != 0) {
		io_FormatTextBuffer(name, 0x1ce0);
		fcn_00526120(name, 0);
		return 0x81;
	}
	ret = 0;
	found.size = 0x410;
	found.kind = 6;
	found.cd = g_666018;
	found.a = 0;
	io_FormatTextBuffer(name, 0x9b);
	rec = fcn_005bdc30(1, (int*) &found, name, 0, 0);
	if (rec == 0)
		return 0;
	if (*(unsigned short*) (rec + 0x27) == 0xffff)
		return 0;
	state_ptr = (char*) &((Slot5d81f0*) g_7f4ca0)[*(unsigned short*) (rec + 0x27)];
	j = fcn_00470820(0, 0, (char*) 0x6acd8c);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(j);
	d2_SetForm(j, 1);
	i = io_AppendText(0x1ddd, 5, *(unsigned short*) state_ptr, rec);
	kid = fcn_00472250(j, 1, i);
	i = fcn_00472250(j, 1, i + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_67d370 == kid) {
				if (fcn_00525f60(a0, 5) != 0) {
					fcn_004c6ae0(*(int*) (a0 + 4), -5);
					thr = fcn_004c5420(*(int*) (other + 4), 0x1c8, 4, 0x80, 0);
					while (fcn_004c4450(thr) == 0) {
						fcn_00535960();
					}
					io_FormatTextBuffer(text, 0x1dde);
					fcn_00526120(text, 0);
					r = gm_RandomMod(0x300) & 0xffff;
					ent = 0;
					count = 0x300;
					do {
						if (((Slot5d81f0*) g_7f4ca0)[r].id != 0xffff &&
						    ((Slot5d81f0*) g_7f4ca0)[r].rec == rec &&
						    ((Slot5d81f0*) g_7f4ca0)[r].kind == 0) {
							ent = (char*) &((Slot5d81f0*) g_7f4ca0)[r];
							break;
						}
						count -= 1;
						r = (r + 1) % 0x300;
					} while (count != 0);
					if (ent != 0) {
						if (*(unsigned char*) (state_ptr + 2) == 6 ||
						    *(unsigned char*) (state_ptr + 2) == 7) {
							io_FormatTextBuffer(text, 0x1ddf, *(unsigned short*) a0, rec,
								*(unsigned short*) ent);
							fcn_00545d40(*(int*) (state_ptr + 4), *(int*) (state_ptr + 4),
								text, 0, 0x5fb, (char*) 0x6a59fc);
						}
						fcn_005099e0(ent, (int) g_773da8);
						fcn_004c57e0(*(int*) (ent + 4), 1);
					}
					ret = 0x81;
					g_774654 = 1;
				}
			} else if (g_67d370 == i) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0)
			g_774654 = 1;
	} while (fcn_005373e0((int) fcn_005d81f0, 0x657c7) != 0);
	fcn_00471e30(j);
	return ret;
fail60:
	return 0x60;
}
