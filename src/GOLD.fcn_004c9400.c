int __cdecl fcn_004e6a30(int);
int __cdecl fcn_004e6bd0(int, int);

/* ADDRESS: GOLD 0x004c9400 */
int __cdecl fcn_004c9400(int *s, unsigned char *flag)
{
	if (fcn_004e6a30(s[4]) == 0)
		return 1;
	if (fcn_004e6bd0(s[4], s[5]) == 0)
		return 1;
	if (flag != 0)
		*flag = 1;
	return 0;
}
