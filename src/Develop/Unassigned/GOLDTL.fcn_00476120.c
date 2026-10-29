#include <string.h>

int __cdecl fcn_0047b8b0(int a1, int a2, int a3, int a4, void* out);
void __cdecl fcn_004372d0(int a1, int a2, int a3, int a4, int a5);

/* ADDRESS: GOLDTL 0x00476120 */
int __cdecl fcn_00476120(int left, int top, int width, int height, char* src,
						  char* dest, int mode)
{
	int area[6];
	int params[2];
	int frame[42];
	void* target;
	int surface_src;
	int surface_dest;

	if ((*(unsigned char*) dest & 0x10) != 0 && *(void**) 0x7725ec != 0) {
		if (fcn_0047b8b0(left, top, width, height, frame) == 0) {
			return 0;
		}
		surface_src = *(int*) (src + 0x20);
		target = (void*) surface_src;
		if ((*(int (__stdcall**) (int, int, int, int*, int))
			 (*(char**) *(void**) 0x772614 + 0x2c))(*(int*) 0x772614, 0, 0x18,
													&surface_src, 0x2000) < 0) {
			return 0;
		}
		target = (void*) surface_src;
		memcpy(target, frame, 0xa8);
		(*(int (__stdcall**) (int)) (*(char**) *(void**) 0x772614 + 0x30))
			(*(int*) 0x772614);
		(*(int (__stdcall**) (int, int, int, int))
		 (*(char**) *(void**) 0x6b5de0 + 0x14c))(*(int*) 0x6b5de0, 0,
												*(int*) 0x772614, 0x1c);
		(*(int (__stdcall**) (int, int))
		 (*(char**) *(void**) 0x6b5de0 + 0x130))(*(int*) 0x6b5de0, 0x144);
		fcn_004372d0(0xfe, 0, 0, 1, 1);
		(*(int (__stdcall**) (int, int, int))
		 (*(char**) *(void**) 0x6b5de0 + 0xc8))(*(int*) 0x6b5de0, 7, 0);
		area[0] = 0;
		area[1] = 0;
		area[2] = *(int*) (dest + 0x54);
		area[3] = *(int*) (dest + 0x58);
		area[4] = 0;
		area[5] = 0x3f800000;
		if ((*(int (__stdcall**) (int, int, void*))
			 (*(char**) *(void**) 0x7725ec + 0x14))(*(int*) 0x7725ec,
													*(int*) (dest + 0x24), area) >= 0) {
			(*(int (__stdcall**) (int, int, int))
			 (*(char**) *(void**) 0x6b5de0 + 0xc8))(*(int*) 0x6b5de0, 7, 0);
			(*(int (__stdcall**) (int, int, int, int, int, int))
			 (*(char**) *(void**) 0x6b5de0 + 0x90))(*(int*) 0x6b5de0, 0, 1, 0xff,
												   0x3f800000, 0);
			(*(int (__stdcall**) (int, int, int))
			 (*(char**) *(void**) 0x6b5de0 + 0xf4))(*(int*) 0x6b5de0, 0,
													*(int*) (src + 0x20));
			(*(int (__stdcall**) (int, int, int, int))
			 (*(char**) *(void**) 0x6b5de0 + 0x118))(*(int*) 0x6b5de0, 4, 0, 2);
			(*(int (__stdcall**) (int))
			 (*(char**) *(void**) 0x7725ec + 0x18))(*(int*) 0x7725ec);
		}
		(*(int (__stdcall**) (int, int, int))
		 (*(char**) *(void**) 0x6b5de0 + 0xc8))(*(int*) 0x6b5de0, 7, 1);
		return 1;
	}

	area[0] = left;
	area[1] = top;
	area[2] = left + width;
	area[3] = top + height;
	params[0] = (int) dest;
	params[1] = mode;
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
	 (*(char**) *(void**) 0x6b5de0 + 0x70))(*(int*) 0x6b5de0, surface_dest,
											area, 1, surface_src, params);
	return 1;
}
