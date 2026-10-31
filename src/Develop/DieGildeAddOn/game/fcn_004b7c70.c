#include <string.h>

int __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004a55c0(int*, int, int*, int, int, int*);
int __cdecl fcn_0042e410(int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004b7c70 */
int __cdecl fcn_004b7c70(int* a0)
{
	int frame[2];
	char text[0x400];
	int* ent;
	int* slot;
	int v;
	int code;

	ent = (int*) gm_LookupEntityRecordById(*a0);
	if (ent == 0)
		return 1;
	frame[1] = 0x600c00;
	if (fcn_004a55c0(ent, 1, &frame[1], 0, 0x42c80000, &frame[0]) == 0)
		return 0x400;
	slot = (int*) (0x7f4ca0 + (frame[0] & 0xffff) * 0x21c);
	code = (fcn_0042e410(4) & 0xffff) * 2 + 4;
	fcn_004c54c0(ent[1], *(int*) ((char*) slot + 4), code, 1);
	v = *(unsigned short*) slot;
	io_FormatTextBuffer(text, *(unsigned short*) ((char*) a0 + 4) + 0x12e7, v, v);
	fcn_00545d40(ent[1], ent[1], text, 0x100 < strlen(text), 0x603, 0);
	return 0;
}
