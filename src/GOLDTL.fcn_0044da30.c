typedef struct
{
	char pad00[0xc0];
	char fc0;
	char padc1[0xe0 - 0xc1];
} fcn_0044da30_Rec;
// SIZE 0xe0

typedef struct
{
	int pad00[2];
	int n;
	int pad0c;
	fcn_0044da30_Rec* recs;
} fcn_0044da30_Ctx;
// SIZE 0x14

void __cdecl fcn_00401180(void* stream, void* dst);

/* ADDRESS: GOLD 0x0044f100 */
/* ADDRESS: GOLDTL 0x0044da30 */
void __cdecl fcn_0044da30(void* stream, fcn_0044da30_Ctx* c)
{
	fcn_00401180(stream, &c->recs[c->n].fc0);
}
