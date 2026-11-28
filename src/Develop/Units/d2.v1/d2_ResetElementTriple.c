
/* ADDRESS: GOLDTL 0x004bf1a0 */
/* ADDRESS: GOLDDE 0x004acd20 */
void __cdecl d2_ResetElementTriple(char* obj)
{
    *(int*) obj = -1;
    *(int*) (obj + 4) = -1;
    *(int*) (obj + 8) = -1;
}
