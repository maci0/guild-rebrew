


// SIZE 0x1
struct bits {
	unsigned char a : 1;
	unsigned char b : 1;
	unsigned char rest : 6;
};

char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl he_AbortActionIfFlag2(char*);
void __cdecl cm_RequestUpdateStraftatState(int, int, int, int);

void __cdecl he_ClearEntityActions(char* h)
{
	char* e;

	if (h == 0 || *(unsigned short*) h == 0xffff) {
		return;
	}
	for (e = he_StartHandlungSearch(1, 0, 0x41); e != 0; e = he_fn_Handlung()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b)) {
			if (*(int*) (e + 0xac) == *(int*) (h + 4)) {
				gm_LookupEntityRecordById(*(int*) (e + 0xb0));
				he_AbortActionIfFlag2(e);
			} else if (*(int*) (e + 0xb0) == *(int*) (h + 4)) {
				gm_LookupEntityRecordById(*(int*) (e + 0xac));
				he_AbortActionIfFlag2(e);
			}
		}
	}
	for (e = he_StartHandlungSearch(1, 0, 0x6f); e != 0; e = he_fn_Handlung()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b)) {
			if (*(int*) (e + 0xac) == *(int*) (h + 4)) {
				gm_LookupEntityRecordById(*(int*) (e + 0xb0));
				he_AbortActionIfFlag2(e);
			} else if (*(int*) (e + 0xb0) == *(int*) (h + 4)) {
				gm_LookupEntityRecordById(*(int*) (e + 0xac));
				he_AbortActionIfFlag2(e);
			}
		}
	}
	for (e = he_StartHandlungSearch(1, 0, 0x45); e != 0; e = he_fn_Handlung()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b)) {
			if (*(int*) (e + 0xac) == *(int*) (h + 4)) {
				gm_LookupEntityRecordById(*(int*) (e + 0xb0));
				he_AbortActionIfFlag2(e);
			} else if (*(int*) (e + 0xb0) == *(int*) (h + 4)) {
				gm_LookupEntityRecordById(*(int*) (e + 0xac));
				he_AbortActionIfFlag2(e);
			}
		}
	}
	for (e = he_StartHandlungSearch(1, 0, 0x2c); e != 0; e = he_fn_Handlung()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b)) {
			if (*(int*) (e + 0xac) == *(int*) (h + 4) || *(int*) (e + 0xb4) == *(int*) (h + 4)
			    || *(int*) (e + 0xc0) == *(int*) (h + 4)) {
				cm_RequestUpdateStraftatState(*(int*) (e + 0xac), *(int*) (e + 0xb0), *(int*) (e + 4), 0);
				he_AbortActionIfFlag2(e);
			} else if (*(int*) (e + 0xb0) == *(int*) (h + 4)) {
				he_AbortActionIfFlag2(e);
			}
		}
	}
	for (e = he_StartHandlungSearch(1, 0, 0x47); e != 0; e = he_fn_Handlung()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b)
		    && (*(int*) (e + 0xac) == *(int*) (h + 4) || *(int*) (e + 0xb0) == *(int*) (h + 4))) {
			he_AbortActionIfFlag2(e);
		}
	}
	for (e = he_StartHandlungSearch(1, 0, 0x5e); e != 0; e = he_fn_Handlung()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b) && *(int*) (e + 0xac) == *(int*) (h + 4)) {
			he_AbortActionIfFlag2(e);
		}
	}
	for (e = he_StartHandlungSearch(1, 0, 0x5f); e != 0; e = he_fn_Handlung()) {
		if ((((struct bits*) (e + 0x78))->a || ((struct bits*) (e + 0x78))->b) && *(int*) (e + 0xac) == *(int*) (h + 4)) {
			he_AbortActionIfFlag2(e);
		}
	}
}
