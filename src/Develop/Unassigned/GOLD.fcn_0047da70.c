
// fcn_0047da70 — for slots: if([p]!=0xffff) fcn_0047daa0(p).

void __cdecl fcn_0047daa0(int);

void __cdecl fcn_0047da70(void)
{
	int p;
	for (p = 0x770b80; p < 0x7d5f80; p += 0x21c) {
		if (*(unsigned short*) p != 0xffff) {
			fcn_0047daa0(p);
		}
	}
}
