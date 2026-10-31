int __cdecl io_FormatTextBuffer(void *buf, int len);
int __cdecl fcn_005cad70(char *a0, char *a1);
int __cdecl gm_LookupEntityRecordById(int value);
int __cdecl fcn_005dcf40(unsigned char *e, int idx);

/* ADDRESS: GOLDTL 0x005dd130 */
int __cdecl fcn_005dd130(char *a0, int *a1)
{
	char buf[0x100];
	int r;

	if (a0[2] == 6) {
		io_FormatTextBuffer(buf, 0x9d);
		r = fcn_005cad70(a0, buf);
	} else {
		r = gm_LookupEntityRecordById(a1[1]);
	}
	if (r != 0) {
		fcn_005dcf40((unsigned char *) r, 4);
		return 1;
	}
	return 0;
}
