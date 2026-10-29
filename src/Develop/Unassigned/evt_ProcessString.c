int __cdecl strchr_64e790(char* s, int c);
void __cdecl memcpy_64d530(void* d, void* s, unsigned int n);
void __cdecl fcn_00425bf0(char* s, int a, char* fmt);

/* ADDRESS: GOLDTL 0x00427000 */
int __cdecl evt_ProcessString(char* msg, char* src, char* dst)
{
	char* quote;
	char* semi;
	unsigned int n;

	quote = strchr_64e790(src, 0x22);
	semi = strchr_64e790(src, 0x3b);
	if (quote != 0) {
		if ((unsigned int) semi < (unsigned int) quote) {
			fcn_00425bf0(msg, 0, (char*) 0x6793a4);
			return 0;
		}
	}
	n = (unsigned int) (quote - src);
	memcpy_64d530(dst, src, n);
	dst[n] = 0;
	return (int) (quote + 1);
}
