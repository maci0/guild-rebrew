extern char* g_1006920[];
extern int g_7728f4;

char* __cdecl d3_AcquireModel(char* key, char* val);

void __cdecl gv_SpawnIfPending(char*);
extern char g_6813e8[];
extern char g_6813dc[];
extern char g_68140c[];
extern char g_681430[];
extern char g_6813f4[];
extern char g_681420[];

void __cdecl anm_SpawnQueuedAnimals(void);
char* __cdecl anm_QueueAnimalModel(char*);

/* ADDRESS: GOLDTL 0x004bcab0 */
char* __cdecl anm_QueueAnimalModel(char* name)
{
	int index;
	char* found;

	found = d3_AcquireModel(name, name);
	index = g_7728f4;
	g_1006920[index] = found;
	found = ((char**) g_1006920)[index];
	g_7728f4 = index + 1;
	return found;
}

/* ADDRESS: GOLDTL 0x004bcae0 */
void __cdecl anm_SpawnQueuedAnimals(void)
{
	int i;

	for (i = 0; i < g_7728f4; i++) {
		if (g_1006920[i] != 0)
			gv_SpawnIfPending(g_1006920[i]);
		g_1006920[i] = 0;
	}
}

/* ADDRESS: GOLDTL 0x004bcb20 */
void __cdecl anm_QueueDefaultAnimalModels(void)
{
	if (g_7728f4 != 0)
		anm_SpawnQueuedAnimals();
	anm_QueueAnimalModel(g_6813e8);
	anm_QueueAnimalModel(g_6813dc);
	anm_QueueAnimalModel(g_68140c);
	anm_QueueAnimalModel(g_681430);
	anm_QueueAnimalModel(g_6813f4);
	anm_QueueAnimalModel(g_681430);
	anm_QueueAnimalModel(g_681420);
}
