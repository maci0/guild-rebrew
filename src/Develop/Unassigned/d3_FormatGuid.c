


#include <stdio.h>

// SIZE 0x10
typedef struct {
	unsigned long d1;
	unsigned short d2;
	unsigned short d3;
	unsigned char d4[8];
} Guid;

char* __cdecl d3_FormatGuid(Guid* guid, char* out)
{
	char* r;

	r = 0;
	if (guid != 0 && out != 0) {
		sprintf(out, "%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x", guid->d1, guid->d2, guid->d3, guid->d4[0], guid->d4[1], guid->d4[2], guid->d4[3], guid->d4[4], guid->d4[5], guid->d4[6], guid->d4[7]);
		r = out;
	}
	return r;
}
