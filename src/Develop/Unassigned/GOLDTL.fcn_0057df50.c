


extern int g_7749f4;

void __cdecl fcn_0057df50(int id, int on)
{
	switch (id) {
	case 0x605:
		if (on) {
			g_7749f4 |= 1;
		} else {
			g_7749f4 &= ~1;
		}
		break;
	case 0x606:
		if (on) {
			g_7749f4 |= 2;
		} else {
			g_7749f4 &= ~2;
		}
		break;
	case 0x607:
		if (on) {
			g_7749f4 |= 4;
		} else {
			g_7749f4 &= ~4;
		}
		break;
	case 0x608:
		if (on) {
			g_7749f4 |= 8;
		} else {
			g_7749f4 &= ~8;
		}
		break;
	case 0x609:
		if (on) {
			g_7749f4 |= 0x10;
		} else {
			g_7749f4 &= ~0x10;
		}
		break;
	case 0x60a:
		if (on) {
			g_7749f4 |= 0x20;
		} else {
			g_7749f4 &= ~0x20;
		}
		break;
	case 0x60b:
		if (on) {
			g_7749f4 |= 0x40;
		} else {
			g_7749f4 &= ~0x40;
		}
		break;
	case 0x60c:
		if (on) {
			g_7749f4 |= 0x80;
		} else {
			g_7749f4 &= ~0x80;
		}
		break;
	case 0x60d:
		if (on) {
			g_7749f4 |= 0x100;
		} else {
			g_7749f4 &= ~0x100;
		}
		break;
	}
}
