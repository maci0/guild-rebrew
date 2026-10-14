

extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_6b5c80;
extern int g_6b5c84;
extern int g_6772bc;
extern int g_6772c0;
extern char g_14cf7c8;
extern char g_14cf7d0;
extern char g_14cf7cb;
extern char g_14cf7cd;
extern int g_774a58;
extern int g_774a4c;
extern int g_778d24;
extern int g_778d20;

int __cdecl fcn_005a7d10(char* w)
{
	int r;
	int x;
	int y;

	r = 0;
	x = *(int*) (w + 0x258);
	g_774a58 = x;
	y = *(int*) (w + 0x248);
	if (g_14ce8c0 <= g_6b5c80) {
		x -= 10;
	} else if (g_14ce8c0 >= g_6772bc) {
		x += 10;
	}
	if (g_14ce8c2 <= g_6b5c84) {
		y -= 10;
	} else if (g_14ce8c2 >= g_6772c0) {
		y += 10;
	}
	if (g_14cf7c8 != 0) {
		y -= 10;
	} else if (g_14cf7d0 != 0) {
		y += 10;
	} else if (g_14cf7cb != 0) {
		x -= 10;
	} else if (g_14cf7cd != 0) {
		x += 10;
	}
	g_774a58 = x < 0 ? 0 : x;
	if (g_778d24 - 0x200 < g_774a58) {
		g_774a58 = g_778d24 - 0x200;
	}
	g_774a4c = y < 0 ? 0 : y;
	if (g_778d20 - 0x168 < g_774a4c) {
		g_774a4c = g_778d20 - 0x168;
	}
	if (g_774a58 != *(int*) (w + 0x258) || g_774a4c != *(int*) (w + 0x248)) {
		*(int*) (w + 0x258) = g_774a58;
		*(int*) (w + 0x248) = g_774a4c;
		r = 1;
	}
	return r;
}
