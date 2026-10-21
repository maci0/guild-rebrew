/* Fades the objects of a selected animation slot in or out after a mode switch
   and stores the new current slot. */

int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00588200(int, int, int);
void __cdecl fcn_004518a0(float*);
void __cdecl fcn_00438b40(char*, int*);
char __cdecl fcn_00442c00(char*, char);

/* ADDRESS: GOLDTL 0x00588710 */
void __cdecl fcn_00588710(int a0, int a1, int a2, int a3, int a4)
{
	unsigned int start = *(unsigned int*) 0x6b7fac;
	float f;
	float vec[4];
	float pos[4];
	int i;

	if (a3 == *(int*) (a1 + 0xa0) || a3 > *(int*) (a1 + 0xdc)) {
		return;
	}
	while (fcn_005373e0((void*) 0x588710, a4) != 0) {
		fcn_00588200(a0, a1, a2);
		if ((float) (*(unsigned int*) 0x6b7fac - start) >
		    *(float*) 0x665f3c) {
			*(int*) 0x774654 = 1;
		} else {
			f = (float) (*(unsigned int*) 0x6b7fac - start) /
			    *(float*) 0x665f3c;
			vec[0] = *(float*) (a1 + 0x24);
			vec[2] = *(float*) (a1 + 0x2c);
			vec[1] = 0.0f;
			fcn_004518a0(vec);
			f *= *(float*) 0x665f40;
			vec[0] = *(float*) a1 - vec[0] * f;
			vec[1] = *(float*) (a1 + 4) - f * vec[1];
			vec[2] = *(float*) (a1 + 8) - f * vec[2];
			fcn_00438b40((char*) *(int*) (a1 + 0x98), (int*) vec);
			vec[0] = *(float*) 0x665f28 + f * *(float*) 0x662d40;
			vec[1] = *(float*) 0x665f2c + f * *(float*) 0x662d44;
			vec[2] = *(float*) 0x665f30 + f * *(float*) 0x662d48;
			fcn_00438b40((char*) *(int*) (a1 + 0x9c), (int*) vec);
		}
	}
	for (i = 0; i != 3; i++) {
		fcn_00442c00((char*) *(int*) (a1 + 0x8c + i * 4), 0);
	}
	fcn_00442c00((char*) *(int*) (a1 + 0x8c + a3 * 4), 1);
	*(int*) (a1 + 0xa0) = a3;
	start = *(unsigned int*) 0x6b7fac;
	while (fcn_005373e0((void*) 0x588710, a4) != 0) {
		fcn_00588200(a0, a1, a2);
		if ((float) (*(unsigned int*) 0x6b7fac - start) >
		    *(float*) 0x665f3c) {
			*(int*) 0x774654 = 1;
		} else {
			vec[0] = *(float*) (a1 + 0x24);
			vec[2] = *(float*) (a1 + 0x2c);
			vec[1] = 0.0f;
			f = *(float*) 0x6628a0 -
			    (float) (*(unsigned int*) 0x6b7fac - start) /
			        *(float*) 0x665f3c;
			fcn_004518a0(vec);
			f *= *(float*) 0x665f40;
			pos[0] = *(float*) a1 - vec[0] * f;
			pos[1] = *(float*) (a1 + 4) - f * vec[1];
			pos[2] = *(float*) (a1 + 8) - f * vec[2];
			fcn_00438b40((char*) *(int*) (a1 + 0x98), (int*) pos);
			pos[0] = *(float*) 0x665f28 + f * *(float*) 0x662d40;
			pos[1] = *(float*) 0x665f2c + f * *(float*) 0x662d44;
			pos[2] = *(float*) 0x665f30 + f * *(float*) 0x662d48;
			fcn_00438b40((char*) *(int*) (a1 + 0x9c), (int*) pos);
		}
	}
	*(int*) (a1 + 0x6c) = *(int*) 0x6b7fac;
}
