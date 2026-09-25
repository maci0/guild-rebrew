// FUNCTION: GOLDTL 0x004f1a40
// SIZE: 130
// FUNCTION: GOLD 0x004ef930
// SIZE: 144

typedef struct
{
	int id;
	char pad[0x40];
} Rec44;
// SIZE 0x44

extern unsigned char* g_868050;

int __cdecl fcn_004f1320(unsigned char* e);
unsigned short __cdecl fcn_0042e410(unsigned short n);

Rec44* __cdecl fcn_004f1a40(unsigned char* e)
{
	unsigned char* ent;
	char* d;
	Rec44* recs;
	int n;
	int k;
	int idx;

	ent = g_868050 + *e * 0x24d;
	d = *(char**) (e + 0x65);
	if (ent[0] == 0x1d && ent[0x247] >= 1 && ent[0x247] <= 3) {
		n = fcn_004f1320(e);
		idx = fcn_0042e410((unsigned short) n);
		k = n;
		if (k != 0) {
			recs = *(Rec44**) (d + 0x20);
			while (k != 0) {
				if (recs[idx].id != -1) {
					return &recs[idx];
				}
				k--;
				idx = (idx + 1) % n;
			}
		}
	}
	return 0;
}
