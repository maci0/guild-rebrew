/* ADDRESS: GOLDTL 0x0044cf20 */
void* __cdecl d3_ParseMatDone(void* a0, void* object)
{
	(void) a0;
	*(int*) ((char*) object + 8) += 1;
	return object;
}
