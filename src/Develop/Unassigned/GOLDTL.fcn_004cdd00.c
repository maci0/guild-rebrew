


int __cdecl fcn_004f0960(int);
int __cdecl d3_ReleaseSlot170(int);

int __cdecl cm_ExDispatchSlotNCt(char* request, char* response)
{
	int result;
	int code;

	if (response != 0) {
		response[0] = 2;
		response[1] = 0;
		*(int*) (response + 6) = 0;
	}
	code = *(int*) (request + 0x10);
	if (code == 0x6154436e) {
		result = fcn_004f0960(*(int*) (request + 0x14));
	} else if (code == 0x6454436e) {
		result = d3_ReleaseSlot170(*(int*) (request + 0x14));
	} else {
		return -1;
	}
	if (response != 0 && result != 0) {
		*response = 1;
	}
	if (result == 0) {
		return -1;
	}
	return 0;
}
