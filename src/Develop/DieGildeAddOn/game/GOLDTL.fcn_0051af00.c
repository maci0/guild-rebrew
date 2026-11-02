#include <string.h>
#include <ctype.h>

/*
 * io_Text-family output-buffer grammar expansion (attested "io_Text()"
 * diagnostic at 0x51c68a). Native shape from 0x51af00:
 *
 *   push ebp / mov ebp,esp / and esp,-8 / mov eax,0x332c / call __chkstk
 *   push ebx / push esi / push edi
 *
 * chkstk immediate = total local bytes - 4 x saved-register pushes (verified
 * with a throwaway frame probe: 0x17e0 locals and four pushes produced
 * 0x17d0).  The align(8) aggregate below keeps the aligned prologue and the
 * native local displacements: buf at 0x398, tmp at 0x1b68, frame 0x3330.
 * Native is 0x332c because this CL saves only esi/edi here (loop index in
 * esi, directive digit in a scratch register) where the reference saves
 * ebx/esi/edi: 0x3338 - 2*4 = 0x3330 versus 0x3338 - 3*4 = 0x332c.  A third
 * live callee-saved value would land the reference immediate exactly.
 *
 * Locals, offsets from the post-push esp:
 *   0x10 res, 0x14 k, 0x18 vararg walker, 0x1c grammar_state,
 *   0x20 p, 0x24 kind, 0x28 flag, 0x2c num[0x14], 0x40 format scratch,
 *   0x78 tab78[8], 0x98/0x118/0x158/0x198/0x1d8/0x218/0x258/0x298
 *   per-branch scratch, 0x398 buf[0x17d0], 0x1b68 tmp[0x17d0].
 *   text.unrecovered stands in for the native scratch at 0x2a8..0x397, whose
 *   users are not yet identified; it carries no source semantics.
 *
 * arg1 out buffer, arg2 text id (<0x4800 indexes g_14a5320) or a direct
 * char* template, then printf-style varargs read through one walking
 * pointer.  The 22-case dispatch (selector table 0x51c7e4, jump table
 * 0x51c78c) covers % B C D E F G I N S T U a b e f i r u v w; the case
 * bodies are laid out in native order.
 *
 * Remaining gaps against the native body: the loop index sits in esi here and
 * the directive digit in a scratch register (native: ebx and esi), so the
 * guard and every case body differ in register names; the repeated
 * strlen/memmove/strcpy bursts are written once per case rather than with the
 * reference's folded tails; the 'I' regrouping loop and the 'G' icon path are
 * transcribed from the decoded call/format shape, not instruction for
 * instruction; text.unrecovered has no identified user.
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
extern char g_6a2350[];
extern char g_6a2354[];
extern char g_6a238c[];
extern char g_699a68[];
extern char g_773d75[];

int __cdecl fcn_0042b2f0(char*, int, int);
int __cdecl fcn_0064d530(char*, const char*, unsigned int);
int __cdecl fcn_0064eeec(char*);
int __cdecl fcn_0064d41a(char*, const char*, ...);
int __cdecl fcn_0064d740(char*, char*, int);
int __cdecl fcn_00517b90(char*, int, char*);
int __cdecl fcn_0051e070(void);
void __cdecl fcn_00500d60(void*, void*);
int __cdecl fcn_004fe330(char*, int);
int __cdecl fcn_0050bc10(int, int, char*);
int __cdecl fcn_00517c00(int, char*, int, char*);
int __cdecl ReportClientMessage(char*);
int __cdecl gm_RandomMod(int);
int __cdecl __isctype(int, int);
int sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x0051af00 */
/* ADDRESS: GOLD 0x00517700 */
void __cdecl io_FormatTextBuffer(char* output, int format_selector, ...)
{
	char num[0x14];
	char fmt_scratch[0x38];
	int tab78[8];
	char slot98[0x40];
	char slotd8[0x40];
	char slot118[0x40];
	char slot158[0x40];
	char slot198[0x40];
	char slot1d8[0x40];
	char slot218[0x40];
	char slot258[0x40];
	char slot298[0x40];
	__declspec(align(8)) struct {
		/* native scratch 0x2a8..0x397; its users are not yet identified */
		char unrecovered[0x100];
		char buf[0x17d0];
		char tmp[0x17d0];
	} text;
	int i = 0;
	int res;
	int k;
	char* cursor;
	int grammar_state;
	int kind;
	char* p;
	int flag;
	int e;
	int r;
	int j;
	char c;

	grammar_state = 0;
	kind = 0;
	flag = 0;
	if (g_1052de0 == 0) {
		return;
	}
	cursor = (char*) &format_selector + 4;
	memset(text.buf, 0, 0x17d0);
	if (format_selector < 0x4800) {
		p = g_14a5320[format_selector];
		if (p == 0) {
			return;
		}
		if (strlen(p) > 0x17c0) {
			return;
		}
		fcn_0064d530(text.buf, p, 0x17c0);
	} else {
		strcpy(text.buf, (char*) format_selector);
	}
	if (strlen(text.buf) == 0) {
		goto done;
	}
	for (;;) {
		if (i > 0x17d0) {
			break;
		}
		c = text.buf[i];
		if (c != '%' && c != '$' && c != '{') {
			i++;
			if (i < (int) strlen(text.buf)) {
				continue;
			}
			break;
		}
		r = text.buf[i + 1] - '0';
		i++;
		if (r >= 0 && r <= 9) {
			i++;
		} else {
			r = -1;
		}
		c = text.buf[i];
		switch (c) {
		case 'C':
			i++;
			memset(output, 0, 0x80);
			break;
		case 'S':
		case 's':
			cursor += 4;
			p = *(char**) (cursor - 4);
			if ((int) p < 0x4800) {
				kind = g_11bb000[(int) p];
				p = g_14a5320[(int) p];
			}
			k = (r != -1) ? 3 : 2;
			if (kind == 0xff) {
				if (p == 0) {
					p = g_14a5320[(int) p];
				}
			} else {
				if (r == -1) {
					r = 1;
				}
				if (text.buf[i - 1] == 's' && flag == 0) {
					p = (char*) fcn_0042b2f0(p, r, 4);
				} else {
					p = (char*) fcn_0042b2f0(p, r, 8);
				}
			}
			if (grammar_state == 0) {
				if ((int) strlen(p) + i > 0x17cb) {
					return;
				}
				e = i - k;
				fcn_0064d740(text.buf + e + strlen(p), text.buf + i,
					(int) strlen(text.buf) + 2 - i);
				strcpy(text.buf + e, p);
				break;
			}
			e = i - k - 1;
			while (e >= 0) {
				if (g_6b25b0 > 1) {
					res = __isctype(text.buf[e], 4);
				} else {
					res = ((unsigned char*) g_6b23a4)[text.buf[e] * 2] & 4;
				}
				if (res != 0) {
					break;
				}
				if (text.buf[e] != 0x20) {
					e = -1;
					break;
				}
				e--;
			}
			if (grammar_state == 1 || grammar_state == 2) {
				if (text.buf[i - 1] == 's' && flag == 0) {
					res = fcn_0042b2f0(g_14a540c[kind], r, 4);
				} else {
					res = fcn_0042b2f0(g_14a540c[kind], r, 8);
				}
				if (e > -1) {
					k = fcn_00517b90(text.buf, e, slot258);
					sprintf(text.tmp, g_6a22d8, res, slot258, p);
				} else {
					sprintf(text.tmp, g_68b3f8, res, p);
				}
				if (fcn_0051e070() == 0 && grammar_state == 2) {
					text.tmp[0] = (char) toupper((unsigned char) text.tmp[0]);
				}
			} else if (grammar_state == 3 || grammar_state == 4) {
				if (text.buf[i - 1] == 's' && flag == 0) {
					res = fcn_0042b2f0(g_14a5400[kind], r, 4);
				} else {
					res = fcn_0042b2f0(g_14a5400[kind], r, 8);
				}
				if (e > -1) {
					k = fcn_00517b90(text.buf, e, slot198);
					sprintf(text.tmp, g_6a22d8, res, slot198, p);
				} else {
					sprintf(text.tmp, g_68b3f8, res, p);
				}
				if (fcn_0051e070() == 0 && grammar_state == 4) {
					text.tmp[0] = (char) toupper((unsigned char) text.tmp[0]);
				}
			} else if (grammar_state == 5 || grammar_state == 6) {
				if (text.buf[i - 1] == 's' && flag == 0) {
					res = fcn_0042b2f0(g_14a5418[kind], r, 4);
				} else {
					res = fcn_0042b2f0(g_14a5418[kind], r, 8);
				}
				if (e > -1) {
					k = fcn_00517b90(text.buf, e, slot218);
					sprintf(text.tmp, g_6a22d8, res, slot218, p);
				} else {
					sprintf(text.tmp, g_68b3f8, res, p);
				}
				if (fcn_0051e070() == 0 && grammar_state == 6) {
					text.tmp[0] = (char) toupper((unsigned char) text.tmp[0]);
				}
			}
			if ((int) strlen(text.tmp) + i > 0x17cb) {
				return;
			}
			e = i - k;
			fcn_0064d740(text.buf + e + strlen(text.tmp), text.buf + i,
				(int) strlen(text.buf) + 2 - i);
			strcpy(text.buf + e, text.tmp);
			grammar_state = 0;
			flag = 0;
			break;
		case 'i':
			c = text.buf[i + 1];
			if (c == 'i' || c == 'c' || c == 'b' || c == 'a' || c == 'n') {
				i += 2;
				break;
			}
			cursor += 4;
			j = *(int*) (cursor - 4);
			if (j > 1 || j == 0) {
				flag = 1;
			}
			if (r != -1) {
				sprintf(num, g_6a2354, r);
				sprintf(text.tmp, num, j);
			} else {
				sprintf(text.tmp, g_67d444, j);
			}
			fcn_0064d740(text.buf + i - 3 + strlen(text.tmp), text.buf + i,
				(int) strlen(text.buf) - i + 1);
			strcpy(text.buf + i - 2, text.tmp);
			break;
		case 'I':
			if (r != -1) {
				sprintf(num, g_6a2354, r);
				strcpy(fmt_scratch, num);
			} else {
				strcpy(fmt_scratch, g_6a234c);
			}
			strcat(fmt_scratch, g_6a2350);
			cursor += 4;
			j = *(int*) (cursor - 4);
			if (j > 1 || j == 0) {
				flag = 1;
			}
			sprintf(text.tmp, fmt_scratch, j);
			e = (int) strlen(text.tmp);
			k = e + e / 3;
			text.tmp[k] = 0;
			res = 0;
			for (e = e - 1; e >= 0; e--) {
				text.tmp[k] = text.tmp[e];
				k--;
				if (e != 0 && j >= 0 && (res + 1) % 3 == 0) {
					text.tmp[k] = '.';
					k--;
				}
				res++;
			}
			if (j >= 0) {
				strcpy(slot298, text.tmp);
			} else {
				slot298[0] = '-';
				strcpy(slot298 + 1, text.tmp);
			}
			fcn_0064d740(text.buf + i - 1 + strlen(slot298), text.buf + i,
				(int) strlen(text.buf) - i + 1);
			strcpy(text.buf + i - 1, slot298);
			break;
		case 'T':
			if (text.buf[i - 1] != '%') {
				break;
			}
			cursor += 4;
			res = *(int*) (cursor - 4);
			fcn_0050bc10(res, g_773d75[0], text.tmp);
			fcn_0064d740(text.buf + i - 1 + strlen(text.tmp), text.buf + i + 1,
				(int) strlen(text.buf) - i + 1);
			strcpy(text.buf + i - 1, text.tmp);
			break;
		case 'w':
			cursor += 4;
			res = *(int*) (cursor - 4);
			res = (int) fcn_0042b2f0(
				g_14a79c0[*(unsigned short*) (0x8680b4 + res * 0x2f4)], 1, 8);
			strcpy(text.tmp, (char*) res);
			fcn_0064d740(text.buf + i - 1 + strlen(text.tmp), text.buf + i + 1,
				(int) strlen(text.buf) - i + 1);
			strcpy(text.buf + i - 1, text.tmp);
			break;
		case 'f':
			j = text.buf[i + 1] - '0';
			if (j > 0 && j < 9) {
				i++;
			}
			if (r != -1) {
				sprintf(num, g_6a2354, r);
			}
			strcpy(fmt_scratch, g_6a234c);
			if (r != -1) {
				strcat(fmt_scratch, num);
			}
			strcat(fmt_scratch, g_6a2350);
			cursor += 8;
			{
				double d = *(double*) (cursor - 8);
				sprintf(text.tmp, fmt_scratch, d);
			}
			if ((int) strlen(text.tmp) + i > 0x17cb) {
				return;
			}
			i++;
			fcn_0064d740(text.buf + i - 1 + strlen(text.tmp), text.buf + i,
				(int) strlen(text.buf) - i + 1);
			strcpy(text.buf + i - 1, text.tmp);
			break;
		case 'v':
			c = text.buf[i + 1];
			i++;
			if (c != 'v') {
				break;
			}
			cursor += 4;
			break;
		case 'F':
			i++;
			break;
		case 'u':
			e = i - ((r != -1) ? 3 : 2);
			k = e;
			grammar_state = 1;
			fcn_0064d740(text.buf + k, text.buf + i + 1,
				(int) strlen(text.buf) - i);
			i = k - 1;
			break;
		case 'U':
			e = i - ((r != -1) ? 3 : 2);
			k = e;
			grammar_state = 2;
			fcn_0064d740(text.buf + k, text.buf + i + 1,
				(int) strlen(text.buf) - i);
			i = k - 1;
			break;
		case 'b':
			e = i - ((r != -1) ? 3 : 2);
			k = e;
			grammar_state = 3;
			fcn_0064d740(text.buf + k, text.buf + i + 1,
				(int) strlen(text.buf) - i);
			i = k - 1;
			break;
		case 'B':
			e = i - ((r != -1) ? 3 : 2);
			k = e;
			if (text.buf[k] != '%') {
				break;
			}
			grammar_state = 4;
			fcn_0064d740(text.buf + k, text.buf + i + 1,
				(int) strlen(text.buf) - i);
			i = k - 1;
			break;
		case 'e':
			e = i - ((r != -1) ? 3 : 2);
			k = e;
			grammar_state = 5;
			fcn_0064d740(text.buf + k, text.buf + i + 1,
				(int) strlen(text.buf) - i);
			i = k - 1;
			break;
		case 'E':
			e = i - ((r != -1) ? 3 : 2);
			k = e;
			grammar_state = 6;
			fcn_0064d740(text.buf + k, text.buf + i + 1,
				(int) strlen(text.buf) - i);
			i = k - 1;
			break;
		case 'N':
			i++;
			if (r == -1) {
				break;
			}
			if (text.buf[i - 3] != '%' || text.buf[i - 2] == '$') {
				break;
			}
			cursor += 4;
			kind = *(int*) (cursor - 4);
			fcn_00517c00(kind, (char*) (text.buf[i] - '0'), i, text.tmp);
			fcn_0064d740(text.buf + i + strlen(text.tmp) - 4, text.buf + i,
				(int) strlen(text.buf) + 2 - i);
			strcpy(text.buf + i - 3, text.tmp);
			break;
		case 'a':
			if (text.buf[i - 1] != '%') {
				sprintf(text.tmp, g_6a2348, 0x14);
				fcn_0064d740(text.buf + i - 1 + strlen(text.tmp), text.buf + i + 1,
					(int) strlen(text.buf) - i + 1);
				strcpy(text.buf + i - 1, text.tmp);
				break;
			}
			cursor += 4;
			res = *(int*) (cursor - 4);
			sprintf(text.tmp, g_699a68, res, 0x14);
			fcn_0064d740(text.buf + i - 1 + strlen(text.tmp), text.buf + i + 1,
				(int) strlen(text.buf) - i + 1);
			strcpy(text.buf + i - 1, text.tmp);
			break;
		case 'D':
			cursor += 4;
			res = *(int*) (cursor - 4);
			fcn_00500d60(fmt_scratch + 0xc, (void*) res);
			res = fcn_004fe330(fmt_scratch + 0xc, *(short*) (fmt_scratch + 0x16));
			sprintf(text.tmp, g_6a2310, g_14a5450[res]);
			fcn_0064d740(text.buf + i - 2 + strlen(text.tmp), text.buf + i,
				(int) strlen(text.buf) + 2 - i);
			strcpy(text.buf + i - 1, text.tmp);
			break;
		case 'G':
			cursor += 4;
			p = *(char**) (cursor - 4);
			i++;
			kind = 0;
			j = *(unsigned char*) p;
			j = j * 7 + 0x48e;
			if (j <= 0x4800) {
				kind = g_11bb000[j];
				p = g_14a5320[j];
			} else {
				p = (char*) j;
			}
			if (r == -1) {
				k = 2;
				r = 1;
			} else {
				k = 3;
			}
			p = (char*) fcn_0042b2f0(p, r, 4);
			if (p == 0) {
				p = g_14a5320[j];
			}
			if (p[5] != 0) {
				sprintf(slot98, g_6a2308, p, p + 5);
			} else {
				strcpy(slot98, p);
			}
			if (grammar_state == 0) {
				if ((int) strlen(slot98) + i > 0x17cb) {
					return;
				}
				e = i - k;
				fcn_0064d740(text.buf + e + strlen(slot98), text.buf + i,
					(int) strlen(text.buf) + 2 - i);
				strcpy(text.buf + e, slot98);
				grammar_state = 0;
				flag = 0;
				break;
			}
			e = i - k - 1;
			while (e >= 0) {
				if (g_6b25b0 > 1) {
					res = __isctype(text.buf[e], 4);
				} else {
					res = ((unsigned char*) g_6b23a4)[text.buf[e] * 2] & 4;
				}
				if (res != 0) {
					break;
				}
				if (text.buf[e] != 0x20) {
					e = -1;
					break;
				}
				e--;
			}
			if (grammar_state == 1 || grammar_state == 2) {
				res = fcn_0042b2f0(g_14a540c[kind], r, 4);
				if (e > -1) {
					k = fcn_00517b90(text.buf, e, slot1d8);
					sprintf(text.tmp, g_6a22d8, res, slot1d8, slot98);
				} else {
					sprintf(text.tmp, g_68b3f8, res, slot98);
				}
				if (fcn_0051e070() == 0 && grammar_state == 2) {
					text.tmp[0] = (char) toupper((unsigned char) text.tmp[0]);
				}
			} else if (grammar_state == 3 || grammar_state == 4) {
				res = fcn_0042b2f0(g_14a5400[kind], r, 4);
				if (e > -1) {
					k = fcn_00517b90(text.buf, e, slot118);
					sprintf(text.tmp, g_6a22d8, res, slot118, slot98);
				} else {
					sprintf(text.tmp, g_68b3f8, res, slot98);
				}
				if (fcn_0051e070() == 0 && grammar_state == 4) {
					text.tmp[0] = (char) toupper((unsigned char) text.tmp[0]);
				}
			} else if (grammar_state == 5 || grammar_state == 6) {
				res = fcn_0042b2f0(g_14a5418[kind], r, 4);
				if (e > -1) {
					k = fcn_00517b90(text.buf, e, slot158);
					sprintf(text.tmp, g_6a22d8, res, slot158, slot98);
				} else {
					sprintf(text.tmp, g_68b3f8, res, slot98);
				}
				if (fcn_0051e070() == 0 && grammar_state == 6) {
					text.tmp[0] = (char) toupper((unsigned char) text.tmp[0]);
				}
			}
			if ((int) strlen(text.tmp) + i > 0x17cb) {
				return;
			}
			e = i - k;
			fcn_0064d740(text.buf + e + strlen(text.tmp), text.buf + i,
				(int) strlen(text.buf) + 2 - i);
			strcpy(text.buf + e, text.tmp);
			grammar_state = 0;
			break;
		case 'r':
			memset(tab78, 0, 0x20);
			res = 0;
			j = text.buf[i + 1] - '1';
			if (j >= 0 && j <= 9) {
				res = j + 9;
			}
			e = i + 3;
			do {
				if (g_6b25b0 > 1) {
					j = __isctype(text.buf[e], 4);
				} else {
					j = ((unsigned char*) g_6b23a4)[text.buf[e] * 2] & 4;
				}
				e++;
			} while (j != 0);
			fcn_0064d530((char*) tab78, text.buf + i + 3, e - i - 4);
			j = fcn_0064eeec((char*) tab78);
			r = format_selector;
			while (r < g_6b7f98) {
				if (g_11bb000[r] == res) {
					break;
				}
				r++;
			}
			if (r >= g_6b7f98) {
				ReportClientMessage(g_6a2318);
				break;
			}
			j = gm_RandomMod(j) & 0xffff;
			if (g_14a5320[j + r] == 0) {
				break;
			}
			p = g_14a5320[j + r];
			fcn_0064d740(text.buf + strlen(p) + (i - e) - 5, text.buf + i,
				(int) strlen(text.buf) - (i - e) + 5);
			strcpy(text.buf + i - 1, p);
			break;
		case '%':
			text.buf[i - 1] = 0x16;
			fcn_0064d740(text.buf + i + 1, text.buf + i + 2,
				(int) strlen(text.buf) - i + 1);
			break;
		default:
			break;
		}
	}
done:
	strcpy(output, text.buf);
}
