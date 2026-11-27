typedef struct {
	char pad0[0xd];
	unsigned char state;
	char padE[0x6];
	void* obj;
} D3_PFLANZEN_MAP_ENTRY;
// SIZE 0x18

void __cdecl init_SetPflanzenMap(D3_PFLANZEN_MAP_ENTRY*, void*);
void __cdecl d3_SetSubtreeVisible(void*, int);


/* ADDRESS: GOLDTL 0x004bd150 */
void __cdecl d3_ShowPflanzenMapEntries(D3_PFLANZEN_MAP_ENTRY* tab)
{
	int i;

	if (tab != 0) {
		for (i = 0; i < 64; i++) {
			if (tab[i].state != 0xff) {
				if (tab[i].obj == 0) {
					init_SetPflanzenMap(&tab[i], tab[i].obj);
					if (tab[i].obj == 0)
						continue;
				}
				d3_SetSubtreeVisible(tab[i].obj, 1);
			}
		}
	}
}
