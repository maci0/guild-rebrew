typedef struct Rec38 {
	char pad0[0x24];
	int a;
	int b;
	char pad2c[0xc];
} Rec38;
// SIZE 0x38

extern char g_662d18[];

char* __cdecl fcn_0064f026(char* s, const char* delim);
int __cdecl fcn_0064eeec(const char* s);

// FUNCTION: GOLD 0x0044ec70
// FUNCTION: GOLDTL 0x44d500
void __cdecl fcn_0044d500(int unused, char* s)
{
	char* t;

	t = fcn_0064f026(0, g_662d18);
	(*(Rec38**) (s + 0x20))[*(int*) (s + 0x18)].a = -1;
	(*(Rec38**) (s + 0x20))[*(int*) (s + 0x18)].b = fcn_0064eeec(t);
	*(int*) (s + 0x18) += 1;
}
