#include "../includes/Character.hpp"
#include "../includes/Shadow.hpp"
#include "../includes/Berserk.hpp"
//#include "../includes/Guardian.hpp"

void	versusBattle( Character *Player, Character *Computer ) {
	bool		StaminaLeft;
	bool		KnockOut;
	int			Turn;

	StaminaLeft = Player->getStamina() or Computer->getStamina();
	KnockOut = !Player->getHitPoints() or !Computer->getHitPoints();
	Turn = (std::rand() % 2);
	if (Turn == COMPUTER)
		std::cout << BOLD << ITAL << "\t\tComputer " << *Computer << " goes First\n" << RC << std::endl;
	else
		std::cout << BOLD << ITAL << "\t\tPlayer " << *Player << " goes First\n" << RC << std::endl;
	while (StaminaLeft and !KnockOut) {
		if (Turn == COMPUTER) {
			Computer->NewTurn(COMPUTER, Player);
			Turn = PLAYER;
		}
		else {
			Player->NewTurn(PLAYER, Computer);
			Turn = COMPUTER;
		}
		StaminaLeft = Player->getStamina() or Computer->getStamina();
		KnockOut = !Player->getHitPoints() or !Computer->getHitPoints();
		usleep(500000);
	}
	if (KnockOut) {
		if (!Player->getHitPoints() and !Computer->getHitPoints())
			std::cout << MA << "\n\t\tIT'S A DRAW! Both Fighters are knocked out!" << RC <<std::endl;
		if (!Player->getHitPoints())
			std::cout << MA << "\n\t\tWE HAVE A WINNER! " << Computer->getName() << " knockned out " << Player->getName() << "!" << RC << std::endl; 
		else
			std::cout << MA << "\n\t\tWE HAVE A WINNER! " << Player->getName() << " knockned out " << Computer->getName() << "!" << RC << std::endl;
	}
	else
		std::cout << MA << "\n\t\tIT'S A DRAW! Both Fighters have no Energy left!" << RC <<std::endl;
}

std::string	askName( void ) {
	std::string	cmd;
	std::string	scmd;
	bool		ask;
	
	ask = true;
	while (ask) {
		std::cout << BOLD << "\t\tPlease enter your Fighter's Name: " << RC;
		std::getline(std::cin, cmd);
		if (!cmd.length()) {
			std::cout << RE << "\t\tEmpty name not allowed" << RC << std::endl;
		}
		else if (cmd.length() > 12) {
			scmd = cmd.substr(0, 11);
			scmd.append(".");
			return (scmd);
		}
		else
			return (cmd);
	}
	return ("Unamed Fighter");
}

bool	askReplay( void ) {
	std::string	cmd;
	bool		ask;
	
	ask = true;
	while (ask) {
		std::cout << BOLD << "\n\t\tWould you like to play again ( y / N )" << BLINK << ": " << RC;
		std::getline(std::cin, cmd);
		if (!cmd.compare("y"))
			return (true);
		else if (!cmd.compare("N"))
			return (false);
		else
			std::cout << RE << "\t\tInvalid answer" << RC << std::endl;
	}
	return (false);
}

Character	*SelectCharacter( void ) {
	std::string	cmd;
	Character	*Player = NULL;
	
	while (!Player) {
		std::cout << BOLD << "\t\tSelect your Class ( SHADOW / BERSERK ) : " << RC;
		std::getline(std::cin, cmd);
		if (!cmd.compare("SHADOW"))
			Player = new Shadow(askName());
		else if (!cmd.compare("BERSERK"))
			Player = new Berserk(askName());
		else
			std::cout << RE << "\t\tInvalid answer" << RC << std::endl;
	}
	return (Player);
}

Character	*SelectAICharacter( Character *Player) {
	Character	*Computer = NULL;
	std::string	PlayerClass(Player->getClassType());

	if (!PlayerClass.compare("Shadow")) {
		Computer = new Berserk("J42VIS");
		std::cout << "BERSERK" << std::endl; 
	}
	else {
		Computer = new Shadow("J42VIS");
		std::cout << "SHADOW" << std::endl; 
	}
	return (Computer);
}

void	Title( void ) {
	std::cout << RE << "\n" << std::endl;
	std::cout << "\t" << " ▄████▄   ██▓    ▄▄▄        ██████   ██████     ▄▄▄▄    ▄▄▄     ▄▄▄█████▓▄▄▄█████▓ ██▓    ▓█████ " << std::endl;
	std::cout << "\t" << "▒██▀ ▀█  ▓██▒   ▒████▄    ▒██    ▒ ▒██    ▒    ▓█████▄ ▒████▄   ▓  ██▒ ▓▒▓  ██▒ ▓▒▓██▒    ▓█   ▀ " << std::endl;
	std::cout << "\t" << "▒▓█    ▄ ▒██░   ▒██  ▀█▄  ░ ▓██▄   ░ ▓██▄      ▒██▒ ▄██▒██  ▀█▄ ▒ ▓██░ ▒░▒ ▓██░ ▒░▒██░    ▒███   " << std::endl;
	std::cout << "\t" << "▒▓▓▄ ▄██▒▒██░   ░██▄▄▄▄██   ▒   ██▒  ▒   ██▒   ▒██░█▀  ░██▄▄▄▄██░ ▓██▓ ░ ░ ▓██▓ ░ ▒██░    ▒▓█  ▄ " << std::endl;
	std::cout << "\t" << "▒ ▓███▀ ░░██████▒▓█   ▓██▒▒██████▒▒▒██████▒▒   ░▓█  ▀█▓ ▓█   ▓██▒ ▒██▒ ░   ▒██▒ ░ ░██████▒░▒████▒" << std::endl;
	std::cout << "\t" << "░ ░▒ ▒  ░░ ▒░▓  ░▒▒   ▓▒█░▒ ▒▓▒ ▒ ░▒ ▒▓▒ ▒ ░   ░▒▓███▀▒ ▒▒   ▓▒█░ ▒ ░░     ▒ ░░   ░ ▒░▓  ░░░ ▒░ ░" << std::endl;
	std::cout << "\t" << "  ░  ▒   ░ ░ ▒  ░ ▒   ▒▒ ░░ ░▒  ░ ░░ ░▒  ░ ░   ▒░▒   ░   ▒   ▒▒ ░   ░        ░    ░ ░ ▒  ░ ░ ░  ░" << std::endl;
	std::cout << "\t" << "░          ░ ░    ░   ▒   ░  ░  ░  ░  ░  ░      ░    ░   ░   ▒    ░        ░        ░ ░      ░   " << std::endl;
	std::cout << "\t" << "░ ░          ░  ░     ░  ░      ░        ░      ░            ░  ░                     ░  ░   ░  ░" << std::endl;
	std::cout << "\t" << "░                                                    ░                                           " << std::endl;
	std::cout << RC << "\n" << std::endl;
}

int	main( void ) {
	bool	Play = true;

	std::srand(time(NULL));
	while (Play) {
		std::system("clear");
		Title();
		std::cout << BOLD << ITAL << UNDRL << "\t\tPlayer Class Selection" << RC << BOLD << ": \n" << RC << std::endl;
		Character	*Player = SelectCharacter();
		if (!Player) {
			std::cout << "\t\tFailed to select Character" << std::endl;
			return 0;
		}
		std::cout << BOLD << ITAL << UNDRL << "\n\t\tComputer Class Selection" << RC << BOLD << ": " << RC;
		Character	*Computer = SelectAICharacter(Player);
		if (!Computer) {
			std::cout << "\t\tFailed to create Computer" << std::endl;
			return 0;
		}
		std::cout << BOLD << "\n\t\tFighters are ready to fight! > " << RC;
		versusBattle(Player, Computer);
		delete Player;
		delete Computer;
		Play = askReplay();
		std::cout << std::endl;
	}
	return 0;
}