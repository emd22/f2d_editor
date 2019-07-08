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
// int cooldown = 0;
texture_t texture;
// texture_t bg_tile;

long patchData[][16] = {
    {102,103,104,105,4,5,6,7,8,9,10,11,12,13,14,15},
    {12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27},
    {24,25,26,27,29,30,31,32,33,34,35,36,37,38,39,40},
    {96,96,96,96,97,98,99,100,101,101,101,101,0,1,2,3,},
    {0,1,2,3,106,107,108,109,110,111,112,113,114,115,116,117},
    {118,118,118,118,124,122,119,121,123,126,125,120,40,39,38,37},
    {41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56},
    {53,54,55,56,57,58,59,60,61,62,63,64,28,65,66,67},
    {68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83},
    {80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95}
};

float cpData[][3] = {
    {0.2,0,2.7},{0.2,-0.112,2.7},{0.112,-0.2,2.7},{0,-0.2,2.7},
    {1.3375,0,2.53125},{1.3375,-0.749,2.53125},{0.749,-1.3375,2.53125},
    {0,-1.3375,2.53125},{1.4375,0,2.53125},{1.4375,-0.805,2.53125},
    {0.805,-1.4375,2.53125},{0,-1.4375,2.53125},{1.5,0,2.4},{1.5,-0.84,2.4},
    {0.84,-1.5,2.4},{0,-1.5,2.4},{1.75,0,1.875},{1.75,-0.98,1.875},
    {0.98,-1.75,1.875},{0,-1.75,1.875},{2,0,1.35},{2,-1.12,1.35},
    {1.12,-2,1.35},{0,-2,1.35},{2,0,0.9},{2,-1.12,0.9},{1.12,-2,0.9},
    {0,-2,0.9},{-2,0,0.9},{2,0,0.45},{2,-1.12,0.45},{1.12,-2,0.45},
    {0,-2,0.45},{1.5,0,0.225},{1.5,-0.84,0.225},{0.84,-1.5,0.225},
    {0,-1.5,0.225},{1.5,0,0.15},{1.5,-0.84,0.15},{0.84,-1.5,0.15},
    {0,-1.5,0.15},{-1.6,0,2.025},{-1.6,-0.3,2.025},{-1.5,-0.3,2.25},
    {-1.5,0,2.25},{-2.3,0,2.025},{-2.3,-0.3,2.025},{-2.5,-0.3,2.25},
    {-2.5,0,2.25},{-2.7,0,2.025},{-2.7,-0.3,2.025},{-3,-0.3,2.25},
    {-3,0,2.25},{-2.7,0,1.8},{-2.7,-0.3,1.8},{-3,-0.3,1.8},{-3,0,1.8},
    {-2.7,0,1.575},{-2.7,-0.3,1.575},{-3,-0.3,1.35},{-3,0,1.35},
    {-2.5,0,1.125},{-2.5,-0.3,1.125},{-2.65,-0.3,0.9375},{-2.65,0,0.9375},
    {-2,-0.3,0.9},{-1.9,-0.3,0.6},{-1.9,0,0.6},{1.7,0,1.425},
    {1.7,-0.66,1.425},{1.7,-0.66,0.6},{1.7,0,0.6},{2.6,0,1.425},
    {2.6,-0.66,1.425},{3.1,-0.66,0.825},{3.1,0,0.825},{2.3,0,2.1},
    {2.3,-0.25,2.1},{2.4,-0.25,2.025},{2.4,0,2.025},{2.7,0,2.4},
    {2.7,-0.25,2.4},{3.3,-0.25,2.4},{3.3,0,2.4},{2.8,0,2.475},
    {2.8,-0.25,2.475},{3.525,-0.25,2.49375},{3.525,0,2.49375},
    {2.9,0,2.475},{2.9,-0.15,2.475},{3.45,-0.15,2.5125},{3.45,0,2.5125},
    {2.8,0,2.4},{2.8,-0.15,2.4},{3.2,-0.15,2.4},{3.2,0,2.4},{0,0,3.15},
    {0.8,0,3.15},{0.8,-0.45,3.15},{0.45,-0.8,3.15},{0,-0.8,3.15},
    {0,0,2.85},{1.4,0,2.4},{1.4,-0.784,2.4},{0.784,-1.4,2.4},{0,-1.4,2.4},
    {0.4,0,2.55},{0.4,-0.224,2.55},{0.224,-0.4,2.55},{0,-0.4,2.55},
    {1.3,0,2.55},{1.3,-0.728,2.55},{0.728,-1.3,2.55},{0,-1.3,2.55},
    {1.3,0,2.4},{1.3,-0.728,2.4},{0.728,-1.3,2.4},{0,-1.3,2.4},{0,0,0},
    {1.425,-0.798,0},{1.5,0,0.075},{1.425,0,0},{0.798,-1.425,0},
    {0,-1.5,0.075},{0,-1.425,0},{1.5,-0.84,0.075},{0.84,-1.5,0.075}
};

int tea_list;

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

void window_start(void) {
    window = window_new("Interesting Title", WINDOW_FLAG_ROOT);
}

void Teapot(long grid)
{
    float p[4][4][3], q[4][4][3], r[4][4][3], s[4][4][3];
    long i, j, k, l;

    tea_list = 1;
    glNewList(tea_list, GL_COMPILE);
    glPushMatrix();
    glRotatef(270.0, 1.0, 0.0, 0.0);
    for (i = 0; i < 10; i++) {
	for (j = 0; j < 4; j++) {
	    for (k = 0; k < 4; k++) {
		for (l = 0; l < 3; l++) {
		    p[j][k][l] = cpData[patchData[i][j*4+k]][l];
		    q[j][k][l] = cpData[patchData[i][j*4+(3-k)]][l];
		    if (l == 1) {
			q[j][k][l] *= -1.0;
		    }
		    if (i < 6) {
			r[j][k][l] = cpData[patchData[i][j*4+(3-k)]][l];
			if (l == 0) {
			    r[j][k][l] *= -1.0;
			}
			s[j][k][l] = cpData[patchData[i][j*4+k]][l];
			if (l == 0) {
			    s[j][k][l] *= -1.0;
			}
			if (l == 1) {
			    s[j][k][l] *= -1.0;
			}
		    }
		}
	    }
	}
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &p[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(grid, 0.0, 1.0, grid, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, grid, 0, grid);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &q[0][0][0]);
	glEvalMesh2(GL_FILL, 0, grid, 0, grid);
	if (i < 6) {
	    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &r[0][0][0]);
	    glEvalMesh2(GL_FILL, 0, grid, 0, grid);
	    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &s[0][0][0]);
	    glEvalMesh2(GL_FILL, 0, grid, 0, grid);
	}
    }
    glDisable(GL_MAP2_VERTEX_3);
    glPopMatrix();
    glEndList();
}

void setup(void) {
    float position[] = {0.0, 3.0, 3.0, 0.0};
    float local_view[] = {0.0};
    float ambient[] = {0.1745, 0.01175, 0.01175};
    float diffuse[] = {0.61424, 0.04136, 0.04136};
    float specular[] = {0.727811, 0.626959, 0.626959};

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glFrontFace(GL_CW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.6*128.0);

    glClearColor(0.5, 0.5, 0.5, 1.0);
    glColor3f(1.0, 1.0, 1.0);

    Teapot(14);
    

    shader_id = shader_load("../shaders/tex.vert", "../shaders/tex.frag");
    // printf("shaderid = %u\n", shader_id);
    // texture = texture_load("../car.bmp");
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

// void check_keys(void) {
//     int i;
//     char ch;
//     for (i = 0; i < key_index; i++) {
//         ch = keys[i];
//         if (ch == 'w')
//             texture.y += PLAYER_SPEED; 
//         else if (ch == 'a')
//             texture.x -= PLAYER_SPEED;
//         else if (ch == 's')
//             texture.y -= PLAYER_SPEED;
//         else if (ch == 'd')
//             texture.x += PLAYER_SPEED;
//         else if (ch == 'q')
//             wm_events_kill();
//     }
// }

void on_event(event_t event) {
    switch (event.type) {
        case EVENT_CLIENTMESSAGE:
            wm_events_kill();
            break;
        case EVENT_KEYPRESS:
            // printf("keypress\n");
            keys = wm_get_pressed_keys(&key_index);
            break;
    }
}

void cleanup() {
    // texture_delete(&texture);
    // texture_delete(&bg_tile);
    shader_delete(shader_id);
}

void draw() {
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    // glFlush();
    // if (cooldown == 0) {
    //     texture_spritesheet_next(&texture);
    //     cooldown = 100;
    // }

    draw_all(NULL, &window, shader_id);
}

void draw_callback(void) {
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glRotatef(0, 0, 1, 0);
    glRotatef(0, 1, 0, 0);
    glCallList(tea_list);
    glPopMatrix();
    glFlush();
    printf("drew'd\n");
}

int main() {
    f2d_parameters_t f2d_params;
    f2d_params.wm_start_setup_func = &window_start;
    f2d_params.wm_start_func       = &setup;
    f2d_params.draw_func           = &draw;
    f2d_params.on_event_func       = &on_event;
    f2d_params.cleanup_func        = &cleanup;
    f2d_start(f2d_params);

    while (!started);

    while (wm_events_is_running()) {
        // check_keys();
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