extern int g_14ce86c;
extern int g_6b89b0, g_6b89b8;
/* Chooses a display mode through the device vtable, stores the accepted mode
   and the flag bytes, then lets fcn_00456c80 build the surfaces. */

void __cdecl d3s_AllocCache(int, int);
void __cdecl d3_AllocShadowTextures(void);
extern unsigned int g_14ce798, g_10405fc, g_104061c;
extern unsigned char g_1040600;
extern void* g_6b5ddc;
extern unsigned char g_6b89bc;
extern char g_6b89bd;

#define SET_MODE(f) \
	(*(int (__stdcall **)(int, int, int, int, int, int, int)) \
	    (*(int*) g_6b5ddc + 0x28))( \
	    (int) g_6b5ddc, *(int*) 0x14ce744, *(int*) 0x14ce72c, \
	    g_14ce86c, 1, 3, (f))

/* ADDRESS: GOLDTL 0x00456750 */
void __cdecl d3_SelectShadowTextureFormat(unsigned int minSize, unsigned int maxSize, int unused2, int unused3,
                          char formatFlag, char tryAdditionalModes, int shadowDepth)
{
	int r;
	unsigned int h;

	h = maxSize;
	if (h >= g_14ce798) {
		maxSize = g_14ce798;
	}
	g_10405fc = maxSize;
	g_104061c = minSize;
	if (minSize >= maxSize) {
		g_104061c = maxSize;
	}
	g_6b89b0 = shadowDepth;
	g_1040600 = 1;
	*(char*) 0x1040601 = formatFlag;
	*(char*) 0x10405f8 = 1;
	d3s_AllocCache(unused2, unused3);
	r = 0;
	g_6b89b8 = r;
	if (tryAdditionalModes) {
		r = SET_MODE(0x1c);
		if (r >= 0) {
			r = 0x1c;
			g_6b89b8 = r;
			goto chosen;
		}
		r = g_6b89b8;
		if (r != 0) {
			goto chosen;
		}
		r = SET_MODE(0x19);
		if (r >= 0) {
			r = 0x19;
			g_6b89b8 = r;
			goto chosen;
		}
		r = g_6b89b8;
		if (r != 0) {
			goto chosen;
		}
		r = SET_MODE(0x1a);
		if (r >= 0) {
			r = 0x1a;
			g_6b89b8 = r;
			goto chosen;
		}
		r = g_6b89b8;
		if (r != 0) {
			goto chosen;
		}
		r = SET_MODE(0x1d);
		if (r >= 0) {
			r = 0x1d;
			g_6b89b8 = r;
			goto chosen;
		}
		r = g_6b89b8;
		if (r != 0) {
			goto chosen;
		}
		r = SET_MODE(0x15);
		if (r >= 0) {
			r = 0x15;
			g_6b89b8 = r;
			goto chosen;
		}
		r = g_6b89b8;
		if (r != 0) {
			goto chosen;
		}
		r = SET_MODE(0x1f);
		if (r >= 0) {
			r = 0x1f;
			g_6b89b8 = r;
			goto chosen;
		}
		r = g_6b89b8;
	}
chosen:
	g_6b89bc = r != 0;
	if (r != 0) {
		goto second;
	}
	r = SET_MODE(0x1b);
	if (r >= 0) {
		r = 0x1b;
		goto store;
	}
	r = g_6b89b8;
	if (r != 0) {
		goto second;
	}
	r = SET_MODE(0x17);
	if (r >= 0) {
		r = 0x17;
		goto store;
	}
	r = g_6b89b8;
	if (r != 0) {
		goto second;
	}
	r = SET_MODE(0x18);
	if (r >= 0) {
		r = 0x18;
		goto store;
	}
	r = g_6b89b8;
	if (r != 0) {
		goto second;
	}
	r = SET_MODE(0x1e);
	if (r >= 0) {
		r = 0x1e;
		goto store;
	}
	r = g_6b89b8;
	if (r != 0) {
		goto second;
	}
	r = SET_MODE(0x14);
	if (r >= 0) {
		r = 0x14;
		goto store;
	}
	r = g_6b89b8;
	if (r != 0) {
		goto second;
	}
	r = SET_MODE(0x16);
	if (r >= 0) {
		r = 0x16;
		goto store;
	}
	r = g_6b89b8;
	if (r != 0) {
		goto second;
	}
	r = g_14ce86c;
store:
	g_6b89b8 = r;
second:
	r = SET_MODE(r);
	g_6b89bd = r >= 0;
	d3_AllocShadowTextures();
}
