#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (__cdecl *HST_HANDLER)(int, int*, int, char*, int*);

#pragma optimize("y", off)

/* Attested name: hst_ParseContext (log strings at 0x68092c, 0x68095c, 0x680990) */
/* ADDRESS: GOLDTL 0x004b2300 */
int __cdecl hst_ParseContext(char* text, int* arg, int* out)
{
	int id;
	int sel;
	int n;
	char* p;
	char buf[0x100];
	char* t;
	int i;
	int index;

	id = -1;
	sel = 4;
	if (text == 0)
		goto wrong_group;
	if (arg == 0)
		goto wrong_group;
	for (i = 0, t = (char*) 0x680738; t < (char*) 0x680747; t += 5, i++) {
		if (*(int*) t == *(int*) text)
			sel = i;
	}
	n = 0x100;
	p = buf;
	memset(p, 0, n);
	if (sel == 4)
		goto lookup;
	if (out == 0)
		goto wrong_group;
	if (*out == 0)
		goto wrong_group;
	buf[0] = text[5];
	id = atoi(buf);
	text += 6;
	if (id < 0 || id > 7) {
		sprintf(buf, (char*) 0x680990, id);
		return 0;
	}
lookup:
	if (sel == 1) {
		index = out[id * 2 + 2];
	} else {
		text += 1;
		index = 0;
		for (t = (char*) 0x680378; t < (char*) 0x680738; t += 0x40, index++) {
			if (strcmp(text, t) == 0)
				break;
		}
		if (t >= (char*) 0x680738) {
			sprintf(buf, (char*) 0x68092c);
			return 0;
		}
		text += strlen(t);
		if (sel == 0)
			out[id * 2 + 2] = index;
	}
	if (index >= 0xf) {
		sprintf(buf, (char*) 0x68092c);
		return 0;
	}
	index = ((HST_HANDLER*) 0x680758)[index](sel, out, id, text, arg);
	if (index != 0)
		return index;
	if (out != 0)
		*out = index;
	return 0;
wrong_group:
	sprintf(buf, (char*) 0x68095c);
	return 0;
}
