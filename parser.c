#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define flag_umap_size 4
#define arg_umap_size 3

void f_help(settings *stt) { stt->help = true; }
void f_verbose(settings *stt) { stt->verbose = true; }

void a_infile(settings *stt, char *arg) { strncpy(stt->infile, arg, sizeof(stt->infile)); }
void a_outfile(settings *stt, char *arg) { strncpy(stt->outfile, arg, sizeof(stt->outfile)); }
void a_value(settings *stt, char *arg) { stt->value = atoi(arg); }

flag_umap_entry flags[flag_umap_size] = {
    {"--help", f_help},
    {"-H", f_help},

    {"--verbose", f_verbose},
    {"-V", f_verbose},
};

arg_umap_entry args[arg_umap_size] = {
    {"--output", a_outfile},
    {"-O", a_outfile},

    {"--value", a_value},
};

void init_settings(settings *stt) {
    stt->help = false;
    stt->verbose = false;
    memset(stt->infile, 0, sizeof(stt->infile));
    memset(stt->outfile, 0, sizeof(stt->outfile));
    stt->value = 0;
}

void print_settings(settings *my_settings) {
    printf("(cl-parser) [Flags]\n\r");
    printf("(cl-parser)  help: %s\n\r", (my_settings->help ? "true" : "false"));
    printf("(cl-parser)  verbose: %s\n\r\n\r", (my_settings->verbose ? "true" : "false"));

    printf("(cl-parser) [Arguments]\n\r");
    printf("(cl-parser)  infile: %s\n\r", my_settings->infile);
    printf("(cl-parser)  outfile: %s\n\r", my_settings->outfile);
    printf("(cl-parser)  value: %i\n\r", my_settings->value);
}

void parse_settings(settings *stt, int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        char opt[MAX_NAME_SIZE] = "";
        strcpy(opt, argv[i]);
        bool found = false;

        for (int j = 0; j < flag_umap_size; j++) {
            if (strstr(opt, flags[j].name) != NULL) {
                found = true;
                flags[j].handler(stt);
            }
        }
        for (int j = 0; j < arg_umap_size; j++) {
            if (strstr(opt, args[j].name) != NULL) {
                found = true;
                if (++i < argc) {
                    args[j].handler(stt, argv[i]);
                } else {
                    char tmp[1024];
                    sprintf(tmp, "(cl-parser) missing param after %s", argv[i]);
                    fputs(tmp, stderr);
                    exit(0);
                }
            }
        }
        if (!stt->infile[0] && !found) {
            found = true;
            if (argv[i][0] != '-') {
                strcpy(stt->infile, argv[i]);
            } else {
                char tmp[1024];
                sprintf(tmp, "(cl-parser) unrecognized command line option: %s", argv[i]);
                fputs(tmp, stderr);
                exit(0);
            }
        } else if (!found) {
            char tmp[1024];
            sprintf(tmp, "[cl-parser] unrecognized command line option: %s", argv[i]);
            fputs(tmp, stderr);
            exit(0);
        }
    }
};
