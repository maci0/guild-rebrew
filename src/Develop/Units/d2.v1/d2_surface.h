#ifndef D2_SURFACE_H
#define D2_SURFACE_H

/* The allocation is 0x5c bytes; these fields describe its observed prefix. */
typedef struct {
	int flags;
	int width;
	int height;
	char unk_0c[0x14];
	void* surface;
} D2_SURFACE;

extern D2_SURFACE* g_77256c;

#endif
