/* Chooses a display mode through the device vtable, stores the accepted mode
   and the flag bytes, then lets fcn_00456c80 build the surfaces. */

void __cdecl fcn_00456530(int, int);
void __cdecl fcn_00456c80(void);

#define SET_MODE(f) \
	(*(int (__stdcall **)(int, int, int, int, int, int, int)) \
	    (*(int*) *(int*) 0x6b5ddc + 0x28))( \
	    *(int*) 0x6b5ddc, *(int*) 0x14ce744, *(int*) 0x14ce72c, \
	    *(int*) 0x14ce86c, 1, 3, (f))

/* ADDRESS: GOLDTL 0x00456750 */
void __cdecl fcn_00456750(unsigned int a0, unsigned int a1, int a2, int a3,
                          char a4, char a5, int a6)
{
	int r;
	unsigned int h;

	h = a1;
	if (h >= *(unsigned int*) 0x14ce798) {
		a1 = *(unsigned int*) 0x14ce798;
	}
	*(unsigned int*) 0x10405fc = a1;
	*(unsigned int*) 0x104061c = a0;
	if (a0 >= a1) {
		*(unsigned int*) 0x104061c = a1;
	}
	*(int*) 0x6b89b0 = a6;
	*(char*) 0x1040600 = 1;
	*(char*) 0x1040601 = a4;
	*(char*) 0x10405f8 = 1;
	fcn_00456530(a2, a3);
	*(int*) 0x6b89b8 = 0;
	if (a5) {
		r = SET_MODE(0x1c);
		if (r >= 0) {
			*(int*) 0x6b89b8 = r;
			goto chosen;
		}
		r = *(int*) 0x6b89b8;
		if (r != 0) {
			goto second;
		}
		r = SET_MODE(0x19);
		if (r >= 0) {
			*(int*) 0x6b89b8 = r;
			goto chosen;
		}
		r = *(int*) 0x6b89b8;
		if (r != 0) {
			goto second;
		}
		r = SET_MODE(0x1a);
		if (r >= 0) {
			*(int*) 0x6b89b8 = r;
			goto chosen;
		}
		r = *(int*) 0x6b89b8;
		if (r != 0) {
			goto second;
		}
		r = SET_MODE(0x1d);
		if (r >= 0) {
			*(int*) 0x6b89b8 = r;
			goto chosen;
		}
		r = *(int*) 0x6b89b8;
		if (r != 0) {
			goto second;
		}
		r = SET_MODE(0x15);
		if (r >= 0) {
			*(int*) 0x6b89b8 = r;
			goto chosen;
		}
		r = *(int*) 0x6b89b8;
		if (r != 0) {
			goto second;
		}
		r = SET_MODE(0x1f);
		if (r >= 0) {
			*(int*) 0x6b89b8 = r;
			goto chosen;
		}
		r = *(int*) 0x6b89b8;
	} else {
		r = 0;
	}
chosen:
	*(char*) 0x6b89bc = r != 0;
	if (r != 0) {
		goto second;
	}
	r = SET_MODE(0x1b);
	if (r >= 0) {
		r = 0x1b;
		goto store;
	}
	r = *(int*) 0x6b89b8;
	if (r != 0) {
		goto second;
	}
	r = SET_MODE(0x17);
	if (r >= 0) {
		r = 0x17;
		goto store;
	}
	r = *(int*) 0x6b89b8;
	if (r != 0) {
		goto second;
	}
	r = SET_MODE(0x18);
	if (r >= 0) {
		r = 0x18;
		goto store;
	}
	r = *(int*) 0x6b89b8;
	if (r != 0) {
		goto second;
	}
	r = SET_MODE(0x1e);
	if (r >= 0) {
		r = 0x1e;
		goto store;
	}
	r = *(int*) 0x6b89b8;
	if (r != 0) {
		goto second;
	}
	r = SET_MODE(0x14);
	if (r >= 0) {
		r = 0x14;
		goto store;
	}
	r = *(int*) 0x6b89b8;
	if (r != 0) {
		goto second;
	}
	r = SET_MODE(0x16);
	if (r >= 0) {
		r = 0x16;
		goto store;
	}
	r = *(int*) 0x6b89b8;
	if (r != 0) {
		goto second;
	}
	r = *(int*) 0x14ce86c;
store:
	*(int*) 0x6b89b8 = r;
second:
	r = SET_MODE(r);
	*(char*) 0x6b89bd = r >= 0;
	fcn_00456c80();
}
