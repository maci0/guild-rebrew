int __cdecl fcn_00492950(char*, char*, int);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_004929e0(void*, void*, int);
void __cdecl fcn_00492990(char*, char*, int);

/* ADDRESS: GOLDTL 0x00492d60 */
int __cdecl fcn_00492d60(int* p, char* q, int kind)
{
	if (!fcn_00492950((char*) p, q, kind)) {
		return 0;
	}
	switch (kind) {
	case 1:
		if (q[2] == 6) {
			fcn_004c51a0(-1, *(int*) (q + 4), 0, *p);
		}
		p[0x15] += *p;
		fcn_004929e0(p, q, 1);
		fcn_00492990((char*) p, q, kind);
		return 1;
	case 2:
		if (q[2] == 6) {
			fcn_004c51a0(-1, *(int*) (q + 4), 0, p[1]);
		}
		p[0x15] += p[1];
		fcn_004929e0(p, q, 0);
		fcn_00492990((char*) p, q, kind);
		return 1;
	case 3:
		if (q[2] == 6) {
			fcn_004c51a0(-1, *(int*) (q + 4), 0, p[1]);
		}
		p[0x15] += p[1];
		fcn_00492990((char*) p, q, kind);
		return 1;
	case 4:
		fcn_00492990((char*) p, q, kind);
		return 1;
	default:
		return 0;
	}
}
