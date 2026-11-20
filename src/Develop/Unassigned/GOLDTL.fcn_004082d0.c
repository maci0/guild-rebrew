


char __cdecl d3_GridPointToWorld(int, int, int, float*);
int __cdecl ch_WorldToGridCoordinates(int, float*, int, int);

int __cdecl ch_ConvertGridPointToCharacterGrid(int a1, int a2, int a3, int a4, int a5, int a6)
{
	float vector[4];

	if (d3_GridPointToWorld(a1, a2, a3, vector)) {
		ch_WorldToGridCoordinates(a4, vector, a5, a6);
		return 1;
	}
	return 0;
}
