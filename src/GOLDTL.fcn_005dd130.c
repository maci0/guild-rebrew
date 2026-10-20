int __cdecl fcn_0051af00(void *buf, int len);
int __cdecl fcn_005cad70(char *a0, char *a1);
int __cdecl fcn_00508e40(int value);
int __cdecl fcn_005dcf40(unsigned char *e, int idx);

/* ADDRESS: GOLDTL 0x005dd130 */
int __cdecl fcn_005dd130(char *a0, int *a1)
{
	char buf[0x100];
	int r;

	if (a0[2] == 6) {
		fcn_0051af00(buf, 0x9d);
		r = fcn_005cad70(a0, buf);
	} else {
		r = fcn_00508e40(a1[1]);
	}
	if (r != 0) {
		fcn_005dcf40((unsigned char *) r, 4);
		return 1;
	}
	return 0;
}
