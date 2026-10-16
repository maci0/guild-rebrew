int __cdecl fcn_005de7a2(char *buf, char *fmt, int arg);
char __cdecl fcn_0044be60(char *buf, int a, int b);
void __cdecl fcn_00438e60(int obj, int a, int b, int cb);

/* ADDRESS: GOLD 0x0050d6d0 */
char __cdecl fcn_0050d6d0(int name)
{
	char buf[256];

	fcn_005de7a2(buf, (char *)0x622ed4, name);
	if (fcn_0044be60(buf, 0, 0) == 0)
		return 0;
	fcn_00438e60(*(int *)0x5fb5b0, 0, 6, 0x50d730);
	return 1;
}
