#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <ctype.h>

#define EDITOR_VERSION "0.0.1"
#define EDITOR_NAME "AshVim"

#define CTRL_KEY(k) ((k) & 0x1f)

enum editor_key
{
    BACKSPACE = 127,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

enum editor_mode
{
    MODE_NORMAL,
    MODE_INSERT,
    MODE_COMMAND,
    MODE_VISUAL
};

typedef struct erow
{
    int size;
    int rsize;
    char *chars;
    char *render;
} erow;

struct editor_config
{
    int cx, cy;
    int rx;
    int rowoff;
    int coloff;
    int screenrows;
    int screencols;
    int numrows;
    erow *row;
    int dirty;
    char *filename;
    char statusmsg[80];
    time_t statusmsg_time;
    enum editor_mode mode;
    struct termios orig_termios;
};

extern struct editor_config  E;

void die(const char *s);
void disbale_raw_mode(void);
void enable_raw_mode(void);
int editor_read_key(void);
int get_cursor_position(int *rows, int *cols);
int get_window_size(int *rows, int *cols);

void editor_insert_row(int at, char *s, size_t len);
void editor_update_row(erow *row);
void editor_delete_char(void);
void editor_insert_char(int c);
void editor_insert_newline(void);

char *editor_rows_to_string(int *buflen);
void editor_open(char *filename);
void editor_save(void);

void editor_process_keypress(void);
void editor_move_cursor(int key);

void editor_scroll(void);
void editor_draw_rows(struct abuf *ab);
void editor_draw_status_bar(struct abuf *ab);
void editor_draw_message_bar(struct abuf *ab);
void editor_refresh_screen(void);
void editor_set_status_message(const char *fmt, ...);

void init_editor(void);

struct abuf
{
    char *b;
    int len;
};

#define ABUF_INIT {NULL, 0}

void ab_append(struct abuf *ab, const char *s, int len);
void ab_free(struct abuf *ab);

#endif