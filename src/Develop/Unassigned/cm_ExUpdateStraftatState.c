


int __cdecl cm_UpdateStraftatState(int, int, int, int);

int __cdecl cm_ExUpdateStraftatState(void* input, char* response)
{
	char b;

	b = 2;
	if (cm_UpdateStraftatState(*(int*) ((char*) input + 0x10), *(int*) ((char*) input + 0x14),
	                 *(int*) ((char*) input + 0x18), *(int*) ((char*) input + 0x1c)) > 0) {
		b = 1;
	}
	if (response != 0) {
		response[0] = b;
		response[1] = 0;
		*(int*) (response + 6) = 0;
	}
	return 0;
}
