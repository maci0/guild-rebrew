void __cdecl fcn_004b5440(int, void*);
int __cdecl fcn_004b52d0(int, int, int);

struct stat_4b4dc0 {
	int value;
	int count;
	float ratio;
};
// SIZE 0xc

/* ADDRESS: GOLD 0x004b4c50 */
/* ADDRESS: GOLDTL 0x004b4dc0 */

int __cdecl fcn_004b4dc0(int a0, int a1, char* a2)
{
	struct stat_4b4dc0 s;

	fcn_004b5440(0xb, &s);
	if (s.count > 0 && s.ratio < 1.0f)
		return fcn_004b52d0(a1, 0, *(int*) (a2 + 0x18));
	fcn_004b5440(0xc, &s);
	if (s.count > 0 && s.ratio < 1.0f)
		return fcn_004b52d0(a1, 0, *(int*) (a2 + 0x18));
	fcn_004b5440(0xd, &s);
	if (s.count > 0 && s.ratio < 1.0f)
		return fcn_004b52d0(a1, 0, *(int*) (a2 + 0x18));
	return fcn_004b52d0(a1, *(int*) (a2 + 0x14) <= 3, *(int*) (a2 + 0x18));
}
