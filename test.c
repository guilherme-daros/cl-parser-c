#include <stdio.h>

#include "parser.h"

int main(int argc, char *argv[]) {
    settings stt;
    init_settings(&stt);
    parse_settings(&stt, argc, argv);

    print_settings(&stt);
}
