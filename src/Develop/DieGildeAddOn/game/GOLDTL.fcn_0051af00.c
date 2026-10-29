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
int __cdecl fcn_0041d9e0(char*);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_0046f2c0(int, int);


/* Expands the localized markup template named by `fmt` with the varargs
 * into `out`. */
/* ADDRESS: GOLDTL 0x0051af00 */
void __cdecl fcn_0051af00(char* out, int fmt, ...)
{
	char tmp[0x17d0];
	char buf[0x17d0];
	int tab78[8];
	char txt58[0x20];
	char rec58[0x0c];
	char num[0x14];
	int flag;
	int kind;
	char* p;
	int state;
	char* ap;
	int k;
	int prec;
	int i;
	int j;
	int r;
	int e;
	int res;
	char c;

	ap = (char*) &fmt + 4;
	if (g_1052de0 == 0) {
		return;
	}
	memset(buf, 0, 0x17d0);
	if (fmt < 0x4800) {
		p = g_14a5320[fmt];
		if (p == 0) {
			return;
		}
		if (strlen(p) > 0x17c0) {
			return;
		}
		fcn_0064d530(buf, p, 0x17c0);
	} else {
		strcpy(buf, (char*) fmt);
	}
	state = 0;
	flag = 0;
	p = 0;
	kind = 0;
	if (strlen(buf) == 0) {
		goto done;
	}
	i = 0;
	while (i <= 0x17d0) {
		c = buf[i];
		if (c != '%' && c != '$' && c != '{') {
			i++;
			if (i >= (int) strlen(buf)) {
				break;
			}
			continue;
		}
		r = buf[i + 1] - '0';
		i++;
		if (r >= 0 && r <= 9) {
			i++;
		} else {
			r = -1;
		}
		c = buf[i];
		switch (c) {
		case 'C':
			i++;
			memset(out, 0, 0x80);
			break;
		case 'S':
		case 's':
			p = *(char**) ap;
			ap += 4;
			if ((int) p < 0x4800) {
				kind = g_11bb000[(int) p];
				p = g_14a5320[(int) p];
			}
			k = (r != -1) ? 3 : 2;
			if (kind == 0xff) {
				if (p == 0) {
					p = g_14a5320[(int) p];
				}
			} else if (buf[i] == 's' && flag == 0) {
				p = (char*) fcn_0042b2f0(p, r, 4);
			} else {
				p = (char*) fcn_0042b2f0(p, r, 8);
			}
			if (state == 0) {
				if (strlen(p) + i > 0x17cb) {
					return;
				}
				e = i - k;
				fcn_0064d740(buf + e + strlen(p), buf + i,
					(int) strlen(buf) - e);
				strcpy(buf + e, p);
				break;
			}
			e = i - k - 1;
			while (e >= 0) {
				if (g_6b25b0 > 1) {
					res = __isctype(buf[e], 4);
				} else {
					res = ((unsigned char*) g_6b23a4)[buf[e] * 2] & 4;
				}
				if (res != 0) {
					break;
				}
				if (buf[e] != 0x20) {
					e = -1;
					break;
				}
				e--;
			}
			if (state == 1 || state == 2) {
				res = fcn_0042b2f0(g_14a540c[0], r, 4);
				if (e > -1) {
					k = i - fcn_00517b90(buf, e, txt58);
					sprintf(tmp, g_6a22d8, res, txt58, p);
				} else {
					sprintf(tmp, g_68b3f8, res, p);
				}
				if (fcn_0051e070() == 0 && state == 2) {
					tmp[0] = (char) toupper((unsigned char) tmp[0]);
				}
			} else if (state == 3 || state == 4) {
				res = fcn_0042b2f0(g_14a5400[0], r, 4);
				if (e > -1) {
					k = i - fcn_00517b90(buf, e, txt58);
					sprintf(tmp, g_6a22d8, res, txt58, p);
				} else {
					sprintf(tmp, g_68b3f8, res, p);
				}
				if (fcn_0051e070() == 0 && state == 4) {
					tmp[0] = (char) toupper((unsigned char) tmp[0]);
				}
			} else {
				res = fcn_0042b2f0(g_14a5418[0], r, 4);
				if (e > -1) {
					k = i - fcn_00517b90(buf, e, txt58);
					sprintf(tmp, g_6a22d8, res, txt58, p);
				} else {
					sprintf(tmp, g_68b3f8, res, p);
				}
				if (fcn_0051e070() == 0 && state == 6) {
					tmp[0] = (char) toupper((unsigned char) tmp[0]);
				}
			}
			if (strlen(tmp) + i > 0x17cb) {
				return;
			}
			fcn_0064d740(buf + (i - k) + strlen(tmp), buf + i,
				(int) strlen(buf) - (i - k));
			strcpy(buf + (i - k), tmp);
			state = 0;
			flag = 0;
			break;
		case 'F':
			i++;
			break;
		case 'T':
			if (buf[i - 1] != '%') {
				break;
			}
			res = *(int*) ap;
			ap += 4;
			fcn_0050bc10(res, g_773d75[0], tmp);
			fcn_0064d740(buf + i - 1 + strlen(tmp), buf + i + 1,
				(int) strlen(buf) - i + 1);
			strcpy(buf + i - 1, tmp);
			break;
		case 'w':
			res = *(int*) ap;
			ap += 4;
			res = (int) fcn_0042b2f0(
				g_14a79c0[*(unsigned short*) (0x8680b4 + res * 0x2f4)], 1, 8);
			strcpy(tmp, (char*) res);
			fcn_0064d740(buf + i - 1 + strlen(tmp), buf + i + 1,
				(int) strlen(buf) - i + 1);
			strcpy(buf + i - 1, tmp);
			break;
		case 'i':
			c = buf[i + 1];
			if (c == 'i' || c == 'c' || c == 'b' || c == 'a' ||
			    c == 'n' || c == 't') {
				i += 2;
				break;
			}
			j = *(int*) ap;
			ap += 4;
			if (j > 1 || j == 0) {
				flag = 1;
			}
			if (r != -1) {
				sprintf(num, g_6a2354, r);
				sprintf(tmp, num, j);
			} else {
				sprintf(tmp, g_67d444, j);
			}
			fcn_0064d740(buf + i - 3 + strlen(tmp), buf + i,
				(int) strlen(buf) - i + 1);
			strcpy(buf + i - 2, tmp);
			break;
		case 'I':
			if (r != -1) {
				sprintf(num, g_6a2354, r);
				sprintf(tmp, num, *(int*) ap);
				ap += 4;
				fcn_0064d740(buf + i - 3 + strlen(tmp), buf + i,
					(int) strlen(buf) - i + 1);
				strcpy(buf + i - 2, tmp);
			} else {
				sprintf(tmp, g_67d444, *(int*) ap);
				ap += 4;
				fcn_0064d740(buf + i - 1 + strlen(tmp), buf + i + 1,
					(int) strlen(buf) - i + 1);
				strcpy(buf + i - 1, tmp);
			}
			break;
		case 'f':
			prec = buf[i + 1] - '0';
			if (prec <= 0 || prec >= 9) {
				prec = 0;
			}
			if (prec > 0) {
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
				double d = *(double*) ap;
				ap += 8;
				sprintf(tmp, txt58, d);
			}
			if (strlen(tmp) + i > 0x17cb) {
				return;
			}
			i++;
			fcn_0064d740(buf + i - 1 + strlen(tmp), buf + i,
				(int) strlen(buf) - i + 1);
			strcpy(buf + i - 1, tmp);
			break;
		case 'u':
			k = (r != -1) ? 3 : 2;
			e = i - k;
			state = 1;
			fcn_0064d740(buf + e, buf + i + 1, (int) strlen(buf) - i);
			i = e - 1;
			break;
		case 'U':
			k = (r != -1) ? 3 : 2;
			e = i - k;
			state = 2;
			fcn_0064d740(buf + e, buf + i + 1, (int) strlen(buf) - i);
			i = e - 1;
			break;
		case 'b':
			k = (r != -1) ? 3 : 2;
			e = i - k;
			state = 3;
			fcn_0064d740(buf + e, buf + i + 1, (int) strlen(buf) - i);
			i = e - 1;
			break;
		case 'B':
			k = (r != -1) ? 3 : 2;
			e = i - k;
			if (buf[e] != '%') {
				break;
			}
			state = 4;
			fcn_0064d740(buf + e, buf + i + 1, (int) strlen(buf) - i);
			i = e - 1;
			break;
		case 'e':
			state = 5;
			goto join;
		case 'E':
			state = 6;
		join:
			c = buf[i + 1];
			k = (r != -1) ? 3 : 2;
			e = i - k;
			if (c == 0x20) {
				fcn_0064d740(buf + e, buf + i + 1, (int) strlen(buf) + 2 - i);
			} else {
				fcn_0064d740(buf + e, buf + i + 2, (int) strlen(buf) + 2 - i);
			}
			i = e - 1;
			break;
		case 'N':
			i++;
			if (r == -1) {
				break;
			}
			if (buf[i - 3] != '%' || buf[i - 2] == '$') {
				break;
			}
			kind = *(int*) ap;
			ap += 4;
			fcn_00517c00(kind, buf[i] - '0', i, tmp);
			fcn_0064d740(buf + i + strlen(tmp) - 4, buf + i,
				(int) strlen(buf) + 2 - i);
			strcpy(buf + i - 3, tmp);
			break;
		case 'a':
			if (buf[i - 1] == '%') {
				res = *(int*) ap;
				ap += 4;
				sprintf(tmp, g_699a68, res, 0x14);
				fcn_0064d740(buf + i - 1 + strlen(tmp), buf + i + 1,
					(int) strlen(buf) - i + 1);
				strcpy(buf + i - 1, tmp);
			} else {
				sprintf(tmp, g_6a2348, 0x14);
				memmove(buf + i - 1 + strlen(tmp), buf + i + 1,
					strlen(buf) - i + 1);
				strcpy(buf + i - 1, tmp);
			}
			break;
		case 'r':
			memset(tab78, 0, 0x20);
			prec = 0;
			j = buf[i + 1] - '1';
			if (j >= 0 && j <= 9) {
				prec = j + 9;
			}
			k = i + 3;
			while (1) {
				if (g_6b25b0 > 1) {
					res = __isctype(buf[k], 4);
				} else {
					res = ((unsigned char*) g_6b23a4)[buf[k] * 2] & 4;
				}
				if (res == 0) {
					break;
				}
				k++;
			}
			fcn_0064d530((char*) tab78, buf + i + 3, k - i - 4);
			res = fcn_0064eeec((char*) tab78);
			j = fmt;
			while (j < g_6b7f98) {
				if (g_11bb000[j] == prec) {
					break;
				}
				j++;
			}
			if (j >= g_6b7f98) {
				fcn_0041d9e0(g_6a2318);
				break;
			}
			res = gm_RandomMod(res) & 0xffff;
			p = g_14a5320[res + j];
			if (p == 0) {
				break;
			}
			fcn_0064d740(buf + strlen(p) + (i - k) - 5, buf + i,
				(int) strlen(buf) - (i - k) + 5);
			strcpy(buf + i - 1, p);
			break;
		case 'D':
			fcn_00500d60(&rec58[0], tmp);
			res = fcn_004fe330();
			sprintf(tmp, g_6a2310, g_14a5450[res]);
			fcn_0064d740(buf + strlen(tmp), buf + i, (int) strlen(tmp) + 2 - i);
			strcpy(buf + i - 1, tmp);
			break;
		case 'G':
			p = *(char**) ap;
			ap += 4;
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
			if (buf[i - 2] != 0) {
				sprintf(txt58, g_6a2308, p, buf + i - 2);
			} else {
				strcpy(txt58, p);
			}
			if (strlen(txt58) + i > 0x17cb) {
				return;
			}
			if (r == -1) {
				memmove(buf + i - 2 + strlen(txt58), buf + i,
					strlen(buf) + 2 - i);
			} else {
				memmove(buf + i - 3 + strlen(txt58), buf + i,
					strlen(buf) + 2 - i);
			}
			strcpy(buf + i - 2, txt58);
			state = 0;
			i -= 3;
			break;
		case 'v':
			if (buf[i + 1] == 'v') {
				ap += 4;
				i++;
			}
			break;
		case '%':
			buf[i - 1] = 0x16;
			fcn_0064d740(buf + i + 1, buf + i + 2,
				(int) strlen(buf) - i + 1);
			break;
		default:
			break;
		}
	}
done:
	strcpy(out, buf);
}
