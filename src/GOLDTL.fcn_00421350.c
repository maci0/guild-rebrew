extern int g_6b7d64;
extern unsigned char g_678c08;
extern unsigned short g_678c0c;

// SIZE 0xc
struct path_421350 {
	int n;
	int max;
	unsigned char* cells;
};

// SIZE 0x1c
struct cell_421350 {
	char pad0[0x1a];
	unsigned short prev;
};

unsigned short __cdecl fcn_00421890(char*, int, int, int, int, int);
unsigned short __cdecl fcn_004214c0(char*, int, int, int, int, int);

// FUNCTION: GOLD 0x424f30
// SIZE: 353
// FUNCTION: GOLDTL 0x421350
// SIZE: 353

/* Finds a path on a map and unrolls it into the caller's cell list. */
unsigned short __cdecl fcn_00421350(struct path_421350* path, char* map, int x0, int y0, int x1, int y1, int flags)
{
	unsigned short r;
	unsigned short c;

	if (map == 0 || x1 > *(int*) (map + 0x20) || y1 > *(int*) (map + 0x20) || x1 < 0 || y1 < 0) {
		return 0xffff;
	}
	path->n = 0;
	if (g_6b7d64 != 0) {
		r = fcn_00421890(map, x0, y0, x1, y1, flags);
		if (r != 0xffff) {
			for (c = r; path->n < path->max && c != 0xffff; c = (*(struct cell_421350**) (map + 0x24))[c].prev) {
				path->cells[path->n * 2] = g_678c08 & (unsigned char) c;
				path->cells[path->n * 2 + 1] = (unsigned char) (c >> g_678c0c);
				path->n++;
			}
		}
	} else {
		r = fcn_004214c0(map, x0, y0, x1, y1, flags);
		if (r != 0xffff) {
			for (c = r; path->n < path->max && c != 0xffff; c = (*(struct cell_421350**) (map + 0x24))[c].prev) {
				path->cells[path->n * 2] = g_678c08 & (unsigned char) c;
				path->cells[path->n * 2 + 1] = (unsigned char) (c >> g_678c0c);
				path->n++;
			}
		}
	}
	return r;
}
