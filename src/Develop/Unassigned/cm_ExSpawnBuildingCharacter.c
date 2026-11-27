


int __cdecl init_SpawnBuildingCharacter(int, int, int, int, int);

int __cdecl cm_ExSpawnBuildingCharacter(char* params, char* out)
{
	int result;

	result = init_SpawnBuildingCharacter(*(int*) (params + 0x10), *(int*) (params + 0x14), *(int*) (params + 0x18), 0, 0);
	if (result == 0) {
		return 1;
	}
	if (out != 0) {
		out[0] = 2;
		out[1] = 7;
		*(int*) (out + 6) = result;
	}
	return 0;
}
