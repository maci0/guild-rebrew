extern int gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern short cm_PacketDeltaBase;

int __cdecl d2_RunCityScrollMapDialog(int a, int* dlg, char* txt, int c, int d);
void __cdecl io_FormatTextBuffer(char* buf, int fmt, ...);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl cm_BeginPacketFieldDelta(int a, int b);
int __cdecl cm_AppendPacketFieldDelta(unsigned char a, unsigned char b, unsigned short c, char* d);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl gm_ApplyRandomDisease(char* slot, int a, int b);
int __cdecl gm_HasActiveSpecialObject(char* slot, int mode);
double __cdecl gm_RandomFloat01(void);
int __cdecl fcn_00503fe0(int a, int b, int c);
void __cdecl he_PostEntityMessage(int a, int b, char* buf, int c, int d, int e);

/* Handles the two result kinds of a diebesgilde spionage dialog: report the
 * outcome packet and tear the slot down. Native body: 869 bytes. */
/* ADDRESS: GOLDTL 0x005dc270 */
/* ADDRESS: GOLDDE 0x005bd810 */
int __cdecl gm_ObjInflictTargetAffliction(char* cmd, char* action)
{
	int dlg[0x14];
	char txt[0x100];
	char msg[0xf8];
	char line[0x800];
	char* esi;
	char* slot;
	short h;
	int i;

	if ((unsigned char) cmd[2] == 6) {
		memset(dlg, 0, 0x50);
		for (i = 7; i < 15; i++) {
			dlg[i] = -1;
		}
		io_FormatTextBuffer(txt, 0x9a);
		dlg[0] = 1;
		dlg[1] = -1;
		dlg[4] = 6;
		dlg[2] = 4;
		esi = (char*) d2_RunCityScrollMapDialog(1, dlg, txt, 0, 0);
		if (esi == 0 || *(short*) (esi + 0x27) == 0) {
			return 0;
		}
		*(int*) (msg + 8) = *(int*) (cmd + 4);
		*(int*) (msg + 0x28) = gm_GameTime;
		*(int*) (msg + 0x2c) = gm_GameTimeHour;
		*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
		*(int*) (msg + 0x58) = *(int*) (esi + 1);
		*(short*) (msg + 0x6e) = 0x177;
		msg[4] = 0x76;
		*(int*) (msg + 0xc) = -1;
		*(short*) (msg + 0x34) = gm_GameTimeTailWord;
		msg[0x36] = 0xa;
		cm_SendCopyEntityData(msg);
		cm_BeginPacketFieldDelta(*(int*) action, *(int*) (*(int*) action + 2));
		h = *(short*) action;
		cm_AppendPacketFieldDelta(4, 1, h - cm_PacketDeltaBase + 0x25, esi + 1);
		cm_RequestChangeAttribute();
		slot = (char*) (0x7f4ca0 + *(unsigned short*) (esi + 0x27) * 0x21c);
		gm_ApplyRandomDisease(slot, 0, 0);
		if (((char*) (0x7f4ca0 + *(unsigned short*) (esi + 0x27) * 0x21c))[2] == 6
		    || ((char*) (0x7f4ca0 + *(unsigned short*) (esi + 0x27) * 0x21c))[2] == 7) {
			io_FormatTextBuffer(line, 0xff1);
		slot = (char*) (0x7f4ca0 + *(unsigned short*) (esi + 0x27) * 0x21c);
			he_PostEntityMessage(*(int*) (slot + 4), -1, line, 0, 0x5fb, 0);
		}
		return 1;
	}
	esi = (char*) fcn_00503fe0(1, 1, *(int*) (action + 4));
	if (esi == 0 || *(short*) (esi + 0x27) == 0) {
		return 0;
	}
	*(int*) (msg + 8) = *(int*) (cmd + 4);
	*(int*) (msg + 0x28) = gm_GameTime;
	*(int*) (msg + 0x2c) = gm_GameTimeHour;
	*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
	*(int*) (msg + 0x58) = *(int*) (esi + 1);
	*(short*) (msg + 0x6e) = 0x177;
	msg[4] = 0x76;
	*(int*) (msg + 0xc) = -1;
	*(short*) (msg + 0x34) = gm_GameTimeTailWord;
	msg[0x36] = 0xa;
	cm_SendCopyEntityData(msg);
	cm_BeginPacketFieldDelta(*(int*) action, *(int*) (*(int*) action + 2));
	h = *(short*) action;
	cm_AppendPacketFieldDelta(4, 1, h - cm_PacketDeltaBase + 0x25, esi + 1);
	cm_RequestChangeAttribute();
	slot = (char*) (0x7f4ca0 + *(unsigned short*) (esi + 0x27) * 0x21c);
	if (gm_HasActiveSpecialObject(slot, 0x2c4) == 0 || 0.75f < gm_RandomFloat01()) {
		slot = (char*) (0x7f4ca0 + *(unsigned short*) (esi + 0x27) * 0x21c);
		gm_ApplyRandomDisease(slot, 0, 0);
	}
	if (((char*) (0x7f4ca0 + *(unsigned short*) (esi + 0x27) * 0x21c))[2] == 6
	    || ((char*) (0x7f4ca0 + *(unsigned short*) (esi + 0x27) * 0x21c))[2] == 7) {
		io_FormatTextBuffer(line, 0xff1);
		slot = (char*) (0x7f4ca0 + *(unsigned short*) (esi + 0x27) * 0x21c);
		he_PostEntityMessage(*(int*) (slot + 4), -1, line, 0, 0x5fb, 0);
	}
	return 1;
}
