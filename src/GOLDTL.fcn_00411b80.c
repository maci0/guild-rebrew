#include <string.h>

/* Watch the cursor and the two button click latches, then publish the new
 * highlight/selection state into the shared UI state block. */
/* ADDRESS: GOLDTL 0x00411b80 */
void __cdecl fcn_00411b80(void)
{
	int armed;
	int pressed;
	int timedout;
	int state;
	int other;
	int time;
	int* probe;

	if (*(int*) 0x6b5c90) {
		return;
	}
	if (*(int*) 0x6b5c98) {
		time = *(int*) 0x6b7fb8;
		if (0x10 <= time - *(int*) 0x6b5c98 || (int) *(short*) 0x14ce920 < *(int*) 0x6b5ca4 - 3 || *(int*) 0x6b5ca4 + 3 < (int) *(short*) 0x14ce920 || *(int*) 0x6b5ca8 + 3 < (int) *(short*) 0x14ce922 || (int) *(short*) 0x14ce922 < *(int*) 0x6b5ca8 - 3) {
			*(int*) 0x14ce934 = 1;
			*(int*) 0x6b5c98 = 0;
			*(int*) 0x6b5cac = -1;
			armed = -1;
			pressed = 0;
			goto after_check;
		}
	}
	armed = *(int*) 0x6b5cac;
	pressed = *(int*) 0x6b5c98;
after_check:
	other = *(int*) 0x6b5ca4;
	if (*(int*) 0x14ce92c && *(int*) 0x6b5c8c) {
		*(int*) 0x6b5c8c = 0;
		*(int*) 0x14ce930 = 0;
		goto label_411cbe;
	}
	if (*(int*) 0x14ce930 && !pressed) {
		other = (int) *(short*) 0x14ce920;
		*(int*) 0x6b5ca8 = (int) *(short*) 0x14ce922;
		*(int*) 0x6b5c98 = *(int*) 0x6b7fb8;
		*(int*) 0x6b5ca4 = other;
	}
	if (armed != -1 && 0x29 <= *(int*) 0x6b7fb8 - armed) {
		armed = -1;
		*(int*) 0x6b5c98 = 0;
		*(int*) 0x6b5cac = -1;
	}
	if (*(int*) 0x14ce92c) {
		if (armed == -1 || 0x28 <= *(int*) 0x6b7fb8 - armed) {
			*(int*) 0x6b5cac = *(int*) 0x6b7fb8;
			if (*(int*) 0x14ce934) {
label_411cbe:
				*(int*) 0x14ce92c = 0;
				*(int*) 0x6b5cac = -1;
label_411cca:
				*(int*) 0x6b5c98 = 0;
				*(int*) 0x14ce934 = 0;
			} else {
				goto label_411cca;
			}
		} else {
			*(int*) 0x14ce93c = 1;
			*(int*) 0x14ce92c = 0;
			*(int*) 0x6b5cac = -1;
			*(int*) 0x6b5c98 = 0;
		}
	}
	armed = *(int*) 0x6b5c9c;
	pressed = *(int*) 0x14ce948;
	if (*(int*) 0x14ce944) {
		if (!*(int*) 0x6b5c9c) {
			other = (int) *(short*) 0x14ce920;
			*(int*) 0x6b5ca8 = (int) *(short*) 0x14ce922;
			*(int*) 0x6b5c9c = *(int*) 0x6b7fb8;
			armed = *(int*) 0x6b7fb8;
			*(int*) 0x6b5ca4 = other;
			goto label_411d04;
		}
label_411d08:
		if (!*(int*) 0x14ce948 && *(int*) 0x14ce944) {
			if (0x10 <= *(int*) 0x6b7fb8 - armed) {
				pressed = 1;
				*(int*) 0x6b5c9c = 0;
				*(int*) 0x14ce948 = 1;
			}
			if ((int) *(short*) 0x14ce920 < other - 3 || other + 3 < (int) *(short*) 0x14ce920 || *(int*) 0x6b5ca8 + 3 < (int) *(short*) 0x14ce922 || (int) *(short*) 0x14ce922 < *(int*) 0x6b5ca8 - 3) {
				*(int*) 0x6b5c9c = 0;
				*(int*) 0x14ce948 = 1;
				pressed = 1;
			}
		}
	} else {
label_411d04:
		if (armed) {
			goto label_411d08;
		}
	}
	armed = *(int*) 0x14ce940;
	if (*(int*) 0x14ce940) {
		if (pressed) {
			armed = 0;
			pressed = 0;
			*(int*) 0x14ce940 = 0;
			*(int*) 0x14ce948 = 0;
			*(int*) 0x14ce930 = 0;
			*(int*) 0x14ce934 = 0;
		}
		*(int*) 0x6b5c9c = 0;
	}
	state = *(int*) 0x6b5ca0;
	timedout = *(int*) 0x14ce958;
	if (*(int*) 0x14ce954) {
		if (!*(int*) 0x6b5ca0) {
			other = (int) *(short*) 0x14ce920;
			*(int*) 0x6b5ca8 = (int) *(short*) 0x14ce922;
			*(int*) 0x6b5ca0 = *(int*) 0x6b7fb8;
			state = *(int*) 0x6b7fb8;
			*(int*) 0x6b5ca4 = other;
			goto label_411ddd;
		}
	} else {
label_411ddd:
		if (!state) {
			goto label_411e58;
		}
	}
	if (!*(int*) 0x14ce958 && *(int*) 0x14ce954) {
		if (0x10 <= *(int*) 0x6b7fb8 - state) {
			timedout = 1;
			*(int*) 0x6b5ca0 = 0;
			*(int*) 0x14ce958 = 1;
		}
		if ((int) *(short*) 0x14ce920 < other - 3 || other + 3 < (int) *(short*) 0x14ce920 || *(int*) 0x6b5ca8 + 3 < (int) *(short*) 0x14ce922 || (int) *(short*) 0x14ce922 < *(int*) 0x6b5ca8 - 3) {
			*(int*) 0x6b5ca0 = 0;
			*(int*) 0x14ce958 = 1;
			timedout = 1;
		}
	}
label_411e58:
	if (*(int*) 0x14ce950) {
		*(int*) 0x14ce950 = 0;
		if (timedout) {
			timedout = 0;
			*(int*) 0x14ce958 = 0;
		}
		*(int*) 0x6b5ca0 = 0;
	}
	if ((*(int*) 0x14ce92c != *(int*) 0x14cf90c || *(int*) 0x14ce930 != *(int*) 0x14cf910 || *(int*) 0x14ce934 != *(int*) 0x14cf914 || *(int*) 0x14ce93c != *(int*) 0x14cf91c || armed != *(int*) 0x14cf920 || *(int*) 0x14ce944 != *(int*) 0x14cf924 || pressed != *(int*) 0x14cf928 || *(int*) 0x14cf930 || *(int*) 0x14ce954 != *(int*) 0x14cf934 || timedout != *(int*) 0x14cf938 || *(int*) 0x14ce964 != *(int*) 0x14cf944 || *(int*) 0x14ce960 != *(int*) 0x14cf940) && (armed = 0x1f, !*(int*) 0x14cf2fc)) {
		probe = (int*) 0x14cf2fc;
		do {
			probe = &probe[-0x13];
			armed -= 1;
			if (probe < (int*) 0x14ce9c8) {
				armed = 0;
				goto label_411f42;
			}
		} while (!*probe);
		if (armed <= 0x1e) {
label_411f42:
			armed = (armed + 1) * 0x4c;
			memcpy((void*) (armed + 0x14ce980), (void*) 0x14ce920, 0x4c);
			*(unsigned int*) (armed + 0x14ce9c8) = 1;
		}
	}
	memcpy((void*) 0x14cf900, (void*) 0x14ce920, 0x4c);
}
