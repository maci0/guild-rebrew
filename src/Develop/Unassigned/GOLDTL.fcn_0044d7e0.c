extern int g_6b86c0;

int __cdecl fcn_0044d770(void* h);
int __cdecl FindTableEntryIndex(int a1, int* p, int kind);

/* ADDRESS: GOLDTL 0x0044d7e0 */
void __cdecl fcn_0044d7e0(void* stream, int* table, int kind, void* extra)
{
	int* rec;
	int idx;
	int v;

	v = fcn_0044d770(stream);
	if (v != 0x27) {
		do {
			if (v == 0x2f) {
				break;
			}
			if (v == 0x2b) {
				break;
			}
			if (v == 0x28) {
				idx = FindTableEntryIndex(0x28, table, kind);
				if (idx != 0x27) {
					rec = table + idx * 3;
					if (rec[1] != 0) {
						((void (__cdecl*) (void*, void*)) rec[1]) (stream, extra);
					}
				}
				break;
			}
			idx = FindTableEntryIndex(v, table, kind);
			if (idx != 0x27) {
				rec = table + idx * 3;
				if (rec[1] != 0 && rec[2] == 0) {
					((void (__cdecl*) (void*, void*)) rec[1]) (stream, extra);
				} else {
					g_6b86c0++;
					if (rec[2] != 0) {
						fcn_0044d7e0(stream, (int*) rec[1], rec[2], extra);
					} else {
						fcn_0044d7e0(stream, table, kind, extra);
					}
				}
			}
			v = fcn_0044d770(stream);
		} while (v != 0x27);
	}
	g_6b86c0--;
}
