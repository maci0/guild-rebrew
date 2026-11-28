char* __cdecl fcn_00503fe0(int a, int b, int c);

/* ADDRESS: GOLDTL 0x0057f100 */
/* ADDRESS: GOLDDE 0x00564ed0 */
void __cdecl d2_InitTutCh2RathausStep(void* mode)
{
	char* r;

	if (mode == 0) {
		r = fcn_00503fe0(1, 5, 0xf);
		if (r != 0) {
			*(unsigned short*) (r + 0x29) = 0x10e;
		}
	}
}
