// FUNCTION: GOLD 0x004fea50
// SIZE: 211
// FUNCTION: GOLDTL 0x005015e0
// SIZE: 211

extern void* g_99ec10;
extern char g_7f4ca0[];
extern char* g_90e094;
extern char* g_868054;
extern int g_773d8c;

int __cdecl fcn_005015e0(void** dynamic, void** existing, void** static_ptr, int entity_id)
{
	int i;
	char* cursor;

	if (g_99ec10 == 0) {
		return 0;
	}
	if (dynamic != 0) {
		*dynamic = 0;
	}
	if (existing != 0) {
		*existing = 0;
	}
	if (static_ptr != 0) {
		*static_ptr = 0;
		cursor = g_7f4ca0;
		for (i = 0; i < 0x300; i++) {
			if (*(unsigned short*) cursor != 0xffff && *(int*) (cursor + 4) == entity_id) {
				*static_ptr = cursor;
				return 3;
			}
			cursor += 0x21c;
		}
	}
	if (dynamic != 0) {
		cursor = g_90e094;
		for (i = 0; i < 0x100; i++, cursor += 0xa9) {
			if (*cursor != 0 && *(int*) (cursor + 1) == entity_id) {
				*dynamic = cursor;
				return 1;
			}
		}
	}
	if (existing != 0) {
		cursor = g_868054;
		for (i = 0; i < g_773d8c; cursor += 0x43) {
			if (*(unsigned short*) cursor != 0) {
				if (*(int*) (cursor + 2) == entity_id) {
					*existing = cursor;
					return 2;
				}
				i++;
			}
		}
	}
	return 0;
}
