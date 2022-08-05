#include "../includes/Guardian.hpp"

Guardian::Guardian( void ) : Character("Unamed Fighter"), _GateKeeper(false), _Absorbed(0) {
	this->_HitPoints = Guardian::__HitPoints;
	this->_MaxHP = Guardian::__HitPoints;
	this->_Stamina = Guardian::__Stamina;
	this->_MaxStam = Guardian::__Stamina;
	this->_AttackDamage = Guardian::__AttackDamage;
	this->TakeTurn[PLAYER] = &Guardian::GuardPlayerTurn;
	this->TakeTurn[COMPUTER] = &Guardian::GuardComputerTurn;
	this->Actions[SPECIAL] = "GUARD";
}

Guardian::Guardian( std::string name) : Character(name), _GateKeeper(false), _Absorbed(0) {
	this->_HitPoints = Guardian::__HitPoints;
	this->_MaxHP = Guardian::__HitPoints;
	this->_Stamina = Guardian::__Stamina;
	this->_MaxStam = Guardian::__Stamina;
	this->_AttackDamage = Guardian::__AttackDamage;
	this->TakeTurn[PLAYER] = &Guardian::GuardPlayerTurn;
	this->TakeTurn[COMPUTER] = &Guardian::GuardComputerTurn;
	this->Actions[SPECIAL] = "GUARD";
}

Guardian::Guardian( Guardian const & src ) : Character(src), _GateKeeper(false), _Absorbed(0) {
	this->_MaxHP = Guardian::__HitPoints;
	this->_MaxStam = Guardian::__Stamina;
	this->Actions[SPECIAL] = "GUARD";
}

Guardian::~Guardian( void ) {
	this->_GateKeeper = false;
	this->_Absorbed = 0;
	this->TakeTurn[PLAYER] = NULL;
	this->TakeTurn[COMPUTER] = NULL;
	this->Actions[SPECIAL].clear();
}

Guardian	&Guardian::operator=( Guardian const & src ) {
	this->_Name = src.getName();
	this->_HitPoints = src.getHitPoints();
	this->_Stamina = src.getStamina();
	this->_AttackDamage = src.getAttackDamage();
	this->_Dodge = src.getDodge();
	this->_Bleed = src.getBleed();
	this->_Peace = src.getPeace();
	return (*this);
}

void	Guardian::setGateKeeper( bool const value ) {
	this->_GateKeeper = value;
}

bool	Guardian::getGateKeeper( void ) const {
	return (this->_GateKeeper);
}

void	Guardian::setAbsorbed( unsigned int const value ) {
	this->_Absorbed = value;
}

unsigned int	Guardian::getAbsorbed( void ) const {
	return (this->_Absorbed);
}

void	Guardian::absorbDamage( unsigned int amount ) {
	unsigned int		absorbed(0);
	unsigned int		damage(0);
	std::stringstream	ss;
	
	ss.str(std::string());
	amount /= 2;
	if (!amount)
		amount = 1;
	if ( this->_Absorbed + amount <= Guardian::__ShieldCapacity and this->_Stamina >= amount ) {
		this->_Stamina -= amount;
		this->_Absorbed += amount;
		ss << CY << *this << "'s Shield absorbed " << amount << " Damages." << RC << std::endl;
		if (this->_Absorbed == Guardian::__ShieldCapacity) {		
			ss << CY << "\t\t\t\t\tMaximum Shield Capacity reached." << RC << std::endl;
			this->_GateKeeper = false;
			this->_Absorbed = 0;
		}
		else if (!this->_Stamina) {
			ss << CY << "\t\t\t\t\t" << *this << " has no Stamina left." << RC << std::endl;
			this->_GateKeeper = false;
			this->_Absorbed = 0;
		}
	}
	else if ( this->_Absorbed + amount > Guardian::__ShieldCapacity and (Guardian::__ShieldCapacity - this->_Absorbed) <= this->_Stamina) {
		absorbed = Guardian::__ShieldCapacity - this->_Absorbed;
		damage = amount - absorbed;
		this->_Stamina -= absorbed;
		ss << CY << "Maximum Shield Capacity exceeded.\n\t\t\t\t\t" << absorbed << " Damages absorbed and " << damage << " Damages pierced." << RC << std::endl;
		this->_GateKeeper = false;
		this->_Absorbed = 0;
	}
	else if ((Guardian::__ShieldCapacity - this->_Absorbed) > this->_Stamina) {
		absorbed = this->_Stamina;
		damage = amount - absorbed;
		this->_Stamina = 0;
		ss << CY << "No more Stamina to withstand Damages. " << absorbed << " Damges absorbed and " << damage << " Damages pierced." << RC << std::endl;
		this->_GateKeeper = false;
		this->_Absorbed = 0;
	}
	if (!this->_GateKeeper)
		ss << CY << "\t\t\t\t\t" << *this << " is not FIGHTING DEFENSIVELY anymore" << RC << std::endl;
	else
		ss << CY << "\t\t\t\t\tShield capacity left: " << (Guardian::__ShieldCapacity - this->_Absorbed) << RC << std::endl;
	std::cout << this->getLog() << ss.str();
	if (damage)
		this->takeDamage(damage);
}

void	Guardian::takeDamage(unsigned int amount) {
	std::stringstream	ss;
	bool				shield = this->_GateKeeper;

	ss.str(std::string());
	if (!this->_HitPoints)
		ss << RE << *this << " has already been killed!" << RC << std::endl;

	else if (this->_hasDodged)
		ss << BL << *this << " DODGE the attack and took no Damage!" << RC << std::endl;
	else if (this->_GateKeeper)
		absorbDamage(amount);
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
			}
		}
	}
	if (!this->_HitPoints)
		this->_Stamina = 0;
	if (!shield or this->_hasDodged)
		std::cout << this->getLog() << ss.str();
	if ((std::rand() % 100) < Guardian::__PeaceAura) {
		std::cout << this->getLog() << CY << *this << "'s Peaceful Aura benumb his Opponent" << RC << std::endl;
		this->_Peace = true;
	}
	if (shield and (std::rand() % 100) < Guardian::__Counter) {
		std::cout << this->getLog() << RE << *this << " counter attack!" << RC << std::endl;
		this->_Counter = true;
		this->_AttackDamage = 12;
		this->_Stamina++;
	}
	this->_hasDodged = false;
}

void	Guardian::guardGate( void ) {
	std::stringstream	ss;
	
	ss.str(std::string());
	if (!this->_Stamina)
		ss << CY << "No Stamina left." << *this << "cannot FIGHT DEFENSIVELY" << RC << std::endl;
	else if (!this->_GateKeeper) {
		ss<< CY << *this << " is FIGHTING DEFENSIVELY" << RC << std::endl;
		this->_GateKeeper = true;
		this->_Absorbed = 0;
	}
	else
		ss << CY << *this << " is already FIGHTING DEFENSIVELY\n\t\t\t\t\tShield Capacity left: " << Guardian::__ShieldCapacity - this->_Absorbed << RC << std::endl;
	std::cout << this->getLog() << ss.str();
}

void Guardian::attack(std::string const target) {
	Character		*Char;
	unsigned int	Damages = 2 + (std::rand() % this->_AttackDamage) + (std::rand() % this->_AttackDamage);
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
			std::cout << RE << *this << " slam " << target << " with his shield for " << Damages << " Damages!" << RC << std::endl;
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

void	Guardian::NewTurn( int Fighter, Character *Opponent ) {
	if (this->_AttackDamage != Guardian::__AttackDamage)
		this->_AttackDamage = Guardian::__AttackDamage;
	if (this->_Dodging)
		this->_Dodge -= 20;
	if (!this->checkPeace(Opponent))
		(this->*TakeTurn[Fighter])(Opponent);
	this->Bleeding();
}

std::string	Guardian::getLog( void ) {
	std::stringstream	ss;

	ss.str(std::string());
	ss << BOLD << "\t[ ";
	if (this->_GateKeeper)
		ss << CY;
	ss << "G-" << std::setw(12) << std::left << *this << RE << " " << std::setw(3) << std::right << this->_HitPoints << "  " << CY << std::setw(3) << std::right << this->_Stamina << RC << BOLD << " ]\t" << RC;
	return (ss.str());
}

std::string	Guardian::getClassType( void ) {
	return ("Guardian");
}

void	Guardian::GuardComputerTurn( Character *Player ) {
	int	healChance = 0;
	int	guardChance = 33;
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
			this->guardGate();
			break;
		case DODGE:
			this->Dodging();
			break;
		default:
			percent = std::rand() % 100;
			if (this->_HitPoints < (this->_MaxHP / 2))
				healChance = 33;
			if (percent < healChance)
				this->Heal((std::rand() % 4) + (std::rand() % 4) + 3);
			else if (percent < (healChance + guardChance) and !this->_GateKeeper)
				this->guardGate();
			else 
				this->attack(Player->getName());
			break;
	}
}

std::string	Guardian::askAction( void ) {
	return ("Please select action ( ATTACK / HEAL / REST / DODGE / GUARD ): ");
}

void	Guardian::GuardPlayerTurn( Character *Computer ) {
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
			this->guardGate();
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
