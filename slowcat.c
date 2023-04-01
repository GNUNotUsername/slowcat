/**
 * Cat a file with a delay between each newline
 * Usage:   slowcat file delay
 *
 * file :   file to be catted
 * delay:   delay between each newline (ms)
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*      Argv            */
#define DELAY           2
#define GOOD_ARGC       3
#define PATH            1

/*      Error Codes     */
#define BAD_ARGC        1
#define BAD_FILE        2
#define BAD_DELAY       3
#define GOOD            0

/*      Error Messages  */
#define BAD_COUNT       "Delay must be a nonnegative integer"
#define F_NEXIST        "No such file"
#define USAGE           "Usage: slowcat file delay"

/*      File I/O        */
#define READ            "r"

/*      Strings         */
#define EMPTY_STRING    1
#define EOS             '\0'
#define NEWLINE         '\n'

/*      Timing          */
#define MICROSECONDS    1000

void        fail        (char *, int);
bool        is_numeric  (char *     );
char    *   take_line   (FILE *     );

int
main(int argc, char **argv)
{
    char    *delay, *line, *path;
    FILE    *src;
    int     count;

    if (argc != GOOD_ARGC) fail(USAGE, BAD_ARGC);
    path    = argv[PATH];
    delay   = argv[DELAY];

    src     = fopen(path, READ);
    if (!src) fail (F_NEXIST, BAD_FILE);

    if (!is_numeric(delay)) fail(BAD_COUNT, BAD_DELAY);
    count   = atoi(delay) * MICROSECONDS;

    while (!(feof(src) || ferror(src))) {
        line = take_line(src);
        if (feof(src) || ferror(src)) break;
        printf("%s\n", line);
        fflush(stdin);
        free(line);
        usleep(count);
    }

    return (GOOD);
}

void
fail(char *message, int exitCode)
{
    printf("%s\n", message);
    exit(exitCode);
}

bool
is_numeric(char *cand)
{
    bool    verdict;
    int     check, len;

    verdict = true;
    len     = strlen(cand);
    for (check = 0; verdict && (check < len); check++)
            verdict = (bool)isdigit(cand[check]);

    return (verdict);
}

char *
take_line(FILE *src)
{
    char    add, *out;
    int     len;

    out = NULL;
    len = 0;
    while (!(feof(src) || ferror(src))) {
        add = fgetc(src);
        if (add == NEWLINE) add = EOS;
        out = realloc(out, (len + 1) * sizeof(char));
        out[len++] = add;
        if (add == EOS) break;
    }

    return (out);
}
