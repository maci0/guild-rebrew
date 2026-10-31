


#include <string.h>

extern unsigned short g_774970;
extern char g_7f4ca4[];
extern char g_9b0e20[];

char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
int* __cdecl fcn_004ceac0(char*, char*);

int __cdecl fcn_004ccdf0(char* x, char* out)
{
	int i;
	int* d;

	if (*(int*) (x + 0x40) != *(int*) (g_7f4ca4 + g_774970 * 0x21c + 0x208))
		return 1;
	for (i = 0; i < 16; i++) {
		if (*(int*) (g_9b0e20 + i * 0x35c + 0x10) == *(int*) (x + 0x10)) {
			d = fcn_004ceac0(g_9b0e20 + i * 0x35c, gm_LookupEntityRecordIn32SlotTable(*(int*) (x + 0x14)));
			if (d[1] == *(int*) (x + 0x18) && (d[1] != 2 || d[4] == *(int*) (x + 0x24)))
				memcpy(d, x + 0x14, 0x2c);
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
