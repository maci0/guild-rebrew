
// fcn_0042e940 — init callback globals + call [0x5eb274].

int (__stdcall* f1_5eb288)(int);
int (__stdcall* f2_5eb274)(int);

void __cdecl fcn_0042e940(void)
{
	int e;
	e = *(int*) 0x6333c8;
	if (e != 0) {
		if (((int (__stdcall*)(int)) *(void**) 0x5eb288)(e) == 0) {
			*(int*) 0x6333c8 = e * 0;
		}
	}
	((int (__stdcall*)(int)) *(void**) 0x5eb274)(*(int*) 0xfe7a80 + 5);
}
