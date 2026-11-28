int __cdecl gm_ExecCannonFire(char*, char*);


/* ADDRESS: GOLDTL 0x004cdd60 */
/* ADDRESS: GOLDDE 0x004bb540 */
int __cdecl cm_ExAdjustResourceSlots(char* a1, char* output)
{
	int status;

	if (output != 0) {
		output[0] = 2;
		output[1] = 0;
		*(int*) (output + 6) = 0;
	}
	status = gm_ExecCannonFire(a1 + 0x10, output);
	if (output != 0 && status != 0)
		output[0] = 1;
	if (status != 0)
		return 0;
	return -1;
}
