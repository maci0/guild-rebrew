#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (__cdecl *HST_HANDLER)(int, int*, int, char*, int*);



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
		return 0;
	if (arg == 0)
		return 0;
	for (i = 0, t = (char*) 0x680738; (int) t < 0x680747; t += 5, i++) {
		if (*(int*) t == *(int*) text)
			sel = i;
	}
	n = 0x100;
	p = buf;
	__asm {
		mov edi, p
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short FillBuf
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	FillBuf:
		add ecx, ebx
		rep stosb
	}
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
		for (t = (char*) 0x680378; (int) t < 0x680738; t += 0x40, index++) {
			if (memcmp(text, t, strlen(t)) == 0)
				break;
		}
		if ((int) t >= 0x680738) {
			p = (char*) 0x68092c;
			goto error;
		}
		text += strlen(t);
		if (sel == 0)
			out[id * 2 + 2] = index;
	}
	if (index >= 0xf) {
		p = (char*) 0x68092c;
		goto error;
	}
	index = ((HST_HANDLER*) 0x680758)[index](sel, out, id, text, arg);
	if (index != 0)
		return index;
	if (out != 0)
		*out = index;
	return 0;
wrong_group:
	p = (char*) 0x68095c;
error:
	sprintf(buf, p);
	return 0;
}
