#ifndef PARSING_H
#define PARSING_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 64
#endif

typedef struct s_texture
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;
} t_texture;

typedef struct s_info
{
    t_texture textures;
    char *floor;
    char *ceil;
    char **map;
    int map_row;
} t_info;

size_t ft_strlen(const char *str);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *get_next_line(int fd);
int file_extension_check(char *filename);
int is_empty_line(char *line);
char *extract_texture(char *line, int *i);
int extract_no(char *line, int i, t_info *info);
int extract_so(char *line, int i, t_info *info);
int extract_we(char *line, int i, t_info *info);
int extract_ea(char *line, int i, t_info *info);
int extract_floor(char *line, int i, t_info *info);
int extract_ceil(char *line, int i, t_info *info);
int all_data_found(t_info *info);
void free_info(t_info *info);
int extract_map(char *line, t_info *info);

#endif