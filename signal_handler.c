#include "main.h"

/**
  * signal_handler - handles the SIG_INT.
  *
  * Return: no return.
  */
void signal_handler()
{
	write(STDOUT_FILENO, "\n", 1);
	prompt();
}