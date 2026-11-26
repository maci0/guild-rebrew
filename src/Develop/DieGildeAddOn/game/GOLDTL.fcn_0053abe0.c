extern unsigned char g_773d75;
extern char g_6a3bb4[];
/* SIZE 0x10: record copied from g_6a3bb4 */
typedef struct {
	int w[4];
} Blk16_53abe0;

char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int id);
char* __cdecl fcn_00502cd0(int a, int b, int c, int d, ...);
void __cdecl fcn_005059b0(char* e, int a, int b);
void __cdecl fcn_005058b0(char* e, char* q, int a);
int __cdecl fcn_004c51f0(int a, int b, int c, int d, unsigned char k, int n);
void __cdecl fcn_004c6090(char* e, int a, int b, int c);
void __cdecl cm_BeginCommandSync(void);
void __cdecl cm_EndCommandSync(void);
char* __cdecl fcn_004c44c0(void);
void __cdecl fcn_00535960(void);

/* ADDRESS: GOLDTL 0x0053abe0 */
void __cdecl fcn_0053abe0(unsigned int ownerSlot)
{
	char* e;
	char* q;
	int n;

	e = gm_StartFilteredEntitySearch(1, 0, 6);
	if (e != 0) {
		*(Blk16_53abe0*) (e + 5) = *(Blk16_53abe0*) g_6a3bb4;
		fcn_005059b0(e, ownerSlot, ownerSlot);
		q = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0x13);
		if (q != 0) {
			fcn_005058b0(e, q, ownerSlot);
		}
		fcn_004c51f0(*(int*) (e + 1), -1, 0x15, 1, g_773d75, 0);
		fcn_004c51f0(*(int*) (e + 1), -1, 0x17, 1, g_773d75, 0);
		fcn_004c51f0(*(int*) (e + 1), -1, 0x18, 1, g_773d75, 0);
		fcn_004c51f0(*(int*) (e + 1), -1, 0x14, 1, g_773d75, 0);
	}
	e = gm_StartFilteredEntitySearch(1, 0, 0x20);
	if (e != 0) {
		*(short*) (e + 0x25) = (short) ownerSlot;
		*(short*) (e + 0x27) = (short) ownerSlot;
		n = 3;
		do {
			fcn_004c6090(e, 0, 10, 0);
			n--;
		} while (n);
		q = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x2a);
		if (q != 0) {
			cm_BeginCommandSync();
			fcn_004c51f0(*(int*) (q + 2), -1, 0x1d0, 0x19, g_773d75, 0);
			cm_EndCommandSync();
			while (!fcn_004c44c0()) {
				fcn_00535960();
			}
		}
	}
	e = gm_StartFilteredEntitySearch(1, 0, 0x2a);
	if (e != 0) {
		fcn_005059b0(e, ownerSlot, ownerSlot);
		q = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x2a);
		if (q != 0) {
			cm_BeginCommandSync();
			fcn_004c51f0(*(int*) (q + 2), -1, 0x1d0, 0x14, g_773d75, 0);
			fcn_004c51f0(*(int*) (q + 2), -1, 0x1d7, 0x0f, g_773d75, 0);
			fcn_004c51f0(*(int*) (q + 2), -1, 0x1d6, 0x0f, g_773d75, 0);
			fcn_004c51f0(*(int*) (q + 2), -1, 0x158, 10, g_773d75, 0);
			cm_EndCommandSync();
			while (!fcn_004c44c0()) {
				fcn_00535960();
			}
		}
	}
	e = gm_StartFilteredEntitySearch(1, 0, 0x1e);
	if (e != 0) {
		fcn_005059b0(e, ownerSlot, ownerSlot);
	}
	e = gm_StartFilteredEntitySearch(1, 0, 0x1f);
	if (e != 0) {
		fcn_005059b0(e, ownerSlot, ownerSlot);
	}
	e = gm_StartFilteredEntitySearch(1, 0, 0x12);
	if (e != 0) {
		fcn_005059b0(e, ownerSlot, ownerSlot);
	}
	e = gm_StartFilteredEntitySearch(1, 0, 0x14);
	if (e != 0) {
		fcn_005059b0(e, ownerSlot, ownerSlot);
		fcn_004c51f0(*(int*) (e + 1), -1, 0xf7, 1, g_773d75, 0);
	}
	e = gm_StartFilteredEntitySearch(1, 0, 0x32);
	if (e != 0) {
		fcn_005059b0(e, ownerSlot, ownerSlot);
		q = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x2a);
		if (q != 0) {
			cm_BeginCommandSync();
			fcn_004c51f0(*(int*) (q + 2), -1, 0x1cb, 10, g_773d75, 0);
			fcn_004c51f0(*(int*) (q + 2), -1, 0x1cc, 10, g_773d75, 0);
			fcn_004c51f0(*(int*) (q + 2), -1, 0x1d0, 10, g_773d75, 0);
			cm_EndCommandSync();
			while (!fcn_004c44c0()) {
				fcn_00535960();
			}
		}
	}
	e = gm_StartFilteredEntitySearch(1, 0, 0x21);
	if (e != 0) {
		fcn_005059b0(e, ownerSlot, ownerSlot);
		fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x2a);
	}
	e = gm_StartFilteredEntitySearch(1, 0, 0x19);
	if (e != 0) {
		fcn_005059b0(e, ownerSlot, ownerSlot);
		fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x2a);
	}
	e = gm_StartFilteredEntitySearch(1, 0, 0x34);
	if (e != 0) {
		fcn_005059b0(e, ownerSlot, ownerSlot);
		q = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x2a);
		if (q != 0) {
			cm_BeginCommandSync();
			fcn_004c51f0(*(int*) (q + 2), -1, 0x1cb, 10, g_773d75, 0);
			fcn_004c51f0(*(int*) (q + 2), -1, 0x1cc, 10, g_773d75, 0);
			fcn_004c51f0(*(int*) (q + 2), -1, 0x1d0, 10, g_773d75, 0);
			cm_EndCommandSync();
			while (!fcn_004c44c0()) {
				fcn_00535960();
			}
		}
	}
	e = gm_StartFilteredEntitySearch(1, 0, 0x36);
	if (e == 0) {
		return;
	}
	fcn_005059b0(e, ownerSlot, ownerSlot);
	fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x2a);
}
