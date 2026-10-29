#include <string.h>
#include <stdlib.h>

#define LEX_426680 (*(char**) (*(char**) 0x6b7e98 + 0x118))

/* SIZE 0x64 */
struct tok_426680 {
	int type;
	union {
		char text[0x60];
		void* sym;
		int num;
		float fnum;
	} u;
};

int __cdecl _isctype(int, int);
int __cdecl fcn_004265f0(char*, char*);
void* __cdecl fcn_004260f0(char*, char*);
int __cdecl fcn_00426490(char*);
void* __cdecl fcn_004262b0(char*, char*);
void* __cdecl fcn_00429e60(char*);
void* __cdecl fcn_00426240(char*, char*);


/* Lexes the next token of the script text at s. */
/* ADDRESS: GOLDTL 0x00426680 */
void __cdecl fcn_00426680(char* s, struct tok_426680* t)
{
	char buf[0x100];
	char found;
	char c;
	register struct tok_426680* tok;
	char* p;
	char* q;
	int i;
	int j;
	int len;
	int start;
	int r;

	q = LEX_426680;
	found = 0;
	if (q[0] == 0 || q[1] == 0) {
		tok->type = 0xc;
		return;
	}
	tok->type = 0;
	start = 0;
	while (s[start] == ' ' && start < (int) strlen(s)) {
		start++;
	}
	i = start;
	len = (int) strlen(s);
	do {
		if (i >= len) {
			break;
		}
		for (j = 1; j < 0x1e; j++) {
			if (s[i] == *(char*) (0x14cb840 + j * 5)) {
				if (j != 0x1d) {
					break;
				}
				if (*(int*) 0x6b25b0 > 1) {
					r = _isctype(s[i - 1], 4);
				} else {
					r = *(unsigned char*) (*(unsigned char**) 0x6b23a4 + s[i - 1] * 2) & 4;
				}
				if (r == 0) {
					break;
				}
			}
		}
		if (j < 0x1e) {
			if (i == start) {
				for (j = 1; j < 0x1e; j++) {
					if (fcn_004265f0(s + i, (char*) (0x14cb840 + j * 5))) {
						i += (int) strlen((char*) (0x14cb840 + j * 5));
						break;
					}
				}
			}
			memcpy(buf, s + start, i - start);
			buf[i - start] = 0;
			found = 1;
			LEX_426680 = s + start + strlen(buf);
		}
		i++;
	} while (found == 0);

	tok = t;
	c = buf[0];
	for (j = 1; j < 9; j++) {
		if (c == *(char*) (0x14cb3b0 + (j - 1) * 0x10) && fcn_004265f0(buf, (char*) (0x14cb3b0 + (j - 1) * 0x10)) != 0) {
			tok->type = 0xa;
			tok->u.num = j;
			return;
		}
	}
	for (j = 1; j < 0x1e; j++) {
		if (c == *(char*) (0x14cb840 + j * 5) && fcn_004265f0(buf, (char*) (0x14cb840 + j * 5)) != 0) {
			tok->type = 1;
			tok->u.num = j;
			if (j == 0xe) {
				q = strchr(LEX_426680, '"');
				if (q != 0) {
					memcpy(tok->u.text, LEX_426680, q - LEX_426680);
					tok->u.text[q - LEX_426680] = 0;
				}
				tok->type = 7;
				LEX_426680 = q + 1;
			}
			*(int*) 0x6b7eb4 = j;
			if (j == 0xc) {
				*(int*) 0x6b7ec4 += 1;
				return;
			}
			if (j == 0xd) {
				*(int*) 0x6b7ec4 -= 1;
				return;
			}
			return;
		}
	}
	if (*(int*) 0x6b25b0 > 1) {
		r = _isctype(c, 4);
	} else {
		r = *(unsigned char*) (*(unsigned char**) 0x6b23a4 + c * 2) & 4;
	}
	if (r != 0) {
		if (strchr(buf, '.')) {
			tok->type = 6;
			tok->u.fnum = (float) atof(buf);
		} else {
			tok->type = 5;
			tok->u.num = atoi(buf);
		}
	} else {
		if ((p = fcn_004260f0(*(char**) 0x6b7e98, buf)) != 0) {
			tok->type = 2;
			tok->u.sym = p;
			return;
		}
		if ((r = fcn_00426490(buf)) != 0) {
			tok->type = 8;
			tok->u.num = r;
			return;
		}
		if ((p = fcn_004262b0(*(char**) 0x6b7e98, buf)) != 0) {
			tok->type = 3;
			tok->u.sym = p;
			return;
		}
		if ((p = fcn_00429e60(buf)) != 0) {
			tok->type = 4;
			tok->u.sym = p;
			return;
		}
		if ((p = fcn_00426240(*(char**) 0x6b7e98, buf)) != 0) {
			tok->type = 0xb;
			tok->u.sym = p;
			return;
		}
	}
	if (tok->type != 0) {
		return;
	}
	p = buf;
	q = tok->u.text;
	do {
		c = *p;
		*q = c;
		p++;
		q++;
	} while (c != 0);
}
