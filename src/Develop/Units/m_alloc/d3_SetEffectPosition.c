


void __cdecl d3_SetNodePosition(char*, float*);

/* ADDRESS: GOLDDE 0x00447f80 */
void __cdecl d3_SetEffectPosition(char* p, float* position)
{
	if (p == 0) {
		return;
	}
	d3_SetNodePosition(p + 0xe8, position);
}
