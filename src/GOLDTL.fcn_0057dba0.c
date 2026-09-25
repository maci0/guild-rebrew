// FUNCTION: GOLDTL 0x57dba0
// SIZE: 135

char* __cdecl fcn_00508e40(int);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_0057dc30(char*);
void __cdecl fcn_0057dd40(char*);
void __cdecl fcn_0057dd70(char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_0057dba0(char* o)
{
	char* x;
	float r;

	x = fcn_00508e40(*(int*) (o + 0xc));
	if (*(int*) (o + 0x70) != -1 && *(int*) (o + 0x70) != -2 && x != 0) {
		r = gm_RandomFloat01();
		if (r > 0.8f) {
			fcn_0057dc30(x);
		} else if (r > 0.4f) {
			fcn_0057dd40(x);
		} else {
			fcn_0057dd70(x);
		}
	}
	fcn_00546190(o);
}
