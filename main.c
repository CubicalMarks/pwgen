/*
 * pwgen, a small password generator.
 *
 * Generates desired number of alphanumeric passwords of arbitrary
 * length with optional special characters.
 *
 * Copyright (c) 2006 Marcus Libäck <marcus@terminal.se>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "pwgen.h"

#define DEFAULT_LEN 12
#define DEFAULT_NUM 1
int pwlen = DEFAULT_LEN;
int num = DEFAULT_NUM;

int main(int argc, char **argv)
{
    int c, i;
    int special = 0, error = 0;
    char *digit, *password;

    /* Take care of command line options. */
    while ((c = getopt(argc, argv, ":shl:n:")) != -1) {
        switch (c) {
        case 's':
            special = 1;
            break;
        case 'h':
            error++;
            break;
        case 'l':
            /* Check for illegal argument. */
            digit = optarg;
            while (*digit != '\0')
                if (!isdigit(*(digit++))) {
                    error++;
                    break;
                }
            pwlen = atoi(optarg);
            break;
        case 'n':
            /* Check for illegal argument. */
            digit = optarg;
            while (*digit != '\0')
                if (!isdigit(*(digit++))) {
                    error++;
                    break;
                }
            num = atoi(optarg);
            break;
        case ':':
            error++;
            break;
        case '?':
            fprintf(stderr, "Unrecognised option: -%c\n\n",    optopt);
            error++;
        }

        if (error > 0) {
            print_help();
            exit(1);
        }
    }

    srand(get_rand());

    /* Allocate memory for the password. */
    if ((password = calloc(pwlen+1, sizeof(char))) == NULL) {
        fprintf(stderr, "Insufficient memory.");
        exit(2);
    }

    for (i=0;i<num;++i)
        printf("%s\n", pwgen(pwlen, special, password));

    free(password);

    return 0;
}

/* Help. */
void print_help()
{
    printf("Usage: pwgen [options]\n"
        "\n"
        "Options:\n"
        " -h\tdisplay this text.\n"
        "\n"
        " -l <num>    password length, defaults to %d.\n"
        " -n <num>    number of passwords to generate, defaults to %d.\n"
        " -s          includes special characters.\n", DEFAULT_LEN, num);
}
