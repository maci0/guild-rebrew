int __cdecl cm_ResolveSpecialEntityId(char*, int);
int __cdecl gm_ResolveEntityById(int*, char**, int*, int);
int __cdecl gm_QueryEntities(int, int, int, int);
int __cdecl gm_eval_SlotVoll(char*, int, int);
char* __cdecl fcn_0050d490(char*);
int __cdecl gm_CheckInventoryCapacity(int, int, int);
int __cdecl gm_QueryEntitySum(int, char);

/* ADDRESS: GOLDTL 0x004c6f70 */
int __cdecl cm_ChkClientSellObjekt(char* request)
{
	int v12;
	int v13;
	int v14;
	int id;
	int obj;
	char* p;
	unsigned short type;
	char* record;

	if (*(int*) (request + 0x14) != -1) {
		id = cm_ResolveSpecialEntityId(request, *(int*) (request + 0x14));
		*(int*) (request + 0x14) = id;
		if (gm_ResolveEntityById(&v13, &record, &v12, id) == 0) {
			return 1;
		}
		if (v13 != 0) {
			p = (char*) v13 + 0x5d;
		} else if (record != 0) {
			p = record + 0x14;
		} else {
			p = (char*) v12 + 0x178;
		}
		obj = gm_QueryEntities(*(int*) p, 1, 0, *(unsigned short*) (request + 0x18));
		if (obj == 0) {
			return 1;
		}
		if (*(int*) (obj + 0xe) < *(int*) (request + 0x1f)) {
			return 1;
		}
	}
	if (*(int*) (request + 0x10) != -1) {
		id = cm_ResolveSpecialEntityId(request, *(int*) (request + 0x10));
		*(int*) (request + 0x10) = id;
		if (gm_ResolveEntityById(&v14, &record, &v12, id) == 0) {
			return 1;
		}
		if (v14 != 0) {
			if (*(unsigned short*) (v14 + 0x27) != 0xffff) {
				obj = *(unsigned short*) (v14 + 0x27) * 0x21c + 0x7f4ca0;
			} else {
				obj = 0;
			}
		} else if (record != 0) {
			type = *(unsigned short*) record;
			if ((type == 0x2a || type == 0x116 || type == 0x1dd) &&
			    gm_eval_SlotVoll(record, *(unsigned short*) (request + 0x18), *(int*) (request + 0x1f)) <
				    *(int*) (request + 0x1f)) {
				return 1;
			}
			obj = (int) fcn_0050d490(record);
		} else {
			if (gm_CheckInventoryCapacity(v12, *(unsigned short*) (request + 0x18), *(int*) (request + 0x1f)) <
			    *(int*) (request + 0x1f)) {
				return 1;
			}
			obj = v12;
		}
		if (*(int*) (request + 0x23) != 0 && obj != 0) {
			if (gm_QueryEntitySum(*(int*) (obj + 0x178), *(char*) (request + 0x1e)) <
			    *(int*) (request + 0x1f) * *(int*) (request + 0x23)) {
				return 1;
			}
		}
	}
	return 0;
}
