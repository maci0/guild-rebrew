int __cdecl FindStraftatIndexById(int a);
int __cdecl fcn_004f4830(int idx, void* dst);
char* __cdecl gm_LookupEntityRecordById(int a1);
int __cdecl fcn_00508eb0(unsigned short a0, int a1);
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);

/* ADDRESS: GOLDTL 0x004f7120 */
int __cdecl fcn_004f7120(int id, short* a1, int* a2, short* a3, int* a4)
{
	int rec[9];
	int idx;
	char* o;
	int sum;
	int extra;
	float f;

	if (id != -1) {
		idx = FindStraftatIndexById(id);
		if (idx != -1) {
			if (fcn_004f4830(*(unsigned char*) (0x9a381c + idx * 0x2d), rec) != 0) {
				sum = rec[3];
				if (sum != 0) {
					o = gm_LookupEntityRecordById(*(int*) (0x9a3816 + idx * 0x2d));
					if (o != 0) {
						*a3 = *(short*) o;
						extra = fcn_00508eb0(*(unsigned short*) o, 1);
						f = fcn_0050f980(*(unsigned short*) o, *(unsigned short*) a1, 1);
						*a2 = (int) ((f * 0.005f + 0.5f) * (extra + sum) * 1600.0f);
						*a4 = rec[0] & 0xff;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
