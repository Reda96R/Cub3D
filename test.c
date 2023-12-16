/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:25:49 by rerayyad          #+#    #+#             */
/*   Updated: 2023/12/16 15:25:54 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "mlx_linux/mlx.h"
#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>

#define ESCAPE_KEY 65307
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100

typedef struct {
    int x;
    int y;
    int size;
    void *mlx;
    void *win;
} Square;

void drawSquare(void *mlx, void *win, int x, int y, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mlx_pixel_put(mlx, win, x + i, y + j, 0xFFFFFF); // White color
        }
    }
}

void clearSquare(void *mlx, void *win, int x, int y, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mlx_pixel_put(mlx, win, x + i, y + j, 0x000000); // Black color (clear)
        }
    }
}

int keyPress(int keycode, void *param) {
    Square *square = (Square *)param;
    void *mlx = square->mlx;
    void *win = square->win;

    clearSquare(mlx, win, square->x, square->y, square->size);

    // Handle movement based on the key pressed
    if (keycode == W_KEY) {
        square->y -= 5; // Move up
    } else if (keycode == A_KEY) {
        square->x -= 5; // Move left
    } else if (keycode == S_KEY) {
        square->y += 5; // Move down
    } else if (keycode == D_KEY) {
        square->x += 5; // Move right
    } else if (keycode == ESCAPE_KEY) {
        exit(0); // Exit the program on ESC key
    }

    drawSquare(mlx, win, square->x, square->y, square->size);
    mlx_do_sync(mlx); // Synchronize the changes

    return 0;
}

int keyPressLoop(void *param) {
    // This function is empty for Linux
    return 0;
}

int main() {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 500, 500, "MiniLibX Example");

    Square square = {100, 100, 50, mlx, win};

    mlx_hook(win, 2, 1L<<0, keyPress, &square);
    mlx_loop_hook(mlx, keyPressLoop, &square);

    drawSquare(mlx, win, square.x, square.y, square.size);

    mlx_loop(mlx);

    return 0;
}

