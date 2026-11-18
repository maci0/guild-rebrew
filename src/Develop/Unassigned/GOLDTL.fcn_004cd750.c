


int __cdecl fcn_004e8810(char*);

int __cdecl fcn_004cd750(char* input, char* response)
{
	int r;

	if (response != 0) {
		response[0] = 2;
		response[1] = 0;
		*(int*) (response + 6) = 0;
	}
	r = fcn_004e8810(input + 0x10);
	if (response != 0 && r != 0) {
		*response = 1;
	}
	if (r != 0) {
		return 0;
	}
	return 1;
}
