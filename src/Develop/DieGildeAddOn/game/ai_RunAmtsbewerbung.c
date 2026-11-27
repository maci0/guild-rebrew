


int __cdecl amt_ApplyForOffice(int, int);

int __cdecl ai_RunAmtsbewerbung(int entity, char* request)
{
	if (*request != 0xa) {
		return 0;
	}
	return amt_ApplyForOffice(entity, *(int*) (request + 4)) != 0 ? 0xa : 0;
}
