


int __cdecl amt_ApplyForOffice(int, int);

int __cdecl fcn_00497000(int a1, char* request)
{
	if (*request != 0xa) {
		return 0;
	}
	return amt_ApplyForOffice(a1, *(int*) (request + 4)) != 0 ? 0xa : 0;
}
