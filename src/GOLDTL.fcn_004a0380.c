void __cdecl fcn_004eba60(int, int*);

/* ADDRESS: GOLD 0x004a0940 */
/* ADDRESS: GOLDTL 0x004a0380 */

int __cdecl fcn_004a0380(int a, char* e)
{
	int msg[5];

	if (*e != 7 && *e != 0x16)
		return 0;
	msg[0] = *(int*) (e + 0x10);
	msg[1] = *(int*) (e + 4);
	msg[2] = 0;
	fcn_004eba60(a, msg);
	return 0x38;
}
