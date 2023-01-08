#ifndef GUARDIAN_HPP
# define GUARDIAN_HPP

# include "Character.hpp"

class Guardian : public Character {
	private:
		Guardian( void );
		
		void			(Guardian::*TakeTurn[2])( Character *Opponent );

		bool			_GateKeeper;
		unsigned int	_Absorbed;

		static const unsigned int	__HitPoints = 25;
		static const unsigned int	__Stamina = 20;
		static const unsigned int	__AttackDamage = 6;
		static const int			__Dodge = 5;
		static const unsigned int	__ShieldCapacity = 10;
		static const int			__PeaceAura = 10;
		static const int			__Counter = 33;

	public:
		Guardian( std::string name);
		Guardian( Guardian const & src );
		~Guardian( void );

		Guardian	&operator=( Guardian const & src );

		void			setGateKeeper( bool const value );
		void			setAbsorbed( unsigned int const value );
		void			setShieldCapacity( unsigned int const value );
		void			setPeaceAura( int const value );

		bool			getGateKeeper( void ) const;
		unsigned int	getAbsorbed( void ) const;
		unsigned int	getShieldCapacity( void ) const;
		int				getPeaceAura( void ) const;

		void			attack( std::string const target );
		virtual void	takeDamage( unsigned int const amount );
		void			absorbDamage( unsigned int amount );
		void			guardGate( void );

		virtual	void		NewTurn( int Fighter, Character *Opponent);
		virtual std::string	askAction( void );

		void	GuardPlayerTurn( Character *Computer );
		void	GuardComputerTurn( Character *Player );
		
		virtual std::string	getLog( void );
		virtual std::string	getClassType( void );
};

#endif
