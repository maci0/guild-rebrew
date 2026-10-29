


char __cdecl fcn_0045b920(int, int, int, float*);
int __cdecl fcn_00408270(int, float*, int, int);

int __cdecl fcn_004082d0(int a1, int a2, int a3, int a4, int a5, int a6)
{
	float v[4];

	if (fcn_0045b920(a1, a2, a3, v)) {
		fcn_00408270(a4, v, a5, a6);
		return 1;
	}
	return 0;
}
