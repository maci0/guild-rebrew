// FUNCTION: GOLDTL 0x4cd2a0
// SIZE: 135

int __cdecl fcn_00451840(char*, float*, float);
void __cdecl fcn_00438b40(char*, float*);
void __cdecl fcn_00438cb0(char*, float*);

void __cdecl fcn_004cd2a0(char* e, float* pos, float* rot, int v)
{
	if (e != 0 && *(char**) (e + 0x184) != 0) {
		if (fcn_00451840(*(char**) (*(char**) (e + 0x184) + 0x34) + 0x4c, pos, 8.0f) == 0)
			fcn_00438b40(*(char**) (*(char**) (e + 0x184) + 0x34), pos);
		if (fcn_00451840(*(char**) (*(char**) (e + 0x184) + 0x34) + 0x84, rot, 8.0f) == 0)
			fcn_00438cb0(*(char**) (*(char**) (e + 0x184) + 0x34), rot);
		*(int*) (e + 0x24) = v;
	}
}
