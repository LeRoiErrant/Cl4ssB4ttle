#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <iostream>
# include <sstream>
# include <iomanip>
# include <cstdlib>
# include <ctime>
# include <unistd.h>
# include "Sed.hpp"

# define BLINK "\033[1;5m"
# define BOLD "\033[1m"
# define ITAL "\033[3m"
# define UNDRL "\033[4m"
# define HDDN "\033[8m"
# define GR "\033[32;1m"
# define RE "\033[31;1m"
# define DR "\033[31;1;2m"
# define YE "\033[33;1m"
# define CY "\033[36;1m"
# define LG "\033[37;1;3m"
# define DG "\033[90;1;3m"
# define DGB "\033[90;1m"
# define LB "\033[94;1m"
# define WH "\033[97m"
# define MA "\001\033[1;95m\002"
# define BL "\001\033[1;94m\002"
# define RC "\033[0m"

enum Actions {
	ATTACK,
	HEAL,
	REST,
	DODGE,
	SPECIAL,
	FORFEIT
};

enum Fighter {
	PLAYER,
	COMPUTER,
	FIGHTER = 0,
	OPPONENT
};

class Character {
	private: 
		Character( void );
		
		void			(Character::*TakeTurn[2])( Character *Opponent );

		static const unsigned int	__HitPoints = 10;
		static const unsigned int	__Stamina = 10;
		static const unsigned int	__AttackDamage = 2;
		static const int			__Dodge = 5;

	protected:
		std::string		_Name;
		unsigned int	_HitPoints;
		unsigned int	_MaxHP;
		unsigned int	_Stamina;
		unsigned int	_MaxStam;
		unsigned int	_AttackDamage;
		int				_Dodge;
		bool			_Dodging;
		bool			_hasDodged;
		unsigned int	_Bleed;
		bool			_Peace;
		bool			_Counter;

	public:
		Character(std::string name);
		Character( Character const & src );
		virtual ~Character( void );

		Character	&operator=( Character const & src );

		std::string	Actions[6];

		static Character	*FirstChar;
		static Character	*LastChar;
		Character			*Previous;
		Character			*Next;

		void				Heal( unsigned int const amount );
		virtual void		takeDamage( unsigned int const amount );
		void				attack( std::string const target );
		void				Bleeding( void );
		void				Dodging( void );
		bool				tryDodge( void );
		void				Resting( void );
		bool				checkPeace( Character *Opponent );

		virtual std::string	getLog( void );

		virtual void		NewTurn( int Fighter, Character *Opponent);
		virtual std::string	askAction( void );

		void				CharPlayerTurn( Character *Computer );
		int					PlayerAction( void );
		void				CharComputerTurn( Character *Player );

		void		setName( std::string const value );
		void		setHitPoints( unsigned int const value );
		void		setStamina( unsigned int const value );
		void		setAttackDamage( unsigned int const value );
		void		setDodge( int const value );
		void		setBleed( unsigned int const value );
		void		setPeace( bool const value );
		void		setCounter( bool const value );

		std::string		getName( void ) const;
		unsigned int	getHitPoints( void ) const;
		unsigned int	getMaxHP( void ) const;
		unsigned int	getStamina( void ) const;
		unsigned int	getAttackDamage( void ) const;
		int				getDodge( void ) const;
		unsigned int	getBleed( void ) const;
		bool			getPeace( void ) const;
		bool			getCounter( void ) const;

		virtual std::string	getClassType( void );
};

std::ostream	&operator<<( std::ostream & ostream, Character const & src );

void	slow_print(std::ostringstream & raw, int delay);

#endif
