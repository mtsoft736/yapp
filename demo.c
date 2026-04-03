/*
 * demo.c — yapp library demonstration
 *
 * Compile (after building yapp.dll / libyapp.so):
 *
 *   Windows:  gcc -o demo.exe demo.c -L. -lyapp -I. -Wall
 *   Linux:    gcc -o demo     demo.c -L. -lyapp -I. -Wall
 */

#include <stdio.h>    /* only needed for stderr in yapf calls */
#include "yapp.h"

/* ── helpers ─────────────────────────────────────────────────────────────── */

static void section(const char *title)
{
    yapp("\n");
    yapp("══════════════════════════════════════\n");
    yapp("  %s\n", title);
    yapp("══════════════════════════════════════\n");
}

/* ── main ────────────────────────────────────────────────────────────────── */

int main(void)
{
    /* ── Banner ──────────────────────────────────────────────────────────── */
    yapp("┌─────────────────────────────────────┐\n");
    yapp("│      yapp  —  demo program          │\n");
    yapp("│  Yet Another Print Protocol  v1.0   │\n");
    yapp("└─────────────────────────────────────┘\n");

    /* ── 1. yapp: basic strings ──────────────────────────────────────────── */
    section("1. yapp — basic output");

    yapp("Hello, World!\n");
    yapp("No printf was used to print this line.\n");

    /* ── 2. yapp: format specifiers ─────────────────────────────────────── */
    section("2. yapp — format specifiers");

    int    age    = 22;
    double height = 1.82;
    char  *name   = "Matej";

    yapp("Name   : %s\n",    name);
    yapp("Age    : %d\n",    age);
    yapp("Height : %.2f m\n", height);

    yapp("\n");
    yapp("Hex  : 0x%X\n",  255);
    yapp("Oct  : 0%o\n",   255);
    yapp("Sci  : %e\n",    0.000123);
    yapp("Char : %c\n",    'Y');

    /* ── 3. yappln: auto newline ─────────────────────────────────────────── */
    section("3. yappln — automatic newline");

    yappln("This line has no \\n in the source code.");
    yappln("Neither does this one.");
    yappln("Item %d: %s", 1, "apple");
    yappln("Item %d: %s", 2, "banana");
    yappln("Item %d: %s", 3, "cherry");

    /* ── 4. yapf: stderr ─────────────────────────────────────────────────── */
    section("4. yapf — writing to stderr");

    yapp("The next line goes to stderr (may appear out of order):\n");
    yapf(stderr, "[ERROR] This is an error message on stderr.\n");
    yapp("Back on stdout.\n");

    /* ── 5. yapf: file output ────────────────────────────────────────────── */
    section("5. yapf — writing to a file");

    FILE *log = fopen("demo.log", "w");
    if (log) {
        yapf(log, "=== demo.log ===\n");
        yapf(log, "User   : %s\n", name);
        yapf(log, "Age    : %d\n", age);
        yapf(log, "Status : OK\n");
        fclose(log);
        yappln("Log written to demo.log");
    } else {
        yapf(stderr, "[WARN] Could not open demo.log for writing.\n");
    }

    /* ── 6. UTF-8 ────────────────────────────────────────────────────────── */
    section("6. UTF-8 output");

    yappln("Czech  : Příliš žluťoučký kůň úpěl ďábelské ódy.");
    yappln("Polish : Zażółć gęślą jaźń.");
    yappln("German : Falsches Üben von Xylophonmusik quält jeden Vogel.");
    yappln("Greek  : Ξεσκεπάζω την ψυχοφθόρα βδελυγμία.");
    yappln("Math   : π ≈ 3.14159  |  √2 ≈ 1.41421  |  ∞");

    /* ── 7. Numbers & padding ────────────────────────────────────────────── */
    section("7. Padding & alignment");

    yapp("%-12s %6s %10s\n", "Product",   "Qty",  "Price");
    yapp("%-12s %6s %10s\n", "----------","-----","----------");
    yapp("%-12s %6d %10.2f\n", "Apple",    120,    0.49);
    yapp("%-12s %6d %10.2f\n", "Banana",   85,     0.29);
    yapp("%-12s %6d %10.2f\n", "Cherry",   200,    1.99);
    yapp("%-12s %6d %10.2f\n", "Mango",    34,     2.49);

    /* ── Done ────────────────────────────────────────────────────────────── */
    section("Done");
    yappln("All output produced with yapp, yappln, and yapf.");
    yappln("Zero printf calls were made.");
    yapp("\n");

    return 0;
}
