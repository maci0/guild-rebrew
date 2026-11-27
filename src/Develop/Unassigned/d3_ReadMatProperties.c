typedef struct
{
	int pad0;
	int pad1;
	int idx;
	int pad2;
	int base;
} F4dRec;

int __cdecl vfs_ReadByte(void* stream, void* dst);

/* ADDRESS: GOLDTL 0x0044da90 */
void __cdecl d3_ReadMatProperties(void* stream, F4dRec* r)
{
	vfs_ReadByte(stream, &stream);
	*(unsigned char*) ((char*) r->base + r->idx * 0xe0 + 0xc2) = *(unsigned char*) &stream & 1;
	*(unsigned char*) ((char*) r->base + r->idx * 0xe0 + 0xc5) = (*(unsigned char*) &stream >> 1) & 1;
	*(unsigned char*) ((char*) r->base + r->idx * 0xe0 + 0xc6) = (*(unsigned char*) &stream >> 2) & 0xf;
	*(unsigned char*) ((char*) r->base + r->idx * 0xe0 + 0xc3) = (*(unsigned char*) &stream >> 6) & 1;
}
