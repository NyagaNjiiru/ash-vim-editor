#include "editor.h"
#include <time.h>

struct editor_config E;

int main(int argc, char *argv[])
{
    init_editor();

    if (argc >= 2)
    {
        editor_open(argv[1]);
    }

    editor_set_status_message("HELP: Ctrl-S = save | Ctrl-Q = quit | i = insert mode");

    while (1)
    {
        editor_refresh_screen();
        editor_process_keypress();
    }
    return 0;
}