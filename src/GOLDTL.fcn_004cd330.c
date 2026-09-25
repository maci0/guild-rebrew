extern int* g_772f40;

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004cd2a0(char*, float*, float*, int);
void __cdecl fcn_004d8200(int*);
void __cdecl fcn_004d85c0(int*);
void __cdecl fcn_004d85f0(int*);
void __cdecl fcn_004d8660(int*);
void __cdecl fcn_004d8700(int*);
void __cdecl fcn_004d87b0(int*);
void __cdecl fcn_004d87f0(int*);

// FUNCTION: GOLD 0x004cc7b0
// SIZE: 304
// FUNCTION: GOLDTL 0x4cd330
// SIZE: 304

int __cdecl fcn_004cd330(unsigned char* a1, char* a2)
{
	char* e;

	if (g_772f40 == 0 || *g_772f40 != *(int*) (a1 + 0x10))
		return 1;
	e = gm_LookupEntityRecordById(*(int*) (a1 + 0x35));
	switch (a1[0x14]) {
	case 2:
		if (e[8] != 0) {
			fcn_004cd2a0(e, (float*) (a1 + 0x15), (float*) (a1 + 0x25), *(int*) (a1 + 0x31));
			fcn_004d8200((int*) (a1 + 0x35));
		}
		break;
	case 6:
		if (e[8] != 0) {
			fcn_004cd2a0(e, (float*) (a1 + 0x15), (float*) (a1 + 0x25), *(int*) (a1 + 0x31));
			fcn_004d85c0((int*) (a1 + 0x35));
		}
		break;
	case 1:
		if (e[8] != 0)
			fcn_004d85f0((int*) (a1 + 0x35));
		break;
	case 4:
		if (e[8] != 0)
			fcn_004d8660((int*) (a1 + 0x35));
		break;
	case 5:
		if (e[8] != 0)
			fcn_004d8700((int*) (a1 + 0x35));
		break;
	case 7:
		fcn_004d87b0((int*) (a1 + 0x35));
		break;
	case 3:
		if (e[8] != 0) {
			fcn_004cd2a0(e, (float*) (a1 + 0x15), (float*) (a1 + 0x25), *(int*) (a1 + 0x31));
			fcn_004d87f0((int*) (a1 + 0x35));
		}
		break;
	}
	if (a2 != 0) {
		a2[0] = 1;
		a2[1] = 8;
		*(int*) (a2 + 6) = 0;
	}
	return 0;
}
