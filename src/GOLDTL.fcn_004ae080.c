


#include <string.h>

void __cdecl fcn_004ae080(char* src, char* out, int* consumed, int* rest)
{
	int dashes;
	char prev;
	char* p;
	char* dst;

	dst = out;
	dashes = 0;
	prev = ' ';
	p = src;
	while (*p != 0 && dashes < 2) {
		if (*p == '-') {
			dashes++;
		} else if (*p == '%') {
			if (prev == ' ') {
				*dst++ = *p;
			} else {
				*dst++ = ' ';
				*dst++ = prev = *p;
			}
		} else {
			prev = *p;
			*dst++ = *p;
		}
		p++;
	}
	*consumed = p - src;
	*rest = strlen(p);
}
