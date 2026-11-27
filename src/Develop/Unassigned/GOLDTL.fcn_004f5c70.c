

int __cdecl gm_FindStraftatId(int, int, int*);
void __cdecl gs_RemoveStraftat(int, int);

int __cdecl gs_RemoveEntityStraftaten(int key)
{
	int i;
	int v;

	i = gm_FindStraftatId(key, 0, &v);
	while (i >= 0) {
		gs_RemoveStraftat(v, 1);
		i = gm_FindStraftatId(key, i, &v);
	}
	return 0;
}
