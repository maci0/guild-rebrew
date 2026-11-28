void __cdecl d2_ShowStatusBanner(char *);
void __cdecl d2_BroadcastCutscene0xa2(char *);
int __cdecl d2_RunTradeRouteEditor(char *);
unsigned short * __cdecl gm_QueryEntities(int, int, ...);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short, int);
void __cdecl cm_RequestSysMessage(char, char *);

/* ADDRESS: GOLDTL 0x00535bd0 */
void __cdecl gm_DispatchDebugSubsystemKeys(void)
{
    char *object_entry;
    int i;
    char dialog_buf[124];

    switch ((unsigned char)*(unsigned char *)0x14cf950) {
    case 37:
        object_entry = *(void **)0x7e2a9c;
        if (object_entry)
            d2_BroadcastCutscene0xa2(object_entry);
        break;
    case 35:
        if (*(int *)0x6a3438 = (*(int *)0x6a3438 == 0)) {
            d2_ShowStatusBanner((char *)0x6a3330);
        } else
            d2_ShowStatusBanner((char *)0x6a3320);
        break;
    case 19:
        object_entry = *(void **)0x7e2a9c;
        if (object_entry)
            d2_RunTradeRouteEditor(object_entry);
        else
            d2_RunTradeRouteEditor((char *)gm_QueryEntities(0, 2, 7, 4, 0x1d));
        break;
    case 23:
        if (*(int *)0x6a3434 = (*(int *)0x6a3434 == 0)) {
            d2_ShowStatusBanner((char *)0x6a330c);
        } else
            d2_ShowStatusBanner((char *)0x6a32f8);
        break;
    case 30:
        if (*(int *)0x6a3430 = (*(int *)0x6a3430 == 0)) {
            d2_ShowStatusBanner((char *)0x6a32e4);
        } else
            d2_ShowStatusBanner((char *)0x6a32d0);
        break;
    case 32:
        if (*(int *)0x6a343c = (*(int *)0x6a343c == 0)) {
            d2_ShowStatusBanner((char *)0x6a32bc);
        } else
            d2_ShowStatusBanner((char *)0x6a32a8);
        break;
    case 46:
        if (*(int *)0x6a2c04 = (*(int *)0x6a2c04 == 0)) {
            d2_ShowStatusBanner((char *)0x6a3294);
        } else
            d2_ShowStatusBanner((char *)0x6a327c);
        break;
    case 20:
        gm_ApplyEntityHealthDelta(*(unsigned short *)0x774970, -1000);
        break;
    case 21:
        if (*(unsigned char *)0x7747b0 & 4) {
            for (i = 0; i < 31; i++)
                ((int *)dialog_buf)[i] = 0;
            *(int *)dialog_buf = -1;
            cm_RequestSysMessage(0x11, dialog_buf);
        }
        break;
    case 18:
        if (*(int *)0x6a2c10 = (*(int *)0x6a2c10 == 0)) {
            d2_ShowStatusBanner((char *)0x6a3268);
        } else
            d2_ShowStatusBanner((char *)0x6a3254);
        break;
    case 4:
        if (*(int *)0x6a2c08 = (*(int *)0x6a2c08 == 0)) {
            d2_ShowStatusBanner((char *)0x6a3244);
        } else
            d2_ShowStatusBanner((char *)0x6a3234);
        break;
    case 25:
        if (*(int *)0x6a2c0c = (*(int *)0x6a2c0c == 0)) {
            d2_ShowStatusBanner((char *)0x6a3224);
        } else
            d2_ShowStatusBanner((char *)0x6a3210);
        break;
    default:
        break;
    }
}
