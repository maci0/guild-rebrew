int __cdecl hst_ParseText_Fake_1st_Pass(int, int);
int __cdecl hst_ParseText_Fake_2nd_Pass(int, int);
void __cdecl hst_ParseCommandline_2nd_Pass(int);


/* ADDRESS: GOLDTL 0x004b2dd0 */
int __cdecl fcn_004b2dd0(int a, int b, int c)
{
	if (hst_ParseText_Fake_1st_Pass(a, b + 1) == 0)
		return 0;
	b += 2;
	if (hst_ParseText_Fake_2nd_Pass(a, b) == 0)
		return 0;
	if (c != 0)
		hst_ParseCommandline_2nd_Pass(b);
	return 1;
}
