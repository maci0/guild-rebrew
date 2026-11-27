extern unsigned char* lpGebaeudeINST;


void __cdecl d3_BindEntitySceneObject(char*, char*, int);

char __cdecl d3_BindBuildingSceneObjects(char* e)
{
	int i;
	char* r;

	for (i = 0; i < 0x100; i++) {
		r = ((char*)lpGebaeudeINST) + i * 0xa9;
		if (*r != 0 && *(int*) (e + 0x204) == *(int*) (r + 1)) {
			d3_BindEntitySceneObject(e, r, 2);
		}
	}
	return 1;
}
