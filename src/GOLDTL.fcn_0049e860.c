int __cdecl fcn_004ab0d0(char* e, char* a, char* b);
int __cdecl fcn_004ab3e0(char* e, char* a, char* b);
void __cdecl fcn_004c5420(int id, int a2, int a3, int a4, int a5);

/* ADDRESS: GOLD 0x0049ee20 */
/* ADDRESS: GOLDTL 0x0049e860 */
int __cdecl fcn_0049e860(char* e, char* a, char* b)
{
	if (a[0] == 4 && b[0] == 1) {
		if (fcn_004ab0d0(e, a, b)) {
			return 0x32;
		}
	} else if (a[0] == 0x13 && b[0] == 4) {
		fcn_004c5420(*(int*) (e + 4), 0x1cc, 4, 0x2000000, 0);
		if (fcn_004ab3e0(e, a, b)) {
			return 0x32;
		}
	} else if (a[0] == 0) {
		fcn_004c5420(*(int*) (e + 4), 0x1cc, 4, 0x2000000, 0);
		return 0x32;
	}
	return 0;
}
