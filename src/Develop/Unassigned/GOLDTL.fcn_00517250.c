#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

extern char g_6b5c60[];

int __cdecl fcn_005171a0(char*, int*, int);
int __cdecl fcn_00501490(char*);
int __cdecl fcn_00504eb0(const char*);
int __cdecl _isctype(int, int);

/* ADDRESS: GOLDTL 0x00517250 */
int __cdecl fcn_00517250(char* name, int idx)
{
	char staedte[8][0x40];
	int werte[0x40];
	char datei[0x104];
	char buf[0x100];
	int i;
	int count;
	int k;
	char* tok;
	char* p;
	char* q;

	if (idx == 0) {
		memset((void*) 0x868060, 0, 0xbd0);
	}
	p = (unsigned char*) (0x868060 + idx * 0x2f4);
	sprintf(datei, "%s%s/%s.ini", "\\project\\gfx\\", "gamedata/cities", name);
	GetPrivateProfileStringA("A - ALLGEMEIN", "Stadtname", "Unknown", buf, 0x100, datei);
	strcpy((char*) p, buf);
	GetPrivateProfileStringA("A - ALLGEMEIN", "KartenPosition", "", buf, 0x100, datei);
	fcn_005171a0(buf, (int*) (p + 0x40), 2);
	GetPrivateProfileStringA("A - ALLGEMEIN", "Glaube", "0", buf, 0x100, datei);
	p[0x49] = (unsigned char) atoi(buf);
	GetPrivateProfileStringA("A - ALLGEMEIN", "HistorieStart", "1400", buf, 0x100, datei);
	*(int*) (p + 0x4c) = atoi(buf);
	GetPrivateProfileStringA("A - ALLGEMEIN", "HistorieEnde", "1400", buf, 0x100, datei);
	*(int*) (p + 0x50) = atoi(buf);
	GetPrivateProfileStringA("A - ALLGEMEIN", "Waehrung", "ob_GOLDGULDEN", buf, 0x100, datei);
	*(unsigned short*) (p + 0x54) = (unsigned short) fcn_00501490((char*) (buf + 3));
	GetPrivateProfileStringA("A - ALLGEMEIN", "Land", "0", buf, 0x100, datei);
	p[0x60] = (unsigned char) atoi(buf);
	GetPrivateProfileStringA("A - ALLGEMEIN", "Sprache", "0", buf, 0x100, datei);
	p[0x61] = (unsigned char) atoi(buf);
	GetPrivateProfileStringA("A - ALLGEMEIN", "KartenOffset", "0, 0", buf, 0x100, datei);
	fcn_005171a0(buf, (int*) (p + 0x2ec), 2);
	if (idx == 0) {
		GetPrivateProfileStringA("A - ALLGEMEIN", "NachbarStadt", g_6b5c60, buf, 0x100, datei);
		count = 0;
		tok = strtok(buf, ",");
		while (tok != 0) {
			if (count >= 8) {
				break;
			}
			while (*tok == ' ') {
				tok++;
			}
			strcpy(staedte[count], tok);
			count++;
			tok = strtok(0, ",");
		}
		for (i = 0; i < count; i++) {
			fcn_00517250(staedte[i], i + 1);
		}
	}
	GetPrivateProfileStringA("A - ALLGEMEIN", "MaxPlayer", g_6b5c60, buf, 0x100, datei);
	p[0x48] = (unsigned char) atoi(buf);
	for (i = 0; i < 0xa; i++) {
		sprintf(staedte[0], "Einwohner_%i", i);
		GetPrivateProfileStringA("A - EINWOHNER", staedte[0], "1400,0", buf, 0x100, datei);
		fcn_005171a0(buf, (int*) (p + 0x64 + i * 8), 2);
	}
	for (i = 0; i < 0xa; i++) {
		sprintf(staedte[0], "Prunk_%i", i);
		GetPrivateProfileStringA("A - PRUNK", staedte[0], "1400,0", buf, 0x100, datei);
		fcn_005171a0(buf, (int*) (p + 0xb4 + i * 8), 2);
	}
	GetPrivateProfileStringA("B - WETTER", "Regenwahrscheinlichkeit", "0,0,0,0", buf, 0x100, datei);
	fcn_005171a0(buf, (int*) (p + 0x108), 4);
	GetPrivateProfileStringA("B - WETTER", "Schneewahrscheinlichkeit", "0,0,0,0", buf, 0x100, datei);
	fcn_005171a0(buf, (int*) (p + 0x118), 4);
	GetPrivateProfileStringA("B - WETTER", "Zufrierenwahrscheinlichkeit", "0", buf, 0x100, datei);
	*(int*) (p + 0x128) = atoi(buf);
	GetPrivateProfileStringA("C - PRIVILEGIEN", "Privilegien", "0,0,0,0,0,0,0,0,0,0,0", buf, 0x100, datei);
	fcn_005171a0(buf, werte, 0xb);
	for (i = 0; i < 0xb; i++) {
		p[0x12c + i] = (unsigned char) werte[i];
	}
	q = p + 0x145;
	for (i = 0; i < 8; i++) {
		sprintf(staedte[0], "Umland%i", i);
		GetPrivateProfileStringA("E - UMLAND", staedte[0], g_6b5c60, buf, 0x100, datei);
		tok = strtok(buf, ",");
		k = 0;
		while (tok != 0) {
			if (k >= 0xa) {
				break;
			}
			while (*(int*) 0x6b25b0 > 1 ? _isctype(*tok, 8)
			    : (*(unsigned char*) (*(unsigned char**) 0x6b23a4 + *tok * 2) & 8)) {
				tok++;
			}
			if (k == 0) {
				q[-1] = (unsigned char) fcn_00504eb0((char*) (tok + 3));
			} else if (k == 1) {
				q[0] = (unsigned char) atoi(tok);
			} else {
				*(unsigned short*) (q + 1 + (k - 2) * 2) = (unsigned short) fcn_00501490((char*) (tok + 3));
			}
			k++;
			tok = strtok(0, ",");
		}
		q += 0x12;
	}
	GetPrivateProfileStringA("F - GESETZE", "Verfassungsgesetze", "0,0,0,0", buf, 0x100, datei);
	fcn_005171a0(buf, (int*) (p + 0x1dc), 0xc);
	GetPrivateProfileStringA("F - GESETZE", "Finanzgesetze", "0,0,0,0", buf, 0x100, datei);
	fcn_005171a0(buf, (int*) (p + 0x20c), 0xc);
	GetPrivateProfileStringA("F - GESETZE", "Strafgesetze", "0,0,0,0", buf, 0x100, datei);
	fcn_005171a0(buf, (int*) (p + 0x22c), 0xc);
	GetPrivateProfileStringA("F - GESETZE", "Gildengesetze", "0,0,0,0", buf, 0x100, datei);
	fcn_005171a0(buf, (int*) (p + 0x25c), 0xc);
	GetPrivateProfileStringA("F - GESETZE", "Kirchengesetze", "0,0,0,0", buf, 0x100, datei);
	fcn_005171a0(buf, (int*) (p + 0x274), 0xc);
	GetPrivateProfileStringA("F - GESETZE", "DiebeRaeubergesetze", "0,0,0,0", buf, 0x100, datei);
	fcn_005171a0(buf, (int*) (p + 0x290), 0xc);
	{
		char sep[2] = ",";

		GetPrivateProfileStringA("KONTOR", "Import", g_6b5c60, buf, 0x100, datei);
		k = 0;
		tok = strtok(buf, sep);
		q = p + 0x2ac;
		while (tok != 0) {
			if (k >= 0x10) {
				break;
			}
			while (*(int*) 0x6b25b0 > 1 ? _isctype(*tok, 8)
			    : (*(unsigned char*) (*(unsigned char**) 0x6b23a4 + *tok * 2) & 8)) {
				tok++;
			}
			*(unsigned short*) q = (unsigned short) fcn_00501490((char*) (tok + 3));
			k++;
			q += 2;
			tok = strtok(0, sep);
		}
	}
	{
		char sep[2] = ",";

		GetPrivateProfileStringA("KONTOR", "Export", g_6b5c60, buf, 0x100, datei);
		k = 0;
		tok = strtok(buf, sep);
		q = p + 0x2cc;
		while (tok != 0) {
			if (k >= 0x10) {
				break;
			}
			while (*(int*) 0x6b25b0 > 1 ? _isctype(*tok, 8)
			    : (*(unsigned char*) (*(unsigned char**) 0x6b23a4 + *tok * 2) & 8)) {
				tok++;
			}
			*(unsigned short*) q = (unsigned short) fcn_00501490((char*) (tok + 3));
			k++;
			q += 2;
			tok = strtok(0, sep);
		}
	}
	return 1;
}
