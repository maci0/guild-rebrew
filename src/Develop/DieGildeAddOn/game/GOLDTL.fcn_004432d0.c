#include <string.h>

extern void __cdecl fcn_00443030(char*);
extern void __cdecl fcn_00438b40(int, char*);
extern void __cdecl fcn_00438cb0(int, char*);
extern void __cdecl fcn_00439c60(int);
extern void __cdecl fcn_0045b290(int, int);
extern int __cdecl fcn_0045b700(int, int, int);
extern void __cdecl fcn_00437ac0(int, int, int, int);
extern void __cdecl gv_Free3Fields(int);
extern int __cdecl fcn_00438920(int, int, int);

extern char g_10432c0[];

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x004432d0 */
char __cdecl fcn_004432d0(int a0, char a1)
{
	int off;

	if (a0 >= 0x40)
		return 0;
	if (a0 == *(int*) 0x6b8010) {
		if (a1 == 0)
			*(char*) 0x6b859b = 1;
		return 1;
	}
	off = *(int*) 0x6b8010 * 0x3dc;
	*(int*) (g_10432c0 + off + 0x80) = *(int*) 0x1043254;
	*(int*) (g_10432c0 + off + 0x84) = *(int*) 0x1042538;
	if (*(int*) (g_10432c0 + off + 0x80) == 0x1042340
		&& *(int*) (g_10432c0 + off + 0x84) == 0x1042340) {
		*(int*) (g_10432c0 + off + 0x84) = 0;
		*(int*) (g_10432c0 + off + 0x80) = 0;
	}
	*(int*) (g_10432c0 + off + 0xa4) = *(int*) 0x1040c74;
	*(int*) (g_10432c0 + off + 0xa8) = *(int*) 0x1040958;
	if (*(int*) (g_10432c0 + off + 0xa4) == 0x1040640
		&& *(int*) (g_10432c0 + off + 0xa8) == 0x1040640) {
		*(int*) (g_10432c0 + off + 0xa8) = 0;
		*(int*) (g_10432c0 + off + 0xa4) = 0;
	}
	*(int*) (g_10432c0 + off + 0xac) = *(int*) 0x6b8300;
	*(int*) (g_10432c0 + off + 0xb8) = *(int*) 0x6b89c0;
	*(int*) (g_10432c0 + off + 0x3d8) = *(int*) 0x6b8058;
	*(int*) (g_10432c0 + off + 0xbc) = *(int*) 0x67bbdc;
	*(int*) (g_10432c0 + off + 0xc0) = *(int*) 0x67bbe0;
	*(int*) (g_10432c0 + off + 0xc4) = *(int*) 0x67bbe4;
	*(int*) (g_10432c0 + off + 0xc8) = *(int*) 0x6b86c4;
	*(int*) (g_10432c0 + off + 0xcc) = *(int*) 0x6b86c8;
	*(int*) (g_10432c0 + off + 0xd0) = *(int*) 0x6b86cc;
	memcpy(g_10432c0 + off + 0x128, (void*) 0x1041d80, 0x2a0);
	off = *(int*) 0x6b8010 * 0x3dc;
	*(int*) (g_10432c0 + off + 0xd4) = *(int*) 0x6b805c;
	*(int*) (g_10432c0 + off + 0xd8) = *(int*) 0x10425fc;
	*(int*) (g_10432c0 + off + 0xdc) = *(int*) 0x104329c;
	memcpy(g_10432c0 + off + 0xe0, (void*) 0x1041d20, 0x48);
	off = *(int*) 0x6b8010 * 0x3dc;
	*(int*) (g_10432c0 + off + 0x3cc) = *(int*) 0x67a37c;
	*(int*) (g_10432c0 + off + 0x3d0) = *(int*) 0x67a380;
	*(int*) (g_10432c0 + off + 0x88) = *(int*) 0x6b8484;
	if (*(int*) (g_10432c0 + off + 0x88) != 0) {
		*(int*) (g_10432c0 + off + 0x8c) =
			*(int*) (*(int*) (g_10432c0 + off + 0x88) + 0x4c);
		*(int*) (g_10432c0 + off + 0x90) =
			*(int*) (*(int*) (g_10432c0 + off + 0x88) + 0x50);
		*(int*) (g_10432c0 + off + 0x94) =
			*(int*) (*(int*) (g_10432c0 + off + 0x88) + 0x54);
		*(int*) (g_10432c0 + off + 0x98) =
			*(int*) (*(int*) (g_10432c0 + off + 0x88) + 0x84);
		*(int*) (g_10432c0 + off + 0x9c) =
			*(int*) (*(int*) (g_10432c0 + off + 0x88) + 0x88);
		*(int*) (g_10432c0 + off + 0xa0) =
			*(int*) (*(int*) (g_10432c0 + off + 0x88) + 0x8c);
	}
	off = a0 * 0x3dc;
	if (*(int*) (g_10432c0 + off + 0x80) == 0)
		fcn_00443030(g_10432c0 + off);
	*(int*) 0x1043254 = *(int*) (g_10432c0 + off + 0x80);
	*(int*) 0x1042538 = *(int*) (g_10432c0 + off + 0x84);
	*(int*) 0x1040c74 = *(int*) (g_10432c0 + off + 0xa4);
	*(int*) 0x1040958 = *(int*) (g_10432c0 + off + 0xa8);
	*(int*) 0x6b8300 = *(int*) (g_10432c0 + off + 0xac);
	*(int*) 0x6b89c0 = *(int*) (g_10432c0 + off + 0xb8);
	*(int*) 0x67a37c = *(int*) (g_10432c0 + off + 0x3cc);
	*(int*) 0x67a380 = *(int*) (g_10432c0 + off + 0x3d0);
	*(int*) 0x6b8058 = *(int*) (g_10432c0 + off + 0x3d8);
	*(int*) 0x67bbdc = *(int*) (g_10432c0 + off + 0xbc);
	*(int*) 0x67bbe0 = *(int*) (g_10432c0 + off + 0xc0);
	*(int*) 0x67bbe4 = *(int*) (g_10432c0 + off + 0xc4);
	*(int*) 0x6b86c4 = *(int*) (g_10432c0 + off + 0xc8);
	*(int*) 0x6b86c8 = *(int*) (g_10432c0 + off + 0xcc);
	*(int*) 0x6b86cc = *(int*) (g_10432c0 + off + 0xd0);
	*(int*) 0x6b8014 = 0;
	memcpy((void*) 0x1041d20, g_10432c0 + off + 0xe0, 0x48);
	memcpy((void*) 0x1041d80, g_10432c0 + off + 0x128, 0x2a0);
	*(int*) 0x6b8010 = a0;
	*(int*) 0x67a370 = (int) (g_10432c0 + off);
	if (*(int*) 0x1041d0c == *(int*) 0x6b8484)
		*(int*) 0x1041d0c = *(int*) (g_10432c0 + off + 0x88);
	*(int*) 0x6b8484 = *(int*) (g_10432c0 + off + 0x88);
	if (*(int*) 0x6b8484 != 0) {
		fcn_00438b40(*(int*) 0x6b8484, g_10432c0 + off + 0x8c);
		fcn_00438cb0(*(int*) 0x6b8484, g_10432c0 + off + 0x98);
		fcn_00439c60(*(int*) 0x6b8484);
	}
	if (a1 == 0) {
		if (*(int*) 0x6b8300 == 0) {
			if (*(int*) 0x6b89e4 != 0) {
				fcn_0045b290(*(int*) 0x6b89e4, 0);
			}
			else {
				*(int*) 0x6b89e4 = fcn_0045b700(0, -*(int*) 0x6b89b0, 1);
				fcn_00437ac0(*(int*) 0x67a370, 0, 0xc0, 0x456df0);
			}
		}
		else if (*(int*) 0x6b89e4 != 0) {
			gv_Free3Fields(*(int*) 0x6b89e4);
			*(int*) 0x6b89e4 = 0;
		}
		fcn_00438920(*(int*) (g_10432c0 + off + 0xd8),
			*(int*) (g_10432c0 + off + 0xdc), *(int*) (g_10432c0 + off + 0xd4));
		*(int*) 0x1042a08 = 0;
		*(char*) 0x6b859b = 1;
	}
	return 1;
}
#pragma optimize("", on)
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")
unsigned char _tlead_GOLDTL_fcn_004432d0[144] = {
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
unsigned char _dpad_10432c0[172];
