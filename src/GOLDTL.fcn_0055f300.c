int __cdecl gm_ResolveEntityById();
int __cdecl fcn_00500d20(void*, void*);
void __cdecl fcn_0050fef0(int, int);
void __cdecl fcn_00500bb0(void*, int, int, int);
void* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00504e70(int);
int __cdecl fcn_005049a0(unsigned char*);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(unsigned char, unsigned char, unsigned short, char*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00546190(char*);

/* One stage of the message-box tick; state lives at +0x70 of the caller's record. */
/* ADDRESS: GOLDTL 0x0055f300 */
void __cdecl fcn_0055f300(char* e)
{
	void* item;
	char ch;
	char buf[128];
	int p;
	int value;
	int owner;
	int house;
	int i;
	int* clock;

	item = 0;
	switch (*(int*) (e + 0x70)) {
	case 0:
		break;
	case 1:
		gm_ResolveEntityById(0, &item, 0, *(int*) (e + 0xac));
		if (*(int*) (e + 0xd8) != 0) {
			fcn_0051af00(buf, 0x1c49, (*(unsigned short*) item) * 2 + 0x9a8);
			owner = *(int*) (e + 0x10);
			p = fcn_005049a0((unsigned char*) fcn_00504e70(owner));
			house = *(int*) ((*(unsigned short*) (e + 8)) * 0x21c + 0x7f4ca4);
			if (p != 0) {
				value = *(int*) (p + 2);
			} else {
				value = -1;
			}
			he_MessageBoxQuickjump(house, -1, buf, 0, 0x5ec, owner, value, 0, "_NACHRICHTEN_HS_55");
		}
		fcn_004c5420(*(int*) ((char*) item + 2), 0x13, 1, 0, 0x20);
		ch = *(char*) (e + 0xb4);
		fcn_004c4510((char*) item, *(int*) ((char*) item + 2));
		fcn_004c4570(1, 1, 0x12, &ch);
		fcn_004c5360();
		fcn_00546190(e);
		return;
	case -2:
	case -1:
		gm_ResolveEntityById(0, &item, 0, *(int*) (e + 0xac));
		if (item != 0) {
			fcn_004c5420(*(int*) ((char*) item + 2), 0x13, 1, 0, 0x20);
		}
		fcn_00546190(e);
		return;
	default:
		return;
	}
	i = fcn_00500d20(e + 0x60, (void*) 0x7f4c00);
	item = fcn_00502cd0(0, 2, 7, 1, *(int*) (e + 0xac));
	if (item == 0) {
		item = fcn_00502cd0(0, 2, 7, 1, *(int*) (e + 0xac));
		fcn_00546190(e);
		return;
	}
	if ((int) *((unsigned char*) item + 0x12) < *(int*) (e + 0xb4)) {
		fcn_0050fef0(*(int*) (e + 0xac), i / *(int*) (e + 0xb8));
		clock = (int*) (e + 0x52);
		clock[0] = *(int*) 0x7f4c00;
		clock[1] = *(int*) 0x7f4c04;
		clock[2] = *(int*) 0x7f4c08;
		*(unsigned short*) (clock + 3) = *(unsigned short*) 0x7f4c0c;
		fcn_00500bb0(clock, 0, *(int*) (e + 0xb8) * 2, 0);
	} else {
		*(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
	}
	*(int*) (e + 0x60) = *(int*) 0x7f4c00;
	*(int*) (e + 0x64) = *(int*) 0x7f4c04;
	*(int*) (e + 0x68) = *(int*) 0x7f4c08;
	*(unsigned short*) (e + 0x6c) = *(unsigned short*) 0x7f4c0c;
}
