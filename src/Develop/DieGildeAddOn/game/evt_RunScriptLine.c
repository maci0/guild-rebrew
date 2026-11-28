extern char g_677c94[];
extern char g_6b23a4[];
extern char g_6b25b0[];
#include <string.h>

int __cdecl evt_RunScript(char* script);
void __cdecl evt_CallScriptFunction(char* o, int n, ...);
char* __cdecl fcn_0064f026(char* s, char* delim);
int __cdecl _isctype(int c, int mask);
int __cdecl atoi(char* s);


/* Splits a script call line on spaces and runs the script with up to seven
 * arguments; numeric tokens are converted, other tokens pass as text. */
/* ADDRESS: GOLDTL 0x004284d0 */
/* ADDRESS: GOLDDE 0x00422f30 */
void __cdecl evt_RunScriptLine(char* o, char* line)
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

	*(unsigned short*) delim = *(const unsigned short*) &g_677c94;
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
		if (*(int*) &g_6b25b0 > 1) {
			num = _isctype(*p, 4);
		} else {
			num = *(unsigned char*) (*(unsigned char**) (int) &g_6b23a4 + *p * 2) & 4;
		}
		if (num != 0) {
			values[i] = atoi(p);
		} else {
			values[i] = (unsigned int) (tokens + i * 0x40);
		}
	}
	switch (count) {
	case 0:
		evt_RunScript(o);
		return;
	case 1:
		evt_CallScriptFunction(o, 1, values[0]);
		return;
	case 2:
		evt_CallScriptFunction(o, 2, values[0], values[1]);
		return;
	case 3:
		evt_CallScriptFunction(o, 3, values[0], values[1], values[2]);
		return;
	case 4:
		evt_CallScriptFunction(o, 4, values[0], values[1], values[2], values[3]);
		return;
	case 5:
		evt_CallScriptFunction(o, 5, values[0], values[1], values[2], values[3], values[4]);
		return;
	case 6:
		evt_CallScriptFunction(o, 6, values[0], values[1], values[2], values[3], values[4], values[5]);
		return;
	case 7:
		evt_CallScriptFunction(o, 7, values[0], values[1], values[2], values[3], values[4], values[5], values[6]);
		return;
	default:
		return;
	}
}
