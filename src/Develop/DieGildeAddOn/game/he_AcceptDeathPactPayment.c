


extern unsigned char gm_ActiveTownIndex;

void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);

void __cdecl he_AcceptDeathPactPayment(void* recipient, void* entity)
{
	char buf[0x400];

	cm_RequestTransferCurrencyNoKill(*(int*) recipient, *(int*) ((char*) entity + 4),
	    gm_ActiveTownIndex, *(int*) ((char*) recipient + 0xc));
	cm_RequestChangeBits(*(int*) ((char*) entity + 4), 0x1cc, 4, 1, 0);
	io_FormatTextBuffer(buf, 0x40fe, *(unsigned short*) entity, *(int*) ((char*) recipient + 0xc));
	he_PostEntityMessage(*(int*) recipient, -1, buf, 1, 0x5f4, 0);
}
