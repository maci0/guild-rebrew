int __cdecl fcn_004e7ff0(unsigned char *arg);

/* ADDRESS: GOLDTL 0x004cc410 */
int __cdecl fcn_004cc410(char *a1, char *output)
{
    int status;

    status = fcn_004e7ff0((unsigned char *) (a1 + 0x10));
    if (output != 0) {
        output[0] = (status == 0) + 1;
        output[1] = 0;
        *(int *) (output + 6) = 0;
    }
    return (status == 0);
}
