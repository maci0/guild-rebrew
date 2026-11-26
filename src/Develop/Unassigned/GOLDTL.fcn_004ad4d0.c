


void __cdecl cm_RequestSysMessage(char, char*);

void __cdecl amt_SendSpecialOfficeSlot(int slot)
{
	char buf[0x7c];

	*(int*) buf = slot;
	cm_RequestSysMessage(0x14, buf);
}
