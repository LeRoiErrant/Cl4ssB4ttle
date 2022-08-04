#ifndef BERSERK_HPP
# define BERSERK_HPP

# include "Character.hpp"

class Berserk : public Character {
	private:
		Berserk( void );
		
		void			(Berserk::*TakeTurn[2])( Character *Opponent );

		bool			_Rage;
		unsigned int	_RD;
		unsigned int	_RageDamage;

		static const unsigned int	__HitPoints = 60;
		static const unsigned int	__Stamina = 20;
		static const unsigned int	__AttackDamage = 12;
		static const int			__Dodge = 5;
	public:

		Berserk(std::string const name);
		Berserk( Berserk const & src );
		virtual ~Berserk( void );

		Berserk	&operator=( Berserk const & src );

		void		setRage( bool const value );
		void		setRD( unsigned int const value );

		bool			getRage( void ) const;
		unsigned int	getRD( void ) const;
		
		void			attack(std::string const target);
		void			headbutt(std::string const target);
		virtual void	takeDamage(unsigned int const amount);
		std::string		DamageReduction(unsigned int & Damages);
		void			CheckRage( void );
		void			enrage( void );
		void			calmDown( void );

		virtual	void		NewTurn( int Fighter, Character *Opponent);
		virtual std::string	askAction( void );

		void	BersPlayerTurn( Character *Computer );
		void	BersComputerTurn( Character *Player );

		virtual std::string	getLog( void );	
		virtual std::string	getClassType( void );
};

#endif
