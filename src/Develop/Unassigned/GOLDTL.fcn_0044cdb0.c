#include <string.h>

typedef void (__cdecl* Handler)(void*, int);

// SIZE 0xc
typedef struct {
	const char* name;
	int fn;
	int sub;
} Entry;

char* __cdecl vfs_ReadConfigLine(void*);
int __cdecl d3_LookupParserToken(char*, Entry*, int);


/* ADDRESS: GOLDTL 0x0044cdb0 */
void __cdecl d3_ParseTextBlock(void* stream, Entry* tbl, int count, int user)
{
	char line[0x100];
	char tmp[0x100];
	char* p;
	char* tok;
	int k;
	int depth;

	if (tbl[0].fn != 0) {
		((Handler) tbl[0].fn)(stream, user);
	}
	p = vfs_ReadConfigLine(stream);
	while (p != 0) {
		if (p[0] == '}') {
			if (tbl[1].fn != 0) {
				((Handler) tbl[1].fn)(stream, user);
			}
			return;
		}
		strcpy(line, p);
		strcpy(tmp, p);
		tok = strtok(tmp, " ");
		k = d3_LookupParserToken(tok, tbl, count);
		if (k != -1) {
			if (tbl[k].fn != 0 && tbl[k].sub == 0) {
				((Handler) tbl[k].fn)(stream, user);
			} else if (tbl[k].sub == 0) {
				d3_ParseTextBlock(stream, tbl, count, user);
			} else {
				d3_ParseTextBlock(stream, (Entry*) tbl[k].fn, tbl[k].sub, user);
			}
		} else if (line[strlen(line) - 1] == '{') {
			depth = 1;
			do {
				p = vfs_ReadConfigLine(stream);
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
		p = vfs_ReadConfigLine(stream);
	}
}
