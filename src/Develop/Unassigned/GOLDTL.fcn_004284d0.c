#include <string.h>

int __cdecl evt_RunScript(char* script);
void __cdecl fcn_00428340(char* o, int n, ...);
char* __cdecl fcn_0064f026(char* s, char* delim);
int __cdecl _isctype(int c, int mask);
int __cdecl fcn_0064eeec(char* s);


/* Splits a script call line on spaces and runs the script with up to seven
 * arguments; numeric tokens are converted, other tokens pass as text. */
/* ADDRESS: GOLDTL 0x004284d0 */
void __cdecl fcn_004284d0(char* o, char* line)
{
	char delim[2];
	unsigned int values[16];
	char buf[256];
	char tokens[0x400];
	char* p;
	char* q;
	char* d;
	char* s;
	char c;
	int count;
	int i;
	int num;

	*(unsigned short*) delim = *(const unsigned short*) 0x677c94;
	count = 0;
	strcpy(buf, line);
	p = fcn_0064f026(buf, delim);
	if (p != 0) {
		q = tokens;
		do {
			d = q;
			count++;
			s = p;
			q += 0x40;
			do {
				c = *s++;
				*d++ = c;
			} while (c != 0);
			p = fcn_0064f026(0, delim);
		} while (p != 0);
	}
	for (i = 0; i < count; i++) {
		p = tokens + i * 0x40;
		if (*(int*) 0x6b25b0 > 1) {
			num = _isctype(*p, 4);
		} else {
			num = *(unsigned char*) (*(unsigned char**) 0x6b23a4 + *p * 2) & 4;
		}
		if (num != 0) {
			values[i] = fcn_0064eeec(p);
		} else {
			values[i] = (unsigned int) (tokens + i * 0x40);
		}
	}
	switch (count) {
	case 0:
		evt_RunScript(o);
		return;
	case 1:
		fcn_00428340(o, 1, values[0]);
		return;
	case 2:
		fcn_00428340(o, 2, values[0], values[1]);
		return;
	case 3:
		fcn_00428340(o, 3, values[0], values[1], values[2]);
		return;
	case 4:
		fcn_00428340(o, 4, values[0], values[1], values[2], values[3]);
		return;
	case 5:
		fcn_00428340(o, 5, values[0], values[1], values[2], values[3], values[4]);
		return;
	case 6:
		fcn_00428340(o, 6, values[0], values[1], values[2], values[3], values[4], values[5]);
		return;
	case 7:
		fcn_00428340(o, 7, values[0], values[1], values[2], values[3], values[4], values[5], values[6]);
		return;
	default:
		return;
	}
}
