typedef struct {
	char pad0[0xd];
	unsigned char state;
	char padE[0x6];
	void* obj;
} fcn_004bd150_entry;
// SIZE 0x18

void __cdecl init_SetPflanzenMap(fcn_004bd150_entry*, void*);
void __cdecl fcn_00442d50(void*, int);


/* ADDRESS: GOLDTL 0x004bd150 */
void __cdecl fcn_004bd150(fcn_004bd150_entry* tab)
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
				fcn_00442d50(tab[i].obj, 1);
			}
		}
	}
}
