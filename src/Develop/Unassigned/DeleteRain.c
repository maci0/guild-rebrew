int __cdecl d3_DestroyRain(int value);

/* ADDRESS: GOLDTL 0x0040f9b0 */
int __cdecl DeleteRain(int* arg)
{
	d3_DestroyRain(*arg);
	return 0;
}
