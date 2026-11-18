


#include <string.h>

typedef struct Query {
	int kind;
	int a;
	int b;
	char padc[0x214 - 0xc];
	int c;
	int d;
	char* p;
} Query;
// SIZE 0x220

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_004fa5b0(int k, char* e, Query* q);

int __cdecl fcn_004aa0c0(char* entity, char* cmd, char* params)
{
	Query query;
	char* r;
	int k;

	if (*cmd != 0x10) {
		return 0;
	}
	memset(&query, 0, sizeof(query));
	query.p = 0;
	if ((*(int*) (entity + 0x1c8) & 0x100) && *(int*) (cmd + 8) == 4) {
		for (r = fcn_005463a0(1, 0, 0x45); r != 0; r = he_fn_Handlung()) {
			if (*(int*) (r + 0xac) == *(int*) (entity + 4)) {
				break;
			}
		}
		if (r == 0) {
			return 0;
		}
		query.p = gm_LookupEntityRecordById(*(int*) (r + 0xb0));
	}
	query.kind = *(int*) (cmd + 8);
	k = *(int*) (cmd + 4);
	switch (k) {
	case 0x13:
	case 0x14:
		query.a = *(int*) (params + 4);
		query.b = *(int*) (params + 8);
		break;
	case 0x1c:
		query.c = *(int*) (params + 4);
		query.a = *(int*) (params + 8);
		break;
	case 0x27:
		query.c = *(int*) (params + 4);
		break;
	case 0x25:
	case 0x28:
	case 0x2a:
		query.c = *(int*) (params + 4);
		query.d = *(int*) (params + 8);
		break;
	case 0x2b:
		query.a = *(int*) (cmd + 0x10);
		break;
	case 0x12:
	case 0x2c:
	case 0x31:
	case 0x32:
	case 0x35:
	case 0x37:
		query.c = *(int*) (params + 4);
		break;
	case 0x1d:
	case 0x21:
	case 0x24:
	case 0x29:
	case 0x2d:
		break;
	default:
		return 0;
	}
	return !(fcn_004fa5b0(k, entity, &query) & 0x60);
}
