/* ADDRESS: GOLDTL 0x00440260 */

/* Camera/projection matrix builder: combines a translation step with the
   basis rows from the constant block at 0x1042180 and stores the four
   resulting columns at 0x6b8080. */
unsigned int __cdecl fcn_00440260(int a0, int a1, int a2, int a3)
{
    int v1;
    int i2;
    int i3;
    int i4;
    int i5;
    float v2;
    float v3;
    float v4;
    float v5;
    float v6;
    float v7;
    float v8;
    float v9;
    float v10;
    float v11;
    float v12;
    float v13;
    float v14;
    float v15;
    float v16;

    v1 = *(int*) (a0 + 4);
    i2 = v1 * a2;
    i3 = (a2 + 1) * v1;
    i4 = v1 * a3;
    i5 = (a3 + 1) * v1;
    v2 = (float) i2;
    v3 = (float) i3;
    v4 = (float) i4;
    v5 = (float) i5;
    v6 = (float) *(unsigned char*) (a1 + 0x1ec);
    v9 = *(float*) 0x1042150 * v4;
    v10 = *(float*) 0x1042154 * v4;
    v4 = *(float*) 0x1042158 * v4;
    v11 = *(float*) 0x1042160 * v6;
    v7 = *(float*) 0x1042190 * v2 + *(float*) 0x1042180;
    v8 = *(float*) 0x1042194 * v2 + *(float*) 0x1042184;
    v2 = *(float*) 0x1042198 * v2 + *(float*) 0x1042188;
    *(float*) 0x6b8080 = v11 + v9 + v7;
    v12 = *(float*) 0x1042164 * v6;
    *(float*) 0x6b8084 = v12 + v10 + v8;
    v6 = *(float*) 0x1042168 * v6;
    *(float*) 0x6b8088 = v6 + v4 + v2;
    v13 = *(float*) 0x1042190 * v3 + *(float*) 0x1042180;
    v14 = *(float*) 0x1042194 * v3 + *(float*) 0x1042184;
    v3 = *(float*) 0x1042198 * v3 + *(float*) 0x1042188;
    *(float*) 0x6b80d0 = v11 + v9 + v13;
    *(float*) 0x6b80d4 = v12 + v10 + v14;
    *(float*) 0x6b80d8 = v6 + v4 + v3;
    v15 = *(float*) 0x1042150 * v5;
    v16 = *(float*) 0x1042154 * v5;
    v5 = *(float*) 0x1042158 * v5;
    *(float*) 0x6b8120 = v11 + v15 + v13;
    *(float*) 0x6b8124 = v12 + v16 + v14;
    *(float*) 0x6b8128 = v6 + v5 + v3;
    *(float*) 0x6b8170 = v11 + v15 + v7;
    *(float*) 0x6b8174 = v12 + v16 + v8;
    *(float*) 0x6b8178 = v6 + v5 + v2;
    v6 = (float) *(unsigned char*) (a0 + 0x28d + (a2 + a3 * 8) * 500);
    v11 = *(float*) 0x1042160 * v6;
    *(float*) 0x6b81c0 = v11 + v9 + v7;
    v12 = *(float*) 0x1042164 * v6;
    *(float*) 0x6b81c4 = v12 + v10 + v8;
    v6 = *(float*) 0x1042168 * v6;
    *(float*) 0x6b81c8 = v6 + v4 + v2;
    *(float*) 0x6b8210 = v11 + v9 + v13;
    *(float*) 0x6b8214 = v12 + v10 + v14;
    *(float*) 0x6b8218 = v6 + v4 + v3;
    *(float*) 0x6b8260 = v11 + v15 + v13;
    *(float*) 0x6b8264 = v12 + v16 + v14;
    *(float*) 0x6b8268 = v6 + v5 + v3;
    *(float*) 0x6b82b0 = v11 + v15 + v7;
    *(float*) 0x6b82b4 = v12 + v16 + v8;
    *(float*) 0x6b82b8 = v6 + v5 + v2;
    return 0x6b8080;
}
