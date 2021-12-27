#include "./Game/game.h"
#include "./Communication/net_prisoner_server.h"
#include "Configuration/configuration.h"
#include "./Tests/test.h"

int main()
{
	test_initializations();
	test_game_management();
	test_connections();
 
	return (0);
}