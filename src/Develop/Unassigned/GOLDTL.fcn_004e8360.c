/* Office slot reassignment: validates the requesting entity, resolves the
 * slot by its byte id in the 42-entry office table, detaches the slot's former
 * occupant from its role flags, then rebinds the slot to the new entity. */

typedef struct
{
	unsigned char f00;      /* +0x00 slot / role id */
	char pad01[3];
	int f04;                /* +0x04 occupying entity id, -1 when free */
	unsigned char f08;      /* +0x08 role kind */
	char pad09[3];
	int f0c;                /* +0x0c pending count */
	unsigned char f10;      /* +0x10 status */
	char pad11[3];
	int f14;                /* +0x14 setter entity id */
} Rec18;
// SIZE 0x18

char* __cdecl fcn_00508e40(int id);
void __cdecl fcn_005b2280(void* a1, void* a2);

/* ADDRESS: GOLDTL 0x004e8360 */
int __cdecl fcn_004e8360(char* a0)
{
	char* ent;
	char* setter;
	char* x;
	unsigned char* p;
	unsigned int v;
	unsigned int bit;
	int other;
	int i;
	int k;
	int* ip;

	other = -1;
	setter = 0;
	if (*(int*) (a0 + 7) != -1) {
		setter = fcn_00508e40(*(int*) (a0 + 7));
		if (setter == 0)
			return 0;
	}
	ent = 0;
	if (*(int*) (a0 + 1) != -1) {
		ent = fcn_00508e40(*(int*) (a0 + 1));
		if (ent == 0)
			return 0;
		other = *(int*) (ent + 4);
	}
	p = (unsigned char*) 0x9a9220;
	i = 0;
	while (*p != *(unsigned char*) a0) {
		p += 0x18;
		i++;
		if ((int) p >= (int) 0x9a9610)
			return 0;
	}
	if (i >= 0x2a)
		return 0;
	x = fcn_00508e40(((Rec18*) (0x9a9220 + i * 0x18))->f04);
	if (x != 0 && *(int*) (x + 4) != *(int*) (a0 + 1)) {
		bit = ((Rec18*) (0x9a9220 + i * 0x18))->f08;
		if (*(unsigned char*) (x + 0x166) != (unsigned char) bit) {
			if (*(unsigned char*) (x + 0x169) != (unsigned char) bit) {
				if (bit == '#') {
					*(int*) (x + 0x1cc) &= 0xfffffdff;
				} else if (bit == '$') {
					*(int*) (x + 0x1cc) &= 0xfffffbff;
				} else if (bit == '%') {
					*(int*) (x + 0x1cc) &= 0xfffff7ff;
				}
			} else {
				*(unsigned char*) (x + 0x169) = 0;
			}
		} else {
			*(unsigned char*) (x + 0x166) = 0;
		}
	}
	if (ent == 0)
		goto tail;
	v = ((Rec18*) (0x9a9220 + i * 0x18))->f08;
	if ((int) v > 0x1b) {
		if (v >= 0x1c && v <= 0x22) {
			if (*(unsigned char*) (ent + 0x169) != 0) {
				p = (unsigned char*) 0x9a94f4;
				do {
					if (*(unsigned char*) (p + 4) == *(unsigned char*) (ent + 0x169) &&
					    *(int*) p == *(int*) (ent + 4))
						*(int*) p = -1;
					p += 0x18;
				} while ((int) p < (int) 0x9a959c);
			}
			*(unsigned char*) (ent + 0x169) = (unsigned char) v;
			goto tail;
		}
		bit = *(int*) (ent + 0x1cc) & 0xfffff1ff;
		*(int*) (ent + 0x1cc) = bit;
		k = 0;
		if (v == '#') {
			bit |= 0x200;
			k = 0x4000;
		} else if (v == '$') {
			bit |= 0x400;
			k = 0x8000;
		} else if (v == '%') {
			bit |= 0x800;
			k = 0x10000;
		}
		if (k != 0)
			*(int*) (ent + 0x1cc) = bit;
		for (ip = (int*) 0x7f4e6c; (int) ip < (int) 0x85a26c; ip = (int*) ((char*) ip + 0x21c))
			*ip &= ~k;
		goto tail;
	}
	if (*(unsigned char*) (ent + 0x166) != 0) {
		k = 0;
		ip = (int*) 0x9a9224;
		do {
			if (*ip == other) {
				((Rec18*) (0x9a9220 + k * 0x18))->f04 = -1;
				((Rec18*) (0x9a9220 + k * 0x18))->f14 = -1;
				((Rec18*) (0x9a9220 + k * 0x18))->f10 = 4;
				((Rec18*) (0x9a9220 + k * 0x18))->f0c = 0;
				break;
			}
			ip = (int*) ((char*) ip + 0x18);
			k++;
		} while ((int) ip < (int) 0x9a94f4);
	}
	if (*(unsigned char*) (0x68da70 + *(unsigned char*) (ent + 0x166) * 0x18) <=
	    *(unsigned char*) (0x68da70 + v * 0x18))
		*(unsigned char*) (ent + 0x167) = (unsigned char) v;
	bit = *(unsigned char*) (ent + 0x168);
	*(unsigned char*) (ent + 0x166) = (unsigned char) v;
	if (bit == v)
		*(unsigned char*) (ent + 0x168) = 0;
	if (v == 0x0f) {
		*(int*) (ent + 0x1cc) |= 0x40;
	} else if (v == 0x15) {
		*(int*) (ent + 0x1cc) |= 0x80;
	} else if (v == 0x1b) {
		*(int*) (ent + 0x1cc) |= 0x100;
	}
	if (*(int*) (0x68da78 + v * 0x18) != 0) {
		k = 0;
		p = (unsigned char*) 0x9a9228;
		do {
			if (*(unsigned char*) p == (unsigned char) v && k != i) {
				if (((Rec18*) (0x9a9220 + k * 0x18))->f10 == 3 &&
				    ((Rec18*) (0x9a9220 + k * 0x18))->f0c != 0) {
					((Rec18*) (0x9a9220 + k * 0x18))->f0c =
						((Rec18*) (0x9a9220 + k * 0x18))->f0c - 1;
					if (((Rec18*) (0x9a9220 + k * 0x18))->f0c == 0)
						((Rec18*) (0x9a9220 + k * 0x18))->f10 = 4;
				}
				break;
			}
			p += 0x18;
			k++;
		} while ((int) p < (int) 0x9a94f8);
	}
tail:
	((Rec18*) (0x9a9220 + i * 0x18))->f04 = other;
	((Rec18*) (0x9a9220 + i * 0x18))->f14 = *(int*) (a0 + 7);
	((Rec18*) (0x9a9220 + i * 0x18))->f10 = *(unsigned char*) (a0 + 5);
	if (*(unsigned char*) (a0 + 5) == 3)
		((Rec18*) (0x9a9220 + i * 0x18))->f0c = 0;
	if (setter != 0 && ent != 0 &&
	    *(int*) (0x7f4ca4 + *(unsigned short*) 0x774970 * 0x21c) == *(int*) (ent + 4))
		fcn_005b2280(setter, ent);
	return 1;
}
