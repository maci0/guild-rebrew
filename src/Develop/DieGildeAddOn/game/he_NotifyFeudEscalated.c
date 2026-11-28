extern char io_MessageFormatBuf[];



unsigned short __cdecl gm_RandomMod(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);

/* ADDRESS: GOLDDE 0x00597020 */
void __cdecl he_NotifyFeudEscalated(void* entity, void* recipient)
{
	char buf[0x200];
	char t;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(buf, gm_RandomMod(3) + 0x134a, *(unsigned short*) entity);
		io_FormatTextBuffer(io_MessageFormatBuf, 0x1343, *(unsigned short*) entity,
		    gm_RandomMod(3) +
		        (*(char*) ((char*) recipient + 9) != 0 ? 0x1347 : 0x1344),
		    *(unsigned short*) recipient, buf);
		he_PostEntityMessage(*(int*) ((char*) recipient + 4), -1, io_MessageFormatBuf, 1, 0x5ec, 0);
	}
}
