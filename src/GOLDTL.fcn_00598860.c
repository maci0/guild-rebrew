// FUNCTION: GOLDTL 0x598860
// SIZE: 78

void __cdecl fcn_00438b40(char*, float*);
void __cdecl fcn_004143b0(char*, int, int);
void __cdecl fcn_00455350(char*, char*, float*);

void __cdecl fcn_00598860(char* obj, float* pos)
{
	float v[4];

	fcn_00438b40(obj, pos);
	fcn_004143b0(obj, 1, 0);
	fcn_00455350(obj, obj + 0x4c, v);
	if (v[1] < pos[1]) {
		fcn_00438b40(obj, pos);
	}
}
