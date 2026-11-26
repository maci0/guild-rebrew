

void __cdecl fcn_004e8b40(int, void*);

int __cdecl amt_GetRoleLevel(int office_id)
{
	char buf[0x18];

	fcn_004e8b40(office_id, buf);
	return *(int*) (buf + 8) & 0xff;
}
