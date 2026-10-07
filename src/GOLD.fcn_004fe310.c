// FUNCTION: GOLD 0x004fe310
// fcn_004fe310 — fcn_004fe140(d, c, b, a) (reads [esp+c]=b,[esp+10]=c,[esp+14]=d).

int __cdecl fcn_004fe140(int, int, int, int);

void __cdecl fcn_004fe310(int a, int b, int c, int d)
{
	fcn_004fe140(d, c, b, a);
}
