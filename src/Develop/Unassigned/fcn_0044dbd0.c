typedef struct
{
	char pad0000[0xc9];
	char field;
	char pad00ca[0xe0 - 0xca];
} fcn_0044dbd0_Rec;
// SIZE 0xe0

typedef struct
{
	int pad000;
	int pad004;
	int n;
	int pad00c;
	fcn_0044dbd0_Rec* recs;
} fcn_0044dbd0_Ctx;
// SIZE 0x14

int __cdecl fcn_00401180(void* stream, void* dst);

/* ADDRESS: GOLDTL 0x0044dbd0 */
int __cdecl fcn_0044dbd0(void* stream, fcn_0044dbd0_Ctx* c)
{
	return fcn_00401180(stream, &c->recs[c->n].field);
}
