#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <iostream>
# include <sstream>
# include <iomanip>
# include <cstdlib>
# include <ctime>
# include <unistd.h>

# define GR "\033[32;1m"
# define RE "\033[31;1m"
# define YE "\033[33;1m"
# define CY "\033[36;1m"
# define LB "\094[36;1m"
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
	COMPUTER,
	PLAYER
};

class Character {
	private: 
		Character( void );

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
		unsigned int	_Bleed;
		bool			_Peace;

	public:
		Character(std::string name);
		Character( Character const & src );
		~Character( void );

		Character	&operator=( Character const & src );

		std::string	Actions[6];

		static Character	*FirstChar;
		static Character	*LastChar;
		Character			*Previous;
		Character			*Next;

		void				Heal(unsigned int const amount);
		virtual void		takeDamage(unsigned int const amount);
		void				attack(std::string const target);
		void				Bleeding( void );
		void				Dodging( void );
		void				Resting( void );

		std::string			getLog( void );
		void				PlayerTurn( Character *Computer );
		int					PlayerAction( void );
		void				ComputerTurn( Character *Player );

		void		setName( std::string const value );
		void		setHitPoints( unsigned int const value );
		void		setStamina( unsigned int const value );
		void		setAttackDamage( unsigned int const value );
		void		setDodge( int const value );
		void		setBleed( unsigned int const value );
		void		setPeace( bool const value );

		std::string		getName( void ) const;
		unsigned int	getHitPoints( void ) const;
		unsigned int	getMaxHP( void ) const;
		unsigned int	getStamina( void ) const;
		unsigned int	getAttackDamage( void ) const;
		int				getDodge( void ) const;
		unsigned int	getBleed( void ) const;
		bool			getPeace( void ) const;

};

std::ostream	&operator<<( std::ostream & ostream, Character const & src );

#endif
