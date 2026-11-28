extern char str_space[];


int __cdecl fcn_0064f026(int, void*);
int __cdecl atoi(int);

/* ADDRESS: GOLDDE 0x00442fc0 */
void __cdecl d3_ParseMatScrollY(int unused, char* ctx)
{
	char v;

	v = (char) atoi(fcn_0064f026(0, (void*) &str_space));
	*(char*) (*(int*) (ctx + 0x10) + *(int*) (ctx + 8) * 0xe0 + 0xc8) = v;
}
