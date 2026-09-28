char* __cdecl fcn_00402610(char*);

/* Walks a short run of map cells on the task at obj+0x128. Returns 0 when
 * one of those cells is empty or type 0xd, and 1 otherwise. */
// FUNCTION: GOLDTL 0x409020
// SIZE: 170

int __cdecl fcn_00409020(char* obj)
{
	char* map;
	char* task;
	char* cells;
	unsigned char* pairs;
	int count;
	int start;
	int limit;
	int stride;
	int cell;
	volatile int result;

	result = 1;
	task = *(char**) (obj + 0x128);
	map = fcn_00402610(obj);
	count = *(int*) (task + 0xf0);
	if (count < 2) {
		goto done;
	}
	start = *(int*) (task + 0xf8);
	limit = count - 2;
	if (start + 2 < limit) {
		limit = start + 2;
	}
	if (start < 1) {
		start = 1;
	}
	if (start >= limit) {
		goto done;
	}
	stride = *(int*) (map + 0x20);
	cells = *(char**) (map + 0x24);
	pairs = *(unsigned char**) (task + 0xf4);
	while (start < limit) {
		cell = *(int*) (cells + (pairs[start * 2 + 1] * stride + pairs[start * 2]) * 0x1c);
		if (cell == 0 || cell == 0xd) {
			result = 0;
			goto done;
		}
		start = start + 1;
	}
done:
	return result;
}
