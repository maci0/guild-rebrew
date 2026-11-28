#include <string.h>
#include "Develop/Units/d3/d3_camera.h"
extern char io_LastKeyScancode; extern unsigned char g_1040600; extern char* d3_ObjectListHead;
int __cdecl d3_ResetRenderStates(void *flags);
int __cdecl d3_SetFogEnabled(int enable);
void *__cdecl d3_NextVisibleSceneNode(void *node);
int __cdecl d3_TraverseSceneObjects(int a, int b, int c, const char *s);
int __cdecl d3_InvalidateSceneRenderCache(int a);

/* ADDRESS: GOLDTL 0x00448b10 */
char __cdecl d3_HandleDebugCameraHotkeys(void)
{
	unsigned char flags[8];
	char *node;
	unsigned char value;
	void* dst;
	int count;

	if (io_LastKeyScancode != *(char *) 0x6b85a5) {
		count = 8;
		dst = flags;
		__asm {
			mov edi, dst
			mov esi, 0x1052bd0
			mov ebx, count
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L_copy_tail
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L_copy_tail:
			add ecx, ebx
			rep movsb
		}
		*(char *) 0x6b85a5 = io_LastKeyScancode;
		switch ((unsigned char) io_LastKeyScancode) {
		case 0x30:
			value = flags[0];
			flags[0] = value ^
			           ((unsigned char) (~(value >> 1) << 1 ^ value) &
			            2);
			d3_InvalidateSceneRenderCache(0);
			d3_ResetRenderStates(flags);
			return 0;
		case 0x2e:
			node = d3_ActiveCamera;
			if (*(char **) 0x1041d0c == node) {
				node = d3_ObjectListHead;
				while (*(int *) (node + 0x218) != 4) {
					if (node == (char *) 0x1042340)
						return 0;
					node = (char *) d3_NextVisibleSceneNode(node);
				}
				if (node == (char *) 0x1042340)
					return 0;
			}
			*(char **) 0x1041d0c = node;
			return 0;
		case 0x1f:
			if (flags[0] & 0x1c) {
				if (g_1040600)
					flags[0] &= 0xe3;
				else
					g_1040600 = 1;
			} else {
				g_1040600 = 0;
				flags[0] = (flags[0] & 0xe7) | 4;
			}
			d3_TraverseSceneObjects(*(int *) 0x67a370, 0, 0x1ff,
			             (const char *) 0x456df0);
			d3_InvalidateSceneRenderCache(0);
			d3_ResetRenderStates(flags);
			return 0;
		case 0x14:
			*(char *) 0x6b8019 = !*(char *) 0x6b8019;
			return 0;
		case 0x15:
			d3_SetFogEnabled(!*(char *) 0x6b7ff9);
			return 0;
		}
	}
	return 0;
}
