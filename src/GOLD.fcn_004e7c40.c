// FUNCTION: GOLD 0x004e7c40
// fcn_004e7c40 — fcn_004e6f80(a, buf); return (unsigned char)buf[8].

int __cdecl fcn_004e6f80(void*, void*);

int __cdecl fcn_004e7c40(void* a)
{
	char buf[0x18];
	fcn_004e6f80(a, buf);
	return (unsigned char) buf[8];
}
