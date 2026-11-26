


void __cdecl d3_SetNodePosition(char*, float*);

void __cdecl fcn_004526d0(char* p, float* position)
{
	if (p == 0) {
		return;
	}
	d3_SetNodePosition(p + 0xe8, position);
}
