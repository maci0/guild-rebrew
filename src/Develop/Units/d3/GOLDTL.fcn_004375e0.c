#include <string.h>

int __cdecl io_OpenRegistryKey(const char* sub, int mode);
void __cdecl io_WriteRegistryDword(int, const char*, int);
void __cdecl io_WriteRegistryString(int, const char*, char*);
void __cdecl fcn_00410430(int);


/* Writes the Direct3D display options to the registry. */
/* ADDRESS: GOLDTL 0x004375e0 */
void __cdecl d3_SaveDisplayOptions(unsigned char flags, int fill, const char* key)
{
	int h;
	char mode[0x100];

	h = io_OpenRegistryKey(key, 2);
	if (h == -1) {
		return;
	}
	io_WriteRegistryDword(h, "d3d_beautiful", (flags >> 1) & 1);
	switch (fill) {
	case 1:
		strcpy(mode, "D3DFILL_POINT");
		break;
	case 2:
		strcpy(mode, "D3DFILL_WIREFRAME");
		break;
	case 3:
		strcpy(mode, "D3DFILL_SOLID");
		break;
	default:
		strcpy(mode, "");
		break;
	}
	io_WriteRegistryString(h, "d3d_fillmode", mode);
	io_WriteRegistryDword(h, "d3_mirrors", flags & 1);
	io_WriteRegistryDword(h, "d3d_shadows", (flags >> 2) & 7);
	io_WriteRegistryDword(h, "d3d_registry_version", 3);
	fcn_00410430(h);
}
