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
extern char* txt_TextEntries[];
extern int g_14b7320[];
extern int g_14b731c[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char g_14a0b20[];
extern char g_6b5c60[];
extern int g_6b7f9c;
#include "GOLDTL.txt_OpenText_gconf.h"
extern int g_6b7fa4;

char* __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* p);
void __cdecl ReportClientMessage(char* msg);
int __cdecl txt_ParseTextVariants(char* text, int index);
void __cdecl txt_ParseRandomText(char* s);
int __cdecl fcn_0064d41a(char* dst, char* fmt, ...);
char* __cdecl fcn_0064d1a0(char* s, int c);
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

#define BANK(i) ((TextBank_42bf20*) txt_TextBanks)[i]

/* ADDRESS: GOLDTL 0x0042bf20 */
int __cdecl txt_OpenText(char* definitionPath, char* writeHeader)
{
	int v10;
	int v14;
	int v18;
	int lineNo;
	int v20;
	char* p;
	char* q;
	char* r;
	char* fileName;
	FILE* fp;
	int fileIndex;
	int endPos;
	int k;
	int len;
	int offset;
	int fileCount;
	int startEntry;
	int defineCount;
	int v44;
	int starts[10];
	char line[0xc8];
	char msg[0x100];
	char path[0x104];
	char buf250[0x80];
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
	startEntry = 0;
	v20 = 0;
	defineCount = 0;
	v44 = 0;
	fileCount = 0;
	txt_EntryCount = 0;
	v10 = 0x80;
	p = (char*) txt_TextBanks + 0x68;
	do {
		*(int*) p = 0;
		p += 0x74;
	} while ((int) p < (int) txt_TextBanks + 0x3a68);

	p = m_alloc(0x4800000, "txt_txt_t:TextArray");
	txt_TextBuffer = p;
	if (p == 0) {
		MessageBoxA((HWND) 0, "Konnte speicher nicht reservieren!", "txt_OpenText", 0x30);
		return 0;
	}
	memset(g_1335120, 0, 0x168000);
	memset(p, 0, 0x4800000);
	memset(g_1053000, 0, 0x168000);
	memset(g_11cd000, 0, 0x168000);
	memset(txt_TextEntries, 0, 0x12000);
	memset(txt_TextBanks, 0, 0x3a00);
	for (p = (char*) g_11bb000; p < (char*) (g_11bb000 + 0x4800); p += 4) *(int*) p = 0xff;

	txt_EntryCount = 0;
	g_6b7fa4 = 0;
	v10 = 0x4800;
	p = (char*) fcn_0064d1a0(definitionPath, '\\');
	if (p != 0) {
		memset(g_1052e00, 0, 0x100);
		memset(path, 0, 0x104);
		memcpy(path, definitionPath, p - definitionPath + 1);
		strcpy(g_1052f00, path);
		strcat(g_1052f00, "text\\");
		strcpy(g_1052e00, definitionPath);
		p = (char*) fcn_0064d1a0(g_1052e00, '\\');
		if (p != 0) {
			*p = 0;
		}
		p = (char*) fcn_0064d1a0(g_1052e00, '\\');
		if (p != 0) {
			*p = 0;
		}
		fcn_0064d41a(path, "%s\\resources\\textbin_%s\\", "german");
		strcpy(g_1052e00, path);
	} else {
		strcpy(g_1052f00, "text\\");
		strcpy(g_1052e00, "\\project\\DieGilde\\gfx\\textbin\\");
	}

	fp = (FILE*) fcn_0064e2f9(definitionPath, "rt");
	if (fp == 0) {
		MessageBoxA((HWND) 0, "Could not open Textfiledefinition!", "Error", 0x30);
		m_FreeTracked(txt_TextBuffer);
		txt_TextBuffer = 0;
		return 0;
	}

	/* Pass 1: collect output path, header path and the include list. */
	do {
		memset(line, 0, 0xc8);
		fgets(line, 0xc8, fp);
		if (strstr(line, "//") != 0) {
			goto pass1_done;
		}
		p = (char*) strstr(line, "#outputpath");
		if (p != 0) {
			p = (char*) fcn_0064e790(p, '"');
			if (p == 0) {
				m_FreeTracked(txt_TextBuffer);
				txt_TextBuffer = 0;
				return 0;
			}
			p++;
			q = (char*) fcn_0064e790(p, '"');
			if (q == 0) {
				m_FreeTracked(txt_TextBuffer);
				txt_TextBuffer = 0;
				return 0;
			}
			*q = 0;
			strcpy(g_1052e00, p);
		}
		p = (char*) strstr(line, "#headerfile");
		if (p != 0) {
			p = (char*) fcn_0064e790(p, '"');
			if (p == 0) {
				m_FreeTracked(txt_TextBuffer);
				txt_TextBuffer = 0;
				return 0;
			}
			p++;
			q = (char*) fcn_0064e790(p, '"');
			if (q == 0) {
				m_FreeTracked(txt_TextBuffer);
				txt_TextBuffer = 0;
				return 0;
			}
			*q = 0;
			strcpy(g_1335000, p);
		}
		p = (char*) strstr(line, "#include");
		if (p != 0) {
			p = (char*) fcn_0064e790(p, '"');
			if (p == 0) {
				m_FreeTracked(txt_TextBuffer);
				txt_TextBuffer = 0;
				return 0;
			}
			p++;
			q = (char*) fcn_0064e790(p, '"');
			if (q == 0) {
				m_FreeTracked(txt_TextBuffer);
				txt_TextBuffer = 0;
				return 0;
			}
			*q = 0;
			strcpy(inc[fileCount++], p);
			if (fileCount > 0x80) {
				m_FreeTracked(txt_TextBuffer);
				txt_TextBuffer = 0;
				return 0;
			}
		}
pass1_done:
		;
	} while ((STREAM_FLAG(fp) & 0x10) == 0);
	fcn_0064e1fd(fp);

	/* Pass 2: compile every listed text file into its binary resource. */
	for (fileIndex = 0; fileIndex < fileCount; fileIndex++) {
		strcpy(line, g_1052f00);
		fileName = inc[fileIndex];
		strcat(line, fileName);
		fp = (FILE*) fcn_0064e2f9(line, "rt");
		if (fp == 0) {
			fcn_0064d41a(msg, "Could not open TextFile: '%s' !", line);
			MessageBoxA((HWND) 0, msg, "Error", 0x30);
			m_FreeTracked(txt_TextBuffer);
			txt_TextBuffer = 0;
			return 0;
		}
		lineNo = 0;
		do {
			memset(line, 0, 0xc8);
			fgets(line, 0xc8, fp);
			if (strcmp(line, g_6b5c60) == 0) {
				break;
			}
			lineNo++;
			v10 = 0;
			if (strstr(line, "#define") != 0) {
				line[strlen(line) - 1] = 0;
				fcn_0064d41a(def[defineCount++], "%s\n", line);
				if (defineCount > 0x60) {
					MessageBoxA((HWND) 0, "To many defines!", "Error", 0x30);
				}
				v10 = strlen(line);
			}
			if (v20 != 0) {
				if (fcn_0064e790(line, '"') == 0 && strstr(line, "*/") != 0) {
					v20 = 0;
				}
				v10 = strlen(line);
			}
			while (line[v10++] == ' ') {
			}
			v10--;
			for (v14 = v10; (unsigned int) v10 < strlen(line); v10++, v14++) {
				p = line + v10;
				switch (line[v10]) {
				case '\t':
					v14 += 4;
					continue;
				case '(':
					if (txt_ParseTextVariants(p, v18) == 0) {
						fcn_0064d41a(msg, "Syntax error in file %s in line %i", fileName, lineNo);
						MessageBoxA((HWND) 0, msg, "Error in textfile", 0x30);
					}
					v10 = (int) strlen(line);
					break;
				case '{':
					txt_ParseRandomText(p);
					v10 = v14 + 4;
					continue;
				case '/':
					if (line[v10 + 1] == '*') {
						v20++;
						if (strstr(line + v10 + 1, "*/") != 0) {
							v20--;
						}
					}
					v10 = (int) strlen(line);
					break;
				case '*':
					if (line[v10 + 1] == '/') {
						v20--;
					}
					if (v20 < 0) {
						fcn_0064d41a(msg, "txt_TextOpen(): nested comments found. in file %s in line %i", fileName, lineNo);
					}
					break;
				case '_':
					if (v44 != 0) {
						fcn_0064d41a(msg, "Syntax error in file %s in line %i: missing ';'", inc[fileIndex], lineNo);
						MessageBoxA((HWND) 0, msg, "txt_OpenText", 0x30);
						m_FreeTracked(txt_TextBuffer);
						txt_TextBuffer = 0;
						fcn_0064e1fd(fp);
						return 0;
					}
					g_14b7320[v18] = txt_EntryCount;
					endPos = v10;
					while ((unsigned int) endPos < strlen(line) && line[endPos] != 0xa && line[endPos] != 0x20 && line[endPos] != 9) {
						endPos++;
					}
					memset(g_11cd000[v18], 0, 0x50);
					fcn_0064d530(g_11cd000[v18], line + v10, endPos - v10);
					for (k = 0; k < 8; k++) {
						if (v14 <= starts[k]) {
							g_14a0b20[v18] = (unsigned char) k;
							memset(rec[k], 0, 0x80);
							starts[k] = v14;
							starts[k + 1] = v14 + 0xa;
							memset(g_1335120[v18], 0, 0x50);
							if (k == 0) {
								fcn_0064d530(rec[0], line + v10, endPos - v10);
								strcpy(buf250, rec[0]);
								for (k = 1; k < 8; k++) {
									starts[k] = v14 + k * 0xa;
								}
								k = 0;
							} else {
								strcpy(rec[k], rec[k - 1]);
								strncat(rec[k], line + v10, endPos - v10);
								strcpy(buf250, rec[k - 1]);
								strcat(buf250, rec[k]);
							}
							strcpy(g_1335120[v18], rec[k]);
							v18++;
							if (v18 > 0x4800) {
								fcn_0064d41a(msg, "Zuviele Label! Zeile:%i", lineNo);
								MessageBoxA((HWND) 0, msg, "txt_OpenText", 0x30);
								m_FreeTracked(txt_TextBuffer);
								txt_TextBuffer = 0;
								fcn_0064e1fd(fp);
								return 0;
							}
							v14 = v14 + (endPos - v10) - 2;
							break;
						}
					}
					v10 = endPos - 2;
					v14 = v14 + (endPos - v10) - 2;
					break;
				case '"':
					v10++;
					v14++;
					p = (char*) fcn_0064e790(line + v10, '"');
					k = (int) (p - (line + v10));
					if (k < 0) {
						fcn_0064d41a(msg, "Syntax error in file %s in line %i", fileName, lineNo);
						MessageBoxA((HWND) 0, msg, "Error in textfile", 0x30);
						break;
					}
					memset(msg, 0, sizeof(msg));
					if (k > 0xff) {
						fcn_0064d41a(msg, "Line too long in file %s in line %i", fileName, lineNo);
						MessageBoxA((HWND) 0, msg, "Error in textfile", 0x30);
						break;
					}
					fcn_0064d530(msg, line + v10, k);
					p = (char*) strstr(msg, "/*");
					if (p != 0) {
						v10 += k + 1;
						v14 += k + 1;
						while (p != 0) {
							r = (char*) strstr(msg, "*/");
							if (r < p) {
								fcn_0064d41a(msg, "Syntax error in file %s in line %i: Missing '/*'", fileName, lineNo);
								MessageBoxA((HWND) 0, msg, "Error in textfile", 0x30);
								break;
							}
							if (r == 0) {
								fcn_0064d41a(msg, "Syntax error in file %s in line %i: Missing '*/'", fileName, lineNo);
								MessageBoxA((HWND) 0, msg, "Error in textfile", 0x30);
								break;
							}
							memmove(p, r + 2, strlen(r + 2) + 1);
							p = (char*) strstr(msg, "/*");
						}
						k = (int) strlen(msg);
						if (strlen(&txt_TextBuffer[txt_EntryCount * 0x1000]) + k > 0xfff) {
							fcn_0064d41a(msg, "String too long in file %s in line %i", inc[fileIndex], lineNo);
							m_FreeTracked(txt_TextBuffer);
							txt_TextBuffer = 0;
							return 0;
						}
						strncat(&txt_TextBuffer[txt_EntryCount * 0x1000], msg, k);
					}
					else {
						if (strlen(&txt_TextBuffer[txt_EntryCount * 0x1000]) + k > 0xfff) {
							fcn_0064d41a(msg, "String too long in file %s in line %i", inc[fileIndex], lineNo);
							m_FreeTracked(txt_TextBuffer);
							txt_TextBuffer = 0;
							return 0;
						}
						strncat(&txt_TextBuffer[txt_EntryCount * 0x1000], line + v10, k);
						v10 += k + 1;
						v14 += k + 1;
					}
					g_6b7fa4 += k;
					v44 = 1;
					if (line[v10] == ',') {
						do {
							v10 += 2;
							p = (char*) fcn_0064e790(line + v10, '"');
							k = (int) (p - (line + v10));
							if (k < 0) {
								fcn_0064d41a(msg, "Syntax error in file %s in line %i", fileName, lineNo);
								MessageBoxA((HWND) 0, msg, "Error in textfile", 0x30);
								v10 = (int) strlen(line);
								break;
							}
							msg[0] = '|';
							strcpy(msg + 1, line + v10);
							if (strlen(&txt_TextBuffer[txt_EntryCount * 0x4800000]) + strlen(msg) > 0xfff) {
								fcn_0064d41a(msg, "String too long in file %s in line %i", inc[fileIndex], lineNo);
								m_FreeTracked(txt_TextBuffer);
								txt_TextBuffer = 0;
								return 0;
							}
							strncat(&txt_TextBuffer[txt_EntryCount * 0x1000], msg, strlen(msg));
							g_6b7fa4 += (int) strlen(msg);
							v10 += k + 1;
							v14 += k + 1;
						} while (line[v10] == ',');
					}
					v10--;
					v14--;
					break;
				case ';':
					strcpy(g_1053000[txt_EntryCount], g_1335120[v18 - 1]);
					strcat(g_1053000[txt_EntryCount], "+");
					fcn_00657a73(txt_EntryCount - g_14b7320[v18 - 1], u140, 10);
					strcat(g_1053000[txt_EntryCount], u140);
					g_6b7fa4 = g_6b7fa4 + 1;
					txt_EntryCount = txt_EntryCount + 1;
					if (txt_EntryCount > 0x4800) {
						MessageBoxA((HWND) 0, "Zuviele Textenums!", "txt_OpenText", 0x30);
						m_FreeTracked(txt_TextBuffer);
						txt_TextBuffer = 0;
						fcn_0064e1fd(fp);
						return 0;
					}
					v44 = 0;
					v14++;
					continue;
				default:
					break;
				}
			}
		} while ((STREAM_FLAG(fp) & 0x10) == 0);
		fcn_0064e1fd(fp);
		p = m_alloc(g_6b7fa4, "txt_txt:txt_textbuffer");
		BANK(fileIndex).text = p;
		if (p == 0) {
			MessageBoxA((HWND) 0, "Memory could not be allocated!", "txt_openText", 0x30);
			if (txt_TextBuffer != 0) {
				m_FreeTracked(txt_TextBuffer);
				txt_TextBuffer = 0;
			}
			return 0;
		}
		memset(p, 0, g_6b7fa4);
		offset = 0;
		for (v10 = startEntry; v10 < txt_EntryCount; v10++) {
			memcpy(BANK(fileIndex).text + offset, &txt_TextBuffer[v10 * 0x1000],
				strlen(&txt_TextBuffer[v10 * 0x1000]) + 1);
			txt_TextEntries[v10] = BANK(fileIndex).text + offset;
			offset += (int) strlen(&txt_TextBuffer[v10 * 0x1000]) + 1;
			if (offset > g_6b7fa4) {
				ReportClientMessage("txt_OpenText():Zugriffsverletzung!");
			}
			len = (int) strlen(&txt_TextBuffer[v10 * 0x1000]);
			for (k = 0; k < len; k++) {
				if (txt_TextEntries[v10][k] == '|') {
					txt_TextEntries[v10][k] = 0;
				}
			}
		}
		strcpy(line, g_1052e00);
		strcat(line, fileName);
		q = (char*) fcn_0064d1a0(line, '.');
		if (q != 0) {
			*q = 0;
		}
		strcpy(BANK(fileIndex).name, fileName);
		q = (char*) fcn_0064d1a0(BANK(fileIndex).name, '.');
		if (q != 0) {
			*q = 0;
		}
		BANK(fileIndex).first = startEntry;
		BANK(fileIndex).count = txt_EntryCount - 1;
		strcat(line, ".res");
		fp = (FILE*) fcn_0064e2f9(line, "wb");
		if (fp == 0) {
			MessageBoxA((HWND) 0, "Could not write ResourceFile!", "txt_OpenText", 0x30);
			m_FreeTracked(txt_TextBuffer);
			txt_TextBuffer = 0;
			return 0;
		}
		fcn_0064e48f(fp, 0, 0);
		v10 = txt_EntryCount - startEntry;
		fcn_0064ed28(&v10, 4, 1, fp);
		fcn_0064ed28(&BANK(fileIndex).first, 4, 1, fp);
		fcn_0064ed28(&BANK(fileIndex).count, 4, 1, fp);
		for (v10 = startEntry; v10 < txt_EntryCount; v10++) {
			k = (int) (txt_TextEntries[v10] - BANK(fileIndex).text);
			fcn_0064ed28(&k, 4, 1, fp);
		}
		for (v10 = startEntry; v10 < txt_EntryCount; v10++) {
			fcn_0064ed28(g_1053000[v10], 0x50, 1, fp);
		}
		for (v10 = startEntry; v10 < txt_EntryCount; v10++) {
			fcn_0064ed28(&g_11bb000[v10], 1, 1, fp);
		}
		fcn_0064ed28(&g_6b7fa4, 4, 1, fp);
		fcn_0064ed28(BANK(fileIndex).text, g_6b7fa4, 1, fp);
		fcn_0064e1fd(fp);
		g_6b7fa4 = 0;
		fcn_0064d41a(msg, "txt_OpenText(): %s compiled!", fileName);
		startEntry = txt_EntryCount;
	}

	/* Pass 3: write the C header for the compiled resources. */
	if (writeHeader == 0) {
		goto success;
	}
	strcpy(line, g_1052f00);
	strcat(line, g_1335000);
	fp = (FILE*) fcn_0064e2f9(line, "wt");
	if (fp == 0) {
		MessageBoxA((HWND) 0, "Could not write HeaderFile!", "txt_OpenText", 0x30);
		m_FreeTracked(txt_TextBuffer);
		txt_TextBuffer = 0;
		return 0;
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
	for (v10 = 0; v10 < defineCount; v10++) {
		fputs(def[v10], fp);
	}
	fcn_0064e1fd(fp);

success:
	if (txt_TextBuffer != 0) {
		m_FreeTracked(txt_TextBuffer);
		txt_TextBuffer = 0;
	}
	g_6b7f9c = v18;
	g_1052de0 = 1;
	return 1;
}
