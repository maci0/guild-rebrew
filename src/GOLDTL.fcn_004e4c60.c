/* fcn_004e4c60 — release the global handle when the status slot is clear. */

void __cdecl fcn_004154e0(int);

// FUNCTION: GOLDTL 0x4e4c60
void __cdecl fcn_004e4c60(void)
{
	if (*(int*) 0x772f3c == 0) {
		fcn_004154e0(*(int*) 0x772f6c);
		*(int*) 0x772f6c = 0;
	}
}
