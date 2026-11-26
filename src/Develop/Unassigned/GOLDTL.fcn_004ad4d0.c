


void __cdecl fcn_004c5790(char, char*);

void __cdecl amt_SendSpecialOfficeSlot(int slot)
{
	char buf[0x7c];

	*(int*) buf = slot;
	fcn_004c5790(0x14, buf);
}
