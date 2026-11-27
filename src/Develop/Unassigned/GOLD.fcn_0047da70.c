
// for slots: if([p]!=0xffff) ai_UpdateEntityDrives(p).

void __cdecl ai_UpdateEntityDrives(int);

void __cdecl fcn_0047da70(void)
{
	int p;
	for (p = 0x770b80; p < 0x7d5f80; p += 0x21c) {
		if (*(unsigned short*) p != 0xffff) {
			ai_UpdateEntityDrives(p);
		}
	}
}
