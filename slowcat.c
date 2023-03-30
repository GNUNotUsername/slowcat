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

/*      Argv            */
#define DELAY           2
#define GOOD_ARGC       3
#define PATH            1

/*      Error Codes     */
#define BAD_ARGC        1
#define BAD_FILE        2
#define BAD_DELAY       3

/*      Error Messages  */
#define BAD_COUNT       "Delay must be a nonnegative integer"
#define F_NEXIST        "No such file"
#define USAGE           "Usage: slowcat file delay"

/*      File I/O        */
#define READ            "r"

void    fail        (char *, int);
bool    is_numeric  (char *     );

int
main(int argc, char **argv)
{
    char    *delay, *path;
    FILE    *src;
    int     count;

    if (argc != GOOD_ARGC) fail(USAGE, BAD_ARGC);
    path    = argv[PATH];
    delay   = argv[DELAY];

    src     = fopen(path, READ);
    if (!src) fail (F_NEXIST, BAD_FILE);

    if (!is_numeric(delay)) fail(BAD_COUNT, BAD_DELAY);
    count   = atoi(delay);

    printf("%s %d\n", path, count);
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
