


void __cdecl io_FormatTextBuffer(char*, const char*, ...);

void __cdecl fcn_0058ba20(char* o, char* buf)
{
	if (*(int*) (o + 0x30) != 0 && *(int*) (o + 0x34) != 0) {
		if (*(int*) (o + 0x38) == 0) {
			io_FormatTextBuffer(buf, "%s, %s", *(int*) (o + 0x30) + 0x114, *(int*) (o + 0x34) + 0x130);
		}
		else {
			io_FormatTextBuffer(buf, "%s, %s", *(int*) (o + 0x30) + 0x11e, *(int*) (o + 0x34) + 0x18f);
		}
	}
	else if (*(int*) (o + 0x30) != 0) {
		if (*(int*) (o + 0x38) == 0) {
			io_FormatTextBuffer(buf, "%s", *(int*) (o + 0x30) + 0x114);
		}
		else {
			io_FormatTextBuffer(buf, "%s", *(int*) (o + 0x30) + 0x11e);
		}
	}
	else if (*(int*) (o + 0x34) != 0) {
		if (*(int*) (o + 0x38) == 0) {
			io_FormatTextBuffer(buf, "%s", *(int*) (o + 0x34) + 0x130);
		}
		else {
			io_FormatTextBuffer(buf, "%s", *(int*) (o + 0x34) + 0x18f);
		}
	}
	else {
		buf[0] = 0;
	}
}
