


int __cdecl vfs_ReadDword(void* stream, void* dst);

void __cdecl d3_SkipVector3(void* r)
{
	float t;
	int i;

	for (i = 0; i < 3; i++) {
		vfs_ReadDword(r, &t);
	}
}
