int __cdecl fcn_004eb320(char* e);
char* __cdecl fcn_0049fc80(char* e);
int __cdecl fcn_0049fe50(char* e);
int __cdecl fcn_004a0020(char* e);

/* ADDRESS: GOLD 0x004a0890 */
/* ADDRESS: GOLDTL 0x004a02d0 */
int __cdecl fcn_004a02d0(int a1, char* e, int a3, char* out)
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
	if (fcn_004eb320(e) != 1) {
		return 0;
	}
	c = e[0x169];
	if (c == 0x1e) {
		p = fcn_0049fc80(e);
		if (!p) {
			return 0;
		}
		out[0] = 7;
		*(int*) (out + 4) = *(int*) (p + 4);
		*(int*) (out + 0x10) = 1;
		return 0x38;
	}
	if (c == 0x20) {
		r = fcn_0049fe50(e);
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
