char* __cdecl fcn_00402610(char*);

/* ADDRESS: GOLDTL 0x00409020 */
int __cdecl fcn_00409020(char* obj)
{
	char* task;
	char* map;
	unsigned char* pairs;
	int count;
	int start;
	int limit;
	int stride;
	int cell;
	int result;

	result = 1;
	task = *(char**) (obj + 0x128);
	map = fcn_00402610(obj);
	count = *(int*) (task + 0xf0);
	if (count < 2) {
		return result;
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
	pairs = *(unsigned char**) (task + 0xf4) + start * 2;
	while (1) {
		cell = *(int*) (*(char**) (map + 0x24) + (pairs[1] * stride + pairs[0]) * 0x1c);
		if (cell == 0 || cell == 0xd) {
			result = 0;
			goto done;
		}
		start = start + 1;
		pairs = pairs + 2;
		if (start >= limit) {
			goto done;
		}
	}
done:
	return result;
}
