


void __cdecl fcn_004c4df0(int, int);
int __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5530(int packet)
{
	char buf[0x9c];
	int i;
	int* cursor;

	buf[0] = 0x1c;
	cursor = (int*) (packet + 0x38);
	for (i = 8; i != 0; i--) {
		if (*cursor == 0) {
			*cursor = -1;
		}
		cursor++;
	}
	fcn_004c4df0(0xf8, packet);
	fcn_004c4330(buf);
}
