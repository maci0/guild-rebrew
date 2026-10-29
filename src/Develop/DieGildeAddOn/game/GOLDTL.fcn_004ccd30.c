


#include <string.h>

extern unsigned short g_774970;
extern char g_7f4ca4[];
extern char g_9b0e20[];

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl fcn_00508e40(int);
int* __cdecl fcn_004ceac0(char*, char*);

int __cdecl fcn_004ccd30(char* x, char* out)
{
	int i;
	char* e;
	int* d;
	char* rec;
	int* src;

	if (*(int*) (x + 0x40) != *(int*) (g_7f4ca4 + g_774970 * 0x21c + 0x208))
		return 1;
	for (i = 0; i < 16; i++) {
		if (*(int*) (g_9b0e20 + i * 0x35c + 0x10) == *(int*) (x + 0x10)) {
			rec = g_9b0e20 + i * 0x35c;
			src = (int*) (x + 0x14);
			e = gm_LookupEntityRecordById(*src);
			if (e == 0) {
				e = fcn_00508e40(*src);
				if (e == 0)
					break;
			}
			d = fcn_004ceac0(rec, e);
			memcpy(d, src, 0x2c);
			if (d[1] == 0)
				d[0] = -1;
			break;
		}
	}
	if (out != 0) {
		out[0] = 1;
		out[1] = 8;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
