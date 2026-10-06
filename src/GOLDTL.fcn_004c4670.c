// FUNCTION: GOLD 0x004c3d00
// FUNCTION: GOLDTL 0x4c4670

#include <string.h>

extern unsigned int g_aed208;
extern unsigned char g_aed224;
extern char g_aed225[];

int __cdecl fcn_004c4670(unsigned char type, unsigned char count, short id, void* data)
{
	unsigned int n;
	char* p;

	if (type != 1 && type != 2 && type != 4)
		return 1;
	n = g_aed208 + type * count + 4;
	if (n >= 0x77)
		return 1;
	p = g_aed225 + g_aed208;
	g_aed208 = n;
	g_aed224++;
	*p++ = type;
	*p++ = count;
	*(short*) p = id;
	memcpy(p + 2, data, type * count);
	return 0;
}
