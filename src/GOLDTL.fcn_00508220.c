


typedef struct {
	int a;
	int b;
	int c;
} Rec12;
// SIZE 0xc

extern Rec12 g_696560[];

int __cdecl fcn_00508220(int idx, Rec12* out)
{
	if (idx >= 10) {
		*out = g_696560[0];
		return 0;
	}
	*out = g_696560[idx];
	return 1;
}
