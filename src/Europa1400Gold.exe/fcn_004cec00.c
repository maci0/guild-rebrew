// FUNCTION: GOLD 0x004cec00
// SIZE: 41
// fcn_004cec00 — for slots: if(*p!=-1){ fcn_00472cd0(*p); *p=-1; }.

int __cdecl fcn_00472cd0(int);

void __cdecl fcn_004cec00(void)
{
	int p;
	for (p = 0x935d20; p < 0x935da0; p += 4) {
		if (*(int*) p != -1) {
			fcn_00472cd0(*(int*) p);
			*(int*) p = 0xffffffff;
		}
	}
}
