


void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);

/* ADDRESS: GOLDDE 0x0055f270 */
void __cdecl he_DeclineDeathPactPayment(void* recipient, void* entity)
{
	char buf[0x400];

	io_FormatTextBuffer(buf, 0x40ff, *(unsigned short*) entity);
	he_PostEntityMessage(*(int*) recipient, -1, buf, 1, 0x5f4, 0);
}
