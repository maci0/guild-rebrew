// FUNCTION: GOLDTL 0x4308a0
// SIZE: 111

int __cdecl fcn_00430870(void*);

char* __cdecl fcn_004308a0(char* buf, int max, void* fp)
{
	int c;
	char* p;
	int i;

	c = fcn_00430870(fp);
	if (c == -1) {
		return 0;
	}
	p = buf;
	i = 0;
	while (c != '\r' && c != '\n' && c != -1 && i < max) {
		*p++ = (char) c;
		i++;
		c = fcn_00430870(fp);
	}
	*p = 0;
	if (c != -1) {
		while (c == '\r' || c == '\n') {
			c = fcn_00430870(fp);
		}
	}
	return buf;
}
