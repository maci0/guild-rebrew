


typedef struct
{
	int pad0;
	int pad1;
	int idx;
	int pad2;
	int base;
} F4dRec;
// SIZE 0x14

int __cdecl vfs_ReadByte(void* stream, void* dst);

void __cdecl d3_ReadMatFlags(void* stream, F4dRec* record)
{
	vfs_ReadByte(stream, (char*) &stream);
	*(unsigned char*) ((char*) record->base + record->idx * 0xe0 + 0xc4) = *(unsigned char*) &stream & 1;
	*(unsigned char*) ((char*) record->base + record->idx * 0xe0 + 0xc7) = *(unsigned char*) &stream & 0xfe;
}
