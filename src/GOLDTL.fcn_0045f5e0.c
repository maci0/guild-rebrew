int __cdecl gzread(void* file, void* buf, unsigned len);

// FUNCTION: GOLDTL 0x45f5e0
// SIZE: 79
char* __cdecl fcn_0045f5e0(void* file, char* buf, int len)
{
	char* b = buf;

	if (buf == 0 || len <= 0) {
		return 0;
	}
	while (--len > 0 && gzread(file, buf, 1) == 1 && *buf++ != '\n') {
	}
	*buf = '\0';
	return b == buf && len > 0 ? 0 : b;
}
