extern char str_space[];


int __cdecl fcn_0064f026(int, void*);
float __cdecl fcn_0064d62e(int);

/* ADDRESS: GOLDDE 0x00443000 */
void __cdecl d3_ParseMatUTile(int unused, char* ctx)
{
	*(float*) (*(int*) (ctx + 0x10) + *(int*) (ctx + 8) * 0xe0 + 0xcc) = fcn_0064d62e(fcn_0064f026(0, (void*) &str_space));
}
