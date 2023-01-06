#include "../includes/Berserk.hpp"

Berserk::Berserk( void ) : Character("Unamed Fighter"), _Rage(false), _RD(2), _RageDamage(0) {
	}

Berserk::Berserk( std::string const name) : Character(name), _Rage(false), _RD(2), _RageDamage(0) {
	this->_HitPoints = Berserk::__HitPoints;
	this->_MaxHP = Berserk::__HitPoints;
	this->_Stamina = Berserk::__Stamina;
	this->_MaxStam = Berserk::__Stamina;
	this->_AttackDamage = Berserk::__AttackDamage;
	this->TakeTurn[PLAYER] = &Berserk::BersPlayerTurn;
	this->TakeTurn[COMPUTER] = &Berserk::BersComputerTurn;
	this->Actions[SPECIAL] = "HEADBUTT";
}

Berserk::Berserk( Berserk const & src ) : Character(src), _Rage(false), _RD(2), _RageDamage(2) {
	this->_MaxHP = Berserk::__HitPoints;
	this->_MaxStam = Berserk::__Stamina;
	this->Actions[SPECIAL] = "HEADBUTT";
}

Berserk::~Berserk( void ) {
	this->_Rage = false;
	this->_RD = 2;
	this->_RageDamage = 0;
	this->TakeTurn[PLAYER] = NULL;
	this->TakeTurn[COMPUTER] = NULL;
	this->Actions[SPECIAL].clear(); 
}

Berserk	&Berserk::operator=( Berserk const & src ) {
	this->_Name = src.getName();
	this->_HitPoints = src.getHitPoints();
	this->_MaxHP = Berserk::__HitPoints;
	this->_Stamina = src.getStamina();
	this->_MaxStam = Berserk::__Stamina;
	this->_AttackDamage = src.getAttackDamage();
	this->_Dodge = src.getDodge();
	this->_Bleed = src.getBleed();
	this->_Peace = src.getPeace();
	return (*this);
}

void	Berserk::setRage( bool const value ) {
	this->_Rage = value;
}

bool	Berserk::getRage( void ) const {
	return (this->_Rage);
}

void	Berserk::setRD( unsigned int const value ) {
	this->_RD = value;
}

unsigned int	Berserk::getRD( void ) const {
	return (this->_RD);
}

void	Berserk::BersComputerTurn( Character *Player ) {
	int	healChance = 0;
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
				this->Heal((std::rand() % 4) + (std::rand() % 4) + 3);
			else
				this->attack(Player->getName());
			break;
		case REST:
			this->Resting();
			break;
		case SPECIAL:
			this->headbutt(Player->getName());
			break;
		case DODGE:
			this->Dodging();
			break;
		default:
			percent = std::rand() % 100;
			if (this->_HitPoints < (this->_MaxHP / 4))
				healChance = 33;
			if (percent < healChance)
				this->Heal((std::rand() % 4) + (std::rand() % 4) + 3);
			else 
				this->attack(Player->getName());
			break;
	}
}

std::string	Berserk::askAction( void ) {
	return ("Please select action ( ATTACK / HEAL / REST / DODGE / HEADBUTT ): ");
}

void	Berserk::BersPlayerTurn( Character *Computer ) {
	switch (PlayerAction()) {
		case HEAL:
			this->Heal((std::rand() % 4) + (std::rand() % 4) + 3);
			break;
		case REST:
			this->Resting();
			break;
		case DODGE:
			this->Dodging();
			break;
		case SPECIAL:
			this->headbutt(Computer->getName());
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

std::string	Berserk::DamageReduction(unsigned int & Damages) {
	unsigned int		Old = Damages;
	std::stringstream	ss;

	ss.str(std::string());
	if (Damages < this->_RD)
		Damages = 0;
	else
		Damages -= this->_RD;
	ss << this->getLog() << DR << *this << "'s Hard Skin reduced Damages from " << Old << " to " << Damages << RC << std::endl;
	return (ss.str());
}

void		Berserk::takeDamage(unsigned int const amount) {
	std::stringstream	ss;
	unsigned int		Damages = amount;

	ss.str(std::string());
	if (!this->_HitPoints)
		ss << RE << *this << " has already been killed!" << RC << std::endl;
	else if (this->_hasDodged)
		ss << BL << *this << " DODGE the attack and took no Damage!" << RC << std::endl;
	else {
		std::cout << this->DamageReduction(Damages);
		if (Damages == 0)
			ss << YE << *this << " was attacked but took no Damage!" << RC << std::endl;
		else {
			if (this->_HitPoints >= Damages)
				this->_HitPoints -= Damages;
			else
				this->_HitPoints = 0;
			if (!this->_HitPoints)
				ss << RE << "Final blow! " << *this << " took " << Damages << " Damages and has no HP left!" << RC << std::endl;
			else {
				ss << YE << "Ouch! " << *this << " took " << Damages << " Damages! " << *this << " got " << this->_HitPoints << " HP left!" << RC << std::endl;
			}
		}
	}
	if (!this->_HitPoints)
		this->_Stamina = 0;
	std::cout << this->getLog() << ss.str();
	if (this->_HitPoints < (this->_MaxHP / 2))
		this->enrage();
	this->_hasDodged = false;
}

void	Berserk::CheckRage( void ) {
	if (this->_HitPoints and this->_HitPoints <= (Berserk::__HitPoints / 2) and !this->_Rage)
		this->enrage();
	else if (this->_HitPoints and this->_HitPoints > (Berserk::__HitPoints / 2) and this->_Rage)
		this->calmDown();
}

void	Berserk::enrage( void ) {
	if (!this->_Rage) {
		this->_Rage = true;
		this->_RD *= 2;
		this->_RageDamage = 3;
		std::cout << this->getLog() << DR << *this << " begin to " << RE << "RAGE" << RC <<std::endl;
	}
}

void	Berserk::calmDown( void ) {
	if (this->_Rage) {
		this->_Rage = false;
		this->_RD /= 2;
		this->_RageDamage = 0;
		std::cout << this->getLog() << DR << *this << " calmed down..." << RC << std::endl;
	}
}

void Berserk::attack(std::string const target) {
	Character		*Char;
	unsigned int	Damages = (1 + std::rand() % this->_AttackDamage) + this->_RageDamage;
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
			std::cout << RE << *this << " pounce on " << target << " with his axe for " << Damages << " Damages!" << RC << std::endl;
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


void	Berserk::NewTurn( int Fighter, Character *Opponent ) {
	this->CheckRage();
	if (this->_Dodging)
		this->_Dodge -= 20;
	if (!this->checkPeace(Opponent))
		(this->*TakeTurn[Fighter])(Opponent);
	this->Bleeding();
	this->CheckRage();
}

void	Berserk::headbutt( std::string const target) {
	Character			*Char;
	unsigned int		Damages[2];
	unsigned int		Exhaust = (1 + std::rand() % 8) + this->_RageDamage;
	bool				attack = false;
	
	Damages[OPPONENT] = (1 + std::rand() % 4);
	Damages[FIGHTER] = (1 + std::rand() % 4);
	if (this->_HitPoints and this->_Stamina) {
		this->_Stamina--;
		attack = true;
	}
	if (attack) {
		Char = Character::FirstChar;
		while (Char and target.compare(Char->getName()))
			Char = Char->Next;
		if (Char) {
			this->_HitPoints -= Damages[FIGHTER];
			if (!Char->tryDodge()) {
				if (Char->getStamina() >= Exhaust)
					Char->setStamina(Char->getStamina() - Exhaust);
				else
					Char->setStamina(0);
			}
			std::cout << this->getLog() << RE << *this << " try to HEADBUTT " << target << "\n\t\t\t\t\t" << *this << " loose " << Damages[FIGHTER] << " HP\n\t\t\t\t\tand attack " << target << " for " << Damages[OPPONENT] << " Damages and " << Exhaust << " Stamina Loss" << RC << std::endl;
			Char->takeDamage(Damages[OPPONENT]);
			if (Char->getCounter()) {
				Char->attack(this->getName());
				Char->setCounter(false);
			}
		}
		else {
			std::cout << this->getLog() << YE << "No Target named " << target << " on the Battlefield. The attack failed !" << RC << std::endl;
		}
	}
	else {
		if (!this->_HitPoints)
			std::cout << this->getLog() << RE << *this << " has been killed..." << RC << std::endl;
		else
			std::cout << this->getLog() << CY << *this << " has no Stamina left and can't move anymore..." << RC << std::endl;
	}
}

std::string	Berserk::getLog( void ) {
	std::stringstream	ss;

	ss.str(std::string());
	ss << BOLD << "\t[ ";
	if (this->_Rage)
		ss << RE;
	ss << "B-" << std::setw(12) << std::left << *this << RE << " " << std::setw(3) << std::right << this->_HitPoints << "  " << CY << std::setw(3) << std::right << this->_Stamina << RC << BOLD << " ]\t" << RC;
	return (ss.str());
}

std::string	Berserk::getClassType( void ) {
	return ("Berserk");
}
