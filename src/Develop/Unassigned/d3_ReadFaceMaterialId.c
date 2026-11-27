typedef struct {
	char pad00[0xc];
	int f0c;
	char pad10[8];
	int n;
	char pad1c[4];
	char* recs;
} D3_MESH_STREAM_CTX;

typedef struct {
	char pad00[0x24];
	int f24;
	int f28;
	char pad2c[0xc];
} D3_FACE_MAT_REC;

int __cdecl fcn_004011f0(void* stream, void* dst);
char* __cdecl vfs_ReadByte(void* stream, void* dst);

/* ADDRESS: GOLDTL 0x0044de70 */
void __cdecl d3_ReadFaceMaterialId(void* stream, D3_MESH_STREAM_CTX* c)
{
	unsigned char b;

	((D3_FACE_MAT_REC*) c->recs)[c->n].f24 = -1;
	if (c->f0c > 0xfe) {
		fcn_004011f0(stream, &((D3_FACE_MAT_REC*) c->recs)[c->n].f28);
		c->n++;
		return;
	}
	vfs_ReadByte(stream, &b);
	if (b == 0xff) {
		((D3_FACE_MAT_REC*) c->recs)[c->n].f28 = -1;
		c->n++;
		return;
	}
	((D3_FACE_MAT_REC*) c->recs)[c->n].f28 = b;
	c->n++;
}
