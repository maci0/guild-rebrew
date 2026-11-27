
/* ADDRESS: GOLDTL 0x00476c70 */
int __cdecl d2_WritePixel16(int x, int y, short value, char* surface)
{
	((short*) *(int*) (surface + 0x1c))[x + y * *(int*) (surface + 0x10)] = value;
	return 1;
}
