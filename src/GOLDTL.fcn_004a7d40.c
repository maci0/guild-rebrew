extern char* g_1007cd4;

void __cdecl fcn_004a7f90(int* h, int* rank_n, int* rank, int* suit_n, int* suit);
int __cdecl fcn_004a7770(int* h, int a2, int skip, int* out);
int __cdecl fcn_0042e410(int);

/* ADDRESS: GOLDTL 0x004a7d40 */
void __cdecl fcn_004a7d40(void)
{
	char* p;
	char* q;
	int rank_n;
	int row;
	int off;
	int suit_rank;
	int rank;
	char suit_n[4];
	char suit[4];
	int i;
	int j;
	int n;

	off = 0x34;
	row = 1;
	do {
		p = g_1007cd4 + off;
		if (*(int*) (p + 0x30) == 0
		    && *(int*) (p + 0x24) == 0
		    && *(unsigned char*) (g_1007cd4 + 0xb5) >= 4) {
			*(int*) (p + 0x2c) = *(int*) g_1007cd4;
		}
		i = 0;
		j = 0;
		do {
			q = g_1007cd4 + j;
			if (i != row && *(int*) (q + 0x2c) <= -1) {
				fcn_004a7f90((int*) (q + 4), &rank_n, &rank, (int*) suit_n, (int*) suit);
				switch (*(int*) (p + 0x30)) {
				case 0:
					if (*(int*) (p + 0x24) != 0) {
						if (rank_n >= 3) {
							goto set_g;
						}
					} else if (rank_n >= 2 || fcn_0042e410(4) == 1) {
						goto set_g;
					}
					break;
				case 1:
					if (*(int*) (p + 0x24) != 0) {
						if (fcn_004a7770((int*) (p + 0xc), 0, 7, (int*) suit_n) < rank_n
						    && *(int*) g_1007cd4 >= 6
						    && *(unsigned char*) (g_1007cd4 + 0xb5) >= 5) {
							goto set_g;
						}
					} else {
						n = fcn_004a7770((int*) (p + 0xc), 0, 7, &suit_rank);
						if (*(int*) g_1007cd4 >= 6 && n <= rank_n && (n < rank_n || suit_rank < rank)) {
							goto set_g;
						}
					}
					break;
				case 2:
					if (*(int*) (p + 0x24) == 0
					    && (n = fcn_004a7770((int*) (p + 0xc), 0, 7, (int*) suit_n), *(unsigned char*) (g_1007cd4 + 0xb5) <= 4)
					    && n == 3
					    && fcn_0042e410(4) == 1) {
						goto set_g;
					}
					break;
				case 3:
					if (*(int*) (p + 0x24) == 0
					    && (n = fcn_004a7770((int*) (p + 0xc), 0, 7, (int*) suit_n), *(unsigned char*) (g_1007cd4 + 0xb5) <= 4)
					    && n == 3
					    && fcn_0042e410(5) == 1) {
						goto set_g;
					}
					break;
				}
set_g:
				*(int*) (p + 0x2c) = *(int*) g_1007cd4;
			}
			j += 0x34;
			i++;
		} while (j < 0x68);
		off += 0x34;
		row++;
	} while (off < 0x9c);
}
