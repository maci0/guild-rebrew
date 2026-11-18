
/* ADDRESS: GOLDTL 0x00476c70 */
int __cdecl fcn_00476c70(int x, int y, short value, char* grid)
{
	((short*) *(int*) (grid + 0x1c))[x + y * *(int*) (grid + 0x10)] = value;
	return 1;
}
