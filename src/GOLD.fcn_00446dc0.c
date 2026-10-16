void __cdecl fcn_00441db0(int);
void __cdecl fcn_00441ea0(int);
void __cdecl fcn_00441860(int);

/* ADDRESS: GOLD 0x00446dc0 */
void __cdecl fcn_00446dc0(int obj, unsigned char tag, unsigned char flag)
{
	unsigned char cur;

	cur = *(unsigned char *)(obj + 0x1c71);
	if ((cur & 0xf) != tag) {
		fcn_00441db0(obj);
		cur = *(unsigned char *)(obj + 0x1c71);
		*(unsigned char *)(obj + 0x1c71) = (unsigned char)((cur & ~0xf) | (tag & 0xf));
		fcn_00441ea0(obj);
		if (flag)
			fcn_00441860(obj);
	}
}
