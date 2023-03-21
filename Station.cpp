#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds{
	Station::Station(const std::string& str){
		if(str != ""){
			id_generator++;

			Utilities utils;
			bool more = true;
			size_t next_pos = 0u;

			std::string name = utils.extractToken(str,next_pos,more);
			std::string serial = utils.extractToken(str,next_pos,more);
			std::string stock = utils.extractToken(str,next_pos,more);
			std::string desc = utils.extractToken(str,next_pos,more);
	
			try {
				s_id = id_generator;
				s_name = name;
				s_serial_num = std::stoi(serial);	
				s_stock = std::stoi(stock);
				s_desc = desc;
				if(m_widthField < s_name.length())
					m_widthField = s_name.length();
				//m_widthField = std::max(m_widthField, utils.getFieldWidth());
			} catch (const std::invalid_argument& e) {
  				std::cerr << "Error: invalid value for stock in input file\n";
			}
		}
	}

	const std::string& Station::getItemName()const{
		return s_name;
	}
	size_t Station::getNextSerialNumber(){
		return s_serial_num++;
	}

	size_t Station::getQuantity()const{
		return s_stock;
	}

	void Station::updateQuantity(){
		if(s_stock > 0)
			s_stock--;	
		else s_stock = 0;
	}

	void Station::display(std::ostream& os, bool full)const{
		if(s_name != ""){
		 os << std::setfill('0') << std::right << std::setw(3) << s_id << " | ";
        os << std::setw(m_widthField + 1) << std::left << std::setfill(' ') << s_name << " | ";
        os << std::setw(6) << std::right << std::setfill('0') << s_serial_num << " | ";
        if (full) {
            os << std::setfill(' ') << std::setw(4) << std::right << s_stock << " | ";
            os << std::left <<  s_desc;
        }
        os << std::endl;
		}
	}

}
