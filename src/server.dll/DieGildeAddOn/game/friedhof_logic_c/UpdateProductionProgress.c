/* UpdateProductionProgress - advances a production slot's progress by the
 * building's production time, clamped to [0, 0xff]. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10011790
// SYMBOL: _UpdateProductionProgress

extern char* dword_100a8c30;
extern int g_1003546c;
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern void* __cdecl GetSlotEntry(void* worker, int worktype, unsigned char job);

int __cdecl UpdateProductionProgress(void* building)
{
	void* entity;
	unsigned short grave_id;
	unsigned char field_id;
	void* workers;
	void* slot;
	int sum;

	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) building + 8));
	if (entity) {
		grave_id = *(unsigned short*) ((char*) entity + 0x27);
		if (grave_id != 0xffff) {
			if ((char*) 0x100358a0 + grave_id * 0x21c != (char*) g_1003546c) {
				field_id = *(unsigned char*) entity;
				if (dword_100a8c30[field_id + field_id * 588] != 0x1d) {
					return -2;
				}
				workers = *(void**) ((char*) entity + 0x65);
				if (!workers) {
					return -3;
				}
				if (!gv_CheckSlotActive(workers, *(int*) ((char*) building + 0xc))) {
					return -4;
				}
				slot = GetSlotEntry(workers, *(int*) ((char*) building + 0xc), *(unsigned char*) ((char*) building + 0x10));
				if (!slot) {
					return -7;
				}
				sum = *(unsigned char*) ((char*) slot + 0xc);
				sum += *(int*) ((char*) building + 0x13);
				sum = (sum <= 0) ? 0 : sum;
				if (sum >= 0xff) {
					sum = 0xff;
				}
				*(unsigned char*) ((char*) slot + 0xc) = (unsigned char) sum;
				return 0;
			}
		}
	}
	return -1;
}
