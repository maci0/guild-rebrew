


typedef struct
{
	int pad0;
	int pad1;
	int idx;
	int pad2;
	int base;
} F4dRec;
// SIZE 0x14

int __cdecl fcn_00401180(void* stream, void* dst);

void __cdecl fcn_0044db40(void* stream, F4dRec* record)
{
	fcn_00401180(stream, (char*) &stream);
	*(unsigned char*) ((char*) record->base + record->idx * 0xe0 + 0xc4) = *(unsigned char*) &stream & 1;
	*(unsigned char*) ((char*) record->base + record->idx * 0xe0 + 0xc7) = *(unsigned char*) &stream & 0xfe;
}
