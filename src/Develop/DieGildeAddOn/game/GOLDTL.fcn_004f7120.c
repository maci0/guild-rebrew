int __cdecl fcn_004f36e0(int a);
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

	if (id != -1) {
		idx = fcn_004f36e0(id);
		if (idx != -1) {
			if (fcn_004f4830(*(unsigned char*) (0x9a381c + idx * 0x2d), rec) != 0) {
				sum = rec[3];
				if (sum != 0) {
					o = gm_LookupEntityRecordById(*(int*) (0x9a3816 + idx * 0x2d));
					if (o != 0) {
						*a3 = *(short*) o;
						sum = fcn_00508eb0(*(unsigned short*) o, 1) + sum;
						*a2 = (int) ((fcn_0050f980(*(unsigned short*) o, *(unsigned short*) a1, 1)
						    * *(float*) 0x664138 + *(float*) 0x6628cc) * sum * *(float*) 0x664334);
						*a4 = rec[0] & 0xff;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
