#include "../inc/minishell.h"

t_minishell	*create_struct_1(char **env)
{
	t_minishell	*shell;

    shell = malloc(sizeof(t_minishell));
	shell->env = copy_realloc_data(env, 0);
	return (shell);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	*shell;

	(void)ac;
	(void)av;
    char **env_copy;

	// env_copy = copy_realloc_data(env, 0);
	// free_array(env_copy);

	shell = create_struct_1(env);
    shell->env = add_env_value(shell->env, "test", "test");
	free_array(shell->env);
    free(shell);
	return (0);
}