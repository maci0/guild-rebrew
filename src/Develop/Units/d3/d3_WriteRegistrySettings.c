#include <string.h>
int __cdecl io_OpenRegistryKey(int, int);
void __cdecl io_WriteRegistryDword(int, char*, int);
void __cdecl io_WriteRegistryString(int, char*, char*);
void __cdecl io_WriteRegistryFloat(int, char*, int);
void __cdecl fcn_00411340(int);

/* ADDRESS: GOLDTL 0x0044c6f0 */
void __cdecl d3_WriteRegistrySettings(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8,
			  int a9, int a10, int a11, int a12, int a13, int a14, int a15, int a16,
			  int a17, int a18, int a19, int a20, int a21, int a22, int sectionName)
{
	char* lodText;
	char buf[0x100];
	int sectionId;

	sectionId = io_OpenRegistryKey(sectionName, 2);
	if (sectionId == -1) {
		return;
	}
	io_WriteRegistryDword(sectionId, (char*) 0x67b218, a1);
	io_WriteRegistryDword(sectionId, (char*) 0x67b208, a2);
	io_WriteRegistryDword(sectionId, (char*) 0x67b1f4, a3);
	io_WriteRegistryDword(sectionId, (char*) 0x67b1e4, a4);
	io_WriteRegistryDword(sectionId, (char*) 0x67b1d4, a6);
	io_WriteRegistryDword(sectionId, (char*) 0x67b1c4, a7);
	io_WriteRegistryDword(sectionId, (char*) 0x67b1b4, a8);
	io_WriteRegistryDword(sectionId, (char*) 0x67b19c, a12);
	io_WriteRegistryDword(sectionId, (char*) 0x67b188, a9);
	io_WriteRegistryDword(sectionId, (char*) 0x67b16c, a10);
	io_WriteRegistryDword(sectionId, (char*) 0x67b15c, a5);
	lodText = buf;
	switch (*(int*) 0x67ac90) {
	case 1:
		strcpy(lodText, "d3io_LOD_SWITCH");
		break;
	case 2:
		strcpy(lodText, "d3io_LOD_LOW");
		break;
	case 4:
		strcpy(lodText, "d3io_LOD_HIGH");
		break;
	default:
		lodText[0] = *(char*) 0x6b5c60;
		break;
	}
	io_WriteRegistryString(sectionId, (char*) 0x67b11c, lodText);
	io_WriteRegistryFloat(sectionId, (char*) 0x67b10c, a16);
	io_WriteRegistryFloat(sectionId, (char*) 0x67b0f8, a17);
	io_WriteRegistryFloat(sectionId, (char*) 0x67b0e4, a18);
	io_WriteRegistryFloat(sectionId, (char*) 0x67b0d0, a19);
	io_WriteRegistryFloat(sectionId, (char*) 0x67b0bc, a20);
	io_WriteRegistryFloat(sectionId, (char*) 0x67b0ac, a21);
	io_WriteRegistryFloat(sectionId, (char*) 0x67b094, a22);
	io_WriteRegistryDword(sectionId, (char*) 0x67b080, 3);
	fcn_00411340(sectionId);
}
