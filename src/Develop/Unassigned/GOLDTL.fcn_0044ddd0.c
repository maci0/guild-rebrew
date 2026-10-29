


// SIZE 0x38
typedef struct Face {
	float uv[3][2];
	int idx[3];
	int rest[5];
} Face;

int __cdecl fcn_004011d0(void* stream, void* dst);

void __cdecl fcn_0044ddd0(void* r, char* o)
{
	float t;
	int i;

	for (i = 0; i < 3; i++) {
		fcn_004011d0(r, &(*(Face**) (o + 0x20))[*(int*) (o + 0x18)].uv[i][0]);
	}
	for (i = 0; i < 3; i++) {
		fcn_004011d0(r, &(*(Face**) (o + 0x20))[*(int*) (o + 0x18)].uv[i][1]);
	}
	for (i = 0; i < 3; i++) {
		fcn_004011d0(r, &t);
	}
}
