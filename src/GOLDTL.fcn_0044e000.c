


// SIZE 0x18
typedef struct Vert {
	float x;
	float y;
	float z;
	float rest[3];
} Vert;

void __cdecl fcn_004011d0(int, void*);

void __cdecl fcn_0044e000(int r, char* o)
{
	int i;

	for (i = 0; i < *(int*) (o + 0x24); i++) {
		fcn_004011d0(r, &(*(Vert**) (o + 0x30))[*(int*) (o + 0x28)].x);
		fcn_004011d0(r, &(*(Vert**) (o + 0x30))[*(int*) (o + 0x28)].y);
		fcn_004011d0(r, &(*(Vert**) (o + 0x30))[*(int*) (o + 0x28)].z);
		(*(int*) (o + 0x28))++;
	}
}
