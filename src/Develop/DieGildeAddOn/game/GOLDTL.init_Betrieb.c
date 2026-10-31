extern char* g_entity_type_table; /* 0x868050 */
extern char* g_item_def_table;    /* 0x99ec10 */
extern unsigned char g_773d75;

#pragma pack(push, 1)
typedef struct init_Betrieb_Item {
    char type;                  /* +0x00 */
    char pad1[0x25];            /* +0x01 */
    unsigned short weight[4];   /* +0x26 */
    unsigned short child[4];    /* +0x2e */
    unsigned short div;         /* +0x36 */
    int cache;                  /* +0x38 */
    char pad3c[5];              /* +0x3c */
} init_Betrieb_Item;            /* SIZE 0x41 */
#pragma pack(pop)

int __cdecl gm_GetBuildingTypeCategory(int arg1);
char* __cdecl fcn_00502cd0(int a1, int a2, int a3, ...);
int __cdecl gm_NextEntityQueryMatch(void);
float __cdecl eval_ObjektPreis2Credits(int id, int a1);
int __cdecl fcn_0050dfd0(char* a1, int a2);
int __cdecl fcn_004c51f0(int a1, int a2, int a3, int a4, char a5, int a6);
void __cdecl ReportClientMessage(const char* msg);

/* ADDRESS: GOLDTL 0x00512b40 */
void __cdecl init_Betrieb(unsigned char* a0)
{
    char* geb;
    init_Betrieb_Item* item;
    char* obj;
    char* ent;
    int category;
    int total;
    int limit;
    int i;
    int qty;

    category = gm_GetBuildingTypeCategory(*a0);
    geb = g_entity_type_table + *a0 * 0x24d;
    if (category != 1 && category != 4) {
        return;
    }
    ent = fcn_00502cd0(*(int*)(a0 + 0x5d), 1, 0, 0xff);
    if (ent == 0) {
        return;
    }
    obj = fcn_00502cd0(*(int*)(ent + 0x14), 1, 5);
    while (obj != 0) {
        if (((init_Betrieb_Item*)g_item_def_table)[*(unsigned short*)obj].type
            != '%') {
            break;
        }
        obj = (char*)gm_NextEntityQueryMatch();
    }
    if (obj == 0) {
        return;
    }
    item = &((init_Betrieb_Item*)g_item_def_table)[*(unsigned short*)obj];
    total = 0;
    for (i = 0; i < 4; i++) {
        if (item->child[i] == 0) {
            break;
        }
        if (item->child[i] != 0xffff) {
            total += (int)(eval_ObjektPreis2Credits(item->child[i], 100) *
                           item->weight[i]);
        }
    }
    if (total != 0) {
        if (*geb == 0x15) {
            limit = (int)(24000.0f / total);
        } else {
            limit = 16000 / total;
        }
        if (limit <= 1) {
            limit = 1;
        }
        obj = fcn_00502cd0(*(int*)(a0 + 0x5d), 1, 4, 5);
        if (obj == 0) {
            return;
        }
        i = 0;
        do {
            if (item->child[i] == 0) {
                return;
            }
            if (item->child[i] != 0xffff) {
                qty = item->weight[i];
                if (qty * limit < fcn_0050dfd0(obj, item->child[i])) {
                    limit = qty * limit;
                } else {
                    limit = fcn_0050dfd0(obj, item->child[i]);
                }
                fcn_004c51f0(*(int*)(obj + 2), -1, item->child[i], limit,
                             g_773d75, 0);
            }
            i++;
        } while (i < 4);
    } else {
        ReportClientMessage("init_Betrieb(): costs are zero");
    }
}
