#include <f2d/frutti2d.h>

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GL/gl.h>

#define PLAYER_SPEED 0.3

window_t window;
unsigned shader_id;
int key_index;
char *keys;
bool started = false;
model_t model;
// int cooldown = 0;
// texture_t texture;
// texture_t bg_tile;

// char *texture_merge(texture_t *s1, texture_t *s2) {
//     unsigned width = (s1->x+s1->draw_width)+(s2->x+s2->draw_width);
//     unsigned height = (s1->y+s1->draw_height)+(s2->y+s2->draw_height);
//     char *data = malloc(width*height*4);
//     // int base_x = (s1->x >= s2->x) ? s1->x : s2->x;
//     // int base_y = (s1->y >= s2->y) ? s1->y : s2->y;
//     int base_x = s1->x || s2->x;
//     int base_y = s1->y || s2->y;
//     printf("width: %u, height: %u\nbasex: %d, basey: %d\n", width, height, base_x, base_y);
//     return data;
// }

void window_start(void *arg) {
    window = window_new("Interesting Title", WINDOW_FLAG_ROOT);
}

void setup(void *arg) {
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    shader_id = shader_load("../shaders/tex.vert", "../shaders/tex.frag");
    float vertex_buffer[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };
    model = model_init(vertex_buffer, 3);
    camera_lookat();
    // printf("shaderid = %u\n", shader_id);
    // texture = texture_load("../car.bmp");
    // bg_tile.draw_width = 32;
    // texture.draw_width = 32;
    // texture.draw_height = 32;
    // texture.draw_scalex = 128;
    // texture.draw_scaley = 128;

    // bg_tile = texture_load("../test.bmp");
    // bg_tile.draw_width = 32;
    // bg_tile.draw_height = 32;
    // bg_tile.draw_scalex = 128;
    // bg_tile.draw_scaley = 128;

    // char *data = texture_merge(&texture, &bg_tile);
    
    started = true;
}

void check_keys(void) {
    int i;
    char ch;
    for (i = 0; i < key_index; i++) {
        ch = keys[i];
        // if (ch)
            // printf("K: %.12s\n", keys);
        // if (ch == 'w')
            // texture.y += PLAYER_SPEED; 
        // else if (ch == 'a')
            // texture.x -= PLAYER_SPEED;
        // else if (ch == 's')
            // texture.y -= PLAYER_SPEED;
        // else if (ch == 'd')
            // texture.x += PLAYER_SPEED;
         if (ch == 'q')
            wm_events_kill();
    }
}

void on_event(void *_event) {
    event_t *event = (event_t *)_event;
    switch (event->type) {
        case EVENT_CLIENTMESSAGE:
            wm_events_kill();
            break;
        case EVENT_KEYPRESS:
            // printf("keypress\n");
            keys = wm_get_pressed_keys(&key_index);
            break;
    }
}

void cleanup(void *arg) {
    // texture_delete(&texture);
    // texture_delete(&bg_tile);
    shader_delete(shader_id);
    // model_destroy(model);
}

void draw(void *arg) {
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    // glFlush();
    // if (cooldown == 0) {
    //     texture_spritesheet_next(&texture);
    //     cooldown = 100;
    // }

    draw_all(NULL, &window, shader_id);
}

void draw_callback(void) {
    model_draw(&model);
    // printf("drawn somewhere\n");
}

int main() {
    f2d_add_function(FUNC_WM_START_SETUP, &window_start);
    f2d_add_function(FUNC_WM_START,       &setup);
    f2d_add_function(FUNC_DRAW,           &draw);
    f2d_add_function(FUNC_ON_EVENT,       &on_event);
    f2d_add_function(FUNC_CLEANUP,        &cleanup);
    
    f2d_start();

    while (!started);

    while (wm_events_is_running()) {
        check_keys();
        draw_event_t draw_event;
        draw_event.type = DRAW_EVENT_CALLBACK;
        draw_event.value = 0;
        draw_event.callback = &draw_callback;
        draw_push_event(&draw_event);

        usleep(2000);
        // if (cooldown != 0)
        //     cooldown--;
    }

    f2d_cleanup();
    
    return 0;
}
