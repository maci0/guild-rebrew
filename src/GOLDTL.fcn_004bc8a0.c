extern char* g_67a370;

unsigned short __cdecl fcn_0042e410(unsigned short);
char __cdecl fcn_0045b990(char*, float*, int*, int*, int*);
char __cdecl fcn_00407e30(char*, float*, float*, int, int, int*, int*, int, int);
void __cdecl fcn_0045b920(char*, int, int, float*);

// FUNCTION: GOLD 0x004bc390
// SIZE: 276
// FUNCTION: GOLDTL 0x4bc8a0
// SIZE: 276

int __cdecl fcn_004bc8a0(float* a1, int n, float* out)
{
	int ny;
	int y;
	int x;
	int z;
	int nx;
	int k;
	char* g;

	g = *(char**) (g_67a370 + 0xb0);
	fcn_0045b990(g, a1, &x, &y, &z);
	for (k = 0; k < n; k++) {
		nx = fcn_0042e410(10) + x - 4;
		ny = fcn_0042e410(10) + y - 4;
		if (*(int*) (g + 0x20) - 2 < nx)
			nx = *(int*) (g + 0x20) - 2;
		if (nx < 2)
			nx = 2;
		if (*(int*) (g + 0x20) - 2 < ny)
			ny = *(int*) (g + 0x20) - 2;
		if (ny < 2)
			ny = 2;
		if (fcn_00407e30(g, a1, a1, nx, ny, &nx, &ny, 0x258, 0) != 0)
			fcn_0045b920(g, nx, ny, out + k * 4);
		else
			fcn_0045b920(g, x, y, out + k * 4);
	}
	return n;
}
