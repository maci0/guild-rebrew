

void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b2ca0 */
void __cdecl cm_RequestMoveObjekt(int srcObjId, int dstObjId, int count)
{
	char buf[0x9c];

	buf[0] = 0x13;
	*(int*) (buf + 0x10) = srcObjId;
	*(int*) (buf + 0x14) = dstObjId;
	*(int*) (buf + 0x18) = count;
	cm_EnqueueClientPacket(buf);
}
