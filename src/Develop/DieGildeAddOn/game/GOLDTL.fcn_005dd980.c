


void __cdecl fcn_00508cf0(int, int*);
void __cdecl fcn_005dcf40(unsigned char*, int);
void __cdecl fcn_004c6330(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005dd980(unsigned char* e, int* a2)
{
	int first;
	int ids[5];
	char text[0x800];
	int second;
	int i;
	int n;

	second = 0;
	first = 0;
	a2[4] = 1;
	fcn_00508cf0(5, ids);
	i = 0;
	n = 0;
	while (n < 2 && i < 5) {
		if (e[ids[i] + 0x80] < 0xfc) {
			fcn_005dcf40(e, ids[i]);
			n++;
			if (n == 1) {
				first = ids[i];
			}
			else if (n == 2) {
				second = ids[i];
			}
		}
		i++;
	}
	if (e[2] == 6) {
		fcn_004c6330(*(int*) (e + 4));
		io_FormatTextBuffer(text, 0xfe8, **(unsigned short**) a2 * 2 + 0xd71, second + 0x16b7,
		    first + 0x16b7);
		fcn_005dbe90(text);
	}
	return 1;
}
