// FUNCTION: GOLD 0x005af310
// fcn_005af310 — forwards arg to fcn_005af320 with a 4-byte flag.

int __cdecl fcn_005af320(void*, int);

int __cdecl fcn_005af310(void* a)
{
	return fcn_005af320(a, 4);
}
