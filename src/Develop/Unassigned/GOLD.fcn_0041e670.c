/* ADDRESS: GOLD 0x0041e670 */
unsigned int __cdecl fcn_0041e670(unsigned int r, unsigned int g, unsigned int b)
{
    return (((b & 0xff) >> (*(unsigned char*) 0x1464fc4)) << (*(unsigned char*) 0x1464fbc))
        | (((g & 0xff) >> (*(unsigned char*) 0x1463581)) << (*(unsigned char*) 0x1463578))
        | (((r & 0xff) >> (*(unsigned char*) 0x14650e4)) << (*(unsigned char*) 0x1463579));
}
