#include <stdio.h>

#include "parser.h"

int main(int argc, char *argv[]) {
    parser psr;
    printf("b_init_parser\n");
    init_parser(&psr, "cl-parser");
    printf("f_init_parser\n");

    // settings stt;
    // printf("b_init_settings\n");
    //  init_settings(&stt);
    //  printf("f_init_settings");

    // parse_settings(&psr, &stt, argc, argv);
    // print_settings(&stt);
}
