// FUNCTION: GOLDTL 0x413190

extern char g_10432c0[];

int __cdecl fcn_00413190(char* p)
{
	int r;

	r = (unsigned int) (p - g_10432c0) / 988;
	if (r < 0 || r > 0x3f) {
		r = -1;
	}
	return r;
}
