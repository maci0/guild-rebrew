/* ADDRESS: GOLDTL 0x005373b0 */
void __cdecl main_PopFrameLoopsToBase(void)
{
    int a;
    int b;

    if (*(unsigned short*) 0x774970 == 0xffff) {
        return;
    }
    a = *(int*) 0x774650;
    b = *(int*) 0x774658;
    if (a > b) {
        *(int*) 0x774654 = a - b;
    }
}
