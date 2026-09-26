// FUNCTION: GOLD 0x00407200
// SIZE: 146
// FUNCTION: GOLDTL 0x00407d90
// SIZE: 146

extern void* g_14d0020[];
int __cdecl fcn_00451840(char* a, char* b, float range);

int __cdecl fcn_00407d90(char* self, char** out)
{
	int count;
	char** p;
	char* e;
	char* n;

	count = 0;
	p = ((char**)g_14d0020);
	do {
		if (count >= 16) {
			break;
		}
		e = *p;
		if (e != 0 && self != e && *(int*) (self + 0x88) == *(int*) (e + 0x88) &&
		    *(int*) (self + 0x2c) == *(int*) (e + 0x2c)) {
			n = *(char**) (e + 0x34);
			if (*(int*) (n + 0x218) != 1 ||
			    (*(char**) (e + 0x22c) != 0 &&
			     *(int*) (*(char**) (e + 0x22c) + 0x218) != 1)) {
				if (fcn_00451840(*(char**) (self + 0x34) + 0x4c, n + 0x4c, 300.0f)) {
					out[count] = *p;
					count++;
				}
			}
		}
		p++;
	} while ((int) p < (int) (((char**)g_14d0020) + 0x300));
	return count;
}
