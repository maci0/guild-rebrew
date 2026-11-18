


extern float g_6652d8[];

int __cdecl fcn_004f4440(int, int, int, int, int*);

int __cdecl fcn_004f4550(int a1, int a2, int a3, int* out)
{
	int first;
	int result;

	first = fcn_004f4440(a1, 100, a2, 1, &a2);
	result = fcn_004f4440(a1, 100, a3, 1, &a2) - first / 2;
	*out = (int) (result * g_6652d8[a3]);
	return result;
}
