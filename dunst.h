/* copyright 2013 Sascha Kruse and contributors (see LICENSE for licensing information) */

#pragma once

#include <glib.h>
#include <stdbool.h>

#include "draw.h"

#define ERR(msg) printf("%s : %d\n", (msg), __LINE__)
#define PERR(msg, errnum) printf("(%d) %s : %s\n", __LINE__, (msg), (strerror(errnum)))
#define LENGTH(X)               (sizeof X / sizeof X[0])

#define LOW 0
#define NORM 1
#define CRIT 2

#define ColLast 2
#define ColFG 1
#define ColBG 0

enum alignment { left, center, right };
enum separator_color { FOREGROUND, AUTO, FRAME, CUSTOM };
enum follow_mode { FOLLOW_NONE, FOLLOW_MOUSE, FOLLOW_KEYBOARD };

typedef struct _dimension_t {
        int x;
        int y;
        unsigned int h;
        unsigned int w;
        int mask;
        int negative_width;
} dimension_t;

typedef struct _screen_info {
        int scr;
        dimension_t dim;
} screen_info;

typedef struct _actions {
        char **actions;
        char *dmenu_str;
        gsize count;
} Actions;

typedef struct _notification {
        char *appname;
        char *summary;
        char *body;
        char *icon;
        char *msg;
        const char *format;
        char *dbus_client;
        time_t start;
        time_t timestamp;
        int timeout;
        int urgency;
        bool redisplayed;       /* has been displayed before? */
        int id;
        int dup_count;
        ColorSet *colors;
        char *color_strings[2];

        int progress;           /* percentage + 1, 0 to hide */
        int line_count;
        const char *script;
        char *urls;
        Actions *actions;
} notification;


typedef struct _keyboard_shortcut {
        const char *str;
        KeyCode code;
        KeySym sym;
        KeySym mask;
        bool is_valid;
} keyboard_shortcut;

typedef struct _render_text {
        ColorSet *colors;
        GSList *lines;
} render_text;

extern int verbosity;

/* return id of notification */
int notification_init(notification * n, int id);
int notification_close_by_id(int id, int reason);
gboolean run(void *data);
void wake_up(void);

/* vim: set ts=8 sw=8 tw=0: */
