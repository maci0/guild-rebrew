// FUNCTION: GOLDTL 0x4cc340
// SIZE: 38

void __cdecl fcn_004fb4e0(void*);

int __cdecl fcn_004cc340(char* p, char* out)
{
	fcn_004fb4e0(p + 0x10);
	if (out != 0) {
		out[0] = 1;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
