


#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

char* __cdecl gm_LookupEntityRecordById(int);

int __cdecl cm_ExModifyHealth(char* cmd, char* result)
{
	char* e;
	int v;

	e = gm_LookupEntityRecordById(*(int*) (cmd + 0x10));
	if (result != 0) {
		result[0] = 2;
		result[1] = 0;
		*(int*) (result + 6) = 0;
	}
	if (e == 0)
		return 1;
	v = *(int*) (cmd + 0x14) + *(int*) (e + 0x194);
	*(int*) (e + 0x194) = MIN(MAX(v, 0), 0x32);
	if (result != 0)
		result[0] = 1;
	return 0;
}
