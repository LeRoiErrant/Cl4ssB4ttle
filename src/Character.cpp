#include "../includes/Character.hpp"

Character *Character::FirstChar = NULL;
Character *Character::LastChar = NULL;

Character::Character( void ) : _Name("Unamed Hero"), _HitPoints(__HitPoints), _MaxHP(__HitPoints), _Stamina(__Stamina), _MaxStam(__Stamina), _AttackDamage(__AttackDamage), _Dodge(__Dodge), _Dodging(false), _Bleed(0), _Peace(false), _Counter(false) {
	if (!Character::FirstChar) {
		Character::FirstChar = this;
		Character::LastChar = this;
		this->Previous = NULL;
		this->Next = NULL;
	}
	else {
		Character::LastChar->Next = this;
		this->Previous = Character::LastChar;
		Character::LastChar = this;
	}
	this->Actions[ATTACK] = "ATTACK";
	this->Actions[HEAL] = "HEAL";
	this->Actions[REST] = "REST";
	this->Actions[DODGE] = "DODGE";
	this->Actions[SPECIAL] = "EASTER EGG";
	this->Actions[FORFEIT] = "FORFEIT";
	this->TakeTurn[PLAYER] = &Character::CharPlayerTurn;
	this->TakeTurn[COMPUTER] = &Character::CharComputerTurn;
}

Character::Character( std::string name ) : _Name(name), _HitPoints(__HitPoints), _MaxHP(__HitPoints), _Stamina(__Stamina), _MaxStam(__Stamina), _AttackDamage(__AttackDamage), _Dodge(__Dodge), _Dodging(false), _Bleed(0), _Peace(false), _Counter(false) {
	if (!Character::FirstChar) {
		Character::FirstChar = this;
		Character::LastChar = this;
		this->Previous = NULL;
		this->Next = NULL;
	}
	else {
		Character::LastChar->Next = this;
		this->Previous = Character::LastChar;
		Character::LastChar = this;
	}
	this->Actions[ATTACK] = "ATTACK";
	this->Actions[HEAL] = "HEAL";
	this->Actions[REST] = "REST";
	this->Actions[DODGE] = "DODGE";
	this->Actions[SPECIAL] = "EASTER EGG";
	this->Actions[FORFEIT] = "FORFEIT";
	this->TakeTurn[PLAYER] = &Character::CharPlayerTurn;
	this->TakeTurn[COMPUTER] = &Character::CharComputerTurn;
}

Character::Character( Character const & src ) : _Dodging(false), _Bleed(0), _Peace(false), _Counter(false) {
	this->_Name = src.getName();
	this->_HitPoints = src.getHitPoints();
	this->_MaxHP = Character::__HitPoints;
	this->_Stamina = src.getStamina();
	this->_MaxStam = Character::__Stamina;
	this->_AttackDamage = src.getAttackDamage();
	this->_Dodge = src.getDodge();
	this->TakeTurn[PLAYER] = &Character::CharPlayerTurn;
	this->TakeTurn[COMPUTER] = &Character::CharComputerTurn;
	if (!Character::FirstChar) {
		Character::FirstChar = this;
		Character::LastChar = this;
		this->Previous = NULL;
		this->Next = NULL;
	}
	else {
		Character::LastChar->Next = this;
		this->Previous = Character::LastChar;
		Character::LastChar = this;
	}
}

Character::~Character( void ) {
	if (this != Character::FirstChar and this != Character::LastChar) {
		this->Previous->Next = this->Next;
		this->Next->Previous = this->Previous;
	}
	if (this == Character::LastChar) {
		if (this->Previous)
			this->Previous->Next = NULL;
		Character::LastChar = this->Previous;
	}
	if (this == Character::FirstChar) {
		if (this->Next)
			this->Next->Previous = NULL;
		Character::FirstChar = this->Next;
	}
	this->_Name.clear();
	this->_HitPoints = 0;
	this->_MaxHP = 0;
	this->_Stamina = 0;
	this->_MaxStam = 0; 
	this->_AttackDamage = 0;
	this->_Dodge = 0;
	this->_Dodging = false;
	this->_Bleed = 0;
	this->_Peace = false;
	this->_Counter = false;
	this->TakeTurn[PLAYER] = NULL;
	this->TakeTurn[COMPUTER] = NULL;
	this->Actions[ATTACK].clear();
	this->Actions[HEAL].clear();
	this->Actions[REST].clear();
	this->Actions[DODGE].clear();
	this->Actions[SPECIAL].clear();
	this->Actions[FORFEIT].clear();
}

Character	&Character::operator=( Character const & src ) {
	this->_Name = src.getName();
	this->_HitPoints = src.getHitPoints();
	this->_MaxHP = Character::__HitPoints;
	this->_Stamina = src.getStamina();
	this->_MaxStam = Character::__Stamina;
	this->_AttackDamage = src.getAttackDamage();
	return (*this);
}

void	Character::setName( std::string const value ) {
	this->_Name = value;
}

std::string	Character::getName( void ) const {
	return (this->_Name);
}

void	Character::setHitPoints( unsigned int const value ) {
	this->_HitPoints = value;
}

unsigned int	Character::getHitPoints( void ) const {
	return (this->_HitPoints);
}

void	Character::setStamina( unsigned int const value ) {
	this->_Stamina = value;
}

unsigned int	Character::getMaxHP( void ) const {
	return (this->_MaxHP);
}

unsigned int	Character::getStamina( void ) const {
	return (this->_Stamina);
}

void	Character::setAttackDamage( unsigned int const value ) {
	this->_AttackDamage = value;
}

unsigned int	Character::getAttackDamage( void ) const {
	return (this->_AttackDamage);
}

void	Character::setDodge( int const value ) {
	this->_Dodge = value;
}

int	Character::getDodge( void ) const {
	return (this->_Dodge);
}

void	Character::setBleed( unsigned int const value ) {
	this->_Bleed = value;
}

unsigned int	Character::getBleed( void ) const {
	return (this->_Bleed);
}

void	Character::setPeace( bool const value ) {
	this->_Peace = value;
}

bool	Character::getPeace( void ) const {
	return (this->_Peace);
}

void	Character::setCounter( bool const value ) {
	this->_Counter = value;
}

bool	Character::getCounter( void ) const {
	return (this->_Counter);
}

std::ostream	&operator<<( std::ostream & ostream, Character const & src ) {
	ostream << src.getName();
	return (ostream);
}

std::string	Character::getLog( void ) {
	std::stringstream	ss;

	ss.str(std::string());
	ss << "\t[ " << std::setw(12) << std::left << *this << RE << " " << std::setw(3) << std::right << this->_HitPoints << "  " << CY << std::setw(3) << std::right << this->_Stamina << RC << " ]\t";
	return (ss.str());
}

void	Character::Heal( unsigned int const amount ) {
	std::stringstream	ss;
	
	ss.str(std::string());
	if (this->_HitPoints and this->_Stamina) {
		if (this->_HitPoints == this->_MaxHP) {
			ss << GR << *this << " try to HEAL himself for " << amount << " Damages\n\t\t\t\t\tbut already is at his max Health" << RC << std::endl;
		}
		else if (this->_HitPoints + amount >= this->_MaxHP) {
			ss << GR << *this << " HEALED himself for " << amount << " Damages and is back to max Health\n\t\t\t\t\t(Any extra HP is loss)" << RC << std::endl;
			this->_HitPoints = this->_MaxHP;
		}
		else {
			this->_HitPoints += amount;
			ss << GR << *this << " HEALED himself for " << amount << " Damages and has now " << this->_HitPoints << " HP left!" << RC << std::endl;
		}
		if (this->_Bleed)
			this->_Bleed = 0;
		this->_Stamina--;
	}
	else {
		if (!this->_HitPoints)
			ss << RE << *this << " has been killed..." << RC << std::endl;
		else
			ss << CY << *this << " has no Stamina left and can't move anymore..." << RC << std::endl;
	}
	std::cout << this->getLog() << ss.str();
}

void		Character::takeDamage(unsigned int const amount) {
	std::stringstream	ss;

	ss.str(std::string());
	if (!this->_HitPoints)
		ss << RE << *this << " has already been killed!" << RC << std::endl;
	else if (this->_hasDodged)
		ss << BL << *this << " DODGE the attack and took no Damage!" << RC << std::endl;
	else {
		if (amount == 0)
			ss << YE << *this << " was attacked but took no Damage!" << RC << std::endl;
		else {
			if (this->_HitPoints >= amount)
				this->_HitPoints -= amount;
			else
				this->_HitPoints = 0;
			if (!this->_HitPoints)
				ss << RE << "Final blow! " << *this << " took " << amount << " Damages and has no HP left!" << RC << std::endl;
			else
				ss << YE << "Ouch! " << *this << " took " << amount << " Damages! " << *this << " got " << this->_HitPoints << " HP left!" << RC << std::endl;
		}
	}
	if (!this->_HitPoints)
		this->_Stamina = 0;
	std::cout << this->getLog() << ss.str();
	this->_hasDodged = false;
}

void Character::attack(std::string const target) {
	Character		*Char;
	unsigned int	Damages;
	bool			attack = false;
	
	if (this->_HitPoints and this->_Stamina) {
		this->_Stamina--;
		attack = true;
	}
	std::cout << this->getLog();
	if (attack) {
		Char = Character::FirstChar;
		while (Char and target.compare(Char->getName()))
			Char = Char->Next;
		if (Char) {
			Damages = 1 + (std::rand() % this->_AttackDamage);
			std::cout << RE << *this << " slam " << target << " for " << Damages << " Damages!" << RC << std::endl;
			Char->tryDodge();
			Char->takeDamage(Damages);
			if (Char->getCounter()) {
				Char->attack(this->getName());
				Char->setCounter(false);
			}
		}
		else {
			std::cout << YE << "No Target named " << target << " on the Battlefield. The attack failed !" << RC << std::endl;
		}
	}
	else {
		if (!this->_HitPoints)
			std::cout << RE << *this << " has been killed..." << RC << std::endl;
		else
			std::cout << CY << *this << " has no Stamina left and can't move anymore..." << RC << std::endl;
	}
}

void	Character::Bleeding( void ) {
	if (this->_Bleed and this->_HitPoints) {
		if (this->_Bleed <= this->_HitPoints)
			this->_HitPoints -= this->_Bleed;
		else
			this->_HitPoints = 0;
		std::cout << this->getLog() << RE << *this << " is BLEEDING and loss " << this->_Bleed << " HP..." << RC << std::endl;
		if (!this->_HitPoints)
			std::cout << this->getLog() << RE << *this << " BLED to DEATH." << RC << std::endl;
		this->_Bleed++;
	}
}

bool	Character::tryDodge( void ) {
	if ((std::rand() % 100) < this->_Dodge) {
		this->_hasDodged = true;
		return (true);
	}
	else
		return (false);
}

void	Character::Dodging( void ) {
	if (this->_HitPoints and this->_Stamina) {
		this->_Stamina--;
		this->_Dodge += 20;
		this->_Dodging = true;
		std::cout << this->getLog() << BL << *this << " focus on DODGING" << RC << std::endl;
	}
	else {
		if (!this->_HitPoints)
			std::cout << this->getLog() << RE << *this << " has been killed..." << RC << std::endl;
		else
			std::cout << this->getLog() << CY << *this << " has no Stamina left and can't move anymore..." << RC << std::endl;
	}
}

void	Character::Resting( void ) {
	int	amount = 2 + (std::rand() % 6) + (std::rand() % 6);

	if (this->_Stamina + amount > this->_MaxStam)
		amount = this->_MaxStam - this->_Stamina;
	if (this->_HitPoints) {
		this->_Stamina += amount;
		std::cout << getLog() << CY << *this << " REST and regain " << amount << " Stamina" << RC << std::endl;
	}
	else {
		if (!this->_HitPoints)
			std::cout << RE << *this << " has been killed..." << RC << std::endl;
	}
}

void	Character::CharComputerTurn( Character *Player ) {
	int	percent = 0;

	if (!this->_Stamina) {
		this->Resting();
		return;
	}
	switch (std::rand() % 10) {
		case HEAL:
			this->Heal((std::rand() % 4) + 1);
			break;
		case REST:
			this->Resting();
			break;
		case DODGE:
			this->Dodging();
			break;
		default:
			if ( this->_HitPoints < (this->_MaxHP / 2))
				percent = 50;
			if (std::rand() % 100 < percent)
				this->Heal((std::rand() % 4) + 1);
			else 
				this->attack(Player->getName());
			break;
	}
}

std::string	Character::askAction( void ) {
	return ("Please select action ( ATTACK / HEAL / REST / DODGE ): ");
}

int	Character::PlayerAction( void ) {
	std::string	cmd;
	bool		ask;

	ask = true;
	std::cout << std::endl;
	while (ask) {
		std::cout << BOLD << ITAL <<"\t" << this->askAction() << RC;
		std::getline(std::cin, cmd);
		if (std::cin.eof()) {
			std::cout << std::endl;
			std::exit(0) ;
		}
		for (int i = ATTACK; i <= FORFEIT; i++) {
			if (!cmd.compare(this->Actions[i])) {
				std::cout << std::endl;
				return (i);
			}
		}
		if (!cmd.compare("EXIT") or !cmd.compare("GIVE UP") or std::cin.eof())
			return (FORFEIT);
		std::cout << RE << "\t\t\t\t\tInvalid command" << RC << std::endl;
	}

	return (ATTACK);
}

void	Character::CharPlayerTurn( Character *Computer ) {
	switch (PlayerAction()) {
		case HEAL:
			this->Heal((std::rand() % 4) + 1);
			break;
		case REST:
			this->Resting();
			break;
		case DODGE:
			this->Dodging();
			break;
		case FORFEIT:
			this->_HitPoints = 0;
			this->_Stamina = 0;
			std::cout << "\n" << this->getLog() << RE << *this << " forfeit the duel" << RC << std::endl;
			break;
		default:
			this->attack(Computer->getName());
			break;
	}
}

bool	Character::checkPeace( Character *Opponent ) {
	bool			Peaceful = Opponent->getPeace();
	unsigned int	heal;
	unsigned int	rest;

	if (Peaceful) {
		heal = 1 + std::rand() % 4;
		rest = 1 + std::rand() % 4;
		if (this->_HitPoints + heal <= this->_MaxHP)
			this->_HitPoints += heal;
		else
			this->_HitPoints = this->_MaxHP;
		if (this->_Stamina + rest <= this->_MaxStam)
			this->_Stamina += rest;
		else
			this->_Stamina = this->_MaxStam;
		std::cout << this->getLog() << CY << *this << " is feeling peacefull and just want to rest" << std::endl;
		std::cout << "\t\t\t\t\t" << *this << " regain " << heal << " Hit Points and " << rest << " Stamina" << RC << std::endl;
		Opponent->setPeace(false);
	}
	return (Peaceful);
}

void	Character::NewTurn( int Fighter, Character *Opponent ) {
	this->_Dodge = Character::__Dodge;
	if (!this->checkPeace(Opponent))
		(this->*TakeTurn[Fighter])(Opponent);
	this->Bleeding();
}

std::string	Character::getClassType( void ) {
	return ("Commoner");
}