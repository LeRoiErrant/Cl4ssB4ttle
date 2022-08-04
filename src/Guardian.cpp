#include "../includes/Guardian.hpp"

Guardian::Guardian( void ) {
}

Guardian::Guardian( Guardian const & src ) {
	*this = src;
}

Guardian::~Guardian( void ) {
}

Guardian	&Guardian::operator=( Guardian const & src ) {
	return (*this);
}

void	Guardian::setGateKeeper( bool const value ) {
	this->_GateKeeper = value;
}

bool	Guardian::getGateKeeper( void ) const {
	return (this->_GateKeeper);
}

void	Guardian::setAbsorbed( unsignedint const value ) {
	this->_Absorbed = value;
}

unsignedint	Guardian::getAbsorbed( void ) const {
	return (this->_Absorbed);
}

void	Guardian::setShieldCapacity( unsignedint const value ) {
	this->_ShieldCapacity = value;
}

unsignedint	Guardian::getShieldCapacity( void ) const {
	return (this->_ShieldCapacity);
}

void	Guardian::setPeaceAura( int const value ) {
	this->_PeaceAura = value;
}

int	Guardian::getPeaceAura( void ) const {
	return (this->_PeaceAura);
}

