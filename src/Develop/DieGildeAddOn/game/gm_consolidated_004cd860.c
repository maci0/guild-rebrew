typedef struct {
	short v[7];
} stamp14;

extern int nt_ClientSocket;
extern int gm_NextEntityId;
extern char cm_LastObjectId[];

char* __cdecl gm_SearchTable67(int);
char* __cdecl gm_QueryEntities(int, int, int, int);
char* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl gm_AllocObjekt(int, int, int);

int __cdecl gv_BuryInGrave(char*);
int __cdecl gv_RentGravePlot(char*);
int __cdecl fcn_004f2880(char*);
int __cdecl fcn_004f2a80(char*);
int __cdecl fcn_004f2c00(char*);
int __cdecl fcn_004f2d90(char*);
int __cdecl fcn_004f2ee0(char*);
int __cdecl fcn_0064d3f8(void);

/* ADDRESS: GOLDTL 0x004cd860 */
int __cdecl fcn_004cd860(char* input, char* response)
{
	char* e1;
	char* e2;
	char* q;

	if (nt_ClientSocket != -1)
		gm_NextEntityId = *(int*) (input + 0x10);
	if (response != 0) {
		response[0] = 2;
		response[1] = 0;
		*(int*) (response + 6) = 0;
	}
	e1 = gm_SearchTable67(*(int*) (input + 0x26));
	if (e1 == 0)
		return 1;
	e2 = gm_SearchTable67(*(int*) (input + 0x14));
	if (e2 == 0)
		return 1;
	for (q = gm_QueryEntities(*(int*) (e2 + 0x5d), 1, 0, 0xca); q != 0; q = gm_NextEntityQueryMatch()) {
		if (*(int*) (q + 0x2a) == *(int*) (e1 + 1))
			goto found;
	}
	q = gm_AllocObjekt(*(int*) (e2 + 1), 0xca, 1);
	if (q == 0)
		return 1;
	(*(int*)cm_LastObjectId) = *(int*) (q + 2);
found:
	*(stamp14*) (q + 0x1c) = *(stamp14*) (input + 0x18);
	*(int*) (q + 0x2a) = *(int*) (input + 0x26);
	*(int*) (q + 0x32) = *(int*) (input + 0x2e);
	q[0x36] = input[0x32];
	*(unsigned char*) (q + 0x37) += input[0x33];
	*(unsigned char*) (q + 0x37) = *(unsigned char*) (q + 0x37) > 100 ? 100 : *(unsigned char*) (q + 0x37);
	if (response != 0)
		response[0] = 1;
	return 0;
}

/* ADDRESS: GOLDTL 0x004cd990 */
int __cdecl cm_DispatchGraveyardCommand(char* input, char* response)
{
	int r;
	char* p;

	if (response != 0) {
		response[0] = 2;
		response[1] = 0;
		*(int*) (response + 6) = 0;
	}
	if (*(int*) 0x14cbca0 != -1) {
		*(int*) 0x699364 = *(int*) (input + 0x27);
	} else {
		*(int*) (input + 0x2b) = fcn_0064d3f8();
	}
	p = input + 0x10;
	switch (*(int*) p) {
	case 0:
		r = gv_BuryInGrave(p);
		break;
	case 1:
		r = gv_RentGravePlot(p);
		break;
	case 2:
		r = fcn_004f2880(p);
		break;
	case 3:
		r = fcn_004f2a80(p);
		break;
	case 4:
		r = fcn_004f2c00(p);
		break;
	case 5:
		r = fcn_004f2d90(p);
		break;
	case 6:
		r = fcn_004f2ee0(p);
		break;
	default:
		return -1;
	}
	if (response != 0 && r == 0)
		response[0] = 1;
	return r;
}
