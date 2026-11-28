extern char io_MessageFormatBuf[];
extern char str_empty[];



void __cdecl io_FormatTextBuffer(void*, int, int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_NotifyContractBatch(void* recipient, int sourceName, int count, int total)
{
	char t;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x4151, sourceName, count, count != 1 ? 0x4153 : 0x4152, total);
		he_PostEntityMessage(*(int*) ((char*) recipient + 4), -1, io_MessageFormatBuf, 0, 0x5fc, str_empty);
	}
}
