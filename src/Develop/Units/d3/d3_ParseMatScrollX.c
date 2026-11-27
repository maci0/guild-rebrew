

int __cdecl fcn_0064f026(int, void*);
int __cdecl atoi(int);

void __cdecl d3_ParseMatScrollX(int unused, char* ctx)
{
	char v;

	v = (char) atoi(fcn_0064f026(0, (void*) 0x662d18));
	*(char*) (*(int*) (ctx + 0x10) + *(int*) (ctx + 8) * 0xe0 + 0xc8) = v;
}
