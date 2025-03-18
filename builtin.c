#include "../inc/minishell.h"
#include <linux/limits.h>

void do_pwd(void)
{
    char    cwd[PATH_MAX];

    if(getcwd(cwd, sizeof(cwd) != NULL))
        printf("%s\n", cwd);
    else
        perror("getcwd");
}

void do_cd()
