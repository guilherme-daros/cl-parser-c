#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define flag_umap_size 4
#define arg_umap_size 3

void f_help(settings *stt) { stt->help = true; }
void f_verbose(settings *stt) { stt->verbose = true; }

void a_infile(settings *stt, unsigned char *arg) { strcpy(stt->infile, arg); }
void a_outfile(settings *stt, unsigned char *arg) { strcpy(stt->outfile, arg); }
void a_value(settings *stt, unsigned char *arg) { stt->value = atoi(arg); }

flag_umap_entry flags[flag_umap_size] = {
    {"--help", f_help},
    {"-h", f_help},

    {"--verbose", f_verbose},
    {"-v", f_verbose},
};

arg_umap_entry args[arg_umap_size] = {
    {"--output", a_outfile},
    {"-o", a_outfile},

    {"--value", a_value},
};

void init_parser(parser *psr, unsigned char *name) { strcpy(psr->name, name); }

void init_settings(settings *stt) {
    stt->help = false;
    stt->verbose = false;
    strcpy(stt->infile, " ");
    strcpy(stt->outfile, " ");
    stt->value = 0;
}

void print_settings(settings *my_settings) {
    printf("[Flags]\n\r");
    printf("help: %s\n\r", (my_settings->help ? "true" : "false"));
    printf("verbose: %s\n\r", (my_settings->verbose ? "true" : "false"));

    printf("[Arguments]\n\r");
    printf("infile: %s\n\r", my_settings->infile);
    printf("outfile: %s\n\r", my_settings->outfile);
    printf("value: %i\n\r", my_settings->value);
}

void parse_settings(parser *psr, settings *stt, int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        char opt[MAX_NAME_SIZE];
        strcpy(opt, argv[i]);

        for (int j = 0; j < flag_umap_size; j++) {
            if (flags[j].name == opt) {
                flags[j].handler(stt);
            } else {
                for (int j = 0; j < arg_umap_size; j++) {
                    if (args[j].name == opt) {
                        if (++i < argc) {
                            args[i].handler(stt, argv[i]);
                        } else {
                            char tmp[1024];
                            sprintf(tmp, "[%s] missing param after %s", psr->name, argv[i]);
                            fputs(tmp, stderr);
                            exit(0);
                        }
                    } else {
                        if (!stt->infile) {
                            strcpy(stt->infile, argv[i]);
                        } else {
                            char tmp[1024];
                            sprintf(tmp, "[%s] unrecognized command line option: %s", psr->name,
                                    argv[i]);
                            fputs(tmp, stderr);
                            exit(0);
                        }
                    }
                }
            }
        }
    }
};
