// FUNCTION: GOLDTL 0x445d60

// SIZE 0x38
typedef struct Rec {
	int v[14];
} Rec;

char __cdecl fcn_00445d60(char* o, int i)
{
	if (i >= 0 && i < 7 && *(Rec**) (o + 0x1e8) != 0) {
		(*(Rec**) (o + 0x1e8))[i].v[10] = *(int*) (o + 0x90);
		(*(Rec**) (o + 0x1e8))[i].v[9] = *(int*) (o + 0x94);
		(*(Rec**) (o + 0x1e8))[i].v[11] = *(int*) (o + 0x98);
		(*(Rec**) (o + 0x1e8))[i].v[0] = *(int*) (o + 0x4c);
		(*(Rec**) (o + 0x1e8))[i].v[1] = *(int*) (o + 0x50);
		(*(Rec**) (o + 0x1e8))[i].v[2] = *(int*) (o + 0x54);
		(*(Rec**) (o + 0x1e8))[i].v[6] = *(int*) (o + 0x5c);
		(*(Rec**) (o + 0x1e8))[i].v[7] = *(int*) (o + 0x60);
		(*(Rec**) (o + 0x1e8))[i].v[8] = *(int*) (o + 0x64);
		(*(Rec**) (o + 0x1e8))[i].v[3] = *(int*) (o + 0x84);
		(*(Rec**) (o + 0x1e8))[i].v[4] = *(int*) (o + 0x88);
		(*(Rec**) (o + 0x1e8))[i].v[5] = *(int*) (o + 0x8c);
	}
	return 1;
}
