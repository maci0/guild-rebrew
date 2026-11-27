

// for slots: if([p]!=0xffff) ai_UpdateEntityDrives(p).

void __cdecl ai_UpdateEntityDrives(int);

void __cdecl ai_UpdateAllEntityDrives(void)
{
	int p;
	for (p = 0x7f4ca0; p < 0x85a0a0; p += 0x21c) {
		if (*(unsigned short*) p != 0xffff) {
			ai_UpdateEntityDrives(p);
		}
	}
}
