


int __cdecl gm_QueryEntities(int, int, int, int);
int __cdecl gm_GetMsgField(void*, int);

/* ADDRESS: GOLDDE 0x004f8cf0 */
int __cdecl gm_GetMsgObjektField(void* msg, int obj_id)
{
	int r;

	r = gm_QueryEntities(*(int*) ((char*) msg + 0x14), 1, 0, obj_id);
	if (r == 0) {
		return 0;
	}
	return gm_GetMsgField(msg, r);
}
