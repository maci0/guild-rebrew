#include <string.h>
extern void * g_6b5de0; extern int g_772614; extern int g_7725ec;
int __cdecl fcn_0047b8b0(int a1, int a2, int a3, int a4, void* out);
void __cdecl fcn_004372d0(int a1, int a2, int a3, int a4, int a5);

typedef struct BlitSurf BlitSurf;
typedef struct BlitSurf {
	char pad0[0xc];
	int pitch;              
	int f10;                
	unsigned char bpp;      
	char pad15[3];
	int f18;                
	char* bits;             
	void* a;                
	void* b;                
	char pad28[4];
	int left;               
	int top;                
	int right;              
	int bottom;             
	int locked;             
	char pad40[4];
	int flag;               
} BlitSurf;

int __cdecl fcn_00475fd0(BlitSurf* s);
int __cdecl fcn_00476060(BlitSurf* s);
int __cdecl fcn_00476120(int x, int y, int w, int h, char* src, int sx, int sy, char* dst);
int __cdecl fcn_004763e0(int x, int y, int w, int h, BlitSurf* src, int sx, int sy, BlitSurf* dst, int unused);

/* ADDRESS: GOLDTL 0x00476120 */
int __cdecl fcn_00476120(int left, int top, int width, int height, char* src,
						  int sx, int sy, char* dest)
{
	int area[6];
	int params[2];
	int frame[42];
	void* target;
	int surface_src;
	int surface_dest;

	if ((*(unsigned char*) dest & 0x10) != 0 && *(void**) &g_7725ec != 0) {
		if (fcn_0047b8b0(left, top, width, height, frame) == 0) {
			return 0;
		}
		surface_src = *(int*) (src + 0x20);
		target = (void*) surface_src;
		if ((*(int (__stdcall**) (int, int, int, int*, int))
			 (*(char**) *(void**) &g_772614 + 0x2c))(*(int*) &g_772614, 0, 0x18,
													&surface_src, 0x2000) < 0) {
			return 0;
		}
		target = (void*) surface_src;
		memcpy(target, frame, 0xa8);
		(*(int (__stdcall**) (int)) (*(char**) *(void**) &g_772614 + 0x30))
			(*(int*) &g_772614);
		(*(int (__stdcall**) (int, int, int, int))
		 (*(char**) *(void**) &g_6b5de0 + 0x14c))(*(int*) &g_6b5de0, 0,
												*(int*) &g_772614, 0x1c);
		(*(int (__stdcall**) (int, int))
		 (*(char**) *(void**) &g_6b5de0 + 0x130))(*(int*) &g_6b5de0, 0x144);
		fcn_004372d0(0xfe, 0, 0, 1, 1);
		(*(int (__stdcall**) (int, int, int))
		 (*(char**) *(void**) &g_6b5de0 + 0xc8))(*(int*) &g_6b5de0, 7, 0);
		area[0] = 0;
		area[1] = 0;
		area[2] = *(int*) (dest + 0x54);
		area[3] = *(int*) (dest + 0x58);
		area[4] = 0;
		area[5] = 0x3f800000;
		if ((*(int (__stdcall**) (int, int, void*))
			 (*(char**) *(void**) &g_7725ec + 0x14))(*(int*) &g_7725ec,
													*(int*) (dest + 0x24), area) >= 0) {
			(*(int (__stdcall**) (int, int, int))
			 (*(char**) *(void**) &g_6b5de0 + 0xc8))(*(int*) &g_6b5de0, 7, 0);
			(*(int (__stdcall**) (int, int, int, int, int, int, int))
			 (*(char**) *(void**) &g_6b5de0 + 0x90))(*(int*) &g_6b5de0, 0, 0, 1, 0xff,
												   0x3f800000, 0);
			(*(int (__stdcall**) (int, int, int))
			 (*(char**) *(void**) &g_6b5de0 + 0xf4))(*(int*) &g_6b5de0, 0,
													*(int*) (src + 0x20));
			(*(int (__stdcall**) (int, int, int, int))
			 (*(char**) *(void**) &g_6b5de0 + 0x118))(*(int*) &g_6b5de0, 4, 0, 2);
			(*(int (__stdcall**) (int))
			 (*(char**) *(void**) &g_7725ec + 0x18))(*(int*) &g_7725ec);
		}
		(*(int (__stdcall**) (int, int, int))
		 (*(char**) *(void**) &g_6b5de0 + 0xc8))(*(int*) &g_6b5de0, 7, 1);
		return 1;
	}

	area[0] = left;
	area[1] = top;
	area[2] = left + width;
	area[3] = top + height;
	params[0] = sx;
	params[1] = sy;
	if (*(int*) (dest + 0x20) != 0 && *(int*) (dest + 0x24) == 0) {
		if ((*(int (__stdcall**) (int, int, int*))
			 (*(char**) *(int*) (dest + 0x20) + 0x3c))(*(int*) (dest + 0x20), 0,
													   &surface_dest) != 0) {
			return 0;
		}
		*(int*) (dest + 0x24) = surface_dest;
	} else {
		surface_dest = *(int*) (dest + 0x24);
	}
	if (*(int*) (src + 0x20) != 0 && *(int*) (src + 0x24) == 0) {
		if ((*(int (__stdcall**) (int, int, int*))
			 (*(char**) *(int*) (src + 0x20) + 0x3c))(*(int*) (src + 0x20), 0,
													  &surface_src) != 0) {
			return 0;
		}
		*(int*) (src + 0x24) = surface_src;
	} else {
		surface_src = *(int*) (src + 0x24);
	}
	(*(int (__stdcall**) (int, int, int*, int, int, int*))
	 (*(char**) *(void**) &g_6b5de0 + 0x70))(*(int*) &g_6b5de0, surface_src,
											area, 1, surface_dest, params);
	return 1;
}
