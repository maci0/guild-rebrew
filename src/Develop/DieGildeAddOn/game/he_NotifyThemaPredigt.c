


extern char gm_EntitySlotTable[];
extern char io_MessageFormatBuf[];
extern char str_empty[];

void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);

void __cdecl he_NotifyThemaPredigt(char* preacher, char* target, int topicBuilding)
{
	int i;

	if (target[2] == 6 || target[2] == 7) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x20c1, *(unsigned short*) preacher, topicBuilding);
		he_PostEntityMessage(*(int*) (target + 4), -1, io_MessageFormatBuf, 0, 0x5fb, str_empty);
	}
	io_FormatTextBuffer(io_MessageFormatBuf, 0x20c2, topicBuilding, *(unsigned short*) preacher, (preacher[9] != 0) + 0x20c3,
	    *(unsigned short*) target);
	for (i = 0; i < 768; i++) {
		if (gm_EntitySlotTable + i * 540 != preacher && gm_EntitySlotTable + i * 540 != target &&
		    (gm_EntitySlotTable[i * 540 + 2] == 6 || gm_EntitySlotTable[i * 540 + 2] == 7)) {
			he_PostEntityMessage(*(int*) (gm_EntitySlotTable + i * 540 + 4), -1, io_MessageFormatBuf, 0, 0x5ec, str_empty);
		}
	}
}
