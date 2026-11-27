extern float g_1042150;
extern float g_1042154;
extern float g_1042158;
extern float g_1042160;
extern float g_1042164;
extern float g_1042168;
extern float g_1042180;
extern float g_1042184;
extern float g_1042188;
extern float g_1042190;
extern float g_1042194;
extern float g_1042198;

/* Eight projected corners, 0x50 bytes each, 0x6b8080..0x6b8300. */
float g_6b8080[8][20];

/* Camera/projection matrix builder: combines a translation step with the
   basis rows from the constant block at 0x1042180 and stores the four
   resulting columns at 0x6b8080. */
typedef struct {
    float x;
    float y;
    float z;
    float w;
} PROJECTED_VECTOR;

/* Project one corner of the cell box. */
#define PROJECT_CORNER(out, xs, ys) \
    q.x = g_1042190 * xs + g_1042180; \
    q.y = g_1042194 * xs + g_1042184; \
    q.z = g_1042198 * xs + g_1042188; \
    t.x = g_1042150 * ys + q.x; \
    t.y = g_1042154 * ys + q.y; \
    t.z = g_1042158 * ys + q.z; \
    out[0] = g_1042160 * z + t.x; \
    out[1] = g_1042164 * z + t.y; \
    out[2] = g_1042168 * z + t.z

/* ADDRESS: GOLDTL 0x00440260 */
unsigned int __cdecl d3_ProjectFloorCellBounds(int floor, int cell, int gridX, int gridY)
{
    PROJECTED_VECTOR q;
    PROJECTED_VECTOR t;
    float x0;
    float x1;
    float y0;
    float y1;
    float z;

    x0 = (float) (*(int*) (floor + 4) * gridX);
    x1 = (float) ((gridX + 1) * *(int*) (floor + 4));
    y0 = (float) (*(int*) (floor + 4) * gridY);
    y1 = (float) ((gridY + 1) * *(int*) (floor + 4));
    z = (float) *(unsigned char*) (cell + 0x1ec);
    PROJECT_CORNER(g_6b8080[0], x0, y0);
    PROJECT_CORNER(g_6b8080[1], x1, y0);
    PROJECT_CORNER(g_6b8080[2], x1, y1);
    PROJECT_CORNER(g_6b8080[3], x0, y1);
    z = (float) *(unsigned char*) (floor + 0x28d + (gridX + gridY * 8) * 500);
    PROJECT_CORNER(g_6b8080[4], x0, y0);
    PROJECT_CORNER(g_6b8080[5], x1, y0);
    PROJECT_CORNER(g_6b8080[6], x1, y1);
    PROJECT_CORNER(g_6b8080[7], x0, y1);
    return (unsigned int) g_6b8080;
}
