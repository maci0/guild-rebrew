#include <stdlib.h>
#include <string.h>

typedef struct
{
	char* ent;
	float key;
	int flags;
} fcn_004a3530_Ent;
/* SIZE 0xc */

extern fcn_004a3530_Ent g_10082a0[];
extern int g_664418[];
extern int g_664440[];
extern int* g_664448;
extern int g_7728bc;
extern int g_7747b4;

int __cdecl fcn_004e99c0(unsigned char c);
int __cdecl fcn_004e8b40(int idx, char* out);
int __cdecl fcn_004e8c00(int group, int max, char* out);
int __cdecl fcn_004e9310(int k, int max, char** out);
char* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x004a3530 */
int __cdecl fcn_004a3530(char* a0)
{
	char out[0x90];
	char r[0x18];
	char* out6[6];
	int arr[4];
	int x10;
	int cls;
	int grp;
	int cnt;
	int i;
	int j;
	int n;
	int idx;
	int found;
	int flag;
	int divisor;
	int* pv;
	char* e;
	char* q;

	n = 0;
	g_7728bc = 0;
	memset(g_10082a0, 0, 0x180);
	if (*(unsigned char*) (a0 + 0x166)) {
		cls = fcn_004e99c0(*(unsigned char*) (a0 + 0x166));
		fcn_004e8b40(*(unsigned char*) (a0 + 0x166), r);
		x10 = *(int*) (r + 0x10);
		grp = 0;
		arr[0] = 0;
		arr[1] = 0;
		arr[2] = 0;
		arr[3] = 0;
		idx = 0;
		if (1 <= x10 && x10 <= 3) {
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
		else if (4 <= x10 && x10 <= 5) {
			flag = (x10 == 4) + 4;
			if (cls != 6) {
				if (cls == 4) {
					arr[0] = 1;
					arr[1] = 2;
					arr[2] = 3;
				}
			}
			else
				arr[0] = 6;
		}
		else if (cls == 7) {
			arr[0] = 4;
			arr[1] = 5;
		}
		cnt = fcn_004e8c00(x10, 6, out);
		for (i = 0; i < cnt; i++) {
			e = gm_LookupEntityRecordById(*(int*) (out + i * 0x18));
			if (e && e != a0 && n < 32) {
				g_10082a0[n].flags = 0x10;
				g_10082a0[n].key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
				g_10082a0[n].ent = e;
				n++;
			}
		}
		cnt = fcn_004e8c00(flag, 6, out);
		for (i = 0; i < cnt; i++) {
			e = gm_LookupEntityRecordById(*(int*) (out + i * 0x18));
			if (e && e != a0 && n < 32) {
				g_10082a0[n].flags = 1;
				g_10082a0[n].key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
				g_10082a0[n].ent = e;
				n++;
			}
		}
		cnt = fcn_004e8c00(grp, 6, out);
		for (i = 0; i < cnt; i++) {
			e = gm_LookupEntityRecordById(*(int*) (out + i * 0x18));
			if (e && e != a0 && n < 32) {
				g_10082a0[n].flags = 1;
				g_10082a0[n].key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
				g_10082a0[n].ent = e;
				n++;
			}
		}
		if (cls == 3 || cls == 6) {
			cnt = fcn_004e8c00(arr[0], 6, out);
			for (i = 0; i < cnt; i++) {
				if (abs(fcn_004e99c0(*(unsigned char*) (out + i * 0x18 + 4)) - cls) <= 1) {
					e = gm_LookupEntityRecordById(*(int*) (out + i * 0x18));
					if (!e || e == a0)
						continue;
					found = 0;
					for (j = 0; j < n; j++) {
						if (g_10082a0[j].ent == e) {
							g_10082a0[j].flags |= 0x40;
							found = 1;
							break;
						}
					}
					if (found || n >= 32)
						continue;
					g_10082a0[n].flags = 0x40;
					g_10082a0[n].key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
					g_10082a0[n].ent = e;
					n++;
				}
			}
			cnt = fcn_004e8c00(arr[1], 6, out);
			for (i = 0; i < cnt; i++) {
				if (abs(fcn_004e99c0(*(unsigned char*) (out + i * 0x18 + 4)) - cls) <= 1) {
					e = gm_LookupEntityRecordById(*(int*) (out + i * 0x18));
					if (!e || e == a0)
						continue;
					found = 0;
					for (j = 0; j < n; j++) {
						if (g_10082a0[j].ent == e) {
							g_10082a0[j].flags |= 0x40;
							found = 1;
							break;
						}
					}
					if (found || n >= 32)
						continue;
					g_10082a0[n].flags = 0x40;
					g_10082a0[n].key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
					g_10082a0[n].ent = e;
					n++;
				}
			}
		}
		if (cls == 4 || cls == 7) {
			cnt = fcn_004e8c00(arr[0], 6, out);
			for (i = 0; i < cnt; i++) {
				if (abs(fcn_004e99c0(*(unsigned char*) (out + i * 0x18 + 4)) - cls) <= 1) {
					e = gm_LookupEntityRecordById(*(int*) (out + i * 0x18));
					if (!e || e == a0)
						continue;
					found = 0;
					for (j = 0; j < n; j++) {
						if (g_10082a0[j].ent == e) {
							g_10082a0[j].flags |= 0x80;
							found = 1;
							break;
						}
					}
					if (found || n >= 32)
						continue;
					g_10082a0[n].flags = 0x80;
					g_10082a0[n].key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
					g_10082a0[n].ent = e;
					n++;
				}
			}
			cnt = fcn_004e8c00(arr[1], 6, out);
			for (i = 0; i < cnt; i++) {
				if (abs(fcn_004e99c0(*(unsigned char*) (out + i * 0x18 + 4)) - cls) <= 1) {
					e = gm_LookupEntityRecordById(*(int*) (out + i * 0x18));
					if (!e || e == a0)
						continue;
					found = 0;
					for (j = 0; j < n; j++) {
						if (g_10082a0[j].ent == e) {
							g_10082a0[j].flags |= 0x80;
							found = 1;
							break;
						}
					}
					if (found || n >= 32)
						continue;
					g_10082a0[n].flags = 0x80;
					g_10082a0[n].key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
					g_10082a0[n].ent = e;
					n++;
				}
			}
			cnt = fcn_004e8c00(arr[2], 6, out);
			for (i = 0; i < cnt; i++) {
				if (abs(fcn_004e99c0(*(unsigned char*) (out + i * 0x18 + 4)) - cls) <= 1) {
					e = gm_LookupEntityRecordById(*(int*) (out + i * 0x18));
					if (!e || e == a0)
						continue;
					found = 0;
					for (j = 0; j < n; j++) {
						if (g_10082a0[j].ent == e) {
							g_10082a0[j].flags |= 0x80;
							found = 1;
							break;
						}
					}
					if (found || n >= 32)
						continue;
					g_10082a0[n].flags = 0x80;
					g_10082a0[n].key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
					g_10082a0[n].ent = e;
					n++;
				}
			}
		}
	}
	else {
		for (grp = 1; grp <= 3; grp++) {
			cnt = fcn_004e8c00(grp, 6, out);
			for (i = 0; i < cnt; i++) {
				if (fcn_004e99c0(*(unsigned char*) (out + i * 0x18 + 4)) > 2)
					continue;
				e = gm_LookupEntityRecordById(*(int*) (out + i * 0x18));
				if (e && e != a0 && n < 32) {
					g_10082a0[n].flags = 0x40;
					g_10082a0[n].key = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) a0, 1);
					g_10082a0[n].ent = e;
					n++;
				}
			}
		}
	}
	if (*(unsigned char*) (a0 + 0x168)) {
		cnt = fcn_004e9310(*(unsigned char*) (a0 + 0x168), 6, out6);
		for (i = 0; i < cnt; i++) {
			e = out6[i];
			if (e == a0)
				continue;
			found = 0;
			for (j = 0; j < n; j++) {
				if (g_10082a0[j].ent == e) {
					g_10082a0[j].flags |= 2;
					found = 1;
					break;
				}
			}
			if (found || n >= 32)
				continue;
			g_10082a0[n].flags = 2;
			g_10082a0[n].key = fcn_0050f980(*(unsigned short*) a0, *(unsigned short*) e, 1);
			g_10082a0[n].ent = e;
			n++;
		}
	}
	if (*(unsigned char*) (a0 + 0x168) || *(unsigned char*) (a0 + 2) == 5) {
		for (q = (char*) 0x7f4ca0; q < (char*) 0x85a0a0; q += 0x21c) {
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
			found = 0;
			for (j = 0; j < n; j++) {
				if (g_10082a0[j].ent == q) {
					g_10082a0[j].flags |= 2;
					found = 1;
					break;
				}
			}
			if (found || n >= 32)
				continue;
			g_10082a0[n].flags = 2;
			g_10082a0[n].key = fcn_0050f980(*(unsigned short*) a0, *(unsigned short*) e, 1);
			g_10082a0[n].ent = q;
			n++;
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
		g_664448 = (int*) &g_10082a0[gm_RandomMod(n) & 0xffff];
		g_664448[1] = g_664418[gm_RandomMod(divisor) & 0xffff];
		if (g_664448[1] > 1) {
			if (n % g_664448[1] == 0) {
				i = (gm_RandomMod(2) != 0) ? 1 : -1;
				g_664448[1] += i;
				return i;
			}
			return n / g_664448[1];
		}
		return (int) g_664448;
	}
	g_664448 = (int*) &g_10082a0[0];
	g_664448[1] = 1;
	return 4 - g_7747b4;
}
