#include <string.h>
#include <stdlib.h>
extern char g_14cb3b0[]; extern int g_6b25b0, g_6b23a4;
extern char* evt_CurrentScript;
extern int g_6b7eb4;
extern int g_6b7ec4;
#define LEX_426680 (*(char**) (evt_CurrentScript + 0x118))

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
int __cdecl evt_MatchTokenPrefix(char*, char*);
void* __cdecl evt_FindSymbol(char*, char*);
int __cdecl evt_ClassifyScriptType(char*);
void* __cdecl evt_FindDefinition(char*, char*);
void* __cdecl fcn_00429e60(char*);
void* __cdecl fcn_00426240(char*, char*);


/* Lexes the next token of the script text at s. */
/* ADDRESS: GOLDTL 0x00426680 */
void __cdecl evt_ReadToken(char* s, struct tok_426680* t)
{
	char buf[0x100];
	char found;
	char c;
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
		t->type = 0xc;
		return;
	}
	t->type = 0;
	start = 0;
	while (s[start] == ' ' && start < strlen(s)) {
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
				if (j == 0x1d) {
					if (g_6b25b0 > 1) {
						r = _isctype(s[i - 1], 4);
					} else {
						r = *(unsigned char*) ((unsigned char*) g_6b23a4 + s[i - 1] * 2) & 4;
					}
					if (r != 0) {
						continue;
					}
				}
				if (i - start == 0) {
					for (j = 1; j < 0x1e; j++) {
						if (evt_MatchTokenPrefix(s + i, (char*) (0x14cb840 + j * 5))) {
							i += (int) strlen((char*) (0x14cb840 + j * 5));
							break;
						}
					}
				}
				found = 1;
				memcpy(buf, s + start, i - start);
				buf[i - start] = 0;
				LEX_426680 = s + start + strlen(buf);
				break;
			}
		}
		i++;
	} while (found == 0);

	c = buf[0];
	for (j = 1; j < 9; j++) {
		if (c == *(char*) (g_14cb3b0 + (j - 1) * 0x10) && evt_MatchTokenPrefix(buf, (char*) (g_14cb3b0 + (j - 1) * 0x10)) != 0) {
			t->type = 0xa;
			t->u.num = j;
			return;
		}
	}
	for (j = 1; j < 0x1e; j++) {
		if (c == *(char*) (0x14cb840 + j * 5) && evt_MatchTokenPrefix(buf, (char*) (0x14cb840 + j * 5)) != 0) {
			t->type = 1;
			t->u.num = j;
			if (j == 0xe) {
				q = strchr(LEX_426680, '"');
				if (q != 0) {
					memcpy(t->u.text, LEX_426680, q - LEX_426680);
					t->u.text[q - LEX_426680] = 0;
				}
				t->type = 7;
				LEX_426680 = q + 1;
			}
			g_6b7eb4 = j;
			if (j == 0xc) {
				g_6b7ec4 += 1;
				return;
			}
			if (j == 0xd) {
				g_6b7ec4 -= 1;
				return;
			}
			return;
		}
	}
	if (g_6b25b0 > 1) {
		r = _isctype(c, 4);
	} else {
		r = *(unsigned char*) ((unsigned char*) g_6b23a4 + c * 2) & 4;
	}
	if (r != 0) {
		if (strchr(buf, '.')) {
			t->type = 6;
			t->u.fnum = (float) atof(buf);
		} else {
			t->type = 5;
			t->u.num = atoi(buf);
		}
	} else {
		if ((p = evt_FindSymbol(evt_CurrentScript, buf)) != 0) {
			t->type = 2;
			t->u.sym = p;
			return;
		}
		if ((r = evt_ClassifyScriptType(buf)) != 0) {
			t->type = 8;
			t->u.num = r;
			return;
		}
		if ((p = evt_FindDefinition(evt_CurrentScript, buf)) != 0) {
			t->type = 3;
			t->u.sym = p;
			return;
		}
		if ((p = fcn_00429e60(buf)) != 0) {
			t->type = 4;
			t->u.sym = p;
			return;
		}
		if ((p = fcn_00426240(evt_CurrentScript, buf)) != 0) {
			t->type = 0xb;
			t->u.sym = p;
			return;
		}
	}
	if (t->type != 0) {
		return;
	}
	strcpy(t->u.text, buf);
}
