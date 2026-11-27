#include <math.h>
void __cdecl d3_NormalizeVector(float *);
float __cdecl d3_WrapYawDelta(int, int);

/* ADDRESS: GOLDTL 0x005ea4d0 */
int __cdecl gm_SolveBallisticTrajectory(void *a, void *b, void *c, void *d, void *e, void *f, void *g, void *h, void *i)
{
    float *origin, *target, *bounds, *angle, *bearing, *speed, *velocity, *direction, *normal;
    float vector[4], horizontal[4], distance, height, gravity, dt, da;
    float current_speed, current_angle, sn, cs, apex, time, delta;
    int sign, count;
    origin = (float *)a; target = (float *)b; bounds = (float *)c;
    angle = (float *)d; bearing = (float *)e; speed = (float *)f;
    velocity = (float *)g; direction = (float *)h; normal = (float *)i;
    dt = (bounds[1] - bounds[0]) * 0.5f;
    gravity = *(float *)0x6660e8;
    sign = 0;
    da = (bounds[3] - bounds[2]) * 0.5f;
    vector[0] = target[0] - origin[0];
    vector[1] = target[1] - origin[1];
    vector[2] = target[2] - origin[2];
    horizontal[0] = vector[0]; horizontal[1] = 0.0f; horizontal[2] = vector[2];
    distance = (float)sqrt(vector[2] * vector[2] + vector[0] * vector[0]);
    d3_NormalizeVector(vector);
    d3_NormalizeVector(horizontal);
    *bearing = d3_WrapYawDelta(0x662d40, (int)vector);
    height = (float)fabs(target[1] - origin[1]) * *(float *)0x6660e4;
    distance *= *(float *)0x6660e4;
    if (origin[1] > target[1]) sign = 1;
    else if (origin[1] < target[1]) sign = -1;
    current_angle = bounds[3]; current_speed = bounds[0];
    for (count = 0; count < 16; count++) {
        sn = (float)sin(current_angle);
        cs = (float)cos(current_angle);
        apex = sn * sn * current_speed * current_speed / (gravity + gravity);
        time = (1.0f / gravity) * sn * current_speed;
        if (sign == 1) time += (float)sqrt((apex + height) * (1.0f / gravity) * 2.0f);
        else if (sign == -1) time += (float)sqrt((apex - height) * (1.0f / gravity) * 2.0f);
        delta = time * cs * current_speed - distance;
        if (delta > *(float *)0x6629b0) {
            if (current_speed > bounds[0]) {
                current_speed -= dt; dt *= 0.5f;
            } else if (current_angle > bounds[2]) {
                current_angle -= da; da *= 0.5f;
            } else {
                return -1;
            }
        } else if (delta < *(float *)0x666108) {
            if (current_angle < bounds[3]) {
                current_angle += da; da *= 0.5f;
            } else if (current_speed < bounds[1]) {
                current_speed += dt; dt *= 0.5f;
            } else {
                return -1;
            }
        } else {
            *speed = current_speed; *angle = current_angle;
            velocity[0] = horizontal[0];
            velocity[1] = cs * horizontal[1] - sn * horizontal[2];
            velocity[2] = cs * horizontal[2] + sn * horizontal[1];
            direction[0] = *(float *)0x662d60;
            direction[1] = *(float *)0x662d64 * cs - *(float *)0x662d68 * sn;
            direction[2] = *(float *)0x662d68 * cs + *(float *)0x662d64 * sn;
            normal[0] = direction[2] * velocity[1] - velocity[2] * direction[1];
            normal[1] = velocity[2] * direction[0] - direction[2] * velocity[0];
            normal[2] = velocity[0] * direction[1] - velocity[1] * direction[0];
            return 0;
        }
    }
    return -1;
}
