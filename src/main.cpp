#include "../includes/Character.hpp"
#include "../includes/Shadow.hpp"
#include "../includes/Berserk.hpp"
#include "../includes/Guardian.hpp"

void	YouWon( void ) {
	std::cout << std::endl;
	std::cout << "\t\t\t" << GR << "██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗ ██████╗ ███╗   ██╗██╗" << RC << std::endl;
	std::cout << "\t\t\t" << GR << "╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██╔═══██╗████╗  ██║██║" << RC << std::endl;
	std::cout << "\t\t\t" << GR << " ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║   ██║██╔██╗ ██║██║" << RC << std::endl;
	std::cout << "\t\t\t" << GR << "  ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║   ██║██║╚██╗██║╚═╝" << RC << std::endl;
	std::cout << "\t\t\t" << GR << "   ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝╚██████╔╝██║ ╚████║██╗" << RC << std::endl;
	std::cout << "\t\t\t" << GR << "   ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝" << RC << std::endl;
	std::cout << std::endl;
}

void	Winner ( void ) {
	std::cout << std::endl;
	std::cout << "\t\t\t     " << GR << " ██╗    ██╗██╗███╗   ██╗███╗   ██╗███████╗██████╗ ██╗" << RC << std::endl;
	std::cout << "\t\t\t     " << GR << " ██║    ██║██║████╗  ██║████╗  ██║██╔════╝██╔══██╗██║" << RC << std::endl;
	std::cout << "\t\t\t     " << GR << " ██║ █╗ ██║██║██╔██╗ ██║██╔██╗ ██║█████╗  ██████╔╝██║" << RC << std::endl;
	std::cout << "\t\t\t     " << GR << " ██║███╗██║██║██║╚██╗██║██║╚██╗██║██╔══╝  ██╔══██╗╚═╝" << RC << std::endl;
	std::cout << "\t\t\t     " << GR << " ╚███╔███╔╝██║██║ ╚████║██║ ╚████║███████╗██║  ██║██╗" << RC << std::endl;
 	std::cout << "\t\t\t     " << GR << "  ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚═╝ " << RC << std::endl;
	std::cout << std::endl;
}

void	Looser ( void ) {
	std::cout << std::endl;
	std::cout << "\t\t\t     " << RE << "██╗      ██████╗  ██████╗ ███████╗███████╗██████╗ ██╗" << RC << std::endl;
	std::cout << "\t\t\t     " << RE << "██║     ██╔═══██╗██╔═══██╗██╔════╝██╔════╝██╔══██╗██║" << RC << std::endl;
	std::cout << "\t\t\t     " << RE << "██║     ██║   ██║██║   ██║███████╗█████╗  ██████╔╝██║" << RC << std::endl;
	std::cout << "\t\t\t     " << RE << "██║     ██║   ██║██║   ██║╚════██║██╔══╝  ██╔══██╗╚═╝" << RC << std::endl;
	std::cout << "\t\t\t     " << RE << "███████╗╚██████╔╝╚██████╔╝███████║███████╗██║  ██║██╗" << RC << std::endl;
	std::cout << "\t\t\t     " << RE << "╚══════╝ ╚═════╝  ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝╚═╝" << RC << std::endl;
	std::cout << std::endl;
}

void	ItsaDraw( void ) {
	std::cout << std::endl;
	std::cout << "\t\t   " << YE << "██╗████████╗███████╗     █████╗     ██████╗ ██████╗  █████╗ ██╗    ██╗██╗" << RC << std::endl;
	std::cout << "\t\t   " << YE << "██║╚══██╔══╝██╔════╝    ██╔══██╗    ██╔══██╗██╔══██╗██╔══██╗██║    ██║██║" << RC << std::endl;
	std::cout << "\t\t   " << YE << "██║   ██║   ███████╗    ███████║    ██║  ██║██████╔╝███████║██║ █╗ ██║██║" << RC << std::endl;
	std::cout << "\t\t   " << YE << "██║   ██║   ╚════██║    ██╔══██║    ██║  ██║██╔══██╗██╔══██║██║███╗██║╚═╝" << RC << std::endl;
	std::cout << "\t\t   " << YE << "██║   ██║   ███████║    ██║  ██║    ██████╔╝██║  ██║██║  ██║╚███╔███╔╝██╗" << RC << std::endl;
	std::cout << "\t\t   " << YE << "╚═╝   ╚═╝   ╚══════╝    ╚═╝  ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝ ╚══╝╚══╝ ╚═╝" << RC << std::endl;
	std::cout << std::endl;
}

void	versusBattle( Character *Player, Character *Computer ) {
	bool		StaminaLeft;
	bool		KnockOut;
	int			Turn;

	StaminaLeft = Player->getStamina() or Computer->getStamina();
	KnockOut = !Player->getHitPoints() or !Computer->getHitPoints();
	Turn = (std::rand() % 2);
	if (Turn == COMPUTER)
		std::cout << BOLD << ITAL << "Computer " << *Computer << " goes First\n" << RC << std::endl;
	else
		std::cout << BOLD << ITAL << "Player " << *Player << " goes First" << RC << std::endl;
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
	/*if (KnockOut) {
		if (!Player->getHitPoints() and !Computer->getHitPoints())
			std::cout << MA << "\n\t\tIT'S A DRAW! Both Fighters are knocked out!" << RC <<std::endl;
		if (!Player->getHitPoints())
			std::cout << MA << "\n\t\tWE HAVE A WINNER! " << Computer->getName() << " knockned out " << Player->getName() << "!" << RC << std::endl; 
		else
			std::cout << MA << "\n\t\tWE HAVE A WINNER! " << Player->getName() << " knockned out " << Computer->getName() << "!" << RC << std::endl;
	}
	else
		std::cout << MA << "\n\t\tIT'S A DRAW! Both Fighters have no Energy left!" << RC <<std::endl;
*/
	if (KnockOut) {
		if (!Player->getHitPoints() and !Computer->getHitPoints())
			ItsaDraw();
		if (!Player->getHitPoints())
			Looser();
		else
			Winner();
	}
	else
		ItsaDraw();
}

std::string	askName( void ) {
	std::string	cmd;
	std::string	scmd;
	bool		ask;
	
	ask = true;
	while (ask and !std::cin.eof()) {
		std::cout << BOLD << "\t\tPlease enter your Fighter's Name: " << RC;
		std::getline(std::cin, cmd);
		if (std::cin.eof()) {
			std::cout << std::endl;
			std::exit(0) ;
		}
		if (!cmd.length() and !std::cin.eof()) {
			std::cout << RE << "\t\tEmpty name not allowed" << RC << std::endl;
		}
		else if (cmd.length() > 12) {
			scmd = cmd.substr(0, 11);
			scmd.append(".");
			return (scmd);
		}
		else if(std::cin.eof())
			return("Unamed");
		else
			return (cmd);
	}
	return ("Unamed Fighter");
}

/*bool	askReplay( void ) {
	std::string	cmd;
	bool		ask;
	
	ask = true;
	while (ask) {
		std::cout << BOLD << "\n\t\t\t\t    Would you like to play again ( y / N )" << BLINK << ": " << RC;
		std::getline(std::cin, cmd);
		if (std::cin.eof()) {
			std::cout << std::endl;
			std::exit(0) ;
		}
		if (!cmd.compare("y"))
			return (true);
		else if (!cmd.compare("N") or std::cin.eof())
			return (false);
		else
			std::cout << RE << "\t\tInvalid answer" << RC << std::endl;
	}
	return (false);
}*/

bool	askReplay( void ) {
	std::string	cmd;
	bool		ask;
	
	ask = true;
	while (ask) {
		std::cout << BOLD << "\n\t\t\t\t\t" << BLINK << "< Press ENTER to play again > \n" << RC << HDDN;
		std::getline(std::cin, cmd);
		std::cout << RC << std::endl;
		if (std::cin.eof()) {
			std::cout << std::endl;
			std::exit(0) ;
		}
		else if (!cmd.compare("EXIT42"))
			return (false);
		else
			return (true);
	}
	return (false);
}

void	CharacterClassInfo( void ) {
	std::cout << "\t\t" << BOLD << UNDRL << " " << std::setw(15) << "CHARACTER CLASS" << " | " << std::setw(10) << "Hit Points" << " | " << std::setw(6) << "ATTACK" << " | " << std::setw(8) << "ACTIVE" << " | " << std::setw(12) << "PASSIVE(1)" << " | " << std::setw(15) << "PASSIVE(2)" << " " << RC << std::endl;
	std::cout << "\t\t " << BOLD << std::setw(5) << "1." << DGB << std::setw(10) << "SHADOW" << WH << " | " << std::setw(10) << "40" << " | " << std::setw(6) << "D4" << " | " << std::setw(8) << "HIDE" << " | " << std::setw(12) << "SNEAK ATTACK" << " | " << std::setw(15) << "BLEEDING STRIKE" << std::endl;
	std::cout << "\t\t " << BOLD << std::setw(5) << "2." << RE << std::setw(10) << "BERSERK" << WH << " | " << std::setw(10) << "60" << " | " << std::setw(6) << "D12" << " | " << std::setw(8) << "HEADBUTT" << " | " << std::setw(12) << "RAGE" << " | " << std::setw(15) << "THICK SKIN" << std::endl;
	std::cout << "\t\t " << BOLD << std::setw(5) << "3." << CY << std::setw(10) << "GUARDIAN" << WH << " | " << std::setw(10) << "50" << " | " << std::setw(6) << "D8" << " | " << std::setw(8) << "GUARD" << " | " << std::setw(12) << "COUNTER" << " | " << std::setw(15) << "PEACEFUL AURA" << std::endl;
	std::cout << std::endl;
}

/*void	CharacterClassInfo( void ) {
	std::cout << BOLD << "\t\t| " << DGB << std::setw(15) <<  "SHADOW    " << WH << " | " << RE << std::setw(15) << "BERSERK    " << WH << " | " << CY << std::setw(15) << "GUARDIAN   " << WH << " |" << std::endl;
	std::cout << "\t\t| " << std::setw(15) << "_______________" << " | " << std::setw(15) << "_______________" << " | " << std::setw(15) << "_______________" << " |" << std::endl;
	std::cout << "\t\t| " << std::setw(15) << " " << " | " << std::setw(15) << " " << " | " << std::setw(15) << " " << " |" << std::endl;
	std::cout << "\t\t| " << std::setw(15) << "HP: 40    " << " | " << std::setw(15) << "HP: 60    " << " | " << std::setw(15) << "HP: 50    " << " |" << std::endl;
	std::cout << "\t\t| " << std::setw(15) << "ATTACK: D4  " << " | " << std::setw(15) << "ATTACK: D12  " << " | " << std::setw(15) << "ATTACK: D8  " << " |" << std::endl;
	std::cout << "\t\t| " << std::setw(15) << "SNEAK ATTACK " << " | " << std::setw(15) << "RAGE     " << " | " << std::setw(15) << "COUNTER    " << " |" << std::endl;
	std::cout << "\t\t| " << std::setw(15) << "BLEEDING STRIKE" << " | " << std::setw(15) << "THICK SKIN  " << " | " << std::setw(15) << "PEACEFUL AURA " << " |" << std::endl;
	std::cout << "\t\t| " << std::setw(15) << "HIDE     " << " | " << std::setw(15) << "HEADBUTT   " << " | " << std::setw(15) << "GUARD     " << " |\n" << std::endl;
}*/

Character	*SelectCharacter( void ) {
	std::string	cmd;
	Character	*Player = NULL;
	
	CharacterClassInfo();
	while (!Player and !std::cin.eof()) {
		std::cout << BOLD << "\t\tSelect your Class: " << RC;
		std::getline(std::cin, cmd);
		if (std::cin.eof()) {
			std::cout << std::endl;
			std::exit(0) ;
		}
		else if (!cmd.compare("SHADOW") or !cmd.compare("1"))
			Player = new Shadow(askName());
		else if (!cmd.compare("BERSERK") or !cmd.compare("2"))
			Player = new Berserk(askName());
		else if (!cmd.compare("GUARDIAN") or !cmd.compare("3"))
			Player = new Guardian(askName());
		else
			std::cout << RE << "\t\tInvalid answer" << RC << std::endl;
	}
	return (Player);
}

std::string	SelectAIName( void ) {
	switch (std::rand() % 4) {
		case 1:
			return("HAL-9000");
		case 2:
			return ("AGENT SMITH");
		case 3:
			return ("ROY BATTY");
		default:
			return ("J.A.R.V.I.S.");
	}
}

std::string toUppercase(std::string str) {
	std::string	ret(str);

	for (size_t i = 0; i < ret.length(); i++) {
		ret[i] = std::toupper(ret[i]);
	}
	return (ret);
}

Character	*SelectAICharacter( Character *Player) {
	Character	*Computer = NULL;
	std::string	PlayerClass(Player->getClassType());

	if (!PlayerClass.compare("Shadow")) {
		if (std::rand() % 2)
			Computer = new Berserk(SelectAIName()); 
		else
			Computer = new Guardian(SelectAIName());
	}
	else if (!PlayerClass.compare("Berserk")) {
		if (std::rand() % 2)
			Computer = new Shadow(SelectAIName()); 
		else
			Computer = new Guardian(SelectAIName());
	}
	else {
		if (std::rand() % 2)
			Computer = new Berserk(SelectAIName()); 
		else
			Computer = new Shadow(SelectAIName());
	}
	if (Computer)
		std::cout << BOLD << "\n\n\t\tComputer " << *Computer << " selected the Class: " << toUppercase(Computer->getClassType()) << std::endl;  
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