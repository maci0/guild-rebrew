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
 * 0x17d0).  With text.unrecovered at 0xfc this TU now emits the native
 * prologue: push ebx/esi/edi, immediate 0x332c, loop index in ebx and the
 * directive digit in esi.  The 0xf8 size kept buf at the native 0x398 but
 * collapsed to two pushes and carried an extra spill slot for the index.
 * The 0xfc size adds 4 bytes of aggregate tail padding and leaves buf/tmp at
 * 0x394/0x1b64, four below native.  The small locals occupy 0x10..0x28; the
 * kind slot is 0x20 here where the native one is 0x24.
 *
 * Native locals, offsets from the post-push esp:
 *   0x10 res, 0x14 k, 0x18 vararg walker, 0x1c grammar_state,
 *   0x20 p, 0x24 kind, 0x28 flag, 0x2c num[0x14], 0x40 format scratch,
 *   0x78 tab78[8], 0x98/0x118/0x158/0x198/0x1d8/0x218/0x258/0x298
 *   per-branch scratch, 0x398 buf[0x17d0], 0x1b68 tmp[0x17d0].
 *   The smaller scratch arrays move when the spill set changes (this build:
 *   format scratch 0x48, tab78 0xc0, per-branch bases from 0x40), so their
 *   displacements are not held yet.  text.unrecovered stands in for the
 *   native scratch at 0x2a8..0x397, whose users are not yet identified; it
 *   carries no source semantics.
 *
 * arg1 out buffer, arg2 text id (<0x4800 indexes g_14a5320) or a direct
 * char* template, then printf-style varargs read through one walking
 * pointer.  The 22-case dispatch (selector table 0x51c7e4, jump table
 * 0x51c78c) covers % B C D E F G I N S T U a b e f i r u v w; the case
 * bodies are laid out in native order.
 *
 * Remaining gaps: the object body is 6383 bytes against the native 6455, so
 * 72 bytes of native code are still unrecovered; the earlier 0xf8 build only
 * reached 6455 by spilling the loop index.  Gap trace shows the object
 * running 180 bytes ahead by native offset 819 (extra spill traffic in the
 * S/s grammar_state 1..4 blocks) and short by a few hundred bytes from
 * native 1021 onward.  The copy bursts after each memmove use
 * memcpy(dst, src, strlen(src)), which folds into the reference's shared
 * strlen+rep-movs tails.  The 'I' and 'f' itoa paths, the 'G' index (*14) and
 * the u/U/b/B/e/E directive length (2/1) are transcribed from the native
 * listing.  The kind==0xff reload indexes g_14a5320 with the raw vararg
 * selector, as native reloads it from eax at 0x51b0be; keeping that value in
 * `j` also moved the reference's own S/s setup shape into place.  First
 * remaining divergence is native 227 (inc ebx) against object 230.
 * text.unrecovered has no user yet.
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
extern char g_6a2354[];
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
int __cdecl fcn_00517c00(int, int, int, char*);
int __cdecl fcn_00657a73(int, char*, int);
int __cdecl ReportClientMessage(char*);
int __cdecl gm_RandomMod(int);
int __cdecl __isctype(int, int);
int sprintf(char*, const char*, ...);

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
		/* native scratch 0x2a0..0x397; its users are not yet identified.
		 * 0xfc makes the allocator save ebx/esi/edi and emit the native
		 * 0x332c chkstk immediate; it puts buf/tmp at 0x394/0x1b64. */
		char unrecovered[0xfc];
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
	char* cp_src;
	char* cp_dst;
	int cp_n;

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
		for (;;) {
			c = text.buf[i];
			if (c != '%' && c != '$' && c != '{') {
				break;
			}
		c = text.buf[i + 1];
		i++;
		r = c - '0';
		if (r >= 0 && r <= 9) {
			i++;
		} else {
			r = -1;
		}
		c = text.buf[i];
		switch ((unsigned char) c) {
		case 'C':
			i++;
			memset(output, 0, 0x80);
			break;
		case 'S':
		case 's':
			cursor += 4;
			p = *(char**) (cursor - 4);
			j = (int) p;
			if (j < 0x4800) {
				kind = g_11bb000[j];
				p = g_14a5320[j];
			}
			k = (r != -1) ? 3 : 2;
			if (kind == 0xff) {
				if (p == 0) {
					p = g_14a5320[j];
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
				cp_src = p;
				cp_n = (int) strlen(cp_src);
				cp_dst = text.buf + e;
				fcn_0064d740(cp_dst + cp_n, text.buf + i, (int) strlen(text.buf) + 2 - i);
				memcpy(cp_dst, cp_src, (int) strlen(cp_src));
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
			cp_src = text.tmp;
			cp_n = (int) strlen(cp_src);
			cp_dst = text.buf + e;
			fcn_0064d740(cp_dst + cp_n, text.buf + i, (int) strlen(text.buf) + 2 - i);
			memcpy(cp_dst, cp_src, (int) strlen(cp_src));
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
			if (r != -1) {
				j = *(int*) (cursor - 4);
				if (j > 1 || j == 0) {
					flag = 1;
				}
				sprintf(num, g_6a2354, r);
				sprintf(text.tmp, num, j);
				cp_src = text.tmp;
				cp_n = (int) strlen(cp_src);
				cp_dst = text.buf + i - 2;
				fcn_0064d740(cp_dst + cp_n, text.buf + i, (int) strlen(text.buf) + 1 - i);
				memcpy(cp_dst, cp_src, cp_n);
			} else {
				j = *(int*) (cursor - 4);
				if (j > 1 || j == 0) {
					flag = 1;
				}
				sprintf(text.tmp, g_67d444, j);
				cp_src = text.tmp;
				cp_n = (int) strlen(cp_src);
				cp_dst = text.buf + i - 1;
				fcn_0064d740(cp_dst + cp_n, text.buf + i + 1, (int) strlen(text.buf) + 1 - i);
				memcpy(cp_dst, cp_src, cp_n);
			}
			break;
		case 'I':
			if (r != -1) {
				fcn_00657a73(r, fmt_scratch + 0x18, 10);
				strcpy(num, "%0");
				strcat(num, fmt_scratch + 0x18);
				strcat(num, "i");
				cursor += 4;
				j = *(int*) (cursor - 4);
				if (j > 1 || j == 0) {
					flag = 1;
				}
				sprintf(text.tmp, num, j);
				e = (int) strlen(text.tmp) + (int) strlen(text.tmp) / 3;
				k = (int) strlen(text.tmp);
				res = -1;
				p = num + e;
				while (k >= 0) {
					*p = text.tmp[k];
					p--;
					if (k != 0 && res > 0 && (res + 1) % 3 == 0) {
						*p = '.';
						p--;
					}
					res++;
					k--;
				}
				num[e] = 0;
				cp_src = num;
				cp_n = (int) strlen(cp_src);
				cp_dst = text.buf + i - 2;
				fcn_0064d740(cp_dst + cp_n, text.buf + i, (int) strlen(text.buf) + 1 - i);
				memcpy(cp_dst, cp_src, (int) strlen(cp_src));
			} else {
				cursor += 4;
				j = *(int*) (cursor - 4);
				if (j > 1 || j == 0) {
					flag = 1;
				}
				if (j < 0) {
					sprintf(num, g_67d444, -j);
				} else {
					sprintf(num, g_67d444, j);
				}
				e = (int) strlen(num) + ((int) strlen(num) - 1) / 3;
				k = (int) strlen(num);
				res = -1;
				p = text.tmp + e;
				while (k >= 0) {
					*p = num[k];
					p--;
					if (k != 0 && res > 0 && (res + 1) % 3 == 0) {
						*p = '.';
						p--;
					}
					res++;
					k--;
				}
				text.tmp[e] = 0;
				if (j >= 0) {
					strcpy(slot298, text.tmp);
				} else {
					slot298[0] = '-';
					strcpy(slot298 + 1, text.tmp);
				}
				cp_src = slot298;
				cp_n = (int) strlen(cp_src);
				cp_dst = text.buf + i - 1;
				fcn_0064d740(cp_dst + cp_n, text.buf + i + 1, (int) strlen(text.buf) + 1 - i);
				memcpy(cp_dst, cp_src, cp_n);
			}
			break;
		case 'T':
			if (text.buf[i - 1] != '%') {
				break;
			}
			cursor += 4;
			res = *(int*) (cursor - 4);
			fcn_0050bc10(res, g_773d75[0], text.tmp);
			cp_src = text.tmp;
			cp_n = (int) strlen(cp_src);
			cp_dst = text.buf + i - 1;
			fcn_0064d740(cp_dst + cp_n, text.buf + i + 1, (int) strlen(text.buf) - i + 1);
			memcpy(cp_dst, cp_src, cp_n);
			break;
		case 'w':
			cursor += 4;
			res = *(int*) (cursor - 4);
			res = (int) fcn_0042b2f0(
				g_14a79c0[*(unsigned short*) (0x8680b4 + res * 189 * 4) * 2],
				1, 8);
			strcpy(text.tmp, (char*) res);
			cp_src = text.tmp;
			cp_n = (int) strlen(cp_src);
			cp_dst = text.buf + i - 1;
			fcn_0064d740(cp_dst + cp_n, text.buf + i + 1, (int) strlen(text.buf) - i + 1);
			memcpy(cp_dst, cp_src, (int) strlen(cp_src));
			break;
		case 'f':
			j = text.buf[i + 1] - '0';
			if (j > 0 && j < 9) {
				i++;
			} else {
				j = 0;
			}
			if (r != -1) {
				fcn_00657a73(r, fmt_scratch + 0x18, 10);
				strcpy(num, "%0");
				strcat(num, fmt_scratch + 0x18);
				fcn_00657a73(j, fmt_scratch + 0x18, 10);
				strcat(num, ".");
				strcat(num, fmt_scratch + 0x18);
				strcat(num, "f");
				cursor += 8;
				{
					double d = *(double*) (cursor - 8);
					sprintf(text.tmp, num, d);
				}
				if ((int) strlen(text.tmp) + i > 0x17cb) {
					return;
				}
				i++;
				cp_src = text.tmp;
				cp_n = (int) strlen(cp_src);
				cp_dst = text.buf + i - 4;
				fcn_0064d740(cp_dst + cp_n, text.buf + i, (int) strlen(text.buf) + 1 - i);
				memcpy(cp_dst, cp_src, (int) strlen(cp_src));
			} else {
				fcn_00657a73(j, fmt_scratch + 0x18, 10);
				strcpy(num, "%.");
				strcat(num, fmt_scratch + 0x18);
				strcat(num, "f");
				cursor += 8;
				{
					double d = *(double*) (cursor - 8);
					sprintf(text.tmp, num, d);
				}
				if ((int) strlen(text.tmp) + i > 0x17cb) {
					return;
				}
				i++;
				cp_src = text.tmp;
				cp_n = (int) strlen(cp_src);
				cp_dst = text.buf + i - 3;
				fcn_0064d740(cp_dst + cp_n, text.buf + i, (int) strlen(text.buf) + 1 - i);
				memcpy(cp_dst, cp_src, cp_n);
			}
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
			k = i - ((r != -1) ? 2 : 1);
			grammar_state = 1;
			fcn_0064d740(text.buf + k, text.buf + i + 1,
				(int) strlen(text.buf) - i);
			i = k - 1;
			break;
		case 'U':
			k = i - ((r != -1) ? 2 : 1);
			grammar_state = 2;
			fcn_0064d740(text.buf + k, text.buf + i + 1,
				(int) strlen(text.buf) - i);
			i = k - 1;
			break;
		case 'b':
			k = i - ((r != -1) ? 2 : 1);
			grammar_state = 3;
			fcn_0064d740(text.buf + k, text.buf + i + 1,
				(int) strlen(text.buf) - i);
			i = k - 1;
			break;
		case 'B':
			k = i - ((r != -1) ? 2 : 1);
			if (text.buf[k] == '%') {
				grammar_state = 4;
				fcn_0064d740(text.buf + k, text.buf + i + 1,
					(int) strlen(text.buf) - i);
				i = k - 1;
				break;
			}
			i++;
			break;
		case 'e':
			k = i - ((r != -1) ? 2 : 1);
			grammar_state = 5;
			fcn_0064d740(text.buf + k, text.buf + i + 1,
				(int) strlen(text.buf) - i);
			i = k - 1;
			break;
		case 'E':
			k = i - ((r != -1) ? 2 : 1);
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
			fcn_00517c00(*(int*) (cursor - 4), r,
				(text.buf[i] - '0'), text.tmp);
			cp_src = text.tmp;
			cp_n = (int) strlen(cp_src);
			cp_dst = text.buf + i - 3;
			fcn_0064d740(cp_dst + cp_n, text.buf + i, (int) strlen(text.buf) + 2 - i);
			memcpy(cp_dst, cp_src, cp_n);
			break;
		case 'a':
			if (text.buf[i - 1] == '%') {
				cursor += 4;
				res = *(int*) (cursor - 4);
				sprintf(text.tmp, g_699a68, res, 0x14);
				cp_src = text.tmp;
				cp_n = (int) strlen(cp_src);
				cp_dst = text.buf + i - 1;
				fcn_0064d740(cp_dst + cp_n, text.buf + i + 1, (int) strlen(text.buf) - i + 1);
				memcpy(cp_dst, cp_src, cp_n);
				break;
			}
			sprintf(text.tmp, g_6a2348, 0x14);
			cp_src = text.tmp;
			cp_n = (int) strlen(cp_src);
			cp_dst = text.buf + i - 1;
			fcn_0064d740(cp_dst + cp_n, text.buf + i + 1, (int) strlen(text.buf) - i + 1);
			memcpy(cp_dst, cp_src, cp_n);
			break;
		case 'D':
			cursor += 4;
			res = *(int*) (cursor - 4);
			fcn_00500d60(fmt_scratch + 0xc, (void*) res);
			res = fcn_004fe330(fmt_scratch + 0xc, *(short*) (fmt_scratch + 0xe));
			sprintf(text.tmp, g_6a2310, g_14a5450[res]);
			cp_src = text.tmp;
			cp_n = (int) strlen(cp_src);
			cp_dst = text.buf + i - 1;
			fcn_0064d740(cp_dst + cp_n, text.buf + i, (int) strlen(text.buf) + 2 - i);
			memcpy(cp_dst, cp_src, (int) strlen(cp_src));
			break;
		case 'G':
			cursor += 4;
			p = *(char**) (cursor - 4);
			i++;
			kind = 0;
			j = *(unsigned char*) p;
			j = j * 14 + 0x48e;
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
				cp_src = slot98;
				cp_n = (int) strlen(cp_src);
				cp_dst = text.buf + e;
				fcn_0064d740(cp_dst + cp_n, text.buf + i, (int) strlen(text.buf) + 2 - i);
				memcpy(cp_dst, cp_src, (int) strlen(cp_src));
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
					text.tmp[0] = (char) toupper(text.tmp[0]);
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
					text.tmp[0] = (char) toupper(text.tmp[0]);
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
					text.tmp[0] = (char) toupper(text.tmp[0]);
				}
			}
			if ((int) strlen(text.tmp) + i > 0x17cb) {
				return;
			}
			e = i - k;
			cp_src = text.tmp;
			cp_n = (int) strlen(cp_src);
			cp_dst = text.buf + e;
			fcn_0064d740(cp_dst + cp_n, text.buf + i, (int) strlen(text.buf) + 2 - i);
			memcpy(cp_dst, cp_src, (int) strlen(cp_src));
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
			cp_src = p;
			cp_n = (int) strlen(cp_src);
			cp_dst = text.buf + i - 1;
			fcn_0064d740(cp_dst + cp_n, text.buf + i, (int) strlen(text.buf) - (i - e) + 5);
			memcpy(cp_dst, cp_src, cp_n);
			break;
		case '%':
			text.buf[i - 1] = 0x16;
			fcn_0064d740(text.buf + i, text.buf + i + 1,
				(int) strlen(text.buf) - i + 1);
			break;
			default:
				break;
			}
		}
		i++;
		if (i < (int) strlen(text.buf)) {
			continue;
		}
		break;
	}
done:
	strcpy(output, text.buf);
}
