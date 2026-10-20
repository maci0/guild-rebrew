/*
 * Kugel flight state machine, one step per frame.
 *
 * The handle at self+0xb8 resolves to a map slot; self+0x27 of that object
 * gives the slot index and 0x7f4ca0 + index * 0x21c is the map entry, unless
 * it is the current-entry pointer at 0x773da8.
 *
 * State word at self+0x70: negative unlinks the instance, 0 arms state 1,
 * 1 lets the ball start and sets the flight counters, 2 waits until both
 * counters have drained and then restarts. The two counters at self+0x14 and
 * self+0x18 weight the travel time; the ball position at self+0xb0 is summed
 * until it turns positive, and a negative socket test repeats the loop.
 */

typedef struct S571240Counts {
	int a;
	int b;
} S571240Counts;

void __cdecl fcn_005015e0(void*, int, int, int);
void __cdecl fcn_00529160(int, int, int, int);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_0050c710(int, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
double __cdecl fcn_0050fdb0(int, int, int);
int __cdecl fcn_0050c830(char*, char*, int);
int __cdecl fcn_0064d228(void);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_0051af00(char*, int, int, int);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, char*);
int __cdecl fcn_00500cb0(char*, char*);
void __cdecl fcn_00500bb0(char*, int, int, int);
void __cdecl fcn_004c51f0(int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00571240 */
void __cdecl fcn_00571240(char* self)
{
	char buf[0x100];
	char* map;
	char* entry;
	char* node;
	char* other;
	int state;
	int slot;
	int n;
	int i;
	int r;
	int sum;
	int limit;
	float t;
	float total;
	float prev;

	fcn_005015e0(&node, 0, 0, *(int*) (self + 0xb8));
	if (node == 0) {
		entry = (char*) 0x7f4ca0;
		while (entry < (char*) 0x85a0a0) {
			if (*(int*) (entry + 0x17c) == (int) self) {
				fcn_00529160(0, 0, *(unsigned short*) entry, 0);
			}
			entry += 0x21c;
		}
		fcn_00546190(self);
		return;
	}
	map = 0;
	if (*(unsigned short*) (node + 0x27) != 0xffff) {
		other = (char*) (0x7f4ca0 + *(unsigned short*) (node + 0x27) * 0x21c);
		if (other != (char*) *(int*) 0x773da8) {
			map = other;
		}
	}
	state = *(int*) (self + 0x70);
	switch (state) {
	case -2:
	case -1:
		entry = (char*) 0x7f4ca0;
		while (entry < (char*) 0x85a0a0) {
			if (*(int*) (entry + 0x17c) == (int) self) {
				fcn_00529160(0, 0, *(unsigned short*) entry, 0);
			}
			entry += 0x21c;
		}
		fcn_00546190(self);
		return;
	case 0:
		*(int*) (self + 0x70) = state + 1;
		return;
	case 1:
		if (*(int*) (self + 0x14) == 0 && *(int*) (self + 0x18) == 0) {
			*(int*) (self + 0x70) = 2;
			return;
		}
		fcn_005015e0(&other, 0, 0, *(int*) (self + 0xb8));
		n = fcn_0050c710((int) other, 1, 1);
		t = (float) n * *(double*) 0x6640e8 + *(double*) 0x6629c8;
		if (*(unsigned char*) (self + 0xc8) >= 0x3c) {
			if (map != 0) {
				for (i = 0; i < 8; i++) {
					if (*(int*) (self + 0x8c + i * 4) != -1 && *(int*) (other + 0x41) != 2) {
						fcn_004c54c0(*(int*) (map + 4), *(int*) (self + 0x8c + i * 4), 2 - *(int*) (other + 0x41), 0);
					}
				}
				*(float*) (self + 0xc4) = (float) ((fcn_0050fdb0(*(unsigned short*) map, 8, (int) (self + 0x8c)) - *(double*) 0x662908) * *(double*) 0x662ad8);
			}
			*(unsigned char*) (self + 0xc8) = 0;
		}
		n = fcn_0050c830(self + 0x60, (char*) 0x7f4c00, 0);
		if (n > 0) {
			*(unsigned char*) (self + 0xc8) = *(unsigned char*) (self + 0xc8) + n;
		}
		total = t + *(float*) (self + 0xc4);
		if (fcn_00500cb0(self + 0x52, (char*) 0x7f4c00) >= 0) {
			return;
		}
		r = 0;
		entry = (char*) (0x99ec10 + *(unsigned short*) (self + 0xac) * 0x41);
		for (;;) {
			prev = (float) *(int*) (self + 0xb0);
			n = fcn_0050c830(self + 0x60, self + 0x52, 0);
			limit = n * (*(int*) (self + 0x18) + *(int*) (self + 0x14) * 2);
			t = total - t * (float) limit;
			r = fcn_0064d228();
			*(int*) (self + 0xb0) = r;
			if (r > 0) {
				break;
			}
			fcn_005015e0(&other, 0, 0, *(int*) (self + 0xbc));
			node = fcn_00502cd0(*(int*) (other + 0x14), 1, 0, *(unsigned short*) (self + 0xac));
			fcn_005015e0(&other, 0, 0, *(int*) (self + 0xc0));
			if (node == 0) {
				fcn_0051af00(buf, 0x1bb7, (*(unsigned short*) (self + 0xac)) * 2 + 0x9a8, (int) other);
				fcn_00545e80(*(int*) (0x7f4ca4 + (*(unsigned short*) (self + 8)) * 0x21c), -1, buf, 0, 0x5f1, *(int*) (other + 1), -1, 0, (char*) 0x6a7a78);
				entry = (char*) 0x7f4ca0;
				while (entry < (char*) 0x85a0a0) {
					if (*(int*) (entry + 0x17c) == (int) self) {
						fcn_00529160((int) other, 0, *(unsigned short*) entry, 0);
					}
					entry += 0x21c;
				}
				fcn_00546190(self);
				return;
			}
			limit = *(unsigned short*) (entry + 0x36);
			if (limit >= *(int*) (node + 0xe)) {
				limit = *(int*) (node + 0xe);
			}
			fcn_004c51f0(*(int*) (self + 0xc0), *(int*) (self + 0xbc), *(unsigned short*) (self + 0xac), limit, *(unsigned char*) 0x773d75, 0);
			sum = *(int*) (self + 0xb0) + *(int*) (entry + 0x22);
			*(int*) (self + 0xb0) = sum;
			*(float*) (self + 0xb4) = (float) sum;
			if (sum > 0) {
				break;
			}
		}
		{
			int k;

			k = 0;
			while (k < 0xe) {
				*(char*) (self + 0x60 + k) = map[k];
				k++;
			}
			fcn_00500bb0(map, 0, 0, 5);
			if (fcn_00500cb0(self + 0x52, (char*) 0x7f4c00) < 0) {
				return;
			}
		}
		return;
	case 2:
		if (*(int*) (self + 0x14) > 0 || *(int*) (self + 0x18) > 0) {
			*(int*) (self + 0x70) = 1;
			return;
		}
		fcn_005015e0(&node, 0, 0, *(int*) (self + 0xb8));
		if (node == 0) {
			*(int*) (self + 0x70) = -1;
			return;
		}
		entry = (char*) 0x7f4ca0;
		while (entry < (char*) 0x85a0a0) {
			if (*(int*) (entry + 0x17c) == (int) self) {
				fcn_00529160((int) node, 0, *(unsigned short*) entry, 0);
			}
			entry += 0x21c;
		}
		fcn_00546190(self);
		return;
	}
}
