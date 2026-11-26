

void __cdecl amt_GetRoleTemplate(int, void*);

int __cdecl amt_GetRoleLevel(int office_id)
{
	char buf[0x18];

	amt_GetRoleTemplate(office_id, buf);
	return *(int*) (buf + 8) & 0xff;
}
