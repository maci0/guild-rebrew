/* ls_ReadVfsDataChecked — wrapper around vfs_ReadData, nonzero on success.
 * Identical body to the server twin; the single residual (call rel32 at +21)
 * is an unmasked reloc slot (callee 0x4306b0 not in catalog), not a byte miss. */

// FUNCTION: GOLDTL 0x5218f0
// SIZE: 37

int __cdecl vfs_ReadData(void*, int, int, void*);

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx)
{
	/* vfs_ReadData wrapper: nonzero on success (unsigned > 0 carry idiom). */
	return (unsigned int) vfs_ReadData(outBuffer, elementSize, elementCount, streamCtx) > 0;
}
