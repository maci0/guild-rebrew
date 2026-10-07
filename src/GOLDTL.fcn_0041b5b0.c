// FUNCTION: GOLDTL 0x41b5b0

typedef struct I41b5b0 I41b5b0;
// SIZE 0x4
struct I41b5b0 {
	int (__stdcall** vt)(I41b5b0*, int, int, void*, int);
};

extern int g_6777ac;
extern void* g_6b5df4;
extern char g_6b5df0[];
void __cdecl fcn_0041d9e0(char*);

void __cdecl fcn_0041b5b0(void)
{
	if (g_6777ac != -1) {
		fcn_0041d9e0((char*) 0x677870);
	}
	g_6777ac = 0;
	((I41b5b0*)g_6b5df4)->vt[0x2c / 4](((I41b5b0*)g_6b5df4), 0, 0, g_6b5df0, 0x2000);
}
