extern char io_MessageFormatBuf[];
extern char str_empty[];



void __cdecl io_FormatTextBuffer(void*, int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

/* ADDRESS: GOLDDE 0x00596c20 */
void __cdecl he_NotifyPlotSlotPurchase(void* buyer, void* recipient, int building, int slotInfo)
{
	char t;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x20bc, *(unsigned short*) buyer, building, slotInfo);
		he_PostEntityMessage(*(int*) ((char*) recipient + 4), -1, io_MessageFormatBuf, 0, 0x5ff, str_empty);
	}
}
