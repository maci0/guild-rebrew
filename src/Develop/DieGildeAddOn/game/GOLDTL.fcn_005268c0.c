extern int main_LoopFlags;



int __cdecl fcn_00470820(int, int, const char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl io_AppendText(int);
void __cdecl fcn_005373e0(int, int);

int __cdecl fcn_005268c0(int a, char flags)
{
	int h;

	if (flags & 0x10) {
		h = fcn_00470820(0, 0, "misc\\Messagebox_BIG");
	} else if (flags & 0x20) {
		h = fcn_00470820(0, 0, "misc\\Messagebox_VERY_BIG");
	} else {
		h = fcn_00470820(0, 0, "misc\\Messagebox");
	}
	d2_CenterDialogWindows(h);
	io_AppendText(a);
	fcn_005373e0(0, main_LoopFlags);
	return h;
}
