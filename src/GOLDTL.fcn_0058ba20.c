// FUNCTION: GOLD 0x583410
// SIZE: 240
// FUNCTION: GOLDTL 0x0058ba20
// SIZE: 234

void __cdecl fcn_0051af00(char*, const char*, ...);

void __cdecl fcn_0058ba20(char* o, char* buf)
{
	if (*(int*) (o + 0x30) != 0 && *(int*) (o + 0x34) != 0) {
		if (*(int*) (o + 0x38) == 0) {
			fcn_0051af00(buf, "%s, %s", *(int*) (o + 0x30) + 0x114, *(int*) (o + 0x34) + 0x130);
		}
		else {
			fcn_0051af00(buf, "%s, %s", *(int*) (o + 0x30) + 0x11e, *(int*) (o + 0x34) + 0x18f);
		}
	}
	else if (*(int*) (o + 0x30) != 0) {
		if (*(int*) (o + 0x38) == 0) {
			fcn_0051af00(buf, "%s", *(int*) (o + 0x30) + 0x114);
		}
		else {
			fcn_0051af00(buf, "%s", *(int*) (o + 0x30) + 0x11e);
		}
	}
	else if (*(int*) (o + 0x34) != 0) {
		if (*(int*) (o + 0x38) == 0) {
			fcn_0051af00(buf, "%s", *(int*) (o + 0x34) + 0x130);
		}
		else {
			fcn_0051af00(buf, "%s", *(int*) (o + 0x34) + 0x18f);
		}
	}
	else {
		buf[0] = 0;
	}
}
