


extern char g_7f4ca0[];

int __cdecl gm_FindSimilarEntities(char*, int, int, int, float, unsigned short*);

void __cdecl fcn_005d28e0(char* e, int* count, int* out)
{
	unsigned short ids[10];
	int i;
	int type;

	type = (e[9] != 0 ? -1 : 0) + 0xc0540a;
	*count = gm_FindSimilarEntities(e, 9, type, 0, 100.0f, ids);
	for (i = 0; i < *count; i++) {
		out[i] = *(int*) (g_7f4ca0 + ids[i] * 540 + 4);
	}
}
