extern void* g_6b7fdc;
extern unsigned char g_6b85a4;

void* __cdecl fcn_0042ff50(const char*, const char*, void*);
int __cdecl fcn_004011f0(void* stream, void* dst);
void __cdecl fcn_00430580(void* f);
char* __cdecl fcn_00447110(void* stream, char* parent, unsigned int version, unsigned char resources);
void __cdecl fcn_00439ba0(char* object, char* sibling);
void __cdecl fcn_00439c00(char* object, char* child);

/* Reads one object, or a list of objects, and attaches them under the parent. */
/* ADDRESS: GOLDTL 0x004488e0 */
int __cdecl fcn_004488e0(char* path, void* stream, char* parent)
{
	int magic;
	int count;
	int i;
	void* s;
	char* result;
	char* object;

	result = 0;
	if (stream != 0) {
		s = stream;
	} else {
		s = fcn_0042ff50(path, (char*) 0x6750e8, g_6b7fdc);
	}
	if (s != 0) {
		fcn_004011f0(s, &magic);
		if ((magic & 0xffff0000) != 0x3a6c0000) {
			if (stream == 0) {
				fcn_00430580(s);
			}
			return (int) result;
		}
		if (magic < 0x3a6c00ae) {
			result = fcn_00447110(s, parent, magic, 1);
		} else {
			g_6b85a4 = 0;
			fcn_004011f0(s, &count);
			for (i = 0; i < count; i++) {
				object = fcn_00447110(s, parent, magic, 1);
				if (result == 0) {
					if (object != 0) {
						result = object;
					}
				} else if (object != 0 && parent != 0) {
					fcn_00439ba0(result, object);
				}
			}
		}
		if (stream == 0) {
			fcn_00430580(s);
		}
		if (result != 0 && parent != 0) {
			fcn_00439c00(parent, result);
		}
	}
	return (int) result;
}
