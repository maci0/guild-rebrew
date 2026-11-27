


// SIZE 0x14
typedef struct {
	int w;
	int pad[3];
	unsigned char* data;
} Map;

int __cdecl d3_ScanMapRowMinMax(Map* map, int* lo, int* hi, int x0, int x1, int y)
{
	int tmp;
	int i;
	unsigned char* p;

	if (y < 0 || y >= map->w) {
		return 1;
	}
	if (x1 < x0) {
		tmp = x0;
		x0 = x1;
		x1 = tmp;
	}
	if (x0 >= map->w || x1 < 0) {
		return 1;
	}
	x0 = x0 < 0 ? 0 : x0;
	if (x1 >= map->w - 1) {
		x1 = map->w - 1;
	}
	p = map->data + map->w * y + x0;
	for (i = x0; i <= x1; i++) {
		*lo = *lo < *p ? *lo : *p;
		*hi = *hi > *p ? *hi : *p;
		p++;
	}
	return 0;
}
