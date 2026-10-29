char* __cdecl fcn_00503fe0(int a, int b, int c);

/* ADDRESS: GOLDTL 0x0057f100 */
void __cdecl fcn_0057f100(void* a1)
{
	char* r;

	if (a1 == 0) {
		r = fcn_00503fe0(1, 5, 0xf);
		if (r != 0) {
			*(unsigned short*) (r + 0x29) = 0x10e;
		}
	}
}
