extern char s_67fb68[];
extern char g_7f4ca0[];

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c68c0(void* msg);
void __cdecl fcn_004c58b0(int, int);
void __cdecl fcn_004c51a0(int, int, int, int);
void __cdecl fcn_004c4ef0(char* s);

struct msg_4ab3e0 {
	int tag;
	int who;
	int where;
	int what;
	int amount;
};
// SIZE 0x14

// FUNCTION: GOLD 0x004ab2c0
// SIZE: 288
// FUNCTION: GOLDTL 0x4ab3e0
// SIZE: 288

int __cdecl fcn_004ab3e0(char* a1, char* a2, char* a3)
{
	struct msg_4ab3e0 msg;
	char* e;
	char* q;
	int i;

	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (a3 + 4));
	if (e == 0)
		return 0;
	q = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0x120);
	if (q == 0)
		return 0;
	q = fcn_00502cd0(*(int*) (q + 0x14), 1, 0, 0x12c);
	if (q == 0)
		return 0;
	for (i = 0; i < 3; i++) {
		if (*(int*) (q + 0x1c + i * 4) == *(int*) (a2 + 4))
			break;
	}
	if (i == 3)
		return 0;
	msg.tag = 0x62757920;
	msg.where = *(int*) (e + 1);
	msg.who = *(int*) (a1 + 4);
	msg.what = *(int*) (a2 + 4);
	msg.amount = *(int*) (a2 + 0x10);
	fcn_004c4eb0(s_67fb68);
	fcn_004c68c0(&msg);
	fcn_004c58b0(*(int*) (a2 + 4), *(int*) (a1 + 4));
	fcn_004c51a0(*(int*) (g_7f4ca0 + *(unsigned short*) (e + 0x27) * 540 + 4),
	    *(int*) (a1 + 4), 0, *(int*) (a2 + 0x10));
	fcn_004c4ef0(s_67fb68);
	return 1;
}
