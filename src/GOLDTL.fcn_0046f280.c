/* ADDRESS: GOLDTL 0x010161d0 */
extern char g_10161d0[];
/* ADDRESS: GOLDTL 0x010161bc */
extern char g_10161bc[];


void __cdecl fcn_0046b2b0(int);

int __cdecl fcn_0046f280(int a1)
{
	char* p;

	p = g_10161d0 + a1 * 0x3cc;
	if (*(int*) p != 0) {
		fcn_0046b2b0(*(int*) (g_10161bc + a1 * 0x3cc));
		return 1;
	}
	return 0;
}
