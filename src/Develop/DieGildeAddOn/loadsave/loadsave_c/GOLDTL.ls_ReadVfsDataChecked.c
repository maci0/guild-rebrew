/* ls_ReadVfsDataChecked — wrapper around vfs_ReadData, nonzero on success. */

// FUNCTION: GOLD 0x0051c950
// SIZE: 37
// FUNCTION: GOLDTL 0x5218f0
// SIZE: 37

int __cdecl vfs_ReadData(void*, int, int, void*);

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx)
{
	/* vfs_ReadData wrapper: nonzero on success (unsigned > 0 carry idiom). */
	return (unsigned int) vfs_ReadData(outBuffer, elementSize, elementCount, streamCtx) > 0;
}
