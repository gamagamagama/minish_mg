#include "../inc/minishell.h"
#include "../inc/env_var.h"
#include <linux/limits.h>

typedef struct s_env
{
    void *all;
}t_env;

void do_pwd(void)
{
    char    cwd[PATH_MAX];

    if(getcwd(cwd, sizeof(cwd)) != NULL)
        printf(YELLOW"%s\n"RESET, cwd);
    else
        perror(YELLOW"getcwd err"RESET);
}
int cd_change_dir(char *path, char **old_pwd) 
{
    char *prev_dir = NULL;
    char *curent_dir = NULL;
   
    prev_dir = getcwd(NULL, 0);
    if (!prev_dir) 
    {
        perror(PURPLE"getcwd failed before chdir"RESET);
        return(0);
    }
    if (chdir(path) == -1) 
    {
        perror(PURPLE"cd failed"RESET);
        free(prev_dir);
        return(0);
    }
    free(*old_pwd);
    *old_pwd = prev_dir;
    curent_dir = getcwd(NULL, 0);
    if (curent_dir) 
    {
        printf(PURPLE"Directory changed to: %s\n"RESET, curent_dir);
        free(curent_dir);
    } 
    else 
    {
        perror(PURPLE"getcwd failed after chdir"RESET);
    }
    return(1);
    
}

void do_cd(t_env *env, char *path)
{
    char *home;
    static char *old_pwd = NULL;

    home = get_env_value(env, "HOME");
    if(path == NULL || ft_strcmp(path, "~") == 0)
        path = home;
    else if(ft_strcmp(path, "-") == 0)
    {
        if (old_pwd)
        {
            printf(YELLOW"%s\n"RESET, old_pwd);
            path = old_pwd;
        }
        else
        {
            printf(PURPLE"cd: prev PWD not set\n"RESET);
            return;
        }
    }
    if(!cd_change_dir(path, &old_pwd))
        return;
 
}

void do_echo(t_env *env, t_ast_node **argv)
{
    int is_flag;
    int i;
    
    i = 0;
    is_flag = 0;
    if((*argv)->args[i] && ft_strcmp((*argv)->args[i], "-n") == 0)
    {
        is_flag = 1;
        i++;
    }
    while((*argv)->args[i])
    {
        printf("%s", (*argv)->args[i]);
        if ((*argv)->args[i + 1])
        {
            printf(" ");
        }
        i++;
    }
    if(!is_flag)
        printf("\n");

}



// int main()
// {
//     char cwd[PATH_MAX];
   

//     printf(GREEN "Initial Directory:"RESET""RED" %s\n"RESET, getcwd(cwd, sizeof(cwd)));

//     // Test 1: Change to home directory
//     do_cd(NULL);
//     printf(GREEN "After cd to home:"RESET""RED" %s\n"RESET, getcwd(cwd, sizeof(cwd)));

//     // Test 2: Change to root directory
//     do_cd("/");
//     printf(GREEN"After cd to /:"RESET""RED" %s\n"RESET, getcwd(cwd, sizeof(cwd)));

//     // Test 3: Change to an invalid directory
//     do_cd("/non_existent_directory");
//     printf(GREEN"After cd to invalid directory:"RESET""RED" %s\n"RESET, getcwd(cwd, sizeof(cwd)));

//     // Test 4: Change to a subdirectory (assume /tmp exists)
//     do_cd("/tmp");
//     printf(GREEN"After cd to /tmp:"RESET""RED" %s\n"RESET, getcwd(cwd, sizeof(cwd)));

//     // Test 5: Change back to the previous directory using "-"
//     do_cd("-");
//     printf(GREEN"After cd to previous directory: "RESET""RED" %s\n"RESET, getcwd(cwd, sizeof(cwd)));

//     return 0;
// }