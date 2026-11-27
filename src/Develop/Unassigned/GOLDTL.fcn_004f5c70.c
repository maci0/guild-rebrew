

int __cdecl fcn_004f5c40(int, int, int*);
void __cdecl gs_RemoveStraftat(int, int);

int __cdecl gs_RemoveEntityStraftaten(int key)
{
	int i;
	int v;

	i = fcn_004f5c40(key, 0, &v);
	while (i >= 0) {
		gs_RemoveStraftat(v, 1);
		i = fcn_004f5c40(key, i, &v);
	}
	return 0;
}
