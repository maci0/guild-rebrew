

void __cdecl ch_ValidateCharacterTable(void);
void __cdecl ch_ValidateQueueTable(void);

void __cdecl ch_ValidateObjectTables(void)
{
	ch_ValidateCharacterTable();
	ch_ValidateQueueTable();
}
