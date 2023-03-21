#ifndef STATION_H
#define STATION_H

#include <iostream>

namespace sdds{
	class Station{
		private:
			int s_id;
			std::string s_name;
			std::string s_desc;
			size_t s_serial_num;
			int s_stock;
			
			inline static size_t m_widthField = 0;
			inline static size_t id_generator = 0;
		public:
			Station() = default;
			Station(const std::string& str);		
			const std::string& getItemName() const;
			size_t getNextSerialNumber();
			size_t getQuantity() const;
			void updateQuantity();
			void display(std::ostream& os, bool full) const;
	};
}
#endif
