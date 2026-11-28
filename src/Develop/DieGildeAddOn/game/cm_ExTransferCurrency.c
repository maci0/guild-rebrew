#pragma pack(push, 1)
typedef struct CM_TRANSFER_CURRENCY_CMD {
	char pad0[0x10];
	int h10;
	int h14;
	int f18;
	unsigned char idx1c;
	int f1d;
} CM_TRANSFER_CURRENCY_CMD;
#pragma pack(pop)

int __cdecl cm_ResolveSpecialEntityId(CM_TRANSFER_CURRENCY_CMD* obj, int h);
void __cdecl gm_SubObjectNoKill(int h, unsigned int w, int v);
void __cdecl gm_AddObjekt(int h, unsigned int w, int v);

/* ADDRESS: GOLDTL 0x004c7bb0 */
int __cdecl cm_ExTransferCurrency(CM_TRANSFER_CURRENCY_CMD* obj, char* out)
{
	int h;
	unsigned int w;

	if (*(int*) 0x14cbca0 != -1) {
		*(int*) 0x699364 = obj->f18;
	}
	h = obj->h14;
	if (h != -1) {
		h = cm_ResolveSpecialEntityId(obj, h);
		obj->h14 = h;
		w = *(unsigned short*) (0x8680b4 + (unsigned int) obj->idx1c * 0x2f4);
		gm_SubObjectNoKill(h, w, obj->f1d);
	}
	h = obj->h10;
	if (h != -1) {
		h = cm_ResolveSpecialEntityId(obj, h);
		obj->h10 = h;
		w = *(unsigned short*) (0x8680b4 + (unsigned int) obj->idx1c * 0x2f4);
		gm_AddObjekt(h, w, obj->f1d);
	}
	if (out != 0) {
		*out = 1;
	}
	return 0;
}
