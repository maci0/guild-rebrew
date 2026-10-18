/* Unresolved byte views: 0x1463579, 0x14650e4, 0x1463578, 0x1463581,
   0x1464fbc, 0x1464fc4. No allocation or owner is declared here. */
/* ADDRESS: GOLD 0x0041e6d0 */
void __cdecl fcn_0041e6d0(int wert, unsigned char *ziel_0, unsigned char *ziel_1,
                          unsigned char *ziel_2)
{
    unsigned int logisch;
    unsigned char n;
    unsigned char out;

    logisch = (unsigned int)wert;
    n = *(unsigned char *)0x1463579;
    out = (unsigned char)(logisch >> n);
    n = *(unsigned char *)0x14650e4;
    *ziel_0 = (unsigned char)(out << n);
    n = *(unsigned char *)0x1463578;
    out = (unsigned char)(logisch >> n);
    n = *(unsigned char *)0x1463581;
    *ziel_1 = (unsigned char)(out << n);
    n = *(unsigned char *)0x1464fbc;
    out = (unsigned char)(logisch >> n);
    n = *(unsigned char *)0x1464fc4;
    *ziel_2 = (unsigned char)(out << n);
}
