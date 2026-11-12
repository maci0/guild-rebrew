extern char* g_1007cd4;

void __cdecl fcn_004a7f90(int* h, int* rank_n, int* rank, int* suit_n, int* suit);
int __cdecl fcn_004a7770(int* h, int a2, int skip, int* out);
int __cdecl gm_RandomMod(int);

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
	int unused_rank;
	off = 0x34;
	row = 1;
	do {
		p = g_1007cd4 + off + 4;
		if (*(int*) (p + 0x2c) == 0
		    && *(int*) (p + 0x20) == 0
		    && *(unsigned char*) (g_1007cd4 + 0xb5) >= 4) {
			*(int*) (p + 0x28) = *(int*) g_1007cd4;
		}
		i = 0;
		j = 0;
		do {
			q = g_1007cd4 + j;
			if (i != row && *(int*) (q + 0x2c) < 0) {
				fcn_004a7f90((int*) (q + 4), &rank_n, &rank, (int*) suit_n, (int*) suit);
				switch (*(int*) (p + 0x2c)) {
				case 0:
					if (*(int*) (p + 0x20) != 0) {
						if (rank_n >= 3) {
							goto set_g;
						}
					} else if (rank_n >= 2 || (unsigned short) gm_RandomMod(4) == 1) {
						goto set_g;
					}
					break;
				case 1:
					if (*(int*) (p + 0x20) != 0) {
						if (fcn_004a7770((int*) (p + 8), 0, 7, &unused_rank) < rank_n
						    && *(int*) g_1007cd4 >= 6
						    && *(unsigned char*) (g_1007cd4 + 0xb5) >= 5) {
							goto set_g;
						}
					} else {
						n = fcn_004a7770((int*) (p + 8), 0, 7, &suit_rank);
						if (*(int*) g_1007cd4 >= 6 && n <= rank_n && (n < rank_n || suit_rank < rank)) {
							goto set_g;
						}
					}
					break;
				case 2:
					if (*(int*) (p + 0x20) == 0
					    && (n = fcn_004a7770((int*) (p + 8), 0, 7, &unused_rank), *(unsigned char*) (g_1007cd4 + 0xb5) <= 4)
					    && n == 3
					    && (unsigned short) gm_RandomMod(4) == 1) {
						goto set_g;
					}
					break;
				case 3:
					if (*(int*) (p + 0x20) == 0
					    && (n = fcn_004a7770((int*) (p + 8), 0, 7, &unused_rank), *(unsigned char*) (g_1007cd4 + 0xb5) <= 4)
					    && n == 3
					    && (unsigned short) gm_RandomMod(5) == 1) {
						goto set_g;
					}
					break;
				}
				goto next_opponent;
set_g:
				*(int*) (p + 0x28) = *(int*) g_1007cd4;
next_opponent:;
			}
			j += 0x34;
			i++;
		} while (j < 0x68);
		off += 0x34;
		row++;
	} while (off < 0x9c);
}
