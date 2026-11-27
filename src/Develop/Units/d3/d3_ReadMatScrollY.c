typedef struct
{
	char pad0000[0xc9];
	char field;
	char pad00ca[0xe0 - 0xca];
} D3_MAT_CHUNK_REC;
// SIZE 0xe0

typedef struct
{
	int pad000;
	int pad004;
	int n;
	int pad00c;
	D3_MAT_CHUNK_REC* recs;
} D3_MAT_CHUNK_CTX;
// SIZE 0x14

int __cdecl vfs_ReadByte(void* stream, void* dst);

/* ADDRESS: GOLDTL 0x0044dbd0 */
int __cdecl d3_ReadMatScrollY(void* stream, D3_MAT_CHUNK_CTX* c)
{
	return vfs_ReadByte(stream, &c->recs[c->n].field);
}
