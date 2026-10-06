// FUNCTION: GOLDTL 0x41f490

int* __cdecl fcn_0041f9b0(int);

typedef int (__stdcall* fcn_0041f490_m)(void*);

int __cdecl fcn_0041f490(int a1)
{
	int* node;
	void* obj;

	node = fcn_0041f9b0(a1);
	if (node != 0) {
		obj = (void*) node[0x120 / 4];
		return ((fcn_0041f490_m) ((int*) *(int*) obj)[9])(obj) == 0;
	}
	return 0;
}
