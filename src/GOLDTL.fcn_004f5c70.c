// FUNCTION: GOLDTL 0x4f5c70

int __cdecl fcn_004f5c40(int, int, int*);
void __cdecl fcn_004f5940(int, int);

int __cdecl fcn_004f5c70(int key)
{
	int i;
	int v;

	i = fcn_004f5c40(key, 0, &v);
	while (i >= 0) {
		fcn_004f5940(v, 1);
		i = fcn_004f5c40(key, i, &v);
	}
	return 0;
}
