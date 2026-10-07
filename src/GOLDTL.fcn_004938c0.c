// FUNCTION: GOLD 0x00494290
// FUNCTION: GOLDTL 0x4938c0

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int __cdecl fcn_004938c0(char* p)
{
	return (int) min(max(*(float*) (p + 4) * 0.25f, 2.0f), 6.0f);
}
