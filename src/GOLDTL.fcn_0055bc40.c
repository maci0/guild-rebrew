// FUNCTION: GOLD 0x553b00
// FUNCTION: GOLDTL 0x55bc40

// SIZE 0x1
struct bits {
	unsigned char a : 1;
	unsigned char b : 1;
	unsigned char rest : 6;
};

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_005492e0(char*);
void __cdecl fcn_004c6040(int, int, int, int);

void __cdecl fcn_0055bc40(char* h)
{
	char* e;

	if (h == 0 || *(unsigned short*) h == 0xffff) {
		return;
	}
	for (e = fcn_005463a0(1, 0, 0x41); e != 0; e = fcn_005462a0()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b)) {
			if (*(int*) (e + 0xac) == *(int*) (h + 4)) {
				fcn_00508e40(*(int*) (e + 0xb0));
				fcn_005492e0(e);
			} else if (*(int*) (e + 0xb0) == *(int*) (h + 4)) {
				fcn_00508e40(*(int*) (e + 0xac));
				fcn_005492e0(e);
			}
		}
	}
	for (e = fcn_005463a0(1, 0, 0x6f); e != 0; e = fcn_005462a0()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b)) {
			if (*(int*) (e + 0xac) == *(int*) (h + 4)) {
				fcn_00508e40(*(int*) (e + 0xb0));
				fcn_005492e0(e);
			} else if (*(int*) (e + 0xb0) == *(int*) (h + 4)) {
				fcn_00508e40(*(int*) (e + 0xac));
				fcn_005492e0(e);
			}
		}
	}
	for (e = fcn_005463a0(1, 0, 0x45); e != 0; e = fcn_005462a0()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b)) {
			if (*(int*) (e + 0xac) == *(int*) (h + 4)) {
				fcn_00508e40(*(int*) (e + 0xb0));
				fcn_005492e0(e);
			} else if (*(int*) (e + 0xb0) == *(int*) (h + 4)) {
				fcn_00508e40(*(int*) (e + 0xac));
				fcn_005492e0(e);
			}
		}
	}
	for (e = fcn_005463a0(1, 0, 0x2c); e != 0; e = fcn_005462a0()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b)) {
			if (*(int*) (e + 0xac) == *(int*) (h + 4) || *(int*) (e + 0xb4) == *(int*) (h + 4)
			    || *(int*) (e + 0xc0) == *(int*) (h + 4)) {
				fcn_004c6040(*(int*) (e + 0xac), *(int*) (e + 0xb0), *(int*) (e + 4), 0);
				fcn_005492e0(e);
			} else if (*(int*) (e + 0xb0) == *(int*) (h + 4)) {
				fcn_005492e0(e);
			}
		}
	}
	for (e = fcn_005463a0(1, 0, 0x47); e != 0; e = fcn_005462a0()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b)
		    && (*(int*) (e + 0xac) == *(int*) (h + 4) || *(int*) (e + 0xb0) == *(int*) (h + 4))) {
			fcn_005492e0(e);
		}
	}
	for (e = fcn_005463a0(1, 0, 0x5e); e != 0; e = fcn_005462a0()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b) && *(int*) (e + 0xac) == *(int*) (h + 4)) {
			fcn_005492e0(e);
		}
	}
	for (e = fcn_005463a0(1, 0, 0x5f); e != 0; e = fcn_005462a0()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b) && *(int*) (e + 0xac) == *(int*) (h + 4)) {
			fcn_005492e0(e);
		}
	}
}
