/* ADDRESS: GOLDTL 0x004f1890 */
extern char g_4f1890[];



int __cdecl fcn_004f18d0(int*, int, int, void*, int);

int __cdecl fcn_004f1a10(int a1, int* a2)
{
	if (a2 == 0 || *a2 == -1) {
		return 0;
	}
	return fcn_004f18d0(a2, a1, 0, g_4f1890, 0xff);
}
