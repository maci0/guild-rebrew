/* Runs the town trade/settlement dialog: opens the window, collects the shop
   list, draws the goods rows and processes input until the player closes it. */

int __cdecl fcn_00525fb0(void*);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_0052a0c0(void*, unsigned int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_00594340(void);
void __cdecl fcn_00533dc0(int, int, int);
void __cdecl fcn_00533f40(int, int, int, int);
int __cdecl fcn_00472830(int, int, int, int*, int*, int*);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl fcn_0050e000(int, int, int);
int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl fcn_005462a0(void);
int __cdecl fcn_0057eba0(int, void*, int, unsigned int);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_004c4480(int);
void __cdecl fcn_004c35f0(void);
void __cdecl fcn_00529160(void*, int, int, int);
void __cdecl fcn_00526120(int, int);
int __cdecl fcn_0057ecc0(void);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00502850(void);
int __cdecl fcn_0050df70(int, int);
void __cdecl fcn_00657a73(int, int*, int);
void __cdecl fcn_0046f940(int, int*);
void __cdecl fcn_00595330(int, int, int, int, int);
void __cdecl fcn_00595e20(void*, int);
void __cdecl fcn_005963f0(int, int, int, void*);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0052a2d0(void);

/* ADDRESS: GOLDTL 0x005944d0 */
unsigned int __cdecl fcn_005944d0(unsigned char* a0)
{
	unsigned char* p;
	int window;
	int saved;
	int item;
	int entry;
	int count;
	int idx;
	int limit;
	int i;
	int n;
	int row;
	unsigned int id;
	unsigned int v33;
	unsigned int v34;
	unsigned int v37;
	unsigned int v38;
	unsigned int v39;
	int v13;
	int rect1[4];
	int rect2[4];
	int list[10];
	char tmpl[0x78];
	unsigned short v3;

	p = a0;
	idx = 1;
	item = fcn_00525fb0(a0);
	if (item) {
		return 0;
	}
	fcn_0057e880(0x1f, 0, 0, 0);
	window = fcn_00470820(0, 0, (char*) 0x6aa148);
	saved = window;
	fcn_00471b60(window);
	id = (*(unsigned char*) (*(int*) 0x868050 + (unsigned int) *p * 0x24d) != 0x1e) ? 0 : 2;
	fcn_0052a0c0(p, id);
	fcn_004727a0(window, 3);
	fcn_00519190(0xb7);
	fcn_00594340();
	count = 0;
	fcn_004727a0(window, 0);
	id = 0x70b;
	switch (*(unsigned char*) (*(int*) 0x868050 + (unsigned int) *p * 0x24d)) {
	case 0x13:
	case 0x04:
	case 0x10:
		id = 0x72f;
		break;
	case 0x08:
	case 0x0e:
		id = 0x70f;
		break;
	case 0x06:
		id = 0x713;
		break;
	case 0x16:
		id = 0x717;
		break;
	case 0x0d:
	case 0x0c:
	case 0x0b:
		id = 0x717;
		break;
	}
	fcn_00533dc0(*(int*) 0x772514, id, 0x742);
	fcn_00533f40(0x270, 0x15e, *(int*) 0x772514,
	             fcn_00472830(window, 2, 0x78, rect2, rect1, &v13));
	*(unsigned int*) (*(int*) 0x1015ea0 + 0x84 + v13 * 0x2f4) = 0x54;
	fcn_00473a90(0, 0);
	for (;;) {
		int any;
		int* r;

		fcn_004727a0(window, 2);
		limit = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0xff);
		if (!limit) {
			return 0;
		}
		entry = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x2a);
		if (!entry) {
			return 0;
		}
		if (*(int*) 0x100f1dc != -1 && *(int*) 0x100f884 == window) {
			any = 0;
			r = (int*) 0x7e30e0;
			do {
				if ((int) r >= 0x7e35e0 || r[-4] == 0xffff) {
					break;
				}
				if (*r) {
					any = 1;
				}
				r += 10;
			} while (!any);
			if (1 <= count) {
				row = 0;
				i = count;
				do {
					if (*(int*) 0x67d370 == *(int*) (row + 0x779194)) {
						if (any) {
							int ok;
							int rec;
							int handle;

							ok = 1;
							handle = *(int*) (row + 0x779160);
							rec = *(int*) 0x99ec10 + handle * 0x40;
							v3 = *(unsigned short*) (handle + 0x36 + rec);
							if (fcn_0050e000(entry, handle, v3)) {
								int k;
								unsigned short* q;

								k = 0;
								q = (unsigned short*) (handle + rec + 0x2e);
								do {
									unsigned short val;

									val = *q;
									if (!val) {
										break;
									}
									if (val != 0xffff) {
										int got;

										got = fcn_00502cd0(*(int*) (entry + 0x14), 1, 0, val);
										if (!got ||
										    *(int*) (got + 0xe) < (int) q[-4]) {
											ok = 0;
										}
									}
									k++;
									q += 4;
								} while (k < 4);
								if (ok) {
									int found;

									found = fcn_005463a0(2, 0, 4, 3, *(int*) (p + 1));
									while (found) {
										if (*(unsigned int*) (found + 0xac) ==
										    *(unsigned int*) (row + 0x779160)) {
											goto found_row;
										}
										found = fcn_005462a0();
									}
									if (fcn_0057eba0(0x20, p, 0,
									                 *(unsigned int*) (row + 0x779160)) == 1) {
										for (i = 0; i < 0x1e; i++) {
											*(int*) (tmpl + i * 4) = 0;
										}
										if (*(unsigned short*) (p + 0x27) != 0xffff) {
											v33 = *(unsigned int*) (*(unsigned short*) (p + 0x27) * 0x21c + 0x7f4ca4);
										} else {
											v33 = *(unsigned int*) (*(int*) 0x774970 * 0x21c + 0x7f4ca4);
										}
										v34 = *(unsigned int*) (p + 1);
										*(int*) (tmpl + 0x0c) = *(int*) (entry + 2);
										*(int*) (tmpl + 0x10) = v34;
										*(int*) (tmpl + 0x1c) = 0xffffffff;
										*(unsigned short*) (tmpl + 0x20) =
										    *(unsigned short*) (row + 0x779160);
										*(char*) (tmpl + 0x42) = 1;
										*(unsigned short*) (tmpl + 0x44) =
										    *(unsigned short*) 0x7f4c0c;
										*(int*) (tmpl + 0x48) = *(int*) 0x7f4c08;
										*(int*) (tmpl + 0x4c) = *(int*) 0x7f4c04;
										*(int*) (tmpl + 0x50) = *(int*) 0x7f4c00;
										*(int*) (tmpl + 0x64) = 0;
										*(int*) (tmpl + 0x68) = 0;
										*(int*) (tmpl + 0x6c) = v34;
										*(int*) (tmpl + 0x70) = v33;
										*(int*) (tmpl + 0x74) = 4;
										found = fcn_004c5530(tmpl);
										if (found != -1) {
											while (!fcn_004c4450(found)) {
												fcn_005373e0(0, 0x20007);
											}
										}
										found = fcn_004c4480(found);
										fcn_0057e880(0x20, 0, 0, 0);
									}
found_row:
									fcn_004c35f0();
									r = (int*) 0x7e30d0;
									do {
										if (*r == 0xffff) {
											break;
										}
										if (r[4]) {
											fcn_00529160(p, *(int*) 0x7746cc, *r, found);
											*(unsigned char*) (*r * 0x21c + 0x7f4e28) = 0;
										}
										r += 10;
									} while ((int) r < 0x7e35d0);
									if (found && !*(int*) (found + 0x70)) {
										*(unsigned int*) (found + 0x70) = 1;
									}
								} else {
									fcn_00526120(*(int*) 0x14a5620, 0);
								}
							} else {
								unsigned char kind;

								kind = *(unsigned char*) (handle + rec);
								if (kind != '%' && kind != 0x17) {
									fcn_00526120(*(int*) 0x14a561c, 0);
								} else {
									fcn_00526120(*(int*) 0x14a5618, 0);
								}
							}
						} else {
							int* r2;

							r2 = (int*) 0x7e30d0;
							do {
								int base;
								unsigned char* obj;

								if (*r2 == 0xffff) {
									break;
								}
								base = *r2 * 0x21c;
								obj = *(unsigned char**) (base + 0x7f4e1c);
								if (obj && *obj == 0x04 &&
								    *(int*) (obj + 0x10) == *(int*) (p + 1) &&
								    !(*(unsigned int*) (base + 0x7f4e68) & 0x800) &&
								    *(unsigned short*) (obj + 0xac) ==
								        *(unsigned int*) (row + 0x779160)) {
									*(unsigned char*) (base + 0x7f4e28) = 1;
								}
								r2 += 10;
							} while ((int) r2 < 0x7e35d0);
						}
					}
					row += 0x58;
					i--;
				} while (i);
			}
		}
		if (*(int*) 0x14ce8e0) {
			any = 0;
			r = (int*) 0x7e30e0;
			do {
				if ((int) r >= 0x7e35e0 || r[-4] == 0xffff) {
					break;
				}
				if (*r) {
					any = 1;
				}
				r += 10;
			} while (!any);
			if (!any) {
				if (fcn_0057ecc0() == 1) {
					*(int*) 0x774654 = 1;
					fcn_00532ef0();
				}
				goto after_input;
			}
			r = (int*) 0x7e30d0;
			do {
				int slot;

				slot = *r;
				if (slot == 0xffff) {
					break;
				}
				r += 10;
				*(unsigned char*) (slot * 0x21c + 0x7f4e28) = 0;
			} while ((int) r < 0x7e35d0);
		}
after_input:
		{
			unsigned short* shop;
			int* cell;

			shop = (unsigned short*) fcn_00502cd0(*(int*) (limit + 0x14), 1, 5);
			n = count;
			if (shop) {
				cell = (int*) (count * 0x58 + 0x779160);
				do {
					int dup;

					dup = 1;
					if (2 <= *(int*) ((char*) shop + 14)) {
						int k;
						int* c;

						k = 0;
						c = (int*) 0x779160;
						do {
							if (count <= k) {
								if (dup && (int) cell <= 0x7796df) {
									count++;
									*cell = *(int*) shop;
									cell += 0x16;
								}
								break;
							}
							if (*c == *(int*) shop) {
								dup = 0;
							}
							k++;
							c += 0x16;
						} while (dup);
					}
					shop = (unsigned short*) fcn_00502850();
				} while (shop);
				n = count;
			}
			if (1 <= n) {
				int* r3;
				int rows;

				r3 = (int*) 0x7791b0;
				rows = count;
				do {
					int* cells;
					int off;
					int got;

					cells = r3 - 0x13;
					*r3 = 0x7fffffff;
					off = 0x26;
					do {
						*cells = *(unsigned short*) (off + r3[-0x14] * 0x41 + 8 +
						                              *(int*) 0x99ec10);
						cells[4] = *(unsigned short*) (off + r3[-0x14] * 0x41 +
						                               *(int*) 0x99ec10);
						if (*cells) {
							got = fcn_00502cd0(*(int*) (entry + 0x14), 1, 0, *cells);
							if (got) {
								int best;
								int t;

								best = *r3;
								t = fcn_0050df70(entry, got) /
								    *(unsigned short*) (off + r3[-0x14] * 0x41 +
								                        *(int*) 0x99ec10);
								if (t <= best) {
									*r3 = t;
								}
							} else {
								*r3 = 0;
							}
						}
						off += 2;
						cells++;
					} while (off < 0x2e);
					*r3 = *(unsigned short*) (r3[-0x14] * 0x41 + 0x36 +
					                          *(int*) 0x99ec10) * *r3;
					got = fcn_00502cd0(*(int*) (entry + 0x14), 1, 0, r3[-0x14]);
					if (got) {
						r3[1] = fcn_0050df70(entry, got);
					} else {
						r3[1] = 0;
					}
					r3 += 0x16;
					rows--;
				} while (rows);
			}
			fcn_00657a73(count, list, 10);
			fcn_0046f940(v13, list);
			window = saved;
			*(unsigned int*) (*(int*) 0x1015ea0 + 0x6c + v13 * 0x2f4) = 1;
			*(unsigned int*) (*(int*) 0x1015ea0 + 0x18 + v13 * 0x2f4) = 0x30;
			fcn_00595330(saved, 2, count, entry, 0);
			if (idx) {
				fcn_004727a0(saved, 2);
				idx = 0;
				*(int*) (*(int*) 0x772514 * 0x3cc + 0x1016198) =
				    *(int*) (*(int*) 0x772514 * 0x3cc + 0x10161b4) *
				    (signed char) a0[0x59];
			}
			fcn_00595e20(a0, entry);
			fcn_005963f0(saved, 1, 0, a0);
			if (!fcn_005373e0((void*) 0x5944d0, 0x677c7)) {
				fcn_004727a0(saved, 2);
				a0[0x59] = (unsigned char) ((*(int*) (*(int*) 0x772514 * 0x3cc + 0x10161a0) +
				                             *(int*) (*(int*) 0x772514 * 0x3cc + 0x1016198)) /
				                            *(int*) (*(int*) 0x772514 * 0x3cc + 0x10161b4));
				fcn_00471e30(saved);
				fcn_0052a2d0();
				fcn_0057e880(0x1f, 0, 1, 0);
				return 0;
			}
		}
	}
}
