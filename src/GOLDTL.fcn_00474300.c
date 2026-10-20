int __cdecl fcn_00411610();
void __cdecl fcn_0046b2b0(int id);
int __cdecl fcn_00469c30(int x, int y, int a3);
int __cdecl fcn_00469c40(int x, int y, int win);
int __cdecl fcn_0046b520();
int __cdecl fcn_0064eeec(char* s);
int __cdecl fcn_00657a73(int a0, char* s, int n);

/* ADDRESS: GOLDTL 0x00474300 */
int __cdecl fcn_00474300(void)
{
	int w;
	int w2;
	int i;
	int n;
	int len;
	int id;
	int item;
	int max;
	int t0;
	int t;
	char* text;

	t0 = (int) *(short*) 0x14ce8c2;
	if (*(unsigned char*) 0x14cf950 == 0) {
		return 0;
	}
	switch (*(unsigned char*) 0x14cf950) {
	case 0x0e:
		w = *(int*) 0x7725d0;
		text = (char*) (w + 0x2c);
		len = 0;
		while (text[len] != 0) {
			len++;
		}
		if (len > 0) {
			*(char*) (w + 0x2b + len) = 0;
		}
		*(unsigned char*) 0x14cf950 = 0;
		break;
	case 0x0f:
		w = *(int*) 0x7725d0;
		i = *(int*) (w + 0x134);
		item = *(int*) (*(int*) 0x1015ea0 + i * 0x2f4 + 0x40);
		if (*(unsigned char*) 0x14cf736 != 0 || *(unsigned char*) 0x14cf72a != 0) {
			i = *(int*) 0x100f1cc;
			if (i == 0) {
				i = *(int*) (item + 0x2c);
				*(int*) 0x100f1cc = i;
			}
			i--;
			if (i < 0) {
				goto nav_tail;
			}
			for (;;) {
				id = *(int*) (*(int*) (item + 0x28) + i * 4);
				t = 189 * id;
				if (*(int*) (*(int*) 0x1015ea0 + t * 4 + 0x20) == 0x41 && *(int*) (*(int*) 0x1015ea0 + t * 4 + 0x48) == 0) {
					break;
				}
				i--;
				if (i < 0) {
					goto nav_tail;
				}
			}
		} else {
			i = *(int*) 0x100f1cc;
			if (i >= *(int*) (item + 0x2c) - 1) {
				*(int*) 0x100f1cc = -1;
				i = -1;
			}
			i++;
			if (i >= *(int*) (item + 0x2c)) {
				goto nav_tail;
			}
			for (;;) {
				id = *(int*) (*(int*) (item + 0x28) + i * 4);
				t = 189 * id;
				if (*(int*) (*(int*) 0x1015ea0 + t * 4 + 0x20) == 0x41 && *(int*) (*(int*) 0x1015ea0 + t * 4 + 0x48) == 0) {
					break;
				}
				i++;
				if (i >= *(int*) (item + 0x2c)) {
					goto nav_tail;
				}
			}
		}
		*(int*) 0x100f1cc = i;
		t = 189 * *(int*) (w + 0x134);
		*(int*) (*(int*) 0x1015ea0 + t * 4 + 0x3c) = 0;
		id = *(int*) (*(int*) (item + 0x28) + i * 4);
		t = 189 * id;
		w2 = *(int*) (*(int*) 0x1015ea0 + t * 4 + 0xc);
		*(int*) 0x7725d0 = w2;
		t = 189 * *(int*) (w2 + 0x134);
		*(int*) (*(int*) 0x1015ea0 + t * 4 + 0x3c) = 1;
		*(int*) 0x100f1d4 = *(int*) 0x6772c0 - t0;
		*(int*) 0x100f940 = *(int*) (w2 + 0x12c);
		*(int*) 0x100f950 = 0;
nav_tail:
		i = *(int*) 0x67d8ec;
		if (i != -1) {
			fcn_0046b2b0(i);
			w = *(int*) 0x7725d0;
			*(int*) 0x67d8ec = -1;
		}
		if (*(unsigned char*) (w + 0x28) & 1) {
			i = fcn_0046b520((char*) (w + 0x2c), *(int*) (w + 0x138)) + *(int*) (*(int*) 0x7725d0 + 4);
			*(int*) 0x100f898 = i;
			n = *(int*) (*(int*) 0x7725d0 + 8);
			*(int*) 0x100f89c = n;
			n -= 7;
			if (*(int*) 0x67d8ec == -1) {
				*(int*) 0x67d8ec = fcn_00469c30((short) i, (short) n, *(int*) 0x67d3b0 + 8);
			} else {
				fcn_00469c40(i, n, *(int*) 0x67d8ec);
			}
			w = *(int*) 0x7725d0;
		}
		*(unsigned char*) 0x14cf950 = 0;
		break;
	case 0x1c:
		w = *(int*) 0x7725d0;
		i = *(int*) (w + 0x134);
		*(int*) (*(int*) 0x1015ea0 + i * 0x2f4 + 0x3c) = 0;
		*(int*) 0x7725d0 = 0;
		*(int*) 0x7725e4 = 0;
		i = *(int*) 0x67d8ec;
		if (i != -1) {
			fcn_0046b2b0(i);
			*(int*) 0x67d8ec = -1;
		}
		break;
	case 0x01:
	case 0x3b:
	case 0x3c:
	case 0x3d:
	case 0x3e:
	case 0x3f:
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x44:
	case 0x57:
	case 0x58:
		break;
	default:
		w = *(int*) 0x7725d0;
		n = *(unsigned char*) 0x14cf950;
		if (*(unsigned char*) (w + 0x28) & 2) {
			if (n < 2 || n > 0xb) {
				break;
			}
			if (*(unsigned char*) 0x14cf736 != 0 || *(unsigned char*) 0x14cf72a != 0) {
				break;
			}
			fcn_00657a73(*(int*) (w + 0x12c), (char*) (w + 0x2c), 10);
			w = *(int*) 0x7725d0;
		}
		text = (char*) (w + 0x2c);
		len = 0;
		while (text[len] != 0) {
			len++;
		}
		if (*(unsigned char*) (w + 0x28) & 1) {
			max = *(int*) (w + 0x18);
		} else {
			max = *(unsigned char*) (w + 0x24);
		}
		if (len >= max) {
			break;
		}
		if (*(int*) (w + 0x15c) != 0 && *(int*) 0x100f898 > *(int*) (w + 4) + *(int*) (w + 0x15c)) {
			break;
		}
		if (*(unsigned char*) 0x14cf736 != 0 || *(unsigned char*) 0x14cf72a != 0) {
			t0 = fcn_00411610(1, 0, 0, n);
		} else {
			t0 = fcn_00411610(0, 0, 0, n);
		}
		*(char*) (*(int*) 0x7725d0 + len + 0x2c) = (char) t0;
		*(char*) (*(int*) 0x7725d0 + len + 0x2d) = 0;
		*(unsigned char*) 0x14cf950 = 0;
		break;
	}
	w = *(int*) 0x7725d0;
	if (w == 0) {
		return 0;
	}
	if (*(unsigned char*) (w + 0x28) & 2) {
		*(int*) (w + 0x12c) = fcn_0064eeec((char*) (w + 0x2c));
		w = *(int*) 0x7725d0;
	}
	i = fcn_0046b520((char*) (w + 0x2c), *(int*) (w + 0x138)) + *(int*) (w + 4);
	*(int*) 0x100f898 = i;
	if (*(int*) 0x67d8ec == -1) {
		return 0;
	}
	fcn_00469c40(i, *(int*) 0x100f89c - 7, *(int*) 0x67d8ec);
	return 0;
}
