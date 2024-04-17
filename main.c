#include <stdio.h>

int num_zero(int set) {
    int count = 0;
    for (int i = 1; i <= 9; i++) {
        if (!(set & (1 << i))) {
            count++;
        }
    }
    return count;
}

void setBit(int b[3][9], int row, int col, int k) {
    b[0][row] |= (1 << k);
    b[1][col] |= (1 << k);
    b[2][3 * (row / 3) + col / 3] |= (1 << k);
}

void clearBit(int b[3][9], int row, int col, int k) {
    b[0][row] &= ~(1 << k);
    b[1][col] &= ~(1 << k);
    b[2][3 * (row / 3) + col / 3] &= ~(1 << k);
}

int solveSukoduHelper(int a[9][9], int b[3][9]) {
    int bestSet = 0, bestSize = 9, bestRow = -1, bestCol = -1;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (a[i][j] == 0) {
                int set = b[0][i] | b[1][j] | b[2][3 * (i / 3) + j / 3];
                int size = num_zero(set);

                if (size < bestSize) {
                    bestRow = i;
                    bestCol = j;
                    bestSet = set;
                    bestSize = size;
                }

                if (size == 0) return 0;
            }
        }
    }

    if (bestRow == -1) return 1;

    for (int k = 1; k <= 9; k++) {
        if (!(bestSet & (1 << k))) {
            a[bestRow][bestCol] = k;
            setBit(b, bestRow, bestCol, k);

            if (solveSukoduHelper(a, b)) return 1;

            clearBit(b, bestRow, bestCol, k);
            a[bestRow][bestCol] = 0;
        }
    }

    return 0;
}

void solveSukodu(int a[9][9]) {
    int b[3][9] = {{0}};

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            setBit(b, i, j, a[i][j]);
        }
    }

    solveSukoduHelper(a, b);
}

int main() {
    int n;
    scanf("%d", &n);

    while (n--) {
        int sudoku[9][9];

        for (int i = 0; i < 9; i++) {
            char line[10];
            scanf("%s", line);

            for (int j = 0; j < 9; j++) {
                if (line[j] == '.') sudoku[i][j] = 0;
                else sudoku[i][j] = line[j] - '0';
            }
        }

        solveSukodu(sudoku);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf("%d", sudoku[i][j]);
            }
            printf("\n");
        }

        printf("\n");
    }

    return 0;
}
