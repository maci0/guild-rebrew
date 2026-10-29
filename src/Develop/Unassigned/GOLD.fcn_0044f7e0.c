/* SIZE 0x58 */
typedef struct Bone {
	char name[0x40];
	float a[3];
	float b[3];
} Bone;

int __cdecl fcn_004011d0(void* stream, void* dst);
int __cdecl fcn_00401180(void* stream, void* dst);
char* __cdecl fcn_004011a0(void* stream, char* text);
void __cdecl fcn_00401240(void* stream, void* dst);

void __cdecl fcn_0044f7e0_GOLD(void* r, char* o)
{
	int n;
	int i;
	char t0, t1, t2;

	n = 0;
	fcn_004011d0(r, &n);
	*(int*)(o + 0x34) = n;
	for (i = 0; i < n; i++) {
		fcn_00401180(r, &t0);
		fcn_004011a0(r, ((Bone*)(o + 0x38))[i].name);
		fcn_00401180(r, &t1);
		fcn_00401240(r, ((Bone*)(o + 0x38))[i].a);
		fcn_00401180(r, &t2);
		fcn_00401240(r, ((Bone*)(o + 0x38))[i].b);
	}
}
