#include <stdio.h>

/* SIZE 0x10 */
typedef struct {
	unsigned long d1;
	unsigned short d2;
	unsigned short d3;
	unsigned char d4[8];
} Guid;

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0041c760 */
char __cdecl d3_ParseGuid(const char* s, Guid* g)
{
	int d1;
	int d2;
	int d3;
	int b[8];
	char r;

	r = 0;
	if (s != 0 && *s != 0 && g != 0) {
		sscanf(s, "%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x", &d1, &d2, &d3, &b[0], &b[1], &b[2], &b[3], &b[4], &b[5], &b[6], &b[7]);
		g->d1 = d1;
		g->d2 = (unsigned short) d2;
		g->d3 = (unsigned short) d3;
		g->d4[0] = (unsigned char) b[0];
		g->d4[1] = (unsigned char) b[1];
		g->d4[2] = (unsigned char) b[2];
		g->d4[3] = (unsigned char) b[3];
		g->d4[4] = (unsigned char) b[4];
		g->d4[5] = (unsigned char) b[5];
		g->d4[6] = (unsigned char) b[6];
		g->d4[7] = (unsigned char) b[7];
		r = 1;
	}
	return r;
}
#else
/* ADDRESS: GOLDTL 0x0041b3a0 */
char __cdecl d3_ParseGuid(const char* str, Guid* out_guid)
{
	int d1;
	int d2;
	int d3;
	int b[8];
	int n;
	char ok;

	ok = 0;
	if (str != 0 && *str != 0 && out_guid != 0) {
		n = sscanf(str, "%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x", &d1, &d2, &d3, &b[0], &b[1], &b[2], &b[3], &b[4], &b[5], &b[6], &b[7]);
		out_guid->d1 = d1;
		out_guid->d2 = (unsigned short) d2;
		out_guid->d3 = (unsigned short) d3;
		out_guid->d4[0] = (unsigned char) b[0];
		out_guid->d4[1] = (unsigned char) b[1];
		out_guid->d4[2] = (unsigned char) b[2];
		out_guid->d4[3] = (unsigned char) b[3];
		out_guid->d4[4] = (unsigned char) b[4];
		out_guid->d4[5] = (unsigned char) b[5];
		ok = n == 11;
		out_guid->d4[6] = (unsigned char) b[6];
		out_guid->d4[7] = (unsigned char) b[7];
	}
	return ok;
}
#endif
