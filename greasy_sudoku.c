// compile with gcc -O3 greasy_sudoku.c -o greasy_sudoku

#include <stdio.h>
#include <stdlib.h>

#define UNKNOWN (1 << 10)

int __builtin_popcount(unsigned int x);

void solve(int *pzx) {
    int pz[81];
    int shortest = 11;
    int p_x, p_y;
    int this, that;

    // Copy the puzzle.
    for (int i = 0; i < 81; i++)
        pz[i] = pzx[i];

    // Determine which numbers can be in each empty cell.
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            if (pz[y * 9 + x] & UNKNOWN) {
                // Start with all possible numbers.
                this = 0x7FE;

                // Check the 3x3 square.
                for (int sx = (x / 3) * 3; sx < ((x / 3) * 3 + 3); sx++) {
                    for (int sy = (y / 3) * 3; sy < ((y / 3) * 3 + 3); sy++) {
                        that = pz[sy * 9 + sx];
                        if (!(that & UNKNOWN)) {
                            this &= ~(1 << that);
                        }
                    }
                }

                // If we're left with no numbers, this solution won't work.
                if (this == UNKNOWN)
                    return;

                // Check row & col.
                for (int s = 0; s < 9; s++) {
                    that = pz[y * 9 + s];
                    if (!(that & UNKNOWN)) {
                        this &= ~(1 << that);
                    }
                    that = pz[s * 9 + x];
                    if (!(that & UNKNOWN)) {
                        this &= ~(1 << that);
                    }
                }

                // If we're left with no numbers, this solution won't work.
                if (this == UNKNOWN)
                    return;

                pz[y * 9 + x] = this;

                int length = __builtin_popcount(this & ~UNKNOWN);
                if (length < shortest) {
                    shortest = length;
                    p_x = x;
                    p_y = y;
                }
            }
        }
    }

    if (shortest == 11) {
        // Got it! Print the solution and exit.
        for (int y = 0; y < 9; y++) {
            printf(
                "%d%d%d%d%d%d%d%d%d\n",
                pz[y * 9 + 0],
                pz[y * 9 + 1],
                pz[y * 9 + 2],
                pz[y * 9 + 3],
                pz[y * 9 + 4],
                pz[y * 9 + 5],
                pz[y * 9 + 6],
                pz[y * 9 + 7],
                pz[y * 9 + 8]
            );
        }
        exit(0);
    }

    // p_x and p_y contain the coordinates of the cell with the shortest
    // list of possible numbers.
    int c = pz[p_y * 9 + p_x];
    int mask = 2;

    // Try each of the possible numbers for this cell.
    for (int n = 1; n < 10; n++, mask <<= 1) {
        if (!(c & mask))
            continue;

        // Set the number and then try solving with it.
        pz[p_y * 9 + p_x] = n;
        solve(pz);
    }
}

int main(int argc, char **argv) {
    int pz[81];

    // Load the puzzle. There's no time for error checking.
    FILE *fp = fopen(argv[1], "r");

    for (int y = 0; y < 9; y++) {
        char buf[11];

        fgets(buf, sizeof(buf), fp);

        for (int x = 0; x < 9; x++) {
            if (buf[x] == '0')
                pz[y * 9 + x] = UNKNOWN;
            else
                pz[y * 9 + x] = buf[x] - '0';
        }
    }

    // Let the operating system close the file when the program is done.

    // Solve the puzzle.
    solve(pz);

    // Never reaches here. solve() exits the program when it's done.
    return 0;
}
