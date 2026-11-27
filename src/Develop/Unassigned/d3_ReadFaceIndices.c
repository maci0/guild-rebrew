

// SIZE 0x38
typedef struct Face {
	int pad[6];
	int idx[3];
	int rest[5];
} Face;

int __cdecl fcn_004011f0(void* stream, void* dst);

void __cdecl d3_ReadFaceIndices(void* stream, char* ctx)
{
	int t;

	fcn_004011f0(stream, &t);
	(*(Face**) (ctx + 0x20))[*(int*) (ctx + 0x18)].idx[0] = *(int*) (ctx + 0x2c) + t;
	fcn_004011f0(stream, &t);
	(*(Face**) (ctx + 0x20))[*(int*) (ctx + 0x18)].idx[1] = *(int*) (ctx + 0x2c) + t;
	fcn_004011f0(stream, &t);
	(*(Face**) (ctx + 0x20))[*(int*) (ctx + 0x18)].idx[2] = *(int*) (ctx + 0x2c) + t;
}
