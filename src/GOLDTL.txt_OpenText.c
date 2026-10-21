#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct {
	char name[0x60];
	int first;
	int count;
	char* text;
	char pad6c[8];
} TextBank_42bf20;

extern char g_1052e00[];
extern char g_1052f00[];
extern char g_1335000[];
extern char g_13350d0[];
extern char g_1053000[][0x50];
extern char g_11cd000[][0x50];
extern char g_1335120[][0x50];
extern char* g_14a5320[];
extern int g_14b7320[];
extern int g_14b731c[];
extern char g_149d120[][0x74];
extern int g_11bb000[];
extern unsigned char g_14a0b20[];
extern char g_6b5c60[];
extern int g_1052de0;
extern int g_6b7f98;
extern int g_6b7f9c;
extern char* g_6b7fa0;
extern int g_6b7fa4;

char* __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* p);
void __cdecl fcn_0041d9e0(char* msg);
int __cdecl fcn_0042b810(char* text, int index);
void __cdecl fcn_0042bcb0(char* s);
int __cdecl fcn_0064d41a(char* dst, char* fmt, ...);
char* __cdecl fcn_0064d1a0(char* s, int c);
char* __cdecl fcn_0064d470(char* s, char* sub);
char* __cdecl fcn_0064e790(char* s, int c);
char* __cdecl fgets(char* buf, int n, FILE* f);
char* __cdecl fcn_0064e2f9(char* path, char* mode);
int __cdecl fcn_0064e1fd(FILE* f);
int __cdecl fcn_0064e48f(FILE* f, int off, int whence);
int __cdecl fcn_0064ed28(void* buf, int size, int count, FILE* f);
int __cdecl fputs(char* s, FILE* f);
char* __cdecl strncat(char* dst, char* src, int n);
char* __cdecl fcn_0064d530(char* dst, char* src, int n);
char* __cdecl fcn_00657a73(int value, char* buf, int radix);

/* Reads the stdio EOF flag at FILE+0xc. */
#define STREAM_FLAG(f) (*(int*) ((char*) (f) + 0xc))

#define BANK(i) ((TextBank_42bf20*) g_149d120)[i]

/* ADDRESS: GOLDTL 0x0042bf20 */
int __cdecl txt_OpenText(char* a1, char* a2)
{
	int v10;
	int v14;
	int v18;
	int v24;
	int v20;
	char* p;
	char* q;
	FILE* fp;
	int v2c;
	int k;
	int len;
	int v34;
	int v38;
	int v3c;
	int v40;
	int v44;
	int v48;
	int starts[10];
	char line[0xc8];
	char msg[0x100];
	char buf250[0x80];
	char path[0x104];
	char rec[10][0xc4];
	char u140[0x14];
	char def[0x60][0x100];
	char inc[0x80][0x100];

	starts[0] = 0;
	starts[1] = 0x14;
	starts[2] = 0x28;
	starts[3] = 0x3c;
	starts[4] = 0x50;
	starts[5] = 0x64;
	starts[6] = 0x78;
	starts[7] = 0x8c;
	starts[8] = 0xa0;
	starts[9] = 0xb4;
	v18 = 0;
	v40 = 0;
	v20 = 0;
	v48 = 0;
	v44 = 0;
	v3c = 0;
	g_6b7f98 = 0;
	v10 = 0x80;
	p = (char*) g_149d120 + 0x68;
	do {
		*(int*) p = 0;
		p += 0x74;
	} while (p < (char*) g_149d120 + 0x3a68);

	p = m_alloc(0x4800000, "txt_txt_t:TextArray");
	g_6b7fa0 = p;
	if (p == 0) {
		MessageBoxA((HWND) 0, "Konnte speicher nicht reservieren!", "txt_OpenText", 0x30);
		return 0;
	}
	memset(g_1335120, 0, 0x168000);
	memset(p, 0, 0x4800000);
	memset(g_1053000, 0, 0x168000);
	memset(g_11cd000, 0, 0x168000);
	memset(g_14a5320, 0, 0x12000);
	memset(g_149d120, 0, 0x3a00);
	memset(g_11bb000, 0xff, 0x12000);

	g_6b7f98 = 0;
	g_6b7fa4 = 0;
	v18 = 0x4800;
	p = (char*) fcn_0064d1a0(a1, '\\');
	if (p == 0) {
		strcpy(g_1052f00, "text\\");
		strcpy(g_1052e00, "\\project\\DieGilde\\gfx\\textbin\\");
	}
	else {
		memset(g_1052e00, 0, 0x100);
		memset(path, 0, 0x104);
		memcpy(path, a1, p - a1 + 1);
		strcpy(g_1052f00, path);
		strcat(g_1052f00, "text\\");
		strcpy(g_1052e00, a1);
		p = (char*) fcn_0064d1a0(g_1052e00, '\\');
		if (p != 0) {
			*p = 0;
		}
		p = (char*) fcn_0064d1a0(g_1052e00, '\\');
		if (p != 0) {
			*p = 0;
		}
		fcn_0064d41a(path + 4, "%s\\resources\\textbin_%s\\", "german");
		strcpy(g_1052e00, path);
	}

	fp = (FILE*) fcn_0064e2f9(a1, "rt");
	if (fp == 0) {
		MessageBoxA((HWND) 0, "Could not open Textfiledefinition!", "Error", 0x30);
		goto fail_free;
	}

	/* Pass 1: collect output path, header path and the include list. */
	for (;;) {
		memset(line, 0, 0xc8);
		fgets(line, 0xc8, fp);
		if (fcn_0064d470(line, "//") != 0) {
			goto pass1_done;
		}
		p = (char*) fcn_0064d470(line, "#outputpath");
		if (p != 0) {
			p = (char*) fcn_0064e790(p, '"');
			if (p == 0) {
				goto fail_free;
			}
			p++;
			if (fcn_0064e790(p, '"') == 0) {
				goto fail_free;
			}
			*fcn_0064e790(p, '"') = 0;
			strcpy(g_1052e00, p);
		}
		p = (char*) fcn_0064d470(line, "#headerfile");
		if (p != 0) {
			p = (char*) fcn_0064e790(p, '"');
			if (p == 0) {
				goto fail_free;
			}
			p++;
			if (fcn_0064e790(p, '"') == 0) {
				goto fail_free;
			}
			*fcn_0064e790(p, '"') = 0;
			strcpy(g_1335000, p);
		}
		p = (char*) fcn_0064d470(line, "#include");
		if (p != 0) {
			p = (char*) fcn_0064e790(p, '"');
			if (p == 0) {
				goto fail_free;
			}
			p++;
			if (fcn_0064e790(p, '"') == 0) {
				goto fail_free;
			}
			*fcn_0064e790(p, '"') = 0;
			strcpy(inc[v3c], p);
			v3c++;
			if (v3c > 0x80) {
				goto fail_free;
			}
		}
pass1_done:
		if ((STREAM_FLAG(fp) & 0x10) != 0) {
			break;
		}
	}
	fcn_0064e1fd(fp);

	/* Pass 2: compile every listed text file into its binary resource. */
	v40 = v3c;
	for (v2c = 0; v2c < v40; v2c++) {
		strcpy(line, g_1052f00);
		p = inc[v2c];
		strcat(line, p);
		fp = (FILE*) fcn_0064e2f9(line, "rt");
		if (fp == 0) {
			fcn_0064d41a(msg, "Could not open TextFile: '%s' !", line);
			MessageBoxA((HWND) 0, msg, "Error", 0x30);
			goto fail_free;
		}
		v24 = 0;
		for (;;) {
			memset(line, 0, 0xc8);
			fgets(line, 0xc8, fp);
			if (strcmp(line, g_6b5c60) == 0) {
				break;
			}
			v24++;
			v20 = 0;
			if (fcn_0064d470(line, "#define") != 0) {
				k = strlen(line);
				line[k - 1] = 0;
				fcn_0064d41a(def[v48], "%s\n", line);
				v48++;
				if (v48 > 0x60) {
					MessageBoxA((HWND) 0, "To many defines!", "Error", 0x30);
				}
				v10 = strlen(line);
			}
			if (v20 != 0) {
				if (fcn_0064e790(line, '"') == 0 && fcn_0064d470(line, "*/") != 0) {
					v20 = 0;
				}
				v10 = strlen(line);
			}
			while (line[v10] == ' ') {
				v10++;
			}
			v34 = v18 * 0x50;
			for (v14 = v10; v10 < (int) strlen(line); v10++, v14++) {
				p = line + v10;
				switch (line[v10]) {
				case '\t':
					v14 += 4;
					continue;
				case '"':
					v10++;
					v14++;
					p = (char*) fcn_0064e790(line + v10, '"');
					k = (int) (p - (line + v10));
					if (k < 0) {
						fcn_0064d41a(msg, "Syntax error in file %s in line %i", p, v24);
						MessageBoxA((HWND) 0, msg, "Error in textfile", 0x30);
						break;
					}
					memset(msg, 0, sizeof(msg));
					if (k > 0xff) {
						fcn_0064d41a(msg, "Line too long in file %s in line %i", p, v24);
						MessageBoxA((HWND) 0, msg, "Error in textfile", 0x30);
						break;
					}
					fcn_0064d530(msg, line + v10, k);
					p = (char*) fcn_0064d470(msg, "/*");
					if (p != 0) {
						v10 += k;
						v14 += k;
						while (p != 0) {
							if (fcn_0064d470(msg, "*/") != 0 && fcn_0064d470(msg, "*/") < p) {
								fcn_0064d41a(msg, "Syntax error in file %s in line %i: Missing '/*'", p, v24);
								MessageBoxA((HWND) 0, msg, "Error in textfile", 0x30);
								break;
							}
							if (fcn_0064d470(msg, "*/") == 0) {
								fcn_0064d41a(msg, "Syntax error in file %s in line %i: Missing '*/'", p, v24);
								MessageBoxA((HWND) 0, msg, "Error in textfile", 0x30);
								break;
							}
							memcpy(p, fcn_0064d470(msg, "*/") + 2, strlen(fcn_0064d470(msg, "*/") + 2));
							p = (char*) fcn_0064d470(msg, "/*");
						}
						k = (int) strlen(msg);
						if (strlen(&g_6b7fa0[g_6b7f98 * 0x1000]) + k > 0xfff) {
							fcn_0064d41a(msg, "String too long in file %s in line %i", inc[v2c], v24);
							goto fail_free;
						}
						strncat(&g_6b7fa0[g_6b7f98 * 0x1000], msg, k);
					}
					else {
						if (strlen(&g_6b7fa0[g_6b7f98 * 0x1000]) + k > 0xfff) {
							fcn_0064d41a(msg, "String too long in file %s in line %i", inc[v2c], v24);
							goto fail_free;
						}
						strncat(&g_6b7fa0[g_6b7f98 * 0x1000], line + v10, k);
						v10 += k;
						v14 += k;
					}
					g_6b7fa4 += k;
					v44 = 1;
					if (line[v10 + 1] == ',') {
						do {
							v10 += 2;
							p = (char*) fcn_0064e790(line + v10, '"');
							k = (int) (p - (line + v10));
							if (k < 0) {
								fcn_0064d41a(msg, "Syntax error in file %s in line %i", p, v24);
								MessageBoxA((HWND) 0, msg, "Error in textfile", 0x30);
								v10 = (int) strlen(line) - 1;
								break;
							}
							msg[0] = '|';
							strcpy(msg + 1, line + v10);
							if (strlen(&g_6b7fa0[g_6b7f98 * 0x4800000]) + strlen(msg) > 0xfff) {
								fcn_0064d41a(msg, "String too long in file %s in line %i", inc[v2c], v24);
								goto fail_free;
							}
							strncat(&g_6b7fa0[g_6b7f98 * 0x1000], msg, strlen(msg));
							g_6b7fa4 += (int) strlen(msg);
							v10 += k + 1;
							v14 += k + 1;
						} while (line[v10] == ',');
					}
					break;
				case '(':
					if (fcn_0042b810(p, v18) == 0) {
						fcn_0064d41a(msg, "Syntax error in file %s in line %i", p, v24);
						MessageBoxA((HWND) 0, msg, "Error in textfile", 0x30);
					}
					break;
				case '*':
					if (line[v10 + 1] == '/') {
						v20--;
					}
					if (v20 < 0) {
						fcn_0064d41a(msg, "txt_TextOpen(): nested comments found. in file %s in line %i", p, v24);
					}
					break;
				case '/':
					if (line[v10 + 1] == '*') {
						v20++;
						if (fcn_0064d470(line + v10 + 1, "*/") != 0) {
							v20--;
						}
					}
					break;
				case ';':
					strcpy(g_1053000[g_6b7f98], (char*) (0x13350d0 + v34));
					strcat(g_1053000[g_6b7f98], "+");
					fcn_00657a73(g_6b7f98 - g_14b731c[v2c], u140, 10);
					strcat(g_1053000[g_6b7f98], u140);
					g_6b7fa4 = g_6b7fa4 + 1;
					g_6b7f98 = g_6b7f98 + 1;
					if (g_6b7f98 > 0x4800) {
						MessageBoxA((HWND) 0, "Zuviele Textenums!", "txt_OpenText", 0x30);
						goto fail_free;
					}
					v44 = 0;
					v14++;
					continue;
				case '_':
					if (v44 != 0) {
						fcn_0064d41a(msg, "Syntax error in file %s in line %i: missing ';'", line, v24);
						MessageBoxA((HWND) 0, msg, "txt_OpenText", 0x30);
						goto fail_close;
					}
					g_14b7320[v18] = g_6b7f98;
					v3c = v10;
					while (v3c < (int) strlen(line) && line[v3c] != 0xa && line[v3c] != 0x20 && line[v3c] != 9) {
						v3c++;
					}
					memset(&g_11cd000[v34], 0, 0x50);
					fcn_0064d530((char*) &g_11cd000[v34], line + v10, v3c - v10);
					k = 0;
					while (k < 8) {
						if (v14 <= starts[k]) {
							break;
						}
						k++;
					}
					if (k < 8) {
						g_14a0b20[v18] = (unsigned char) k;
						memset(rec[k], 0, 0x80);
						starts[k] = v14;
						starts[k + 1] = v14 + 0xa;
						memset(&g_1335120[v34], 0, 0x50);
						if (k == 0) {
							fcn_0064d530(rec[0], line + v10, v3c - v10);
							strcpy(buf250, rec[0]);
							for (v3c = 1; v3c < 8; v3c++) {
								starts[v3c] = starts[1] + (v3c - 1) * 0xa;
							}
						}
						else {
							strcpy(rec[k], rec[k - 1]);
							strncat(rec[k], line + v10, v3c - v10);
							strcpy(buf250, rec[k - 1]);
							strcat(buf250, rec[k]);
						}
						strcpy((char*) &g_1335120[v34], rec[k]);
						v18++;
						v34 += 0x50;
						if (v18 > 0x4800) {
							fcn_0064d41a(msg, "Zuviele Label! Zeile:%i", v24);
							MessageBoxA((HWND) 0, msg, "txt_OpenText", 0x30);
							goto fail_close;
						}
						v14 = v14 + (v3c - v10) - 2;
					}
					break;
				case '{':
					fcn_0042bcb0(p);
					v14 += 4;
					continue;
				default:
					break;
				}
			}
			if ((STREAM_FLAG(fp) & 0x10) != 0) {
				break;
			}
		}
		fcn_0064e1fd(fp);
		k = g_6b7fa4;
		p = m_alloc(k, "txt_txt:txt_textbuffer");
		BANK(v2c).text = p;
		if (p == 0) {
			MessageBoxA((HWND) 0, "Memory could not be allocated!", "txt_openText", 0x30);
			goto fail_free;
		}
		memset(p, 0, k);
		v38 = 0;
		for (v10 = v40; v10 < g_6b7f98; v10++) {
			memcpy(BANK(v2c).text + v38, &g_6b7fa0[v10 * 0x1000],
				strlen(&g_6b7fa0[v10 * 0x1000]) + 1);
			g_14a5320[v10] = BANK(v2c).text + v38;
			v38 += (int) strlen(&g_6b7fa0[v10 * 0x1000]) + 1;
			if (v38 > g_6b7fa4) {
				fcn_0041d9e0("txt_OpenText():Zugriffsverletzung!");
			}
			len = (int) strlen(&g_6b7fa0[v10 * 0x1000]);
			for (k = 0; k < len; k++) {
				if (g_14a5320[v10][k] == '|') {
					g_14a5320[v10][k] = 0;
				}
			}
		}
		strcpy(line, g_1052e00);
		strcat(line, p);
		q = (char*) fcn_0064d1a0(line, '.');
		if (q != 0) {
			*q = 0;
		}
		strcpy(BANK(v2c).name, p);
		q = (char*) fcn_0064d1a0(BANK(v2c).name, '.');
		if (q != 0) {
			*q = 0;
		}
		BANK(v2c).first = v40;
		BANK(v2c).count = g_6b7f98 - 1;
		strcat(line, ".res");
		fp = (FILE*) fcn_0064e2f9(line, "wb");
		if (fp == 0) {
			MessageBoxA((HWND) 0, "Could not write ResourceFile!", "txt_OpenText", 0x30);
			goto fail_free;
		}
		fcn_0064e48f(fp, 0, 0);
		v10 = g_6b7f98 - v40;
		fcn_0064ed28(&v10, 4, 1, fp);
		fcn_0064ed28(&BANK(v2c).first, 4, 1, fp);
		fcn_0064ed28(&BANK(v2c).count, 4, 1, fp);
		for (v10 = v40; v10 < g_6b7f98; v10++) {
			k = (int) (g_14a5320[v10] - BANK(v2c).text);
			fcn_0064ed28(&k, 4, 1, fp);
		}
		for (v10 = v40; v10 < g_6b7f98; v10++) {
			fcn_0064ed28(g_1053000[v10], 0x50, 1, fp);
		}
		for (v10 = v40; v10 < g_6b7f98; v10++) {
			fcn_0064ed28(&g_11bb000[v10], 1, 1, fp);
		}
		fcn_0064ed28(&g_6b7fa4, 4, 1, fp);
		fcn_0064ed28(BANK(v2c).text, g_6b7fa4, 1, fp);
		fcn_0064e1fd(fp);
		g_6b7fa4 = 0;
		fcn_0064d41a(msg, "txt_OpenText(): %s compiled!", p);
		v40 = g_6b7f98;
	}

	/* Pass 3: write the C header for the compiled resources. */
	if (a2 == 0) {
		goto success;
	}
	strcpy(line, g_1052f00);
	strcat(line, g_1335000);
	fp = (FILE*) fcn_0064e2f9(line, "wt");
	if (fp == 0) {
		MessageBoxA((HWND) 0, "Could not write HeaderFile!", "txt_OpenText", 0x30);
		goto fail_free;
	}
	fcn_0064e48f(fp, 0, 0);
	if (v18 > 0) {
		for (v10 = 0; v10 < v18; v10++) {
			memset(line, 0, 0xc8);
			strcpy(line, "#define ");
			strcat(line, g_1335120[v10]);
			strcat(line, "  ");
			fcn_00657a73(g_14b7320[v10], u140, 10);
			strcat(line, u140);
			strcat(line, "\n");
			fputs(line, fp);
		}
	}
	for (v10 = 0; v10 < v48; v10++) {
		fputs(def[v10], fp);
	}
	fcn_0064e1fd(fp);

success:
	if (g_6b7fa0 != 0) {
		m_FreeTracked(g_6b7fa0);
		g_6b7fa0 = 0;
	}
	g_6b7f9c = v18;
	g_1052de0 = 1;
	return 1;

fail_close:
	m_FreeTracked(g_6b7fa0);
	g_6b7fa0 = 0;
	fcn_0064e1fd(fp);
	return 0;

fail_free:
	m_FreeTracked(g_6b7fa0);
	g_6b7fa0 = 0;
	return 0;
}
