

void __cdecl d3_TransformPoint(char*, char*, char*);
int __cdecl d3_CreateSceneModelObject(int, char*, char*, int);

/* ADDRESS: GOLDDE 0x0040d660 */
int __cdecl CreateObjectAtDummy(int* a1, char** dummy)
{
	char pos[0x10];

	if (*dummy == 0) {
		return 0;
	}
	d3_TransformPoint(*dummy, *dummy + 0x4c, pos);
	return d3_CreateSceneModelObject(0, pos, *dummy + 0x84, *a1);
}
