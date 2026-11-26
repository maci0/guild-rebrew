extern double g_662908;

unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_00508220(int, int*);
void __cdecl cm_BeginPacketFieldDelta(unsigned short*, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
float __cdecl fcn_004ff210(unsigned short, int);
int __cdecl _ftol(void);

typedef struct {
	unsigned int b0 : 14;
	unsigned int b14 : 3;
	unsigned int b17 : 3;
	unsigned int b20 : 3;
	unsigned int b23 : 2;
} Flags5086f0;

/* Picks the first free animation slot from a random start, updates the four
 * packed flags fields for the chosen slot and hands the record to the pool. */
/* ADDRESS: GOLDTL 0x005086f0 */
unsigned int __cdecl fcn_005086f0(unsigned short* objectContext)
{
	int ids[4];
	int avail[4];
	Flags5086f0 flags;
	Flags5086f0 v;
	int id;
	int i;
	int n;
	int value;

	avail[0] = 0;
	avail[1] = 0;
	avail[2] = 0;
	avail[3] = 0;
	ids[0] = 5;
	ids[1] = 6;
	ids[2] = 7;
	ids[3] = 8;
	flags = *(Flags5086f0*) ((char*) objectContext + 0x2c);
	if (flags.b14 == 0) {
		avail[0] = 1;
	}
	if (flags.b17 == 0) {
		avail[1] = 1;
	}
	if (flags.b20 == 0) {
		avail[2] = 1;
	}
	if (flags.b23 == 0) {
		avail[3] = 1;
	}
	i = gm_RandomMod(4) & 0xffff;
	n = 4;
	while (1) {
		if (avail[i] == 1) {
			break;
		}
		n--;
		i = (i + 1) % 4;
		if (n == 0) {
			return 0;
		}
	}
	if (i == -1) {
		return 0;
	}
	id = ids[i];
	if (fcn_00508220(id, avail) == 0) {
		return 0;
	}
	value = gm_RandomMod((int) ((double) (unsigned int) avail[2] * 0.5)) & 0xffff;
	if (value == 0) {
		return 0;
	}
	n = (int) ((float) value * *(float*) &avail[1]);
	flags = *(Flags5086f0*) ((char*) objectContext + 0x2c);
	if (id == 5) {
		flags.b23 = value;
	} else if (id == 6) {
		flags.b17 = value;
	} else if (id == 7) {
		flags.b20 = value;
	} else if (id == 8) {
		flags.b23 = value;
	}
	v = flags;
	cm_BeginPacketFieldDelta(objectContext, *(int*) ((char*) objectContext + 4));
	cm_AppendPacketFieldDelta(4, 1, 0x2c, &v);
	cm_RequestChangeAttribute();
	fcn_004ff210(*objectContext, -n);
	return id;
}
