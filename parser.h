#include <stdbool.h>

#ifndef PARSER_H_
#define PARSER_H_

#define MAX_FILENAME_SIZE 128
#define MAX_NAME_SIZE 128

typedef struct {
    bool help;
    bool verbose;
    unsigned char infile[128];
    unsigned char outfile[128];
    int value;
} settings;

typedef void (*flag_handler_t)(settings *stt);

typedef void (*arg_handler_t)(settings *stt, unsigned char *arg);

typedef struct {
    char name[MAX_NAME_SIZE];
    flag_handler_t handler;
} flag_umap_entry;

typedef struct {
    char name[MAX_NAME_SIZE];
    arg_handler_t handler;
} arg_umap_entry;

typedef struct {
    unsigned char *name;
} parser;

void init_parser(parser *psr, unsigned char *name);

void init_settings(settings *stt);

void parse_settings(parser *psr, settings *stt, int argc, char *argv[]);

void print_settings(settings *my_settings);

#endif
