typedef struct {
	char pad00[0xc];
	int f0c;
	char pad10[8];
	int n;
	char pad1c[4];
	char* recs;
} Ctx_44de70;

typedef struct {
	char pad00[0x24];
	int f24;
	int f28;
	char pad2c[0xc];
} Rec_44de70;

int __cdecl fcn_004011f0(void* stream, void* dst);
char* __cdecl fcn_00401180(void* stream, void* dst);

/* ADDRESS: GOLDTL 0x0044de70 */
void __cdecl fcn_0044de70(void* stream, Ctx_44de70* c)
{
	unsigned char b;

	((Rec_44de70*) c->recs)[c->n].f24 = -1;
	if (c->f0c > 0xfe) {
		fcn_004011f0(stream, &((Rec_44de70*) c->recs)[c->n].f28);
		c->n++;
		return;
	}
	fcn_00401180(stream, &b);
	if (b == 0xff) {
		((Rec_44de70*) c->recs)[c->n].f28 = -1;
		c->n++;
		return;
	}
	((Rec_44de70*) c->recs)[c->n].f28 = b;
	c->n++;
}
