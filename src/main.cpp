#include "../includes/Character.hpp"

void	versusBattle( Character *Player, Character *Computer ) {
	bool		StaminaLeft;
	bool		KnockOut;
	int			Turn;

	StaminaLeft = Player->getStamina() or Computer->getStamina();
	KnockOut = !Player->getHitPoints() or !Computer->getHitPoints();
	Turn = (std::rand() % 2);
	while (StaminaLeft and !KnockOut) {
		if (Turn == COMPUTER) {
			Computer->ComputerTurn(Player);
			Turn = PLAYER;
		}
		else {
			Player->PlayerTurn(Computer);
			Turn = COMPUTER;
		}
		StaminaLeft = Player->getStamina() or Computer->getStamina();
		KnockOut = !Player->getHitPoints() or !Computer->getHitPoints();
		usleep(500000);
	}
	if (KnockOut) {
		if (!Player->getHitPoints())
			std::cout << MA << "WE HAVE A WINNER! " << Computer->getName() << " knockned out " << Player->getName() << "!" << RC << std::endl; 
		else
			std::cout << MA << "WE HAVE A WINNER! " << Player->getName() << " knockned out " << Computer->getName() << "!" << RC << std::endl;
	}
	else
		std::cout << MA << "IT'S A DRAW! Both Fighters have no Energy left!" << RC <<std::endl;
}

std::string	askName( void ) {
	std::string	cmd;
	std::string	scmd;
	bool		ask;
	
	ask = true;
	while (ask) {
		std::cout << "Please enter your Bot's Name: ";
		std::getline(std::cin, cmd);
		if (!cmd.length()) {
			std::cout << RE << "Empty name not allowed" << RC << std::endl;
		}
		else if (cmd.length() > 12) {
			scmd = cmd.substr(0, 11);
			scmd.append(".");
			return (scmd);
		}
		else
			return (cmd);
	}
	return ("Unamed Hero");
}

int	main( void ) {
	Character	Computer("J42VIS");
	Character	Player(askName());

	std::srand(time(NULL));
	versusBattle(&Player, &Computer);
	return 0;
}