#include <iostream>
#include <stdexcept>
#include "Utilities.h"

//testting!!
namespace sdds{

	std::string Utilities::trim(const std::string& str) {
    		size_t first = str.find_first_not_of(' ');
    		if (std::string::npos == first) 
     		   return str;
   		 
   		 size_t last = str.find_last_not_of(' ');
   		 return str.substr(first, (last - first + 1));
	} 

	void Utilities::setFieldWidth(size_t newWidth){
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth()const{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){
		std::string extractToken = "";
		std::string::size_type find_deli = str.find(m_delimiter, next_pos);
		
		if(find_deli != std::string::npos){

			if(find_deli != next_pos)
				extractToken = str.substr(next_pos, find_deli - next_pos);
			else{
				more = false;
				throw "ERROR: Token is empty!";
			} 
			next_pos = find_deli + 1; 
		}
		else{
			extractToken = str.substr(next_pos);
			more = false;
		} 
		(extractToken.length() > m_widthField) ? m_widthField = extractToken.length() : m_widthField;

		return trim(extractToken);
	}

	void Utilities::setDelimiter(char newDelimiter){
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter(){
		return m_delimiter;
	}
}

