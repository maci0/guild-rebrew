


// fcn_00512500 — fcn_00501190(1,5,0xb); if non-null fcn_00511e90(r).

int __cdecl fcn_00501190(int, int, int);
int __cdecl fcn_00511e90(int);

void __cdecl fcn_00512500(void)
{
	int r;
	r = fcn_00501190(1, 5, 0xb);
	if (r != 0) {
		fcn_00511e90(r);
	}
}

