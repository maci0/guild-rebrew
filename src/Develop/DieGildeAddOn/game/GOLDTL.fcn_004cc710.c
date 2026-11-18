


char* __cdecl gm_FindRecordById(int);
void __cdecl fcn_00506300(char*);

int __cdecl fcn_004cc710(char* input, char* response)
{
	char* p;

	p = gm_FindRecordById(*(int*) (input + 0x10));
	if (p == 0) {
		return 1;
	}
	fcn_00506300(p);
	if (response != 0) {
		response[0] = 1;
		response[1] = 0;
		*(int*) (response + 6) = 0;
	}
	return 0;
}
