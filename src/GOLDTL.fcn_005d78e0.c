
#include <string.h>

typedef struct
{
	int x0;
	int x4;
	__int64 mask;
	int x10;
	char pad14[0x3c];
} Query;
/* SIZE 0x50 */

typedef struct
{
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
} Ent78e;
/* SIZE 8 */

extern int g_100f1dc;
extern int g_14ce8e0;
extern __int64 g_666018;
extern int g_67d370;
extern float g_6628ac;
extern unsigned char g_773d75;
extern int g_774654;
#include "client_types.h"

char* __cdecl fcn_00508e40(int a);
int __cdecl fcn_0050dac0(unsigned short id);
int __cdecl fcn_0050d2a0(char* a);
int __cdecl fcn_0042e410(int a);
int __cdecl fcn_0050f950(int a, int i);
void __cdecl fcn_004c54c0(int a, int b, int c, int d);
void __cdecl fcn_004c5150(int a, int b, char c, int n);
void __cdecl fcn_004c6ae0(int a, int b);
void __cdecl fcn_0051af00(void* out, int id, ...);
void __cdecl fcn_00545d40(int a, int b, char* text, int c, int d, char* file);
int __cdecl fcn_005cd440(Query* q, char* text, int a, void* b);
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00473a90(int a, int b);
void __cdecl fcn_00471b60(int h);
void __cdecl fcn_00471e30(int h);
void __cdecl fcn_004727a0(int h, int a);
int __cdecl fcn_00472250(int h, int a, int b);
int __cdecl fcn_00519190(int id, ...);
int __cdecl fcn_00525f60(char* e, int a);
int __cdecl fcn_00526010(void* e, int a, char b);
void __cdecl fcn_00526120(char* text, int a);
int __cdecl fcn_005373e0(void* fn, int a);

/* ADDRESS: GOLDTL 0x005d78e0 */
int __cdecl fcn_005d78e0(char* a0, char* a1)
{
	Query req;
	char buf[0x100];
	Ent78e* e1;
	Ent78e* e2;
	int rc;
	int v;
	int w1;
	int w2;
	int d1;
	int d2;
	int h;
	int ret;
	int r1;
	int r2;

	if (*(unsigned char*) (a0 + 2) != 6) {
		if (*(int*) (a0 + 0x194) < 4) {
			return 0x20;
		}
		e1 = (Ent78e*) fcn_00508e40(*(int*) (a1 + 0x214));
		if (e1 == 0) {
			return 0x20;
		}
		e2 = (Ent78e*) fcn_00508e40(*(int*) (a1 + 0x218));
		if (e2 == 0) {
			return 0x20;
		}
		v = (int) ((fcn_0050dac0(e2->id) + fcn_0050dac0(e1->id)) * g_6628ac);
		if (fcn_0050d2a0(a0) < v) {
			return 0x20;
		}
		w1 = (fcn_0042e410(0x1e) & 0xffff) + 3;
		w2 = (fcn_0042e410(0x1e) & 0xffff) + 3;
		d1 = fcn_0050f950(e1->id, e2->id);
		d2 = fcn_0050f950(e2->id, e1->id);
		fcn_004c54c0(e1->handle, e2->handle, w1 - d1 - 0x7f, 1);
		fcn_004c54c0(e2->handle, e1->handle, w2 - d2 - 0x7f, 1);
		fcn_004c5150(-1, *(int*) (a0 + 4), *(char*) &g_773d75, v);
		fcn_004c6ae0(*(int*) (a0 + 4), -4);
		if (e1->type == 6 || e1->type == 7) {
			fcn_0051af00(buf, 0x1dd3, e2->id, e2->id);
			fcn_00545d40(e1->handle, e1->handle, buf, 0, 0x5fb, (char*) 0x6a59fc);
		}
		if (e2->type == 6 || e2->type == 7) {
			fcn_0051af00(buf, 0x1dd3, e1->id, e1->id);
			fcn_00545d40(e2->handle, e2->handle, buf, 0, 0x5fb, (char*) 0x6a59fc);
		}
		return 0x10;
	}
	rc = 0;
	memset(&req, 0, sizeof(req));
	req.x4 = 0x400;
	req.x10 = 6;
	req.mask = g_666018;
	fcn_0051af00(buf, 0x1dcf);
	e1 = (Ent78e*) fcn_005cd440(&req, buf, 0, 0);
	if (e1 == 0) {
		return 0;
	}
	fcn_0051af00(buf, 0x1dd0, e1->id);
	e2 = (Ent78e*) fcn_005cd440(&req, buf, 0, 0);
	if (e2 == 0) {
		return 0;
	}
	v = (int) ((fcn_0050dac0(e2->id) + fcn_0050dac0(e1->id)) * g_6628ac);
	h = fcn_00470820(0, 0, (char*) 0x6acd58);
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	fcn_004727a0(h, 1);
	ret = fcn_00519190(0x1dd1, 4, v, e1->id, e2->id);
	r1 = fcn_00472250(h, 1, ret);
	r2 = fcn_00472250(h, 1, ret + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_67d370 == r1) {
				if (fcn_00525f60(a0, 4) != 0 &&
				    fcn_00526010(a0, v, *(char*) &g_773d75) != 0) {
					w1 = (fcn_0042e410(0x1e) & 0xffff) + 3;
					w2 = (fcn_0042e410(0x1e) & 0xffff) + 3;
					d1 = fcn_0050f950(e1->id, e2->id);
					d2 = fcn_0050f950(e2->id, e1->id);
					fcn_004c54c0(e1->handle, e2->handle,
						     w1 - d1 - 0x7f, 1);
					fcn_004c54c0(e2->handle, e1->handle,
						     w2 - d2 - 0x7f, 1);
					fcn_004c5150(-1, *(int*) (a0 + 4),
						     *(char*) &g_773d75, v);
					fcn_004c6ae0(*(int*) (a0 + 4), -4);
					fcn_0051af00(buf, 0x1dd2, e1->id, e2->id);
					fcn_00526120(buf, 0);
					if (e1->type == 6 || e1->type == 7) {
						fcn_0051af00(buf, 0x1dd3, e2->id, e2->id);
						fcn_00545d40(e1->handle, e1->handle, buf,
							     0, 0x5fb, (char*) 0x6a59fc);
					}
					if (e2->type == 6 || e2->type == 7) {
						fcn_0051af00(buf, 0x1dd3, e1->id, e1->id);
						fcn_00545d40(e2->handle, e2->handle, buf,
							     0, 0x5fb, (char*) 0x6a59fc);
					}
					g_774654 = 1;
					rc = 1;
				}
			} else if (g_67d370 == r2) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) 0x5d78e0, 0x657c7) != 0);
	fcn_00471e30(h);
	return rc;
}
