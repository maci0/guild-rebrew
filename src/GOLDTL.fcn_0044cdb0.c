#include <string.h>

typedef void (__cdecl* Handler)(void*, int);

// SIZE 0xc
typedef struct {
	const char* name;
	int fn;
	int sub;
} Entry;

char* __cdecl fcn_004010b0(void*);
int __cdecl fcn_0044cd20(char*, Entry*, int);

// FUNCTION: GOLDTL 0x0044cdb0
// SIZE: 367

void __cdecl fcn_0044cdb0(void* s, Entry* tbl, int arg, int user)
{
	char line[0x100];
	char tmp[0x100];
	char* p;
	char* tok;
	int k;
	int depth;

	if (tbl[0].fn != 0) {
		((Handler) tbl[0].fn)(s, user);
	}
	p = fcn_004010b0(s);
	while (p != 0) {
		if (p[0] == '}') {
			if (tbl[1].fn != 0) {
				((Handler) tbl[1].fn)(s, user);
			}
			return;
		}
		strcpy(line, p);
		strcpy(tmp, p);
		tok = strtok(tmp, " ");
		k = fcn_0044cd20(tok, tbl, arg);
		if (k != -1) {
			if (tbl[k].fn != 0 && tbl[k].sub == 0) {
				((Handler) tbl[k].fn)(s, user);
			} else if (tbl[k].sub == 0) {
				fcn_0044cdb0(s, tbl, arg, user);
			} else {
				fcn_0044cdb0(s, (Entry*) tbl[k].fn, tbl[k].sub, user);
			}
		} else if (line[strlen(line) - 1] == '{') {
			depth = 1;
			do {
				p = fcn_004010b0(s);
				switch (p[strlen(p) - 1]) {
				case '{':
					depth++;
					break;
				case '}':
					depth--;
					break;
				}
			} while (depth > 0);
		}
		p = fcn_004010b0(s);
	}
}
