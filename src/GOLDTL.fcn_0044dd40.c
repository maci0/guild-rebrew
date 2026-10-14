

// SIZE 0x38
typedef struct Face {
	int pad[6];
	int idx[3];
	int rest[5];
} Face;

void __cdecl fcn_004011f0(int, void*);

void __cdecl fcn_0044dd40(int r, char* o)
{
	int t;

	fcn_004011f0(r, &t);
	(*(Face**) (o + 0x20))[*(int*) (o + 0x18)].idx[0] = *(int*) (o + 0x2c) + t;
	fcn_004011f0(r, &t);
	(*(Face**) (o + 0x20))[*(int*) (o + 0x18)].idx[1] = *(int*) (o + 0x2c) + t;
	fcn_004011f0(r, &t);
	(*(Face**) (o + 0x20))[*(int*) (o + 0x18)].idx[2] = *(int*) (o + 0x2c) + t;
}
