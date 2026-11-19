extern unsigned char* lpGebaeudePROT;
extern short* gm_CityEntity;

/* ADDRESS: GOLDTL 0x005cfb00 */
unsigned int __cdecl fcn_005cfb00(short* a0, int* filterSpec, unsigned char* gebaeude)
{
	unsigned int hi;
	unsigned int lo;
	int i;
	unsigned char type;
	int match;
	int accept;
	int inlist;

	short other;
	short* q;

	hi = 0;
	if (!filterSpec)
		return 1;
	if (!gebaeude)
		return 0;
	if (!a0)
		return 0;
	if (!filterSpec[2] && !filterSpec[3] && !filterSpec[4])
		return 1;
	type = (unsigned char) lpGebaeudePROT[gebaeude[0] * 0x24d];
	lo = 0;
	if (type > 0x1f)
		hi = 1u << ((type - 0x20) & 0x1f);
	else
		lo = 1u << (type & 0x1f);
	if (filterSpec[3] < 0) {
		if (gebaeude[0x5a] & 1)
			return 0;
		if (!*(int*) (gebaeude + 0x61))
			return 0;
	}
	if ((filterSpec[2] & lo) || (filterSpec[3] & hi))
		match = 1;
	else
		match = 0;
	accept = 0;
	inlist = 1;

	if (filterSpec[4] == 0) {
		accept = 1;
	} else {
		switch (filterSpec[4]) {
		case 0:
			accept = 1;
			break;
		case 1:
			accept = *(unsigned short*) (gebaeude + 0x27) == 0xffff;
			break;
		case 2:
			accept = *(unsigned short*) (gebaeude + 0x27) != 0xffff;
			break;
		case 3:
			if ((*(short*) (gebaeude + 0x27)) == *a0 || *(unsigned short*) (gebaeude + 0x27) == 0xffff) {
				accept = 1;
				break;
			}
			goto zero;
		case 4:
			accept = (*(short*) (gebaeude + 0x27)) == *a0;
			break;
		case 5:
			accept = (*(short*) (gebaeude + 0x27)) != *a0;
			break;
		case 6:
			other = (*(short*) (gebaeude + 0x27));
			goto compare;
		case 7:
			other = (*(short*) (gebaeude + 0x27));
			if (other == *a0)
				goto zero;
			a0 = gm_CityEntity;
		compare:
			if (other != *a0 && other != -1) {
				accept = 1;
				break;
			}
		zero:
			accept = 0;
			break;
		}
	}
	if ((filterSpec[0x14 / 4] & 1) && *(unsigned short*) (gebaeude + 0x27) != 0xffff) {
		q = (short*) (filterSpec + 7);
		for (i = 0; i < 4; i++, q++) {
			if ((*(short*) (gebaeude + 0x27)) == *q && *q != -1) {
				inlist = 0;
				break;
			}
		}
	}
	if (match && accept && inlist)
		return 1;
	return 0;
}
