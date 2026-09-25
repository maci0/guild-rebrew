#include <string.h>

int __cdecl fcn_004112b0(const char* sub, int mode);
void __cdecl fcn_00411500(int, const char*, int);
void __cdecl fcn_00411520(int, const char*, char*);
void __cdecl fcn_00411340(int);

// FUNCTION: GOLDTL 0x4375e0
// SIZE: 301

/* Writes the Direct3D display options to the registry. */
void __cdecl fcn_004375e0(unsigned char flags, int fill, const char* key)
{
	int h;
	char mode[0x100];

	h = fcn_004112b0(key, 2);
	if (h == -1) {
		return;
	}
	fcn_00411500(h, "d3d_beautiful", (flags >> 1) & 1);
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
	fcn_00411520(h, "d3d_fillmode", mode);
	fcn_00411500(h, "d3_mirrors", flags & 1);
	fcn_00411500(h, "d3d_shadows", (flags >> 2) & 7);
	fcn_00411500(h, "d3d_registry_version", 3);
	fcn_00411340(h);
}
