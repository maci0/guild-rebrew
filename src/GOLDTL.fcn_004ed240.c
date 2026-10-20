#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char s_68dfd8[];
extern char s_68dfa8[];
extern char s_68dfbc[];
extern char s_68df8c[];
extern char s_68df84[];
extern char s_68df78[];
extern char s_68df70[];
extern char s_68df68[];
extern char s_68df60[];
extern char s_68df54[];
extern char s_68df5c[];
extern char s_68df44[];
extern char s_68df4c[];
extern char s_68df80[];
extern char s_68df28[];
extern char s_68df14[];
extern char s_68def8[];
extern char s_68def0[];
extern char s_68deec[];
extern char s_68dee8[];
extern char s_68dee0[];
extern char s_6b5c60[];

extern double g_662950;
extern double g_6629c8;
extern double g_6640e8;
extern int g_7e1f80;
extern int g_772fd8;
extern unsigned char* g_772fdc;
extern int g_772fe0;
extern unsigned char* g_772fe4;

void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl m_FreeTracked(void* p);
int __cdecl fcn_004edcd0(char* text);

/* ADDRESS: GOLDTL 0x004ed240 */
unsigned int __cdecl fcn_004ed240(void)
{
	char path[0x104];
	char app[0x100];
	char out[0x100];
	char* p;
	char* rec;
	int i;
	int v;
	double f;

	GetModuleFileNameA((HMODULE) g_7e1f80, path, 0x104);
	p = strrchr(path, 0x5c);
	p[1] = 0;
	*(unsigned int*) (p + 1) = *(unsigned int*) s_68dfd8;
	*(unsigned int*) (p + 5) = *(unsigned int*) (s_68dfd8 + 4);
	*(unsigned int*) (p + 9) = *(unsigned int*) (s_68dfd8 + 8);
	*(unsigned int*) (p + 0xd) = *(unsigned int*) (s_68dfd8 + 0xc);
	p[0x11] = s_68dfd8[0x10];
	GetPrivateProfileStringA(s_68dfa8, s_68dfbc, s_6b5c60, out, 0x100, path);
	g_772fd8 = atoi(out);
	if (g_772fd8 <= 0) {
		goto drop_second;
	}
	if (g_772fdc) {
		m_FreeTracked(g_772fdc);
		g_772fdc = 0;
	}
	g_772fdc = (unsigned char*) m_alloc(g_772fd8 * 0xc, s_68df8c);
	if (g_772fdc == 0) {
		goto drop_second;
	}
	if (g_772fd8 > 0) {
		rec = (char*) g_772fdc;
		for (i = 0; i < g_772fd8; i++) {
			sprintf(app, s_68df84, i);
			GetPrivateProfileStringA(app, s_68df78, s_68df80, out, 0x100, path);
			v = atoi(out);
			if (v <= 0) {
				v = 0;
			}
			if (v >= 0xfc) {
				v = 0xfc;
			}
			rec[0] = (char) v;
			GetPrivateProfileStringA(app, s_68df70, s_68df80, out, 0x100, path);
			v = atoi(out);
			if (v <= 0) {
				v = 0;
			}
			if (v >= 0xfc) {
				v = 0xfc;
			}
			rec[1] = (char) v;
			GetPrivateProfileStringA(app, s_68df68, s_68df80, out, 0x100, path);
			v = atoi(out);
			if (v <= 0) {
				v = 0;
			}
			if (v >= 0xfc) {
				v = 0xfc;
			}
			rec[2] = (char) v;
			GetPrivateProfileStringA(app, s_68df60, s_68df80, out, 0x100, path);
			v = atoi(out);
			if (v <= 0) {
				v = 0;
			}
			if (v >= 0xfc) {
				v = 0xfc;
			}
			rec[3] = (char) v;
			GetPrivateProfileStringA(app, s_68df54, s_68df5c, out, 0x100, path);
			v = atoi(out);
			if (v <= 0x12) {
				v = 0x12;
			}
			if (v >= 0x1e) {
				v = 0x1e;
			}
			rec[4] = (char) v;
			GetPrivateProfileStringA(app, s_68df44, s_68df4c, out, 0x100, path);
			*(int*) (rec + 8) = fcn_004edcd0(out);
			rec += 0xc;
		}
	}
	GetPrivateProfileStringA(s_68df14, s_68df28, s_6b5c60, out, 0x100, path);
	g_772fe0 = atoi(out);
	if (g_772fe0 <= 0) {
		goto drop_first;
	}
	if (g_772fe4) {
		m_FreeTracked(g_772fe4);
		g_772fe4 = 0;
	}
	g_772fe4 = (unsigned char*) m_alloc(g_772fe0 * 0xc, s_68def8);
	if (g_772fe4 == 0) {
		goto drop_first;
	}
	if (g_772fe0 <= 0) {
		return 1;
	}
	rec = (char*) g_772fe4;
	for (i = 0; i < g_772fe0; i++) {
		sprintf(app, s_68def0, i);
		GetPrivateProfileStringA(app, s_68df78, s_68deec, out, 0x100, path);
		f = atof(out) * g_6640e8;
		if (f > g_662950) {
			f = atof(out) * g_6640e8;
			if (f < g_6629c8) {
				goto clamp_low;
			}
			f = g_6629c8;
		}
		else {
clamp_low:
			f = atof(out) * g_6640e8;
			if (f <= g_662950) {
				f = g_662950;
			}
			else {
				f = atof(out) * g_6640e8;
			}
		}
		*(float*) (rec + 4) = (float) f;
		GetPrivateProfileStringA(app, s_68df70, s_68dee8, out, 0x100, path);
		f = atof(out) * g_6640e8;
		if (f > g_662950) {
			f = atof(out) * g_6640e8;
			if (f < g_6629c8) {
				goto clamp_low2;
			}
			f = g_6629c8;
		}
		else {
clamp_low2:
			f = atof(out) * g_6640e8;
			if (f <= g_662950) {
				f = g_662950;
			}
			else {
				f = atof(out) * g_6640e8;
			}
		}
		*(float*) (rec + 8) = (float) f;
		GetPrivateProfileStringA(app, s_68dee0, s_68df4c, out, 0x100, path);
		*(int*) rec = fcn_004edcd0(out);
		rec += 0xc;
	}
	return 1;
drop_first:
	if (g_772fdc) {
		m_FreeTracked(g_772fdc);
		g_772fdc = 0;
	}
drop_second:
	if (g_772fe4) {
		m_FreeTracked(g_772fe4);
		g_772fe4 = 0;
	}
	g_772fe0 = 0;
	g_772fd8 = 0;
	return 0;
}
