int __cdecl fcn_0045f7d0(char* s, int flush);
void __cdecl fcn_0045fb30(void* file, unsigned long x);
int __cdecl fcn_0045f2c0(char* s);

// FUNCTION: GOLD 0x4636c0
// FUNCTION: GOLDTL 0x45fae0
int __cdecl fcn_0045fae0(char* s)
{
	int err;

	if (s == 0) {
		return -2;
	}
	if (s[0x5c] == 'w') {
		err = fcn_0045f7d0(s, 4);
		if (err == 0) {
			fcn_0045fb30(*(void**) (s + 0x40), *(unsigned long*) (s + 0x4c));
			fcn_0045fb30(*(void**) (s + 0x40), *(unsigned long*) (s + 8));
		}
	}
	return fcn_0045f2c0(s);
}
