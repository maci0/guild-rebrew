typedef struct
{
	char pad00[0xc8];
	char fc8;
	char padc9[0xe0 - 0xc9];
} fcn_0044dba0_Rec;
// SIZE 0xe0

typedef struct
{
	int pad00[2];
	int n;
	int pad0c;
	fcn_0044dba0_Rec* recs;
} fcn_0044dba0_Ctx;
// SIZE 0x14

int __cdecl vfs_ReadByte(void* stream, void* dst);

/* ADDRESS: GOLDTL 0x0044dba0 */
void __cdecl fcn_0044dba0(void* stream, fcn_0044dba0_Ctx* c)
{
	vfs_ReadByte(stream, &c->recs[c->n].fc8);
}
