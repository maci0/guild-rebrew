#include <stdarg.h>

typedef struct {
	char pad0[0x164];
	unsigned char b164;
	char pad165[0x21c - 0x165];
} Rec506ee0;
// SIZE 0x21c

extern char g_7f4ca0[];

/* ADDRESS: GOLDTL 0x00506ee0 */
int __cdecl fcn_00506ee0(unsigned short id, int n, ...)
{
	Rec506ee0 rec;
	va_list ap;
	int r;
	int i;

	r = 0;
	rec = ((Rec506ee0*)g_7f4ca0)[id];
	if (n <= -1) {
		return r;
	}
	va_start(ap, n);
	for (i = 0; i < n; i++) {
		if (rec.b164 == va_arg(ap, int)) {
			r = 1;
			break;
		}
	}
	va_end(ap);
	return r;
}
