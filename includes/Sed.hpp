/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sed.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheran <vheran@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:36:11 by vheran            #+#    #+#             */
/*   Updated: 2023/01/06 16:06:18 by vheran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SED_HPP
# define SED_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>


# define FAILURE 1
# define SUCCESS 0

class Sed
{
	private:

	public:
		Sed();
		~Sed();

		static void	replace(std::string const &filename, std::string const &search, std::string const &replace);
		static std::string	strReplace(std::string const &line, std::string const &search, std::string const &replace);
		static std::string	strToUpper(std::string const &line);
};

#endif
