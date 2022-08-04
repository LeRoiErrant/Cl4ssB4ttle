#include "../includes/Shadow.hpp"

Shadow::Shadow( void ) : Character("Unamed Fighter"), _Hiding(false) {
	this->_HitPoints = Shadow::__HitPoints;
	this->_MaxHP = Shadow::__HitPoints;
	this->_Stamina = Shadow::__Stamina;
	this->_MaxStam = Shadow::__Stamina;
	this->_AttackDamage = Shadow::__AttackDamage;
	this->TakeTurn[PLAYER] = &Shadow::ShadPlayerTurn;
	this->TakeTurn[COMPUTER] = &Shadow::ShadComputerTurn;
	this->Actions[SPECIAL] = "HIDE";
}

Shadow::Shadow( std::string name) : Character(name), _Hiding(false) {
	this->_HitPoints = Shadow::__HitPoints;
	this->_MaxHP = Shadow::__HitPoints;
	this->_Stamina = Shadow::__Stamina;
	this->_MaxStam = Shadow::__Stamina;
	this->_AttackDamage = Shadow::__AttackDamage;
	this->TakeTurn[PLAYER] = &Shadow::ShadPlayerTurn;
	this->TakeTurn[COMPUTER] = &Shadow::ShadComputerTurn;
	this->Actions[SPECIAL] = "HIDE";
}

Shadow::Shadow( Shadow const & src ) : Character(src), _Hiding(false) {
	this->_MaxHP = Shadow::__HitPoints;
	this->_MaxStam = Shadow::__Stamina;
	this->Actions[SPECIAL] = "HIDE";
}

Shadow::~Shadow( void ) {
}

Shadow	&Shadow::operator=( Shadow const & src ) {
	this->_Name = src.getName();
	this->_HitPoints = src.getHitPoints();
	this->_MaxHP = Shadow::__HitPoints;
	this->_Stamina = src.getStamina();
	this->_MaxStam = Shadow::__Stamina;
	this->_AttackDamage = src.getAttackDamage();
	this->_Dodge = src.getDodge();
	this->_Bleed = src.getBleed();
	this->_Peace = src.getPeace();
	return (*this);
}

void	Shadow::setHiding( bool const value ) {
	this->_Hiding = value;
}

bool	Shadow::getHiding( void ) const {
	return (this->_Hiding);
}

void	Shadow::ShadComputerTurn( Character *Player ) {
	int	healChance = 0;
	int	hideChance = 33;
	int	percent;
	
	if (!this->_Stamina) {
		this->Resting();
		return;
	}
	switch (std::rand() % 10) {
		case HEAL:
			percent = std::rand() % 100;
			if (this->_HitPoints == this->_MaxHP)
				healChance = 74;
			if (percent > healChance)
				this->Heal((std::rand() % 4) + 1);
			else
				this->attack(Player->getName());
			break;
		case REST:
			this->Resting();
			break;
		case SPECIAL:
			if (this->_Hiding)
				this->attack(Player->getName());
			else
				this->hide();
			break;
		case DODGE:
			this->Dodging();
			break;
		default:
			percent = std::rand() % 100;
			if (this->_HitPoints < (this->_MaxHP / 2))
				healChance = 33;
			if (percent < healChance)
				this->Heal((std::rand() % 4) + 1);
			else if (percent < (healChance + hideChance))
				this->hide();
			else 
				this->attack(Player->getName());
			break;
	}
}

std::string	Shadow::askAction( void ) {
	return ("Please select action ( ATTACK / HEAL / REST / DODGE / HIDE ): ");
}

void	Shadow::ShadPlayerTurn( Character *Computer ) {
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
		case SPECIAL:
			this->hide();
			break;
		case FORFEIT:
			this->_HitPoints = 0;
			this->_Stamina = 0;
			std::cout << this->getLog() << RE << *this << " forfeit the duel" << RC << std::endl;
			break;
		default:
			this->attack(Computer->getName());
			break;
	}
}

void		Shadow::takeDamage(unsigned int const amount) {
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
			else {
				ss << YE << "Ouch! " << *this << " took " << amount << " Damages! " << *this << " got " << this->_HitPoints << " HP left!" << RC << std::endl;
				if (this->_Hiding)
					ss << this->notHiding();
			}
		}
	}
	if (!this->_HitPoints)
		this->_Stamina = 0;
	std::cout << this->getLog() << ss.str();
	this->_hasDodged = false;
}

std::string	Shadow::sneakAttack( unsigned int & Damages, std::string const target) {
	std::stringstream	ss;

	ss.str(std::string());
	if (this->_Hiding) {
		Damages = (std::rand() % this->_AttackDamage) + (std::rand() % 6) + (std::rand() % 6) + 3;
		ss << " strike from the Dark and stab "<< target << " for " << Damages << " Damages!" << RC << std::endl;
		ss << this->notHiding();
	}
	else {
		Damages = (std::rand() % this->_AttackDamage) + 1;
		ss << " stab " << target << " for " << Damages << " Damages!" << RC << std::endl;
	}
	return (ss.str());
}

void Shadow::attack(std::string const target) {
	Character		*Char;
	unsigned int	OppHP;
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
			OppHP = Char->getHitPoints();
			std::cout << RE << *this << this->sneakAttack(Damages, target);
			Char->tryDodge();
			Char->takeDamage(Damages);
				if (Char->getHitPoints() < OppHP)
					Char->setBleed(Char->getBleed() + 1);
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

void	Shadow::hide( void ) {
	this->_Hiding = true;
	this->_Dodge = 66;
	std::cout << getLog() << DG << *this << " is HIDING in the Shadows..." << RC << std::endl;
}

std::string	Shadow::notHiding( void ) {
	std::stringstream	ss;

	ss.str(std::string());
	this->_Hiding = false;
	ss << this->getLog() << LG << *this << " is not hiding anymore" << RC << std::endl;
	this->_Dodge = Shadow::__Dodge;
	return (ss.str());
}

void	Shadow::refreshDodge( void ) {
	if (this->_Dodging)
		this->_Dodge -= 20;
	if (!this->_Hiding)
		this->_Dodge = Shadow::__Dodge;
	else
		if (this->_Dodge > Shadow::__Dodge)
			this->_Dodge -= 15;
	if (this->_Hiding and this->_Dodge <= Shadow::__Dodge + 1)
		std::cout << this->notHiding();
}

void	Shadow::NewTurn( int Fighter, Character *Opponent ) {
	this->refreshDodge();
	(this->*TakeTurn[Fighter])(Opponent);
	this->Bleeding();
}

std::string	Shadow::getLog( void ) {
	std::stringstream	ss;

	ss.str(std::string());
	ss << BOLD << "\t\t[ ";
	if (this->_Hiding)
		ss << DG;
	ss << "S-" << std::setw(12) << std::left << *this << RE << " " << std::setw(3) << std::right << this->_HitPoints << "  " << CY << std::setw(3) << std::right << this->_Stamina << RC << BOLD << " ]\t" << RC;
	return (ss.str());
}

std::string	Shadow::getClassType( void ) {
	return ("Shadow");
}