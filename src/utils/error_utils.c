int	print_error(char *error, int num_error)
{
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
	free(error);
	return (num_error);
}

void 	exit_program(char *msg_error, int num_error)
{
	// Free master
	if (msg_error)
		print_error(msg_error, num_error);
	// system("leaks minishell");
	if (num_error < 0)
		exit(num_return_error);
	exit (num_error);
}