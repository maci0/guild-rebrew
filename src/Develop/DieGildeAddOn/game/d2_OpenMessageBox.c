extern int main_LoopFlags;



int __cdecl d2_LoadForm(int, int, const char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl io_AppendText(int);
void __cdecl main_RunFrameLoop(int, int);

/* ADDRESS: GOLDDE 0x0050fb80 */
int __cdecl d2_OpenMessageBox(int a, char flags)
{
	int h;

	if (flags & 0x10) {
		h = d2_LoadForm(0, 0, "misc\\Messagebox_BIG");
	} else if (flags & 0x20) {
		h = d2_LoadForm(0, 0, "misc\\Messagebox_VERY_BIG");
	} else {
		h = d2_LoadForm(0, 0, "misc\\Messagebox");
	}
	d2_CenterDialogWindows(h);
	io_AppendText(a);
	main_RunFrameLoop(0, main_LoopFlags);
	return h;
}
