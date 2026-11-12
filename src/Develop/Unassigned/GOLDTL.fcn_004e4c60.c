/* fcn_004e4c60 — release the global handle when the status slot is clear. */
extern char g_772f3c[];
void __cdecl fcn_004154e0(int);

/* ADDRESS: GOLDTL 0x004e4c60 */
void __cdecl fcn_004e4c60(void)
{
	if (*(int*) &g_772f3c == 0) {
		fcn_004154e0(*(int*) 0x772f6c);
		*(int*) 0x772f6c = 0;
	}
}
