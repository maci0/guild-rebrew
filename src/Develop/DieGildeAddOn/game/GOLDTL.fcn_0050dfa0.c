


int __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl gm_GetMsgField(void*, int);

int __cdecl gm_GetMsgObjektField(void* msg, int obj_id)
{
	int r;

	r = fcn_00502cd0(*(int*) ((char*) msg + 0x14), 1, 0, obj_id);
	if (r == 0) {
		return 0;
	}
	return gm_GetMsgField(msg, r);
}
