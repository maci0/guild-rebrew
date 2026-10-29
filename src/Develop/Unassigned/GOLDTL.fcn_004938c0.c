


#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int __cdecl fcn_004938c0(char* p)
{
	return (int) min(max(*(float*) (p + 4) * 0.25f, 2.0f), 6.0f);
}
