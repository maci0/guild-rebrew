extern char* g_entity_type_table;
extern short* g_773da8;

/* ADDRESS: GOLDTL 0x005cfb00 */
unsigned int __cdecl fcn_005cfb00(short* a0, int* a1, unsigned char* a2)
{
	unsigned int hi;
	unsigned int lo;
	unsigned int i;
	unsigned int type;
	int match;
	int accept;
	int inlist;
	short id;
	short other;
	short* q;

	hi = 0;
	lo = 0;
	if (!a1)
		return 1;
	if (!a2)
		return 0;
	if (!a0)
		return 0;
	if (!a1[2] && !a1[3] && !a1[4])
		return 1;
	type = (unsigned char) g_entity_type_table[a2[0] * 0x24d];
	if (type >= 0x20)
		hi = 1 << (type - 0x20);
	else
		lo = 1 << type;
	if (a1[3] < 0) {
		if (a2[0x5a] & 1)
			return 0;
		if (!*(int*) (a2 + 0x61))
			return 0;
	}
	if ((a1[2] & lo) || (a1[3] & hi))
		match = 1;
	else
		match = 0;
	accept = 0;
	inlist = 1;
	id = *(short*) (a2 + 0x27);
	if (a1[4] == 0) {
		accept = 1;
	} else {
		switch (a1[4]) {
		case 0:
			accept = 1;
			break;
		case 1:
			accept = id == -1;
			break;
		case 2:
			accept = id != -1;
			break;
		case 3:
			if (id == *a0 || id == -1) {
				accept = 1;
				break;
			}
			goto zero;
		case 4:
			accept = id == *a0;
			break;
		case 5:
			accept = id != *a0;
			break;
		case 6:
			other = id;
			goto compare;
		case 7:
			other = id;
			if (other == *a0)
				goto zero;
			a0 = g_773da8;
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
	if ((a1[0x14 / 4] & 1) && id != -1) {
		q = (short*) (a1 + 7);
		for (i = 0; i < 4; i++) {
			if (id == q[i] && q[i] != -1) {
				inlist = 0;
				break;
			}
		}
	}
	if (match && accept && inlist)
		return 1;
	return 0;
}
