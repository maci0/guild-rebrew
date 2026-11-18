int __cdecl fcn_004f0cc0(char*, char*);


/* ADDRESS: GOLDTL 0x004cdd60 */
int __cdecl fcn_004cdd60(char* a1, char* output)
{
	int status;

	if (output != 0) {
		output[0] = 2;
		output[1] = 0;
		*(int*) (output + 6) = 0;
	}
	status = fcn_004f0cc0(a1 + 0x10, output);
	if (output != 0 && status != 0)
		output[0] = 1;
	if (status != 0)
		return 0;
	return -1;
}
