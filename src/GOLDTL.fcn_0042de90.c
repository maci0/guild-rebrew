// FUNCTION: GOLD 0x0042e970
// FUNCTION: GOLDTL 0x0042de90

// SIZE 0xc
typedef struct {
	int a;
	int b;
	int c;
} E42de90;

extern int g_1052c60[0x60];
extern char g_679e00[];
void __cdecl fcn_0041d9e0(char* msg);

int __cdecl fcn_0042de90(int a, int b)
{
	int i;

	i = 0;
	while (((E42de90*)g_1052c60)[i++].a != 0 && i < 32) {
	}
	if (i > 32) {
		fcn_0041d9e0(g_679e00);
		return 0;
	}
	i--;
	((E42de90*)g_1052c60)[i].a = a;
	((E42de90*)g_1052c60)[i].b = b;
	((E42de90*)g_1052c60)[i].c = 0;
	return 1;
}
