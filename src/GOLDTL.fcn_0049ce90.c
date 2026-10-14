int __cdecl fcn_004aac00(char*, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);

/* ADDRESS: GOLD 0x0049d450 */
/* ADDRESS: GOLDTL 0x0049ce90 */

int __cdecl fcn_0049ce90(char* a, int b, int c)
{
	if (fcn_004aac00(a, b, c) != 0) {
		fcn_004c5420(*(int*) (a + 4), 0x1e8, 4, 0x200, 0);
		return 0x2a;
	}
	return 0;
}
