// FUNCTION: GOLDTL 0x5171a0
// SIZE: 170

#include <stdlib.h>
#include <string.h>

int __cdecl fcn_005171a0(char* s, int* out, int max)
{
	char buf[256];
	int done;
	int n;
	char* c;

	n = 0;
	done = 0;
	c = strchr(s, ',');
	while (n < max) {
		memset(buf, 0, sizeof(buf));
		strncpy(buf, s, c - s);
		out[n] = atoi(buf);
		n++;
		if (done) {
			break;
		}
		s = c + 1;
		c = strchr(s, ',');
		if (c == 0) {
			c = strchr(s, 0);
			done = 1;
		}
	}
	return n;
}
