int __cdecl fcn_004a75a0(int* h, int* out, int a3);
int __cdecl fcn_004a73f0(int* h, int* out, int a3);

/* ADDRESS: GOLDTL 0x004a76d0 */
int __cdecl fcn_004a76d0(int* h, int* out, int a3)
{
	if (!a3 && fcn_004a75a0(h, out, 0) && fcn_004a73f0(h, out, 0)) {
		return 1;
	}
	return 0;
}
