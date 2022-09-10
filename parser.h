#include <stdbool.h>

#ifndef PARSER_H_
#define PARSER_H_

#define MAX_FILENAME_SIZE 128
#define MAX_NAME_SIZE 128

typedef struct {
    bool help;
    bool verbose;
    char infile[MAX_FILENAME_SIZE];
    char outfile[MAX_FILENAME_SIZE];
    int value;
} settings;

typedef void (*flag_handler_t)(settings *stt);

typedef void (*arg_handler_t)(settings *stt, char *arg);

typedef struct {
    char name[MAX_NAME_SIZE];
    flag_handler_t handler;
} flag_umap_entry;

typedef struct {
    char name[MAX_NAME_SIZE];
    arg_handler_t handler;
} arg_umap_entry;

void init_settings(settings *stt);

void parse_settings(settings *stt, int argc, char *argv[]);

void print_settings(settings *my_settings);

#endif
