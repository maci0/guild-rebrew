#include <string.h>


/* Classifies a script type keyword (up to the first blank or ')'). */
/* ADDRESS: GOLDTL 0x00426490 */
int __cdecl fcn_00426490(const char* s)
{
	char* p;
	int type;
	char buf[0x200];

	strcpy(buf, s);
	p = strchr(buf, ' ');
	if (p == 0) {
		p = strchr(buf, ')');
	}
	if (p != 0) {
		*p = 0;
	}
	if (strcmp(buf, "int") == 0) {
		type = 1;
	} else if (strcmp(buf, "float") == 0) {
		type = 7;
	} else if (strcmp(buf, "void") == 0) {
		type = 5;
	} else if (strcmp(buf, "string") == 0) {
		type = 6;
	} else if (strcmp(buf, "{") == 0) {
		type = 8;
	} else if (strcmp(buf, "}") == 0) {
		type = 9;
	} else if (strcmp(buf, "byte") == 0 || strcmp(buf, "char") == 0) {
		type = 2;
	} else {
		type = 0;
	}
	return type;
}
