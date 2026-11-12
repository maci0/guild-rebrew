#include <stdlib.h>
#include <string.h>
extern char g_7f4ca0[];
typedef struct
{
	char* ent;
	float key;
	int flags;
} fcn_004a3530_Ent;
/* SIZE 0xc */

typedef struct
{
	int x0;
	int id;
	unsigned char x8;
	char pad9[0xf];
} Rec18;
/* SIZE 0x18 */

extern fcn_004a3530_Ent g_10082a0[];
extern int g_664418[];
extern int g_664440[];
extern int* g_664448;
extern int g_7728bc;
extern int g_7747b4;

int __cdecl fcn_004e99c0(unsigned char c);
int __cdecl fcn_004e8b40(int idx, Rec18* out);
int __cdecl fcn_004e8c00(int group, int max, Rec18* out);
int __cdecl fcn_004e9310(int k, int max, char** out);
char* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x004a3530 */
void __cdecl fcn_004a3530(char* a0)
{
	Rec18 out[6];
	Rec18 r;
	int arr[8];
	int x10;
	int cls;
	int grp;
	int cnt;
	int i;
	int j;
	int n;

	int flag;
	int divisor;
	int* pv;
	char* e;
	char* q; fcn_004a3530_Ent* next;

	n = 0;
	g_7728bc = 0;
	memset(g_10082a0, 0, 0x180);
	if (0 == *(unsigned char*) (a0 + 0x166)) {
		cnt = fcn_004e8c00(1, 6, out);
		for (i = 0, next = g_10082a0 + n; i < cnt; i++) {


			if (fcn_004e99c0(out[i].x8) >= 3)
				continue;
			e = gm_LookupEntityRecordById(out[i].id);
			if (!e || e == a0)
				continue;
			next->flags = 0x40;
			next->key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
			next->ent = e;
			n++; ++next;
		}
		cnt = fcn_004e8c00(2, 6, out);
		for (i = 0, next = g_10082a0 + n; i < cnt; i++) {


			if (fcn_004e99c0(out[i].x8) >= 3)
				continue;
			e = gm_LookupEntityRecordById(out[i].id);
			if (!e || e == a0)
				continue;
			next->flags = 0x40;
			next->key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
			next->ent = e;
			n++; ++next;
		}
		cnt = fcn_004e8c00(3, 6, out);
		for (i = 0, next = g_10082a0 + n; i < cnt; i++) {


			if (fcn_004e99c0(out[i].x8) >= 3)
				continue;
			e = gm_LookupEntityRecordById(out[i].id);
			if (!e || e == a0)
				continue;
			next->flags = 0x40;
			next->key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
			next->ent = e;
			n++; ++next;
		}
	}
	else {
		cls = fcn_004e99c0(*(unsigned char*) (a0 + 0x166));
		grp = 0;
		flag = 0;
		fcn_004e8b40(*(unsigned char*) (a0 + 0x166), &r);
		x10 = r.id;
		arr[0] = 0;
		arr[1] = 0;
		arr[2] = 0;
		arr[3] = 0;
		arr[4] = 0;
		if (x10 > 0 && x10 < 4) {
			grp = 3;
			if (x10 != 1) {
				flag = 1;
				if (x10 != 2)
					grp = 2;
			}
			else
				flag = 2;
			if (cls == 3) {
				arr[0] = 4;
				arr[1] = 5;
			}
		}
		else if (x10 > 3 && x10 < 6) {
			flag = (x10 == 4) + 4;
			if (cls == 6)
				arr[0] = 6;
			else if (cls == 4) {
				arr[2] = 1;
				arr[3] = 2;
				arr[4] = 3;
			}
		}
		else if (cls == 7) {
			arr[2] = 4;
			arr[3] = 5;
		}
		cnt = fcn_004e8c00(x10, 6, out);
		for (i = 0, next = g_10082a0 + n; i < cnt; i++) {
			if ((int) next >= (int) (g_10082a0 + 32))
				break;
			e = gm_LookupEntityRecordById(out[i].id);
			if (!e || e == a0)
				continue;
			next->flags = 0x10;
			next->key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
			next->ent = e;
			n++; ++next;
		}
		cnt = fcn_004e8c00(flag, 6, out);
		for (i = 0, next = g_10082a0 + n; i < cnt; i++) {
			if ((int) next >= (int) (g_10082a0 + 32))
				break;
			e = gm_LookupEntityRecordById(out[i].id);
			if (!e || e == a0)
				continue;
			next->flags = 1;
			next->key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
			next->ent = e;
			n++; ++next;
		}
		cnt = fcn_004e8c00(grp, 6, out);
		for (i = 0, next = g_10082a0 + n; i < cnt; i++) {
			if ((int) next >= (int) (g_10082a0 + 32))
				break;
			e = gm_LookupEntityRecordById(out[i].id);
			if (!e || e == a0)
				continue;
			next->flags = 1;
			next->key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
			next->ent = e;
			n++; ++next;
		}
		if (cls == 3 || cls == 6) {
			cnt = fcn_004e8c00(arr[0], 6, out);
			for (i = 0, next = g_10082a0 + n; i < cnt; i++) {
				if ((int) next >= (int) (g_10082a0 + 32))
					break;
				if (abs(fcn_004e99c0(out[i].x8) - cls) > 1)
					continue;
				e = gm_LookupEntityRecordById(out[i].id);
				if (!e || e == a0)
					continue;
				next->flags = 0x40;
				next->key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
				next->ent = e;
				n++; ++next;
			}
			cnt = fcn_004e8c00(arr[1], 6, out);
			for (i = 0, next = g_10082a0 + n; i < cnt; i++) {
				if ((int) next >= (int) (g_10082a0 + 32))
					break;
				if (abs(fcn_004e99c0(out[i].x8) - cls) > 1)
					continue;
				e = gm_LookupEntityRecordById(out[i].id);
				if (!e || e == a0)
					continue;
				next->flags = 0x40;
				next->key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
				next->ent = e;
				n++; ++next;
			}
		}
		if (cls == 4 || cls == 7) {
			cnt = fcn_004e8c00(arr[2], 6, out);
			for (i = 0, next = g_10082a0 + n; i < cnt; i++) {
				if ((int) next >= (int) (g_10082a0 + 32))
					break;
				if (abs(fcn_004e99c0(out[i].x8) - cls) > 1)
					continue;
				e = gm_LookupEntityRecordById(out[i].id);
				if (!e || e == a0)
					continue;
				next->flags = 0x80;
				next->key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
				next->ent = e;
				n++; ++next;
			}
			cnt = fcn_004e8c00(arr[3], 6, out);
			for (i = 0, next = g_10082a0 + n; i < cnt; i++) {
				if ((int) next >= (int) (g_10082a0 + 32))
					break;
				if (abs(fcn_004e99c0(out[i].x8) - cls) > 1)
					continue;
				e = gm_LookupEntityRecordById(out[i].id);
				if (!e || e == a0)
					continue;
				next->flags = 0x80;
				next->key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
				next->ent = e;
				n++; ++next;
			}
			cnt = fcn_004e8c00(arr[4], 6, out);
			for (i = 0, next = g_10082a0 + n; i < cnt; i++) {
				if ((int) next >= (int) (g_10082a0 + 32))
					break;
				if (abs(fcn_004e99c0(out[i].x8) - cls) > 1)
					continue;
				e = gm_LookupEntityRecordById(out[i].id);
				if (!e || e == a0)
					continue;
				next->flags = 0x80;
				next->key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
				next->ent = e;
				n++; ++next;
			}
		}
	}
	if (*(unsigned char*) (a0 + 0x168)) {
		cnt = fcn_004e9310(*(unsigned char*) (a0 + 0x168), 6, (char**) &arr[2]);
		for (i = 0, next = g_10082a0 + n; i < cnt; i++) {
			e = (char*) arr[2 + i];
			if (e == a0)
				continue;
			
			for (j = 0; j < n; j++) {
				if (g_10082a0[j].ent == e) {
					g_10082a0[j].flags |= 2;
					
					break;
				}
			}
			if (j < n)
				continue;
			if ((int) next >= (int) (g_10082a0 + 32))
				continue;
			next->flags = 2;
			next->key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
			next->ent = e;
			n++; ++next;
		}
	}
	if (*(unsigned char*) (a0 + 0x168) || *(unsigned char*) (a0 + 2) == 5) {
		for (q = g_7f4ca0, next = g_10082a0 + n; (int) q < (int) (g_7f4ca0 + 0x65400); q += 0x21c) {
			if (q == a0)
				continue;
			if (*(unsigned short*) q == 0xffff)
				continue;
			flag = 0;
			if ((*(unsigned char*) (q + 2) == 6 || *(unsigned char*) (q + 2) == 7
			     || *(unsigned char*) (q + 2) == 5) && *(unsigned char*) (a0 + 2) == 5)
				flag |= 1;
			if (*(unsigned char*) (q + 0x166) == *(unsigned char*) (a0 + 0x168))
				flag |= 4;
			if (!flag)
				continue;
			
			for (j = 0; j < n; j++) {
				if (g_10082a0[j].ent == q) {
					g_10082a0[j].flags |= flag;
					
					break;
				}
			}
			if (j < n)
				continue;
			if ((int) next >= (int) (g_10082a0 + 32))
				continue;
			next->flags = flag;
			next->key = fcn_0050f980(*(unsigned short*) q, *(unsigned short*) a0, 1);
			next->ent = q;
			n++; ++next;
		}
	}
	flag = (4 - g_7747b4) * 5;
	for (i = 0; i < n; i++) {
		if (*(unsigned char*) (g_10082a0[i].ent + 2) == 6
		    || *(unsigned char*) (g_10082a0[i].ent + 2) == 7)
			g_10082a0[i].key += (float) flag;
	}
	g_7728bc = n;
	if (n > 3) {
		divisor = 0xb;
		pv = g_664440;
		while (divisor) {
			if (*pv < n)
				break;
			divisor--;
			pv--;
		}
		g_664448[0] = (int) &g_10082a0[gm_RandomMod(n) & 0xffff];
		g_664448[1] = g_664418[gm_RandomMod(divisor) & 0xffff];
		if (g_664448[1] > 1) {
			if (g_7728bc % g_664448[1] == 0) {
				i = ((unsigned short) gm_RandomMod(2) != 0) ? 1 : -1;
				g_664448[1] += i;
				return;
			}
			return;
		}
		return;
	}
	g_664448[0] = (int) &g_10082a0[0];
	g_664448[1] = 1;
	return;
}
