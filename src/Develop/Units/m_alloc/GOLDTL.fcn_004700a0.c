#include <stdio.h>
#include <string.h>

extern int g_1015ce0;
extern void** g_772540;
extern char* g_1015ea0;
extern char* g_772500;
extern char* g_77257c;
extern char* g_772580;
extern char* g_772584;
extern char* g_772588;
extern unsigned int g_14ce798;
extern unsigned int g_14ce79c;
extern int g_67dac0;
extern int g_67dabc;
extern int g_14ce77c;
extern signed char g_67d91c;
extern signed char g_67d91d;
extern int g_67d920;
extern char g_1015f40[];
extern char* g_1015ec0[];
extern int g_1040480;
extern int g_1040484;
extern int g_1040488;
extern int g_104048c;
extern int g_1040494;
extern int g_1040490;
extern int g_1038140[];
extern char g_102cbc0[];
extern FILE* g_772564;
extern char g_102d040[];
extern char g_1015da0[];
extern int g_772504;
extern int g_7725b0;
extern char* g_7725ac;
extern float g_67d368;
extern signed char g_772510;
extern int g_1015eac;
extern int g_1015ea8;
extern int g_77250c;
extern void* g_6b5de0;
extern int g_67dab8;
extern int g_77256c;
extern char* g_77253c;
extern int g_67d390;
extern int g_67d394;
extern int g_67d398;
extern int g_67d39c;
extern int g_67d3a0;
extern int g_67d3a4;
extern int g_67d3a8;
extern int g_67d3ac;
extern int g_67d3b0;
extern int g_67d3b4;
extern int g_14ce860;
extern int g_14ce864;
extern float g_664080;
extern char s_67d474[];
extern char s_67d5c8[];
extern char s_67d5dc[];
extern char s_67d5ec[];
extern char s_67d5fc[];
extern char s_67d604[];
extern char s_67d618[];
extern char s_67d624[];
extern char s_67d638[];
extern char s_67d648[];
extern char s_67d654[];
extern char s_67d67c[];
extern char s_67d684[];
extern char s_67d690[];
extern char s_67d6ac[];
extern char s_67d6d4[];
extern char s_67d6f4[];
extern char s_67d700[];
extern char s_67d718[];
extern char s_67d72c[];
extern char s_67d740[];
extern char s_67d754[];
extern char s_67d760[];
extern char s_67d768[];
extern char s_6750e8[];
extern char s_679070[];

char* __cdecl m_alloc(int size, const char* tag);
int __cdecl ReportClientMessage(const char* text);
int __cdecl fcn_00465950(const char* name);
int __cdecl d2_Show(int idx, char* path);
void __cdecl fcn_00477450(void);
void __cdecl fcn_0047c4a0(void);
int __cdecl fcn_0047a040(int a0, int a1, int a2, int a3);
int __cdecl fcn_00477520(int a0, int a1);
int __cdecl fcn_004770a0(void* info, int kind);
void __cdecl fcn_004760c0(int win, char* buf);
int __cdecl fcn_00475fd0(int win);
void __cdecl fcn_00476970(int win);
void __cdecl fcn_00476060(int win);
void __cdecl fcn_00476b10(int x, int y, int r, int g, int b, int win);
void __cdecl fcn_00472880(int handle);
char* __cdecl fcn_0047ce00(char* name, int a1);

/* ADDRESS: GOLDTL 0x004700a0 */
int __cdecl d2_Open(int a0, int a1, int a2, char* a3, char* a4)
{
	char path[0x100];
	char message[0x400];
	char line[0x100];
	char name[0x100];
	char info[0x7c];
	char* p;
	char* q;
	char c;
	int i;
	int j;

	g_1015ce0 = 0;
	g_772540 = (void**) m_alloc(0x1000, s_67d768);
	g_1015ea0 = (char*) m_alloc(0xbd000, s_67d760);
	g_772500 = (char*) m_alloc(0x2a000, s_67d754);
	g_77257c = (char*) m_alloc(0x4000, s_67d740);
	g_772580 = (char*) m_alloc(0x4000, s_67d72c);
	g_772584 = (char*) m_alloc(0x4000, s_67d718);
	g_772588 = (char*) m_alloc(0x5000, s_67d700);
	g_67dac0 = g_14ce798;
	if (!(g_14ce798 < g_14ce79c)) {
		g_67dac0 = g_14ce79c;
	}
	g_67dabc = 1;
	g_67d91c = g_14ce77c & 2;
	g_67d91d = g_14ce77c & 0x20;
	g_67d920 = g_14ce798;
	if (!(g_14ce798 < g_14ce79c)) {
		g_67d920 = g_14ce79c;
	}
	fcn_00477450();
	fcn_0047c4a0();
	for (i = 0; i < 0x5b20; i++) {
		((int*) g_1015f40)[i] = 0;
	}
	*(int*) g_1015ea0 = 0;
	*(int*) g_772500 = 0;
	*(int*) g_772540 = 0;
	g_1040480 = 0;
	g_1040484 = 0;
	g_1040488 = 0;
	for (i = 0; i < 0x20; i++) {
		((int*) g_1015ec0)[i] = 0;
	}
	g_104048c = 0;
	for (i = 0; i < 0x30; i++) {
		*(int*) (0x1038140 + i * 0x2bc) = i;
	}
	for (i = 0; i < 0x60; i++) {
		*(int*) (g_1015f40 + i * 0x3cc) = i;
	}
	for (i = 0; i < 0x400; i++) {
		*(int*) (g_1015ea0 + i * 0x2f4) = i;
	}
	if (g_772564) {
		return 0;
	}
	sprintf(path, s_67d6f4, a3, a4);
	i = 0;
	do {
		c = path[i];
		g_102d040[i] = c;
		i++;
	} while (c);
	i = 0;
	do {
		c = path[i];
		g_1015da0[i] = c;
		i++;
	} while (c);
	p = strrchr(g_1015da0, '\\');
	if (p) {
		p[1] = 0;
	}
	g_772564 = fopen(path, s_6750e8);
	if (g_772564 == 0) {
		sprintf(message, s_67d6d4, path);
		return 0;
	}
	fread(&g_772504, 4, 1, g_772564);
	if (0x800 < g_772504) {
		fclose(g_772564);
		ReportClientMessage(s_67d6ac);
		return 0;
	}
	for (i = 0; i < g_772504; i++) {
		fread(g_772500 + i * 0x54, 0x54, 1, g_772564);
	}
	fclose(g_772564);
	sprintf(path, s_67d690, a3);
	g_772564 = fopen(path, s_679070);
	if (g_772564) {
		g_7725b0 = 0;
		fseek(g_772564, 0, 0);
		do {
			for (i = 0; i < 0x18; i++) {
				((int*) line)[i] = 0;
			}
			fgets(line, 0x60, g_772564);
			p = strchr(line, '"');
			if (p) {
				q = p + 1;
				*strchr(q, '"') = 0;
				p = q;
				do {
					c = *p;
					name[p - q] = c;
					p++;
				} while (c);
				g_7725b0++;
			}
		} while (!(*(unsigned char*) ((char*) g_772564 + 0xc) & 0x10));
		g_7725ac = m_alloc(g_7725b0 * 0x30, s_67d684);
		fseek(g_772564, 0, 0);
		g_7725b0 = 0;
		do {
			for (i = 0; i < 0x18; i++) {
				((int*) line)[i] = 0;
			}
			fgets(line, 0x60, g_772564);
			p = strchr(line, '"');
			if (p) {
				q = p + 1;
				*strchr(q, '"') = 0;
				p = q;
				do {
					c = *p;
					name[p - q] = c;
					p++;
				} while (c);
				p = name;
				q = g_7725ac + g_7725b0 * 0x30;
				do {
					c = *p++;
					*q++ = c;
				} while (c);
				g_7725b0++;
			}
		} while (!(*(unsigned char*) ((char*) g_772564 + 0xc) & 0x10));
		fclose(g_772564);
	}
	fcn_00477520(0, 1);
	for (i = 0; i < g_772504; i++) {
		if ((*(unsigned char*) (g_772500 + i * 0x54 + 0x44) & 1) && *(int*) (g_772500 + i * 0x54 + 0x38)) {
			d2_Show(i, 0);
		}
	}
	g_67d368 = (float) a1 * g_664080;
	if (a1 == 0x320) {
		g_772510 = 0;
	} else if (a1 == 0x400) {
		g_772510 = 1;
	} else if (a1 == 0x480) {
		g_772510 = 2;
	}
	g_1040494 = a1;
	g_1015ce0 = a0;
	g_1040490 = a2;
	fcn_0047a040(0, 0, a1, a2);
	g_1015eac = g_14ce860 >> 1;
	g_1015ea8 = g_14ce864 >> 1;
	for (i = 0; i < 0x17; i++) {
		((int*) (info + 0x10))[i] = 0;
	}
	g_77250c = 0;
	*(int*) (info + 0x14) = g_14ce860;
	*(int*) (info + 0x18) = g_14ce864;
	(*(void (__cdecl**) (void*, int, int, void*)) (*(char**) g_6b5de0 + 0x40))(g_6b5de0, 0, 0, info + 0x34);
	g_77250c = fcn_004770a0(info, 4);
	if (g_77250c) {
		fcn_004760c0(g_77250c, info + 0x5c);
		if (fcn_00475fd0(g_77250c)) {
			fcn_00476970(g_77250c);
			fcn_00476060(g_77250c);
		}
		for (i = 0; i < 0x17; i++) {
			((int*) info)[i] = 0;
		}
		*(int*) (info + 4) = 0x20;
		*(int*) (info + 8) = 0x20;
		*(int*) (info + 0x28) = g_67dab8;
		g_77256c = fcn_004770a0(info, 2);
		if (g_77256c) {
			fcn_00475fd0(g_77256c);
			for (i = 0; i < 0x20; i++) {
				for (j = 0; j < 0x20; j++) {
					fcn_00476b10(i, j, 0xff, 0xff, 0xff, g_77256c);
				}
			}
			fcn_00476060(g_77256c);
			fcn_00472880(fcn_00465950(s_67d474));
			g_77253c = fcn_0047ce00(s_67d67c, 0);
			if (g_77253c == 0) {
				ReportClientMessage(s_67d654);
			}
			g_67d390 = fcn_00465950(s_67d648);
			g_67d394 = fcn_00465950(s_67d638);
			g_67d398 = fcn_00465950(s_67d474);
			g_67d39c = fcn_00465950(s_67d624);
			g_67d3a0 = fcn_00465950(s_67d618);
			g_67d3a4 = fcn_00465950(s_67d604);
			g_67d3a8 = fcn_00465950(s_67d5fc);
			g_67d3ac = fcn_00465950(s_67d5ec);
			g_67d3b0 = fcn_00465950(s_67d5dc);
			g_67d3b4 = fcn_00465950(s_67d5c8);
			return 1;
		}
		return 0;
	}
	return 0;
}
