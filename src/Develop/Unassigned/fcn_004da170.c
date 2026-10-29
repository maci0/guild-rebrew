void __cdecl fcn_004d7d30(void*);
void __cdecl fcn_004d9f20(void*);

/* ADDRESS: GOLDTL 0x004da170 */
void __cdecl fcn_004da170(void* p)
{
	if (*(int*) 0x772f2c != 0) {
		fcn_004d9f20(p);
		return;
	}
	fcn_004d7d30(p);
}
