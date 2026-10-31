#include <string.h>
#include <ctype.h>

/*
 * io_Text-family buffer expansion (attested "io_Text()" diagnostics at
 * 0x51c68a). Native shape from 0x51af00:
 *   frame 0x332c, ebp frame pointer (and esp,-8 + __chkstk 0x332c).
 *   locals, esp-relative after the three callee-saved pushes:
 *     0x10 precision digit, 0x14 k (directive length),
 *     0x18 vararg walker (char*), 0x1c state, 0x20 p (resolved text),
 *     0x24 kind/lookup value, 0x28 flag,
 *     0x2c num[0x14], 0x4c date record[0xc], 0x58.. text scratch area,
 *     0x78 tab78[8], 0x398 buf[0x17d0], 0x1b68 tmp[0x17d0].
 *   arg1 out buffer, arg2 text id (<0x4800 indexes g_14a5320) or a
 *   direct char* template, then printf-style varargs read through a
 *   single walking pointer local.
 * The markup scan and the state machine (u/U/b/B/e/E set the case
 * prefix applied by a later S/s) mirror the sibling io_Text bodies
 * 0x51c840 / 0x519190; this variant consumes its values from the
 * vararg list instead of a call-state record.
 */

extern int g_1052de0;
extern char* g_14a5320[];
extern int g_11bb000[];
extern char* g_14a5400[];
extern char* g_14a540c[];
extern char* g_14a5418[];
extern char* g_14a5450[];
extern char* g_14a79c0[];
extern int g_6b25b0;
extern int g_6b23a4;
extern int g_6b7f98;
extern char g_6a22d8[];
extern char g_68b3f8[];
extern char g_67d444[];
extern char g_6a2308[];
extern char g_6a2310[];
extern char g_6a2318[];
extern char g_6a2348[];
extern char g_6a234c[];
extern char g_6a234e[];
extern char g_6a2350[];
extern char g_6a2354[];
extern char g_6a2388[];
extern char g_6a238c[];
extern char g_6a238e[];
extern char g_699a68[];
extern char g_677c94[];
extern char g_773d75[];

int sprintf(char*, const char*, ...);
int __cdecl __isctype(int, int);
int __cdecl fcn_0042b2f0(char*, int, int);
int __cdecl fcn_0064d530(char*, const char*, unsigned int);
int __cdecl fcn_0064eeec(char*);
int __cdecl fcn_0064d41a(char*, const char*, ...);
int __cdecl fcn_0064d740(char*, char*, int);
int __cdecl fcn_00517b90(char*, int, char*);
int __cdecl fcn_0051e070(void);
int __cdecl fcn_00500d60(void*, void*);
int __cdecl fcn_004fe330(void);
int __cdecl fcn_0050bc10(int, int, char*);
int __cdecl fcn_00517c00(int, int, int, char*);
int __cdecl ReportClientMessage(char*);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_0046f2c0(int, int);


/* Expands the localized markup template named by `fmt` with the varargs
 * into `out`. */
/* ADDRESS: GOLDTL 0x0051af00 */
void __cdecl io_FormatTextBuffer(char* output, int format_selector, ...)
{
	char expansion_buffer[0x17d0];
	char work_buffer[0x17d0];
	int tab78[8];
	char txt58[0x20];
	char rec58[0x0c];
	char num[0x14];
	int flag;
	int kind;
	char* p;
	int grammar_state;
	char* argument_cursor;
	int k;
	int precision;
	int i;
	int j;
	int r;
	int e;
	int res;
	char c;

	argument_cursor = (char*) &format_selector + 4;
	if (g_1052de0 == 0) {
		return;
	}
	memset(work_buffer, 0, 0x17d0);
	if (format_selector < 0x4800) {
		p = g_14a5320[format_selector];
		if (p == 0) {
			return;
		}
		if (strlen(p) > 0x17c0) {
			return;
		}
		fcn_0064d530(work_buffer, p, 0x17c0);
	} else {
		strcpy(work_buffer, (char*) format_selector);
	}
	grammar_state = 0;
	flag = 0;
	p = 0;
	kind = 0;
	if (strlen(work_buffer) == 0) {
		goto done;
	}
	i = 0;
	while (i <= 0x17d0) {
		c = work_buffer[i];
		if (c != '%' && c != '$' && c != '{') {
			i++;
			if (i >= (int) strlen(work_buffer)) {
				break;
			}
			continue;
		}
		r = work_buffer[i + 1] - '0';
		i++;
		if (r >= 0 && r <= 9) {
			i++;
		} else {
			r = -1;
		}
		c = work_buffer[i];
		switch (c) {
		case 'C':
			i++;
			memset(output, 0, 0x80);
			break;
		case 'S':
		case 's':
			p = *(char**) argument_cursor;
			argument_cursor += 4;
			if ((int) p < 0x4800) {
				kind = g_11bb000[(int) p];
				p = g_14a5320[(int) p];
			}
			k = (r != -1) ? 3 : 2;
			if (kind == 0xff) {
				if (p == 0) {
					p = g_14a5320[(int) p];
				}
			} else if (work_buffer[i] == 's' && flag == 0) {
				p = (char*) fcn_0042b2f0(p, r, 4);
			} else {
				p = (char*) fcn_0042b2f0(p, r, 8);
			}
			if (grammar_state == 0) {
				if (strlen(p) + i > 0x17cb) {
					return;
				}
				e = i - k;
				fcn_0064d740(work_buffer + e + strlen(p), work_buffer + i,
					(int) strlen(work_buffer) - e);
				strcpy(work_buffer + e, p);
				break;
			}
			e = i - k - 1;
			while (e >= 0) {
				if (g_6b25b0 > 1) {
					res = __isctype(work_buffer[e], 4);
				} else {
					res = ((unsigned char*) g_6b23a4)[work_buffer[e] * 2] & 4;
				}
				if (res != 0) {
					break;
				}
				if (work_buffer[e] != 0x20) {
					e = -1;
					break;
				}
				e--;
			}
			if (grammar_state == 1 || grammar_state == 2) {
				res = fcn_0042b2f0(g_14a540c[0], r, 4);
				if (e > -1) {
					k = i - fcn_00517b90(work_buffer, e, txt58);
					sprintf(expansion_buffer, g_6a22d8, res, txt58, p);
				} else {
					sprintf(expansion_buffer, g_68b3f8, res, p);
				}
				if (fcn_0051e070() == 0 && grammar_state == 2) {
					expansion_buffer[0] = (char) toupper((unsigned char) expansion_buffer[0]);
				}
			} else if (grammar_state == 3 || grammar_state == 4) {
				res = fcn_0042b2f0(g_14a5400[0], r, 4);
				if (e > -1) {
					k = i - fcn_00517b90(work_buffer, e, txt58);
					sprintf(expansion_buffer, g_6a22d8, res, txt58, p);
				} else {
					sprintf(expansion_buffer, g_68b3f8, res, p);
				}
				if (fcn_0051e070() == 0 && grammar_state == 4) {
					expansion_buffer[0] = (char) toupper((unsigned char) expansion_buffer[0]);
				}
			} else {
				res = fcn_0042b2f0(g_14a5418[0], r, 4);
				if (e > -1) {
					k = i - fcn_00517b90(work_buffer, e, txt58);
					sprintf(expansion_buffer, g_6a22d8, res, txt58, p);
				} else {
					sprintf(expansion_buffer, g_68b3f8, res, p);
				}
				if (fcn_0051e070() == 0 && grammar_state == 6) {
					expansion_buffer[0] = (char) toupper((unsigned char) expansion_buffer[0]);
				}
			}
			if (strlen(expansion_buffer) + i > 0x17cb) {
				return;
			}
			fcn_0064d740(work_buffer + (i - k) + strlen(expansion_buffer), work_buffer + i,
				(int) strlen(work_buffer) - (i - k));
			strcpy(work_buffer + (i - k), expansion_buffer);
			grammar_state = 0;
			flag = 0;
			break;
		case 'F':
			i++;
			break;
		case 'T':
			if (work_buffer[i - 1] != '%') {
				break;
			}
			res = *(int*) argument_cursor;
			argument_cursor += 4;
			fcn_0050bc10(res, g_773d75[0], expansion_buffer);
			fcn_0064d740(work_buffer + i - 1 + strlen(expansion_buffer), work_buffer + i + 1,
				(int) strlen(work_buffer) - i + 1);
			strcpy(work_buffer + i - 1, expansion_buffer);
			break;
		case 'w':
			res = *(int*) argument_cursor;
			argument_cursor += 4;
			res = (int) fcn_0042b2f0(
				g_14a79c0[*(unsigned short*) (0x8680b4 + res * 0x2f4)], 1, 8);
			strcpy(expansion_buffer, (char*) res);
			fcn_0064d740(work_buffer + i - 1 + strlen(expansion_buffer), work_buffer + i + 1,
				(int) strlen(work_buffer) - i + 1);
			strcpy(work_buffer + i - 1, expansion_buffer);
			break;
		case 'i':
			c = work_buffer[i + 1];
			if (c == 'i' || c == 'c' || c == 'b' || c == 'a' ||
			    c == 'n' || c == 't') {
				i += 2;
				break;
			}
			j = *(int*) argument_cursor;
			argument_cursor += 4;
			if (j > 1 || j == 0) {
				flag = 1;
			}
			if (r != -1) {
				sprintf(num, g_6a2354, r);
				sprintf(expansion_buffer, num, j);
			} else {
				sprintf(expansion_buffer, g_67d444, j);
			}
			fcn_0064d740(work_buffer + i - 3 + strlen(expansion_buffer), work_buffer + i,
				(int) strlen(work_buffer) - i + 1);
			strcpy(work_buffer + i - 2, expansion_buffer);
			break;
		case 'I':
			if (r != -1) {
				sprintf(num, g_6a2354, r);
				sprintf(expansion_buffer, num, *(int*) argument_cursor);
				argument_cursor += 4;
				fcn_0064d740(work_buffer + i - 3 + strlen(expansion_buffer), work_buffer + i,
					(int) strlen(work_buffer) - i + 1);
				strcpy(work_buffer + i - 2, expansion_buffer);
			} else {
				sprintf(expansion_buffer, g_67d444, *(int*) argument_cursor);
				argument_cursor += 4;
				fcn_0064d740(work_buffer + i - 1 + strlen(expansion_buffer), work_buffer + i + 1,
					(int) strlen(work_buffer) - i + 1);
				strcpy(work_buffer + i - 1, expansion_buffer);
			}
			break;
		case 'f':
			precision = work_buffer[i + 1] - '0';
			if (precision <= 0 || precision >= 9) {
				precision = 0;
			}
			if (precision > 0) {
				i++;
			}
			if (r != -1) {
				sprintf(num, g_6a238c);
				sprintf(num + 4, g_6a2388);
				sprintf(txt58, g_6a234c);
				sprintf(txt58 + strlen(txt58), g_6a2350);
			} else {
				sprintf(txt58, g_6a234c);
				sprintf(txt58 + strlen(txt58), g_6a2350);
			}
			{
				double d = *(double*) argument_cursor;
				argument_cursor += 8;
				sprintf(expansion_buffer, txt58, d);
			}
			if (strlen(expansion_buffer) + i > 0x17cb) {
				return;
			}
			i++;
			fcn_0064d740(work_buffer + i - 1 + strlen(expansion_buffer), work_buffer + i,
				(int) strlen(work_buffer) - i + 1);
			strcpy(work_buffer + i - 1, expansion_buffer);
			break;
		case 'u':
			k = (r != -1) ? 3 : 2;
			e = i - k;
			grammar_state = 1;
			fcn_0064d740(work_buffer + e, work_buffer + i + 1, (int) strlen(work_buffer) - i);
			i = e - 1;
			break;
		case 'U':
			k = (r != -1) ? 3 : 2;
			e = i - k;
			grammar_state = 2;
			fcn_0064d740(work_buffer + e, work_buffer + i + 1, (int) strlen(work_buffer) - i);
			i = e - 1;
			break;
		case 'b':
			k = (r != -1) ? 3 : 2;
			e = i - k;
			grammar_state = 3;
			fcn_0064d740(work_buffer + e, work_buffer + i + 1, (int) strlen(work_buffer) - i);
			i = e - 1;
			break;
		case 'B':
			k = (r != -1) ? 3 : 2;
			e = i - k;
			if (work_buffer[e] != '%') {
				break;
			}
			grammar_state = 4;
			fcn_0064d740(work_buffer + e, work_buffer + i + 1, (int) strlen(work_buffer) - i);
			i = e - 1;
			break;
		case 'e':
			grammar_state = 5;
			goto join;
		case 'E':
			grammar_state = 6;
		join:
			c = work_buffer[i + 1];
			k = (r != -1) ? 3 : 2;
			e = i - k;
			if (c == 0x20) {
				fcn_0064d740(work_buffer + e, work_buffer + i + 1, (int) strlen(work_buffer) + 2 - i);
			} else {
				fcn_0064d740(work_buffer + e, work_buffer + i + 2, (int) strlen(work_buffer) + 2 - i);
			}
			i = e - 1;
			break;
		case 'N':
			i++;
			if (r == -1) {
				break;
			}
			if (work_buffer[i - 3] != '%' || work_buffer[i - 2] == '$') {
				break;
			}
			kind = *(int*) argument_cursor;
			argument_cursor += 4;
			fcn_00517c00(kind, work_buffer[i] - '0', i, expansion_buffer);
			fcn_0064d740(work_buffer + i + strlen(expansion_buffer) - 4, work_buffer + i,
				(int) strlen(work_buffer) + 2 - i);
			strcpy(work_buffer + i - 3, expansion_buffer);
			break;
		case 'a':
			if (work_buffer[i - 1] == '%') {
				res = *(int*) argument_cursor;
				argument_cursor += 4;
				sprintf(expansion_buffer, g_699a68, res, 0x14);
				fcn_0064d740(work_buffer + i - 1 + strlen(expansion_buffer), work_buffer + i + 1,
					(int) strlen(work_buffer) - i + 1);
				strcpy(work_buffer + i - 1, expansion_buffer);
			} else {
				sprintf(expansion_buffer, g_6a2348, 0x14);
				memmove(work_buffer + i - 1 + strlen(expansion_buffer), work_buffer + i + 1,
					strlen(work_buffer) - i + 1);
				strcpy(work_buffer + i - 1, expansion_buffer);
			}
			break;
		case 'r':
			memset(tab78, 0, 0x20);
			precision = 0;
			j = work_buffer[i + 1] - '1';
			if (j >= 0 && j <= 9) {
				precision = j + 9;
			}
			k = i + 3;
			while (1) {
				if (g_6b25b0 > 1) {
					res = __isctype(work_buffer[k], 4);
				} else {
					res = ((unsigned char*) g_6b23a4)[work_buffer[k] * 2] & 4;
				}
				if (res == 0) {
					break;
				}
				k++;
			}
			fcn_0064d530((char*) tab78, work_buffer + i + 3, k - i - 4);
			res = fcn_0064eeec((char*) tab78);
			j = format_selector;
			while (j < g_6b7f98) {
				if (g_11bb000[j] == precision) {
					break;
				}
				j++;
			}
			if (j >= g_6b7f98) {
				ReportClientMessage(g_6a2318);
				break;
			}
			res = gm_RandomMod(res) & 0xffff;
			p = g_14a5320[res + j];
			if (p == 0) {
				break;
			}
			fcn_0064d740(work_buffer + strlen(p) + (i - k) - 5, work_buffer + i,
				(int) strlen(work_buffer) - (i - k) + 5);
			strcpy(work_buffer + i - 1, p);
			break;
		case 'D':
			fcn_00500d60(&rec58[0], expansion_buffer);
			res = fcn_004fe330();
			sprintf(expansion_buffer, g_6a2310, g_14a5450[res]);
			fcn_0064d740(work_buffer + strlen(expansion_buffer), work_buffer + i, (int) strlen(expansion_buffer) + 2 - i);
			strcpy(work_buffer + i - 1, expansion_buffer);
			break;
		case 'G':
			p = *(char**) argument_cursor;
			argument_cursor += 4;
			i++;
			if ((int) p < 0x4800) {
				kind = g_11bb000[(int) p];
				p = g_14a5320[(int) p];
			}
			if (r != -1) {
				p = (char*) fcn_0042b2f0(p, r, 4);
				i--;
			}
			if (p == 0) {
				p = g_14a5320[(int) p];
			}
			if (work_buffer[i - 2] != 0) {
				sprintf(txt58, g_6a2308, p, work_buffer + i - 2);
			} else {
				strcpy(txt58, p);
			}
			if (strlen(txt58) + i > 0x17cb) {
				return;
			}
			if (r == -1) {
				memmove(work_buffer + i - 2 + strlen(txt58), work_buffer + i,
					strlen(work_buffer) + 2 - i);
			} else {
				memmove(work_buffer + i - 3 + strlen(txt58), work_buffer + i,
					strlen(work_buffer) + 2 - i);
			}
			strcpy(work_buffer + i - 2, txt58);
			grammar_state = 0;
			i -= 3;
			break;
		case 'v':
			if (work_buffer[i + 1] == 'v') {
				argument_cursor += 4;
				i++;
			}
			break;
		case '%':
			work_buffer[i - 1] = 0x16;
			fcn_0064d740(work_buffer + i + 1, work_buffer + i + 2,
				(int) strlen(work_buffer) - i + 1);
			break;
		default:
			break;
		}
	}
done:
	strcpy(output, work_buffer);
}
