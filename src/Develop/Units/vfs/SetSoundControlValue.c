#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

void __cdecl d3snd_PlaySource(char*, int, int, int);
int __cdecl _crt_locked_call4a(void*, int, int, void*);
unsigned int __cdecl vfs_GetByte(int*);
unsigned int __cdecl vfs_FlushStream(int, int);
void __cdecl SetSoundControlValue(int, unsigned int);
int __cdecl vfs_CloseStream(void*);

int __cdecl vfs_ReadUint32BE(int);
int __cdecl vfs_FlushAndClose(int);

/* Stores a sound-object control value, resetting the object for a nonzero value.
 * The vfs file location is a legacy reconstruction label. */

/* ADDRESS: GOLDDE 0x004170d0 */
void __cdecl SetSoundControlValue(int stream, unsigned int value)
{
	if (value != 0)
		d3snd_PlaySource((char*) stream, 0, 0, 0);
	*(unsigned int*) (stream + 0x50) = value;
}
