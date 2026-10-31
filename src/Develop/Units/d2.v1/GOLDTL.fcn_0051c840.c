#include <string.h>
#include <ctype.h>


/*
 * io_Text: localized markup formatter. Native frame 0x3294, locals
 * (esp-relative after the callee-saved pushes):
 *   0x10 base window scale, 0x14 state, 0x18 p (buf - 1, also loop index
 *   and write cursor), 0x1c call result, 0x20 flag, 0x24 num[0x14],
 *   0x38 tmpl[0xa], 0x42 z42[6], 0x48 date/time record (0x10),
 *   0x58 rec58[0xc], 0x64 numbuf[0xc], 0x70 s70[8], 0x78 tab78[8],
 *   0x98 lc (0x1ac: s98[0x100] then rec[0xac]), 0x244 b1[0x40],
 *   0x284 b2[0x40], 0x2c4 b3[0x40], 0x304 buf[0x17d0], 0x1ad4 tmp[0x17c0].
 * The 0x1ac byte span is one object: the allocator orders locals itself, and
 * two separate arrays always land rec first, never the native s98-first order.
 */
extern int g_1052de0;
extern char* g_14a5320[];
extern int g_11bb000[];
extern char* g_14a5400[];
extern char* g_14a540c[];
extern char* g_14a5418[];
extern char* g_14a5450[];
extern char* g_14a7bb0[];
extern int g_772514;
extern int g_6b25b0;
extern int g_6b23a4;
extern int g_6b7f98;
extern char g_6a239c[];
extern int g_6a2390;
extern int g_6a2394;
extern int g_6a2398;
extern char g_67d444[];
extern char g_6a2308[];
extern char g_6a2310[];
extern char g_6a2318[];
extern char g_6a2348[];
extern char g_6a2354[];
extern char g_6a235c[];
extern char g_68b3f8[];
extern char g_6a22d8[];
extern char g_699a68[];
extern char g_677c94[];
extern char g_6a2388[];
extern char g_6a238c[];
extern char g_6a238e[];

int sprintf(char*, const char*, ...);
int __cdecl fcn_0042b2f0(char*, int, int);
int __cdecl fcn_0064d530(char*, const char*, unsigned int);
int __cdecl fcn_0064eeec(char*);
int __cdecl fcn_00517b90(char*, int, char*);
int __cdecl fcn_0051e070(void);
int __cdecl fcn_0046f2c0(int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl ReportClientMessage(char*);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_00500d60(void*, void*);
int __cdecl fcn_004fe330(void*, int);
int __cdecl _ltoa(long, char*, int);
int __cdecl __isctype(int, int);

/* ADDRESS: GOLDTL 0x0051c840 */
int __cdecl fcn_0051c840(int id)
{
	int base;
	int state;
	char* p;
	int res;
	int flag;
	char num[0x14];
	struct {
		char tmpl[10];
		char z42[6];
		int dt[3];
		short w54;
	} st;
	char rec58[0xc];
	char numbuf[0x14];
	char s70[8];
	int tab78[8];
	struct { char s98[0x100]; char rec[0xac]; } lc;
	char b1[0x40];
	char b2[0x40];
	char b3[0x40];
	char buf[0x17d0];
	char tmp[0x17d0];
	int i;
	int k;
	int r;
	int e;
	char c;
	int j;

	st.w54 = 0;
	memset(st.dt, 0, 0xc);
	memcpy(st.tmpl, g_6a239c, 10);
	memset(st.z42, 0, 6);
	state = 0;
	flag = 0;
	*(int*) (num + 0xc) = 0;
	st.dt[0] = 4;
	memset(lc.rec, 0, 0xa9);
	lc.rec[0] = 0x0b;
	*(short*) (lc.rec + 0x27) = -1;
	if (g_1052de0 == 0) {
		return -1;
	}
	base = g_772514 * 0x3cc;
	if (*(int*) ((char*) base + 0x10161d0) == 0) {
		return -1;
	}
	memset(buf, 0, 0x17d0);
	if (id < 0x4800) {
		p = g_14a5320[id];
		if (p == 0) {
			return -1;
		}
		if (strlen(p) > 0x17c0) {
			return -1;
		}
		memcpy(buf, p, 0x17c0);
	} else {
		strcpy(buf, (char*) id);
	}
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
			memset(*(char**) ((char*) base + 0x1015f7c), 0, 0x80);
			*(int*) ((char*) base + 0x10162d4) = 0;
			memset((char*) base + 0x10161d4, 0, 0x100);
			fcn_0046f2c0(*(int*) ((char*) base + 0x1015f40), 0);
			break;
		case 'S':
		case 's':
			p = buf - 1;
			if (p[i] == '$') {
				memmove(buf + i + 9, buf + i + 1, strlen(buf) - i);
				memset(buf + i - 1, 0x20, 10);
				break;
			}
			*(int*) (num + 0xc) = -1;
			if (p[i] == '{') {
				i++;
				break;
			}
			i++;
			k = (r != -1) ? 3 : 2;
			if (state == 0) {
				if (strlen(st.tmpl) + i > 0x17cb) {
					return -1;
				}
				e = i - k;
				memmove(buf + e + strlen(st.tmpl), buf + i,
					strlen(buf) - i + 2);
				flag = 0;
				strcpy(buf + e, st.tmpl);
				break;
			}
			e = i - k - 1;
			while (e >= 0) {
				if (g_6b25b0 > 1) {
					res = __isctype(buf[e], 4);
				} else {
					res = ((unsigned char*)
					       g_6b23a4)[buf[e] * 2] & 4;
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
				if (p[i] == 's' && flag == 0) {
					res = fcn_0042b2f0(g_14a540c[0], r, 4);
				} else {
					res = fcn_0042b2f0(g_14a540c[0], r, 8);
				}
				if (e > -1) {
					k = i - fcn_00517b90(buf, e, b3);
					sprintf(tmp, g_6a22d8, res, b3, st.tmpl);
				} else {
					sprintf(tmp, g_68b3f8, res, st.tmpl);
				}
				if (fcn_0051e070() == 0 && state == 2) {
					tmp[0] = (char) toupper(tmp[0]);
				}
			}
			if (state == 3 || state == 4) {
				if (p[i] == 's' && flag == 0) {
					res = fcn_0042b2f0(g_14a5400[0], r, 4);
				} else {
					res = fcn_0042b2f0(g_14a5400[0], r, 8);
				}
				if (e > -1) {
					k = i - fcn_00517b90(buf, e, b1);
					sprintf(tmp, g_6a22d8, res, b1, st.tmpl);
				} else {
					sprintf(tmp, g_68b3f8, res, st.tmpl);
				}
				if (fcn_0051e070() == 0 && state == 4) {
					tmp[0] = (char) toupper(tmp[0]);
				}
			}
			if (state == 5 || state == 6) {
				if (p[i] == 's' && flag == 0) {
					res = fcn_0042b2f0(g_14a5418[0], r, 4);
				} else {
					res = fcn_0042b2f0(g_14a5418[0], r, 8);
				}
				if (e > -1) {
					k = i - fcn_00517b90(buf, e, b2);
					sprintf(tmp, g_6a22d8, res, b2, st.tmpl);
				} else {
					sprintf(tmp, g_68b3f8, res, st.tmpl);
				}
				if (fcn_0051e070() == 0 && state == 6) {
					tmp[0] = (char) toupper(tmp[0]);
				}
			}
			if (strlen(tmp) + i > 0x17cb) {
				return -1;
			}
			memmove(buf + (i - k) + strlen(tmp), buf + i,
				strlen(buf) - (i - k));
			strcpy(buf + (i - k), tmp);
			state = 0;
			flag = 0;
			break;
		case 'F':
			i++;
			break;
		case 't':
			*(int*) ((char*) base + 0x10161d4 +
				 *(int*) ((char*) base + 0x10162d4) * 4) = 0x1c70;
			*(int*) ((char*) base + 0x10162d4) += 1;
			i++;
			break;
		case 'l':
			*(int*) ((char*) base + 0x10161d4 +
				 *(int*) ((char*) base + 0x10162d4) * 4) = 0x1c70;
			*(int*) ((char*) base + 0x10162d4) += 1;
			i++;
			break;
		case 'T':
			if (buf[i - 1] == '%') {
				sprintf(tmp, g_699a68, 0x3e8, 0x11);
				memmove(buf + i - 1 + strlen(tmp), buf + i + 1,
					strlen(buf) - i + 1);
				strcpy(buf + i - 1, tmp);
			}
			i++;
			break;
		case 'w':
			res = fcn_0042b2f0(g_14a7bb0[0], 1, 8);
			strcpy(tmp, (char*) res);
			memmove(buf + i - 1 + strlen(tmp), buf + i + 1,
				strlen(buf) - i + 1);
			strcpy(buf + i - 1, tmp);
			break;
		case 'i':
			if (buf[i + 1] == 'i' || buf[i + 1] == 'c' ||
			    buf[i + 1] == 'b' || buf[i + 1] == 'a' ||
			    buf[i + 1] == 'n' || buf[i + 1] == 't') {
				if (*(int*) ((char*) base + 0x10162d4) > 0x40) {
					ReportClientMessage(g_6a235c);
					i += 2;
					break;
				}
				*(int*) ((char*) base + 0x10161d4 +
					 *(int*) ((char*) base + 0x10162d4) * 4) = -1;
				if (buf[i + 1] == 'a' || buf[i + 1] == 'n') {
					if (*(int*) ((char*) base + 0x10161cc) == 0x53 ||
					    *(int*) ((char*) base + 0x10161cc) == 0x55) {
						*(int*) ((char*) base + 0x10161d4 +
							 *(int*) ((char*) base + 0x10162d4) * 4) = -1;
					}
				} else if (buf[i + 1] == 't') {
					if (*(int*) ((char*) base + 0x10161cc) == 0x53 ||
					    *(int*) ((char*) base + 0x10161cc) == 0x55) {
						*(int*) ((char*) base + 0x10161d4 +
							 *(int*) ((char*) base + 0x10162d4) * 4) = 2;
					} else {
						*(int*) ((char*) base + 0x10161d4 +
							 *(int*) ((char*) base + 0x10162d4) * 4) = 5;
					}
				} else {
					*(int*) ((char*) base + 0x10161d4 +
						 *(int*) ((char*) base + 0x10162d4) * 4) = 2;
				}
				*(int*) ((char*) base + 0x10162d4) += 1;
				i += 2;
				break;
			}
			if (r != -1) {
				_ltoa((long) r, numbuf, 10);
				strcpy(num, "%0");
				strcat(num, numbuf);
				strcat(num, "i");
				flag = 2;
				sprintf(tmp, num, 0x3e7);
				k = strlen(tmp) / 3 + strlen(tmp);
				e = strlen(tmp) - 1;
				p = num + k;
				k = -1;
				while (e >= 0) {
					*p = tmp[e];
					p--;
					if (e != 0 && k > 0 && (k + 1) % 3 == 0) {
						*p = '.';
						p--;
					}
					k++;
					e--;
				}
				memmove(buf + i - 3 + strlen(num), buf + i,
					strlen(buf) - i + 1);
				strcpy(buf + i - 2, num);
			} else {
				sprintf(num, g_67d444, 0x3e7);
				flag = 2;
				k = strlen(num);
				p = tmp + (k - 1) / 3 + k;
				k = -1;
				e = strlen(num);
				while (e >= 0) {
					*p = num[e];
					p--;
					if (e != 0 && k > 0 && (k + 1) % 3 == 0) {
						*p = '.';
						p--;
					}
					k++;
					e--;
				}
				memmove(buf + i - 1 + strlen(tmp), buf + i + 1,
					strlen(buf) - i + 1);
				strcpy(buf + i - 1, tmp);
			}
			break;
		case 'I':
			if (r != -1) {
				sprintf(num, g_6a2354, r);
				sprintf(tmp, num, 0x270f);
				memmove(buf + i - 3 + strlen(tmp), buf + i,
					strlen(buf) - i + 1);
				strcpy(buf + i - 2, tmp);
			} else {
				sprintf(tmp, g_67d444, 0x270f);
				memmove(buf + i - 1 + strlen(tmp), buf + i + 1,
					strlen(buf) - i + 1);
				strcpy(buf + i - 1, tmp);
			}
			break;
		case 'm':
			c = buf[i + 1];
			i++;
			if (c == 't') {
				*(int*) ((char*) base + 0x10161d4 +
					 *(int*) ((char*) base + 0x10162d4) * 4) = 0x1c70;
				*(int*) ((char*) base + 0x10162d4) += 1;
				*(int*) ((char*) base + 0x10161d4 +
					 *(int*) ((char*) base + 0x10162d4) * 4) = 0x1c70;
				*(int*) ((char*) base + 0x10162d4) += 1;
				i++;
			} else if (c == 'b') {
				*(int*) ((char*) base + 0x10161d4 +
					 *(int*) ((char*) base + 0x10162d4) * 4) = -1;
				*(int*) ((char*) base + 0x10162d4) += 1;
				i++;
			} else {
				*(int*) ((char*) base + 0x10161d4 +
					 *(int*) ((char*) base + 0x10162d4) * 4) = -1;
				*(int*) ((char*) base + 0x10162d4) += 1;
			}
			break;
		case 'W':
			if (r == -1) {
				r = 0;
			}
			e = buf[i + 1] - 0x30;
			if (e <= 0 || e >= 9) {
				e = -1;
			}
			p = *(char**) ((char*) base + 0x1015f7c);
			if (strlen(p) + strlen(buf) < 0x17cf) {
				strncpy(p, buf, i);
				*(short*) (p + strlen(p)) =
					*(short*) g_677c94;
				*(int*) ((char*) base + 0x10161b8) = 2;
			}
			memmove(buf, buf + i + 2, strlen(buf) - i);
			buf[strlen(buf) - i] = 0;
			d2_SetForm(r, e);
			if (e != -1) {
				i += 2;
			} else {
				i++;
			}
			break;
		case 'u':
			k = (r != -1) ? 3 : 2;
			e = i - k;
			state = 1;
			memmove(buf + e, buf + i + 1, strlen(buf) - i);
			break;
		case 'U':
			k = (r != -1) ? 3 : 2;
			e = i - k;
			memmove(buf + e, buf + i + 1, strlen(buf) - i);
			state = 2;
			i = e - 1;
			break;
		case 'b':
			k = (r != -1) ? 3 : 2;
			e = i - k;
			if (buf[e] != '%') {
				break;
			}
			state = 3;
			memmove(buf + e, buf + i + 1, strlen(buf) - i);
			i = e - 1;
			break;
		case 'B':
			k = (r != -1) ? 3 : 2;
			e = i - k;
			if (buf[e] != '%') {
				break;
			}
			state = 4;
			memmove(buf + e, buf + i + 1, strlen(buf) - i);
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
				memmove(buf + e, buf + i + 1, strlen(buf) + 2 - i);
			} else {
				memmove(buf + e, buf + i + 2, strlen(buf) + 2 - i);
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
			*(int*) (tmp + 4) = g_6a2394;
			*(int*) (tmp + 8) = g_6a2398;
			*(int*) tmp = g_6a2390;
			memmove(buf + i + strlen(tmp) - 4, buf + i,
				strlen(buf) + 2 - i);
			strcpy(buf + i - 3, tmp);
			break;
		case 'a':
			if (p[i] == '%') {
				sprintf(tmp, g_699a68, 4, 0x14);
				memmove(buf + i - 1 + strlen(tmp), buf + i + 1,
					strlen(buf) - i + 1);
			} else {
				sprintf(tmp, g_6a2348, 0x14);
				memmove(buf + i - 1 + strlen(tmp), buf + i + 1,
					strlen(buf) - i + 1);
			}
			strcpy(buf + i - 1, tmp);
			break;
		case 'r':
			memset(tab78, 0, 0x20);
			e = 0;
			k = buf[i + 1] - '1';
			if (k >= 0 && k <= 9) {
				e = k + 9;
			}
			k = i + 3;
			while (1) {
				if (g_6b25b0 > 1) {
					res = __isctype(buf[k], 4);
				} else {
					res = ((unsigned char*)
					       g_6b23a4)[buf[k] * 2] & 4;
				}
				if (res == 0) {
					break;
				}
				k++;
			}
			fcn_0064d530((char*) tab78, buf + i + 3, k - i - 4);
			res = fcn_0064eeec((char*) tab78);
			for (j = id; j < g_6b7f98; j++) {
				if (g_11bb000[j] == e) {
					break;
				}
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
			memmove(buf + strlen(p) + (i - k) - 5, buf + i,
				strlen(buf) - (i - k) + 5);
			strcpy(buf + i - 1, p);
			break;
		case 'D':
			fcn_00500d60(st.dt, rec58);
			res = fcn_004fe330(rec58, *(short*) (rec58 + 2));
			sprintf(tmp, g_6a2310, g_14a5450[res]);
			memmove(buf + strlen(tmp), buf + i, strlen(tmp) + 2 - i);
			strcpy(buf + i - 1, tmp);
			break;
		case 'G':
			e = (*(unsigned char*) lc.rec & 0xff) * 7;
			i++;
			e = e * 2 + 0x48e;
			if (e > 0x4800) {
				p = (char*) e;
			} else {
				(*(int*) (num + 0xc)) = g_11bb000[e];
				p = g_14a5320[e];
			}
			if (r != -1) {
				p = (char*) fcn_0042b2f0(p, r, 4);
				i--;
			}
			if (p == 0) {
				p = g_14a5320[e];
			}
			if (lc.rec[5] != 0) {
				sprintf(lc.s98, g_6a2308, p, lc.rec + 5);
			} else {
				strcpy(lc.s98, p);
			}
			if (state == 0) {
				if (strlen(lc.s98) + i > 0x17cb) {
					return -1;
				}
				if (r == -1) {
					memmove(buf + i - 2 + strlen(lc.s98), buf + i,
						strlen(buf) + 2 - i);
				}
				if (r != -1) {
					memmove(buf + i - 3 + strlen(lc.s98), buf + i,
						strlen(buf) + 2 - i);
				}
				strcpy(buf + i - 2, lc.s98);
				i -= 2;
				break;
			}
			if (state == 1 || state == 2) {
				sprintf(tmp, g_68b3f8,
					fcn_0042b2f0(g_14a540c[(*(int*) (num + 0xc))], r, 4),
					lc.s98);
				if (fcn_0051e070() == 0 && state == 2) {
					tmp[0] = (char) toupper((unsigned char) tmp[0]);
				}
			} else if (state == 3 || state == 4) {
				sprintf(tmp, g_68b3f8,
					fcn_0042b2f0(g_14a5400[(*(int*) (num + 0xc))], r, 4),
					lc.s98);
				if (fcn_0051e070() == 0 && state == 4) {
					tmp[0] = (char) toupper((unsigned char) tmp[0]);
				}
			} else {
				sprintf(tmp, g_68b3f8,
					fcn_0042b2f0(g_14a5418[(*(int*) (num + 0xc))], r, 4),
					lc.s98);
				if (fcn_0051e070() == 0 && state == 6) {
					tmp[0] = (char) toupper((unsigned char) tmp[0]);
				}
			}
			if (strlen(tmp) + i > 0x17cb) {
				return -1;
			}
			if (r == -1) {
				memmove(buf + i - 2 + strlen(tmp), buf + i,
					strlen(buf) + 2 - i);
			} else {
				memmove(buf + i - 3 + strlen(tmp), buf + i,
					strlen(buf) + 2 - i);
			}
			strcpy(buf + i - 2, tmp);
			state = 0;
			i -= 2;
			break;
		case '%':
			buf[i - 1] = 0x16;
			memmove(buf + i + 1, tmp, strlen(buf) - i + 1);
			break;
		default:
			break;
		}
	}
done:
	*(int*) ((char*) (g_772514 * 0x3cc) + 0x10161b8) = 2;
	return 0;
}
