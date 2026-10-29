

// SIZE 0x58
typedef struct Bone {
	char name[0x40];
	float a[3];
	float b[3];
} Bone;

int __cdecl fcn_004011f0(void* stream, void* dst);
int __cdecl fcn_00401180(void* stream, void* dst);
char* __cdecl fcn_004011a0(void* stream, char* text);
void __cdecl fcn_00401280(void* stream, void* dst);

void __cdecl fcn_0044e110(void* r, char* o)
{
	int n;
	char c;
	int i;

	n = 0;
	fcn_004011f0(r, &n);
	*(int*) (o + 0x34) = n;
	for (i = 0; i < n; i++) {
		fcn_00401180(r, &c);
		fcn_004011a0(r, ((Bone*) (o + 0x38))[i].name);
		fcn_00401180(r, &c);
		fcn_00401280(r, ((Bone*) (o + 0x38))[i].a);
		fcn_00401180(r, &c);
		fcn_00401280(r, ((Bone*) (o + 0x38))[i].b);
	}
}
