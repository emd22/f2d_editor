#ifndef FRUTTI2D_H
#define FRUTTI2D_H

#include <f2d/wm/wm.h>
#include <f2d/wm/window.h>
#include <f2d/wm/events.h>
#include <f2d/draw.h>
#include <f2d/texture.h>
#include <f2d/shader.h>

typedef struct {
    void (*wm_start_setup_func)(void);
    void (*wm_start_func)(void);
    void (*draw_func)(void);
    void (*on_event_func)(event_t);
    void (*cleanup_func)(void);
} f2d_parameters_t;

void f2d_start(f2d_parameters_t _f2d_parameters);
void f2d_cleanup(void);

#endif