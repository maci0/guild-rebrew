
// fcn_004cec00 — for slots: if(*p!=-1){ fcn_00472cd0(*p); *p=-1; }.

int __cdecl d2_CloseWindowGold(int);

void __cdecl d2_ClearHudWinSlots(void)
{
	int p;
	for (p = 0x935d20; p < 0x935da0; p += 4) {
		if (*(int*) p != -1) {
			d2_CloseWindowGold(*(int*) p);
			*(int*) p = 0xffffffff;
		}
	}
}
