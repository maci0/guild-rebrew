// FUNCTION: GOLDTL 0x5463a0
// SIZE: 224

#include <stdarg.h>

// SIZE 0x14c
struct unit {
	unsigned char kind;
	char pad1[0x14b];
};

extern struct unit g_77e980[1024];
extern struct unit* g_7dc420;
extern char g_7749dc;
extern int g_7749e0;
extern unsigned char g_6a4758;
extern int g_6a475c;
extern unsigned short g_6a4760;
extern int g_6a4764;

struct unit* __cdecl fcn_005462a0(void);

struct unit* __cdecl fcn_005463a0(int n, ...)
{
	va_list ap;
	int i;

	g_6a4758 = 0xff;
	g_6a475c = -1;
	g_6a4760 = 0xffff;
	g_6a4764 = -1;
	g_7749dc = 1;
	g_7749e0 = 0;
	va_start(ap, n);
	for (i = 0; i < n; i++) {
		switch (va_arg(ap, unsigned char)) {
		case 0:
			g_6a4758 = va_arg(ap, unsigned char);
			break;
		case 1:
			g_6a475c = va_arg(ap, int);
			break;
		case 2:
			g_6a4760 = va_arg(ap, unsigned short);
			break;
		case 3:
			g_6a4764 = va_arg(ap, int);
			break;
		}
	}
	va_end(ap);
	g_7dc420 = g_77e980;
	i = 0;
	while (g_7dc420->kind == 0 && i < 0x400) {
		g_7dc420++;
		i++;
	}
	if (i >= 0x400) {
		g_7dc420 = 0;
	}
	return fcn_005462a0();
}
