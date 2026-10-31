extern char g_7f4ca0[];
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;

int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c5620(int, char*);
int __cdecl fcn_004c5da0(unsigned int, unsigned int, int, int, int, char*);
void __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_00529160(int, int, int, int);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_005b2ee0(char*, char*, char*);


/* Runs the plague-heimsuchung action message through its states and updates
 * the action duration it reports back to the caller. */
/* ADDRESS: GOLDTL 0x005784d0 */
void __cdecl fcn_005784d0(char* obj)
{
	unsigned short* lager;
	int state;
	int h;
	int res;
	unsigned int a;
	unsigned int b;

	lager = (unsigned short*) gm_LookupEntityRecordById(*(int*) (obj + 0xb4));
	if (lager == 0) {
		fcn_00546190(obj);
		return;
	}
	state = *(int*) (obj + 0x70);
	if (state == -1 || state == -2) {
		fcn_00529160(0, 0, *lager, (int) obj);
		fcn_00546190(obj);
		return;
	}
	if (*(unsigned char*) (obj + 0x78) & 4) {
		return;
	}
	h = *(int*) (obj + 0x84);
	if (h != -1 && fcn_004c4450(h) == 0) {
		return;
	}
	*(int*) (obj + 0x84) = -1;
	switch (state) {
	case 0:
		if (fcn_004c4450(-1) == 0) {
			return;
		}
		fcn_00529160(0, 0, *lager, (int) obj);
		res = gm_StartFilteredEntitySearch(1, 1, *(int*) (obj + 0xac));
		if (res != 0) {
			a = *(unsigned int*) (res + 1);
			b = *(unsigned int*) &lager[2];
			*(int*) (obj + 0xbc) = fcn_004c5da0(b, a, -1, 0, 1, "HEIMSUCHUNG");
			fcn_004c5620(2, obj);
			return;
		}
		break;
	case 2:
		*(int*) (obj + 0xbc) = -1;
		if (*(int*) (*(int*) &lager[0xc2] + 0x128) != 0) {
			*(int*) (obj + 0x52) = g_7f4c00;
			*(int*) (obj + 0x56) = g_7f4c04;
			*(int*) (obj + 0x5a) = g_7f4c08;
			*(unsigned short*) (obj + 0x5e) = g_7f4c0c;
			fcn_00500bb0(obj + 0x52, 0, 4, 0);
			*(int*) (obj + 0x84) = fcn_004c5620(2, obj);
			return;
		}
		a = *(unsigned int*) (obj + 0xac);
		if (gm_StartFilteredEntitySearch(1, 1, a) != 0) {
			*(int*) (obj + 0x52) = g_7f4c00;
			*(int*) (obj + 0x56) = g_7f4c04;
			*(int*) (obj + 0x5a) = g_7f4c08;
			*(unsigned short*) (obj + 0x5e) = g_7f4c0c;
			h = (int) gm_LookupEntityRecordById(*(int*) (obj + 0xb0));
			if (h != 0) {
				fcn_00500bb0(obj + 0x52, 0x18, 0, 0);
				fcn_005b2ee0(g_7f4ca0 + *(unsigned short*) (obj + 8) * 0x21c,
					(char*) h, obj + 0x52);
			}
			*(int*) (obj + 0x84) = fcn_004c5620(3, obj);
			return;
		}
		break;
	case 3:
		if (*(int*) &lager[0xb6] != 0) {
			a = *(unsigned int*) (*(int*) &lager[0xb6] + 1);
			b = *(unsigned int*) &lager[2];
			*(int*) (obj + 0xbc) = fcn_004c5da0(b, a, -1, 0, 0, "HEIMSUCHUNG");
			*(int*) (obj + 0x84) = fcn_004c5620(4, obj);
			return;
		}
		break;
	case 4:
		if (*(int*) &lager[0xb6] != 0) {
			if (*(int*) (*(int*) &lager[0xc2] + 0x128) == 0) {
				*(int*) (obj + 0x52) = g_7f4c00;
				*(int*) (obj + 0x56) = g_7f4c04;
				*(int*) (obj + 0x5a) = g_7f4c08;
				*(unsigned short*) (obj + 0x5e) = g_7f4c0c;
				fcn_00529160(0, 0, *lager, 0);
				*(int*) (obj + 0x84) = fcn_004c5620(5, obj);
				h = *(int*) (obj + 0xb8) >> 1;
				if (h <= 0) {
					h = 1;
				}
				*(int*) (obj + 0x52) = *(int*) (obj + 0x52) + h + 1;
				return;
			}
			*(int*) (obj + 0x52) = g_7f4c00;
			*(int*) (obj + 0x56) = g_7f4c04;
			*(int*) (obj + 0x5a) = g_7f4c08;
			*(unsigned short*) (obj + 0x5e) = g_7f4c0c;
			fcn_00500bb0(obj + 0x52, 0, 4, 0);
			return;
		}
		break;
	case 5:
		goto set_state;
	default:
		return;
	}
	*(int*) (obj + 0x52) = g_7f4c00;
	*(int*) (obj + 0x56) = g_7f4c04;
	*(int*) (obj + 0x5a) = g_7f4c08;
	*(unsigned short*) (obj + 0x5e) = g_7f4c0c;
set_state:
	*(int*) (obj + 0x84) = fcn_004c5620(-1, obj);
}
