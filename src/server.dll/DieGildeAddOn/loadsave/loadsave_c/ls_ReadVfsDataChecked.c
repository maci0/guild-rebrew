/* ls_ReadVfsDataChecked — wrapper around ReadVfsData, nonzero on success. */

// FUNCTION: SERVER 0x10012440

int __cdecl ReadVfsData(void*, int, int, void*);

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx)
{
	/* ReadVfsData wrapper: nonzero on success (unsigned > 0 carry idiom). */
	return (unsigned int) ReadVfsData(outBuffer, elementSize, elementCount, streamCtx) > 0;
}
