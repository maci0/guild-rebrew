
/* ADDRESS: GOLDTL 0x00476c70 */
int __cdecl fcn_00476c70(int a1, int a2, short a3, char* a4)
{
	((short*) *(int*) (a4 + 0x1c))[a1 + a2 * *(int*) (a4 + 0x10)] = a3;
	return 1;
}
