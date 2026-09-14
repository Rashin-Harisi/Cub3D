#ifndef PARSING_H
#define PARSING_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"

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
    int rgb_floor[3];
    int rgb_ceil[3];
    char **map;
    char **rect_map;
    int map_row;
    int max_col;
    int row;
    int player[2]; //[x,y]
    char player_dir;
} t_info;

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
int info_validation(t_info *info);
char **ft_split(char const *s, char c);
void free_array(char **array);
int texture_validation(t_texture *textures);
int rgb_validation(t_info *info);
int map_validation(t_info *info);
char *extract_rgb(char *line, int *i);
int normalized_map(t_info *info);
int	character_validation(char **map);
int	wall_validation(t_info *info);
void	skip_spaces(char *line, int *i);
int	playable_tile(char **map);
int	handle_rgb_space(char *line, int *i, char *rgb, int j);
void    print(t_info *info);
#endif