#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define p_y 5
#define p_x 16

char map_2d[p_y][p_x + 1] = {
    "111111111111111",
    "100010000000011",
    "100P10000000111",
    "1C00000000000E1",
    "111111111111111"
};

bool isValid(int row, int col, char temp[p_y][p_x]) {
    return (row >= 0 && row < p_y && col >= 0 && col < p_x && map_2d[row][col] != '1' && temp[row][col] == 0);
}

void ft_check_access(int row, int col, char temp[p_y][p_x]) {
    if (!isValid(row, col, temp))
        return;

    temp[row][col] = 1;

    ft_check_access(row + 1, col, temp);
    ft_check_access(row - 1, col, temp);
    ft_check_access(row, col + 1, temp);
    ft_check_access(row, col - 1, temp);
}

int main() {
    int i, j;

    printf("Original map_2d:\n");
    for (i = 0; i < p_y; i++) {
        printf("%s\n", map_2d[i]);
    }

    char temp[p_y][p_x] = {0};

    for (i = 0; i < p_y; i++) {
        for (j = 0; j < p_x; j++) {
            if (map_2d[i][j] == 'P') {
                
            }
        }
    }
    ft_check_access(i, j, temp);
    printf("\nmap_2d after flood fill:\n");
    for (i = 0; i < p_y; i++) {
        for (j = 0; j < p_x; j++) {
            if (temp[i][j] != '\0' && (map_2d[i][j] == '0')) {
                map_2d[i][j] = 'V';
            }
        }
        printf("%s\n", map_2d[i]);
    }

    return 0;
}
