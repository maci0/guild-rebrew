


char* __cdecl gm_LookupEntityRecordById(int);

int __cdecl fcn_005095d0(char* e, int* out_count)
{
	int flag;
	int count;
	int i;
	char* o;

	flag = 0;
	count = 0;
	for (i = 0; i < 5; i++) {
		o = gm_LookupEntityRecordById(*(int*) (e + 0x68 + i * 4));
		if (o != 0 && *(unsigned char*) (o + 8) > 0) {
			count++;
			if (*(unsigned short*) (o + 0xa) > 0xb) {
				flag = 1;
			}
		}
	}
	if (out_count != 0) {
		*out_count = count;
	}
	return flag;
}
