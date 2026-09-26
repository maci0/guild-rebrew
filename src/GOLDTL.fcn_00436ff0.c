#include <stdio.h>

struct unk_436ff0;

// SIZE 0xc
struct unkvtbl_436ff0 {
	long (__stdcall* QueryInterface)(struct unk_436ff0*, void*, void**);
	unsigned long (__stdcall* AddRef)(struct unk_436ff0*);
	unsigned long (__stdcall* Release)(struct unk_436ff0*);
};

// SIZE 0x4
struct unk_436ff0 {
	struct unkvtbl_436ff0* vtbl;
};

extern unsigned long g_14ce728;
extern int g_6b7fdc;
extern unsigned char g_6b7ff8;
extern void* g_6b5de0;

char* __cdecl fcn_0041db70(int size, const char* tag);
void* __cdecl fcn_0042ff50(char*, char*, int);
int __cdecl fcn_004306b0(void*, int, int, void*);
void __cdecl fcn_00430580(void*);
void __cdecl fcn_0041d9e0(char*);
long __stdcall fcn_006129e7(void*, void*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned long, int, int,
    unsigned long, unsigned long, unsigned long, void*, void*, struct unk_436ff0**);
void __cdecl fcn_0041ddd0(void*);

// FUNCTION: GOLDTL 0x436ff0
// SIZE: 286

/* Loads a texture file through the VFS into a managed Direct3D texture,
 * scaled down by the texture detail shift. */
void __cdecl fcn_00436ff0(char* name, int format, struct unk_436ff0** tex, unsigned char mips, unsigned int width, unsigned int height)
{
	char* buf;
	int size;
	int read;
	void* f;
	char msg[0x100];

	if (*tex != 0) {
		g_14ce728 = (*tex)->vtbl->Release(*tex);
		*tex = 0;
	}
	size = width * height * 4 + 0x1036;
	buf = fcn_0041db70(size, "d3d:LoadTexture");
	f = fcn_0042ff50(name, "rb", g_6b7fdc);
	if (f != 0) {
		read = fcn_004306b0(buf, size, 1, f);
		if (read >= size) {
			sprintf(msg, "Memory size estimate for \"%s\" is too small!", name);
			fcn_0041d9e0(msg);
		}
		fcn_00430580(f);
	}
	fcn_006129e7(g_6b5de0, buf, read, width >> (unsigned char) (*(unsigned int*)&g_6b7ff8), height >> (unsigned char) (*(unsigned int*)&g_6b7ff8), mips, 0,
	    format, 1, 0xffffffff, 0xffffffff, 0xff000000, 0, 0, tex);
	fcn_0041ddd0(buf);
}
