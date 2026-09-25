extern int g_774a14;
extern int g_6b7fc0;

// SIZE 0x40
struct cb_57eba0 {
	char pad[0x3c];
	int (__cdecl* fn)(int*);
};

// SIZE 0x1c
struct host_57eba0 {
	char pad[0x18];
	struct cb_57eba0* cb;
};

extern struct host_57eba0* g_665f08;

// FUNCTION: GOLD 0x576600
// SIZE: 125
// FUNCTION: GOLDTL 0x57eba0
// SIZE: 125

int __cdecl fcn_0057eba0(int a, int b, int c, int d)
{
	int buf[4];

	if (g_774a14 == 0) {
		return 1;
	}
	if (g_665f08->cb == 0) {
		return 1;
	}
	if (g_6b7fc0 != 0) {
		return 0;
	}
	if (g_665f08->cb->fn == 0) {
		return 1;
	}
	buf[0] = a;
	buf[1] = b;
	buf[2] = c;
	buf[3] = d;
	return g_665f08->cb->fn(buf);
}
