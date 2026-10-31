/* Build the trade/shop inventory page: clear the entry list, fill the row
 * records from the global item tables and hand them to the page builder. */

extern unsigned char g_773d75;

void __cdecl fcn_00500bb0(int, int, int, int);
void __cdecl fcn_005091d0(int*, int*);
int __cdecl io_FormatTextBuffer(char*, char*, ...);
void __cdecl fcn_0064d530(void*, void*, int);
void __cdecl fcn_00402340(void*, int);
int __cdecl fcn_0050b710(int);

/* ADDRESS: GOLDTL 0x00559200 */
void __cdecl fcn_00559200(int a0)
{
	int i;
	int n;
	int v5;
	int count;
	unsigned short tag;
	char list[5][0x18];
	char row[0x24];
	char line[0x100];
	char text[0x100];
	char rec[0x60];
	int sel;

	if (*(int*) (a0 + 0x70)) {
		if (*(int*) (a0 + 0x70) != 1) {
			return;
		}
		fcn_00500bb0(a0 + 0x52, 0x18, 0, 0);
		*(unsigned short*) (a0 + 0x56) = 7;
		*(int*) (a0 + 0x58) = 0;
		*(int*) (a0 + 0x70) = 0;
		return;
	}
	count = 0;
	sel = 0xcf;
	fcn_005091d0(&sel, &count);
	*(unsigned short*) (rec + 0) = 1;
	*(unsigned short*) (rec + 2) = 3;
	*(unsigned short*) (rec + 4) = 0xcf;
	i = 0;
	do {
		io_FormatTextBuffer(text, (char*) 0x679060, i + 0x16b7);
		fcn_0064d530(list[i], text + 0xc, 0x18);
		list[i][0x17] = 0;
		i += 1;
	} while (i < 5);
	fcn_0064d530(rec, (char*) (0x868080 + (unsigned int) g_773d75 * 0x2f4),
	             0x18);
	*(int*) (rec + 0x20) = *(int*) 0x6a6000;
	*(int*) (rec + 0x24) = *(int*) 0x6a6004;
	*(char*) (rec + 0x28) = *(char*) 0x6a6008;
	*(int*) (rec + 0x38) = *(int*) 0x6a5ff0;
	*(int*) (rec + 0x3c) = *(int*) 0x6a5ff4;
	*(int*) (rec + 0x40) = *(int*) 0x6a5ff8;
	*(char*) (rec + 0x44) = *(char*) 0x6a5ffc;
	*(char*) (rec + 0x58) = (char) sel;
	fcn_00402340(rec, tag);
	if (count > 0) {
		n = 0;
		tag = 0xb9;
		do {
			v5 = *(unsigned short*) (row + 0) * 0x21c;
			text[0] = 1;
			text[1] = 2;
			text[2] = 0xb9;
			*(int*) (text + 0xa) = *(int*) (0x7f4ca4 + v5);
			*(int*) (text + 0x33) = *(int*) (0x7f4ca0 + v5 + 0x30);
			*(char*) (text + 0x37) = *(char*) (0x7f4ca0 + v5 + 0x34);
			*(int*) (row + 0x1c) = fcn_0050b710(*(int*) (0x7f4ca0 + v5));
			fcn_00402340(text, tag);
			n += 1;
		} while (n < count);
	}
	*(int*) (a0 + 0x52) = *(int*) 0x7f4c00;
	*(int*) (a0 + 0x56) = *(int*) 0x7f4c04;
	*(int*) (a0 + 0x5a) = *(int*) 0x7f4c08;
	*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) 0x7f4c0c;
	fcn_00500bb0(a0 + 0x52, 1, 0, 0);
	if (*(unsigned short*) (a0 + 0x56) <= 0x14) {
		return;
	}
	*(int*) (a0 + 0x70) = *(int*) (a0 + 0x70) + 1;
}
