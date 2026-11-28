


int __cdecl vfs_ReadDword(void* stream, void* dst);

/* ADDRESS: GOLDDE 0x00443b90 */
void __cdecl d3_SkipVector3(void* r)
{
	float t;
	int i;

	for (i = 0; i < 3; i++) {
		vfs_ReadDword(r, &t);
	}
}
