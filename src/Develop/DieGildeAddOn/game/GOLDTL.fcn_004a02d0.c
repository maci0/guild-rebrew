int __cdecl amt_CheckHighOfficeEligibility(char* e);
char* __cdecl ai_PickOfficeRival(char* e);
int __cdecl ai_SelectZunftPrivilege0x20Target(char* e);
int __cdecl fcn_004a0020(char* e);

/* ADDRESS: GOLDTL 0x004a02d0 */
int __cdecl ai_StartZunftLevel3(int a1, char* e, int a3, char* out)
{
	char c;
	char* p;
	int r;

	if (a3) {
		return 0;
	}
	if (a1) {
		return 0;
	}
	if (amt_CheckHighOfficeEligibility(e) != 1) {
		return 0;
	}
	c = e[0x169];
	if (c == 0x1e) {
		p = ai_PickOfficeRival(e);
		if (!p) {
			return 0;
		}
		out[0] = 7;
		*(int*) (out + 4) = *(int*) (p + 4);
		*(int*) (out + 0x10) = 1;
		return 0x38;
	}
	if (c == 0x20) {
		r = ai_SelectZunftPrivilege0x20Target(e);
	} else if (c == 0x1f || c == 0x21) {
		r = fcn_004a0020(e);
	} else {
		return 0;
	}
	if (!r) {
		return 0;
	}
	*(int*) (out + 4) = r;
	out[0] = 0x16;
	*(int*) (out + 0x10) = 4;
	return 0x38;
}
