int __cdecl fcn_0064e74f(void);
int __cdecl fcn_00659eda(void* p);
void* __cdecl fcn_0064fde9(void* p, int size);
int __cdecl fcn_0064e758(void);

/* ADDRESS: GOLDTL 0x00650338 */
int __cdecl fcn_00650338(int v)
{
    int* end;
    int* p;
    int cap;

    fcn_0064e74f();
    cap = fcn_00659eda(*(void**) 0x157d400);
    end = *(int**) 0x157d3fc;
    if ((unsigned int)cap < (unsigned int)((char*)end - (char*)*(int**) 0x157d400 + 4)) {
        p = (int*) fcn_0064fde9(*(void**) 0x157d400, fcn_00659eda(*(void**) 0x157d400) + 0x10);
        if (p == 0) {
            fcn_0064e758();
            return 0;
        }
        cap = (int)(*(int**) 0x157d3fc - *(int**) 0x157d400);
        *(int**) 0x157d400 = p;
        end = p + cap;
        *(int**) 0x157d3fc = end;
    }
    *end = v;
    (*(int**) 0x157d3fc)++;
    fcn_0064e758();
    return v;
}
