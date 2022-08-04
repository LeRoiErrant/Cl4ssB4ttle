#ifndef SHADOW_HPP
# define SHADOW_HPP

# include "Character.hpp"

class Shadow : public Character {
	private:
		Shadow( void );
		
		void			(Shadow::*TakeTurn[2])( Character *Opponent );

		bool	_Hiding;
		
		static const unsigned int	__HitPoints = 40;
		static const unsigned int	__Stamina = 20;
		static const unsigned int	__AttackDamage = 4;
		static const int			__Dodge = 20;

	public:
		Shadow( std::string name );
		Shadow( Shadow const & src );
		virtual ~Shadow( void );

		Shadow	&operator=( Shadow const & src );

		void			attack(std::string const target);
		virtual void	takeDamage(unsigned int const amount);
		std::string		sneakAttack( unsigned int & Damages, std::string const target );
		void			hide( void );
		std::string		notHiding( void );
		void			refreshDodge( void );

		virtual	void		NewTurn( int Fighter, Character *Opponent);
		virtual std::string	askAction( void );

		void	ShadPlayerTurn( Character *Computer );
		void	ShadComputerTurn( Character *Player );

		void	setHiding( bool const value );
		bool	getHiding( void ) const;

		virtual std::string	getLog( void );
		virtual std::string	getClassType( void );
};

#endif
