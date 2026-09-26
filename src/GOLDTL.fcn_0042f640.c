extern char g_6b5c60[];

int __cdecl fcn_0042f010(int a, int b);
void __cdecl fcn_0042f420(int x, int c, char* d);

// FUNCTION: GOLDTL 0x42f640
// SIZE: 65
char* __cdecl fcn_0042f640(int a, int b, int c, char* d)
{
	int x;

	x = fcn_0042f010(a, b);
	if (x != 0) {
		if (x != c) {
			fcn_0042f420(x, c, d);
		} else {
			*d = (*(char*)g_6b5c60);
		}
		return d;
	}
	return 0;
}
