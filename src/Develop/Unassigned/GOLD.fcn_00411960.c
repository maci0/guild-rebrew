#include <stdio.h>
#include <string.h>
typedef struct { unsigned int words[3]; } GOLD_ATTACH_OPTIONS; /* Inferred 12-byte argument record. */
unsigned int __cdecl fcn_00401040(char*);
int __cdecl fcn_00433f40(unsigned int);
void __cdecl fcn_0044e4a0(char*, unsigned int, int);
int __cdecl fcn_00435550(char*, unsigned int, GOLD_ATTACH_OPTIONS);
char* __cdecl fcn_0044e2e0(char*, char*, int);

/* ADDRESS: GOLD 0x00411960 */
int __cdecl fcn_00411960(char* object, char* name, unsigned int flags)
{
	char key[256];
	char path[512];
	GOLD_ATTACH_OPTIONS options;
	unsigned char* bytes;
	char* fillDst;
	int fillCount;
	unsigned int id;
	char* result;

	if (object == 0 || name == 0)
		return 0;
	strcpy(key, name);
	id = fcn_00401040(key);
	if (!fcn_00433f40(id))
		fcn_0044e4a0(name, id, 0);
	fillDst = (char*) &options;
	fillCount = sizeof(options);
	__asm {
		mov edi, fillDst
		mov ebx, fillCount
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short OptionsFillTail
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	OptionsFillTail:
		add ecx, ebx
		rep stosb
	}
	bytes = (unsigned char*) &options;
	if (flags & 2) bytes[1] |= 0x10;
	if (flags & 1) bytes[1] &= 0xef;
	if (flags & 4) bytes[1] |= 2;
	if (flags & 0x10) bytes[1] |= 8;
	if (flags & 0x20) bytes[1] |= 4;
	bytes[8] |= 2;
	if (*(char**) (object + 0x1ec) != 0 &&
	    fcn_00435550(*(char**) (object + 0x1ec) + 0xf4, id,
	        options))
		return 1;
	sprintf(path, "%s%s.oam", *(char**) 0xfba940, name);
	result = fcn_0044e2e0(path, object, 1);
	if (result != 0) {
		if (flags & 2) result[0x2d] |= 0x10;
		if (flags & 1) result[0x2d] &= 0xef;
		if (flags & 4) result[0x2d] |= 2;
		if (flags & 0x10) result[0x2d] |= 8;
		if (flags & 0x20) result[0x2d] |= 4;
		return 1;
	}
	return 0;
}
