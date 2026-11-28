


int __cdecl gm_QueryEntitySum(int, int);
void __cdecl io_FormatTextBuffer(char*, int, int);
void __cdecl d2_ShowModalMessageBox(char*, int);

/* ADDRESS: GOLDDE 0x0050f330 */
int __cdecl d2_CheckFundsAndNotify(short* container, int account_id, int lim, int player_idx)
{
	char buf[0x200];

	if (gm_QueryEntitySum(account_id, player_idx) < lim && lim != 0) {
		if (container != 0 && *container == 0x142) {
			io_FormatTextBuffer(buf, 0x76, (unsigned char) player_idx);
		} else if (container != 0 && *container == 0x115) {
			io_FormatTextBuffer(buf, 0x77, (unsigned char) player_idx);
		} else {
			io_FormatTextBuffer(buf, 0x75, (unsigned char) player_idx);
		}
		d2_ShowModalMessageBox(buf, 4);
		return 0;
	}
	return 1;
}
