#include <string.h>

int __cdecl d2_BuildQuadVertices(int a1, int a2, int a3, int a4, void* out);
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

int __cdecl d2_LockSurface(BlitSurf* s);
int __cdecl d2_UnlockSurface(BlitSurf* s);
int __cdecl fcn_00476120(int x, int y, int w, int h, BlitSurf* src, int sx, int sy, BlitSurf* dst);
int __cdecl fcn_004763e0(int x, int y, int w, int h, BlitSurf* src, int sx, int sy, BlitSurf* dst, int unused);

int __cdecl fcn_004763e0(int x, int y, int w, int h, BlitSurf* src, int sx, int sy, BlitSurf* dst, int unused);
/* ADDRESS: GOLDTL 0x00476620 */
void __cdecl fcn_00476620(int x, int y, int width, int height, int src, int sx, int sy, int dst)
{
	fcn_004763e0(x, y, width, height, src, sx, sy, dst, 0);
}
