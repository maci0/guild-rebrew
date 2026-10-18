/* ls_ReadVfsDataChecked — wrapper around vfs_ReadData, nonzero on success. */
#include "../loadsave.h"



int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx)
{
	/* vfs_ReadData wrapper: nonzero on success (unsigned > 0 carry idiom). */
	return (unsigned int) vfs_ReadData(outBuffer, elementSize, elementCount, streamCtx) > 0;
}
