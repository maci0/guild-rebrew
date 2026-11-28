


#include <string.h>

extern char* cm_LoadBuf;
extern unsigned int cm_LoadBufOffset;

/* ADDRESS: GOLDDE 0x004b4e50 */
int __cdecl cm_AppendLoadChunk(char* src, char* out)
{
	memcpy(cm_LoadBuf + cm_LoadBufOffset, src + 0x10, 0x80);
	cm_LoadBufOffset += 0x80;
	if (out != 0) {
		*out = 1;
	}
	return 0;
}
