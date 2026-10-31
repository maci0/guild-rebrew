

char* __cdecl FindVideoById(int);

typedef int (__stdcall* fcn_0041f490_m)(void*);

int __cdecl fcn_0041f490(int a1)
{
	char* node;
	void* obj;

	node = FindVideoById(a1);
	if (node != 0) {
		obj = *(void**) (node + 0x120);
		return ((fcn_0041f490_m) ((int*) *(int*) obj)[9])(obj) == 0;
	}
	return 0;
}
