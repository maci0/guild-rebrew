

// SIZE 0x1
typedef struct State {
	unsigned char lo : 2;
	unsigned char st : 3;
	unsigned char hi : 3;
} State;

char __cdecl d3_SelectFloorChunkLod(char* floor, char* cell, int unused, int n)
{
	float t;
	float s;
	char r;
	char prev;

	if (((State*) (floor + 0x8036))->st != 0) {
		return ((State*) (floor + 0x8036))->st;
	}
	if (*(int*) (floor + 0x24) == 0) {
		return 0;
	}
	t = *(float*) (cell + 0x1dc) / *(float*) (floor + 0x60);
	s = (40.0f - n) * 0.4f;
	if (t > *(float*) (floor + 0x8028) + *(float*) (cell + 0x1d8) + s) {
		r = 4;
	} else if (t > *(float*) (floor + 0x8024) + *(float*) (cell + 0x1d8) + s) {
		r = 2;
	} else {
		r = 1;
	}
	prev = cell[0x1ef];
	if (prev != 0 && prev != -1 && r != prev) {
		cell[0x1f0] = r;
		if (++*(int*) (cell + 0x1e8) <= 8) {
			return prev;
		}
	}
	*(int*) (cell + 0x1e8) = 0;
	return r;
}
