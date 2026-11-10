#include <stdio.h>
#include <string.h>

typedef void (*cmd_fn)(int argc, char **argv);

static void cmd_let_on(int argc, char **argv);
static void cmd_let_off(int argc, char **argv);
static void cmd_echo(int argc, char **argv);
static void cmd_help(int argc, char **argv);

struct command {
    const char *name;
    cmd_fn fn;
    const char *help;
};

static const struct command cmds[] = {
    { "let_on", cmd_let_on, "let_on            Turn on the LED" },
    { "let_off", cmd_let_off, "let_off           Turn off the LED" },
    { "echo", cmd_echo, "echo <args...>    Echo the input arguments" },
    { "help", cmd_help, "help              Display this help message" },
};

static int cmd_count = sizeof(cmds) / sizeof(cmds[0]);

static const struct command *find_cmd(const char *name)
{
    for (int i = 0; i < cmd_count; i++)
    {
        if (strcmp(cmds[i].name, name) == 0)
        {
            return &cmds[i];
        }
    }
    return NULL;
}

static void cmd_let_on(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    printf("LED turned on\n");
}

static void cmd_let_off(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    printf("LED turned off\n");
}

static void cmd_echo(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        printf("%s%s", argv[i], (i + 1 < argc) ? " " : "\n");
    }
    if (argc == 1)
    {
        printf("\n");
    }
}

static void cmd_help(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    for (int i = 0; i < cmd_count; i++)
    {
        printf("  %s\n", cmds[i].help);
    }
}

static int dispatch(int argc, char **argv)
{
    if (argc == 0 || argv[0] == NULL)
    {
        return -1;
    }
    const struct command *c = find_cmd(argv[0]);
    if (c != NULL)
    {
        c->fn(argc, argv);
        return 0;
    }
    printf("unknown command: %s (try help)\n", argv[0]);
    return -1;
}

int main(void)
{
    char line[256];
    printf("callback table demo: help / echo / let_on / let_off / quit\n");
    while (fgets(line, sizeof line, stdin) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0')
        {
            continue;
        }
        if (strcmp(line, "quit") == 0)
        {
            break;
        }
        char *argv[16];
        int argc = 0;
        char *tok = strtok(line, " \t");
        while (tok != NULL && argc < 16)
        {
            argv[argc++] = tok;
            tok = strtok(NULL, " \t");
        }
        dispatch(argc, argv);
    }
    return 0;
}