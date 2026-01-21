#include "parsing.h"

void	exit_program(t_miso *mv)
{
	//update signal number if reason is signal usage
	print_error_message(mv);
	free_misoverse(mv);
}
