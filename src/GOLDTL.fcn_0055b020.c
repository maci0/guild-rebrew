#include <string.h>
#pragma intrinsic(memcpy)

extern char g_7f4ca0[];
extern char g_774964;
extern unsigned short g_774970;
extern int g_100f1dc;

int __cdecl fcn_00545670(char*, short, short, int, int);
void __cdecl fcn_00545780(char*);
void __cdecl fcn_00546190(char*);
char* __cdecl fcn_00508e40(int);
int* __cdecl fcn_004c30a0(int, int, char*, int, int);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00500cb0(void*, void*);

/* ADDRESS: GOLDTL 0x0055b020 */
void __cdecl fcn_0055b020(char* o)
{
	short* slot;
	char* g;
	char buf[0x1fc];
	char* src;
	int n;
	int state;
	int st;
	int code;
	int kind;
	int end;
	int id;
	char flag;

	slot = (short*) (g_7f4ca0 + *(unsigned short*) (o + 8) * 0x21c);
	if (g_774970 != *(unsigned short*) (o + 8))
		return;
	if (g_774964 == 0)
		return;
	if (fcn_00500cb0(o + 0x52, (void*) 0x7f4c00) == 1)
		return;
	g = fcn_00508e40(*(int*) (o + 0xbc));
	state = *(int*) (o + 0x70);
	if (state == -2 || state == -1 || *slot == -1 || g == 0) {
		if (*(int*) (o + 0x74))
			fcn_00545780(o);
		fcn_00546190(o);
		return;
	}
	if (state != 0) {
		if (state != 1)
			return;
		id = *(int*) (o + 0x74);
		if (id == 0) {
			*(int*) (o + 0x70) = 0;
			return;
		}
		if (*(int*) 0x100f884 != *(int*) (id + 8) && *(char*) 0x7749e8 == 0)
			return;
		if (g_100f1dc == 2) {
			fcn_00545780(o);
			fcn_00546190(o);
			return;
		}
		if (*(char*) 0x7749e8 == 0)
			return;
		if (*(int*) 0x7749e4 != id)
			return;
		*(char*) 0x7749e8 = 0;
		fcn_00545780(o);
		fcn_00546190(o);
		return;
	}
	if (*(int*) (o + 0x74) == 0) {
		if (g != (char*) slot)
			fcn_00545670(o, 0, 0, (int) 0x6a5e60, 0x5fe);
		else
			fcn_00545670(o, 0, 0, (int) 0x6a5e78, 0x5fd);
	}
	if (*(int*) (o + 0x74) == 0) {
		fcn_00546190(o);
		return;
	}
	fcn_00471b60(*(int*) (*(int*) (o + 0x74) + 8));
	fcn_004727a0(*(int*) (*(int*) (o + 0x74) + 8), 1);
	if (g != (char*) slot) {
		st = *(int*) (o + 0xc0);
		kind = 0;
		if (st == 0x25)
			kind = 0x42ac;
		else if (st == 0x24)
			kind = 0x42b0;
		else if (st == 0x23)
			kind = 0x42ae;
		if (*(char*) (g + 9))
			end = st + 0x27b;
		else
			end = 0x253;
		fcn_00519190(kind, *(unsigned short*) g, end);
		goto done;
	}
	flag = *(char*) (g + 9);
	code = 0;
	if (*(char*) (g + 0xd) != 9) {
		if (*(char*) (g + 0xd) != 8) {
			code = 0x42a5;
			if (flag == 1)
				src = (char*) 0x6a6160;
			else
				src = (char*) 0x6a6138;
		} else {
			code = 0x42a7;
			if (flag == 1)
				src = (char*) 0x6a61b0;
			else
				src = (char*) 0x6a6188;
		}
	} else {
		code = 0x42a9;
		if (flag == 1)
			src = (char*) 0x6a6200;
		else
			src = (char*) 0x6a61d8;
	}
	memcpy(buf, src, 0x25);
	if (flag == 1)
		code += 1;
	fcn_004c30a0(-7, 0, (char*) 0x6a438c, 0, 100);
	fcn_004c30a0(-7, 0, buf, 0, 100);
	st = *(int*) (o + 0xc0);
	kind = 0;
	n = 0x25;
	if (st == 0x25) {
		kind = 0x42ab;
		if (flag == 1) {
			src = (char*) 0x6a6110;
		} else {
			src = (char*) 0x6a60e8;
			n = 0x26;
		}
	} else if (st == 0x24) {
		kind = 0x42af;
		if (flag == 1) {
			src = (char*) 0x6a60c0;
		} else {
			src = (char*) 0x6a6098;
			n = 0x26;
		}
	} else if (st == 0x23) {
		kind = 0x42ad;
		if (flag == 1) {
			src = (char*) 0x6a6070;
		} else {
			src = (char*) 0x6a6048;
			n = 0x26;
		}
	}
	if (kind != 0)
		memcpy(buf, src, n);
	fcn_004c30a0(-7, 0, buf, 0, 100);
	fcn_004c30a0(-7, 0, (char*) 0x67d908, -1, 0);
	if (flag)
		end = st + 0x27b;
	else
		end = 0x253;
	fcn_00519190(kind, code, (int) (o + 0xac), end);
done:
	fcn_004727a0(*(int*) (*(int*) (o + 0x74) + 8), 2);
	fcn_00519190(0x161c);
	*(int*) (o + 0x70) = 1;
}
