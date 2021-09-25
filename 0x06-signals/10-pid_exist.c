#include <signal.h>

/**
* pid_exist - pings a pid to determine if it exists
* @pid: pid to ping
*
* Return: 0 on success, else -1
*/
int pid_exist(pid_t pid)
{
	return (kill(pid, 0) + 1);
}
