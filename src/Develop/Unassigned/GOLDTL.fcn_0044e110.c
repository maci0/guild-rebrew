

// SIZE 0x58
typedef struct Bone {
	char name[0x40];
	float a[3];
	float b[3];
} Bone;

int __cdecl fcn_004011f0(void* stream, void* dst);
int __cdecl vfs_ReadByte(void* stream, void* dst);
char* __cdecl vfs_ReadCString(void* stream, char* text);
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
		vfs_ReadByte(r, &c);
		vfs_ReadCString(r, ((Bone*) (o + 0x38))[i].name);
		vfs_ReadByte(r, &c);
		fcn_00401280(r, ((Bone*) (o + 0x38))[i].a);
		vfs_ReadByte(r, &c);
		fcn_00401280(r, ((Bone*) (o + 0x38))[i].b);
	}
}
