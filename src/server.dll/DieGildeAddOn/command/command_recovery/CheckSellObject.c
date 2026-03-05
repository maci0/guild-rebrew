// FUNCTION: SERVER 0x1000cbd0
// STATUS: MATCHING
// BLOCKER: register allocation - target caches esi+0x14 in edi, our code uses only esi
// ORIGIN: GAME
// SIZE: 517
// CFLAGS: /O2 /Gd
// SYMBOL: _CheckSellObject

typedef unsigned int uint;
typedef unsigned short ushort;

extern char g_static_entity_table_358a0[];

extern int __cdecl get_field_by_type(char*, int);
extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern int __cdecl StartEntityQuery(int, int, int, uint);
extern int __cdecl CheckInventoryCapacity(char*, uint, int);
extern int __cdecl KannObjektHergestellt(char*, int, int);
extern char* __cdecl ResolveParentEntity(char*);
extern int __cdecl QueryEntitySum(int, int);
extern void __cdecl LogMessageInternal(char*, int, char*, int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ChkSellObjekt___Invalid__quel_1002c8dc[];
extern char s_cm_ChkSellObjekt___No_Objekts_at_1002c8b4[];
extern char s_cm_ChkSellObjekt___Not_enough_Ob_1002c884[];
extern char s_cm_ChkSellObjekt___Invalid__ziel_1002c854[];
extern char s_cm_ChkSellObjekt___Inventory_vol_1002c810[];
extern char s_cm_ChkSellObjekt___Lager_voll_1002c834[];
extern char s_cm_ChkSellObjekt___Not_enough_Cr_1002c7d8[];

int __cdecl CheckSellObject(char* cmd)
{
	int p;
	short sVar1;
	int iVar2;
	char* parent;
	void* src_bldg;
	void* dst_bldg;

	p = (int)cmd;
	iVar2 = *(int*)(p + 0x14);
	if (iVar2 != -1) {
		iVar2 = get_field_by_type((char*)p, iVar2);
		*(int*)(p + 0x14) = iVar2;
		iVar2 = ResolveEntityById(&src_bldg, (void**)&cmd, (void**)&parent, iVar2);
		if (iVar2 == 0) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x236b, s_cm_ChkSellObjekt___Invalid__quel_1002c8dc, 8);
			return 1;
		}
		if (src_bldg != (void*)0) {
			iVar2 = *(int*)((char*)src_bldg + 0x5d);
		} else if (cmd != (char*)0) {
			iVar2 = *(int*)(cmd + 0x14);
		} else {
			iVar2 = *(int*)(parent + 0x178);
		}
		iVar2 = StartEntityQuery(iVar2, 1, 0, (uint)*(ushort*)(p + 0x18));
		if (iVar2 == 0) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2383, s_cm_ChkSellObjekt___No_Objekts_at_1002c8b4, 8);
			return 1;
		}
		if (*(int*)(iVar2 + 0xe) < *(int*)(p + 0x1f)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x238f, s_cm_ChkSellObjekt___Not_enough_Ob_1002c884, 8);
			return 1;
		}
	}
	iVar2 = *(int*)(p + 0x10);
	if (iVar2 != -1) {
		iVar2 = get_field_by_type((char*)p, iVar2);
		*(int*)(p + 0x10) = iVar2;
		iVar2 = ResolveEntityById(&dst_bldg, (void**)&cmd, (void**)&parent, iVar2);
		if (iVar2 == 0) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x23ab, s_cm_ChkSellObjekt___Invalid__ziel_1002c854, 8);
			return 1;
		}
		if (dst_bldg != (void*)0) {
			if (*(ushort*)((char*)dst_bldg + 0x27) == (ushort)0xffff) {
				parent = (char*)0;
			} else {
				parent = g_static_entity_table_358a0 + (uint)*(ushort*)((char*)dst_bldg + 0x27) * 0x21c;
			}
		} else if (cmd != (char*)0) {
			sVar1 = *(short*)cmd;
			if (sVar1 == 0x2a || sVar1 == 0x116 || sVar1 == 0x1dd) {
				iVar2 = KannObjektHergestellt(cmd, (int)(uint)*(ushort*)(p + 0x18), *(int*)(p + 0x1f));
				if (iVar2 < *(int*)(p + 0x1f)) {
					LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x23cd, s_cm_ChkSellObjekt___Lager_voll_1002c834, 8);
					return 1;
				}
			}
			parent = ResolveParentEntity(cmd);
		} else {
			iVar2 = CheckInventoryCapacity(parent, (uint)*(ushort*)(p + 0x18), *(int*)(p + 0x1f));
			if (iVar2 < *(int*)(p + 0x1f)) {
				LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x23e3, s_cm_ChkSellObjekt___Inventory_vol_1002c810, 8);
				return 1;
			}
		}
		if (*(int*)(p + 0x23) != 0 && parent != (char*)0) {
			iVar2 = QueryEntitySum(*(int*)(parent + 0x178), (int)*(unsigned char*)(p + 0x1e));
			if (iVar2 < *(int*)(p + 0x1f) * *(int*)(p + 0x23)) {
				LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x23ff, s_cm_ChkSellObjekt___Not_enough_Cr_1002c7d8, 8);
				return 1;
			}
		}
	}
	return 0;
}
