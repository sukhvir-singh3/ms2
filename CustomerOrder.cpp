#include <iostream>
#include <iomanip>
#include <vector>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds{

	CustomerOrder::~CustomerOrder(){
		for(size_t i = 0; i < m_cntItem; i++)
			delete m_listItem[i];
		delete m_listItem;
	}	

	CustomerOrder::CustomerOrder(const std::string& str)
	:m_name(""), m_product(""), m_cntItem(0), m_listItem(nullptr)
	{

		Utilities util;
		size_t next_pos = 0u;
		bool more = true; 

		m_name = util.extractToken(str,next_pos, more);
		m_product = util.extractToken(str, next_pos, more);

		size_t count = 0;

		//Checking the Quantity of items
		while(more){
			auto COUNT = util.extractToken(str, next_pos, more);
			count++;
		}
		std::cout << "****************" << count << "****************" << std::endl;
		
		size_t lock_pos = next_pos;
		bool lock_more = true;
		m_listItem = new Item*[count];
		size_t index = 0;
		m_cntItem = count;

		//going back to store the items in the array now
		while (lock_more && index < m_cntItem) {
			util.setFieldWidth(m_widthField);
			auto token = util.extractToken(str,lock_pos,lock_more);  
			m_listItem[index] = new Item(token);
			index++;
		}
		if (util.getFieldWidth() > m_widthField) {
    			  m_widthField = util.getFieldWidth();
    	 	}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& other){
		throw std::string("ERROR: Copy is not allowed.");
	}
	
	CustomerOrder::CustomerOrder(CustomerOrder&& other)noexcept{
		//Stealing the data
		m_name = std::move(other.m_name);
		m_product = std::move(other.m_product);
		m_cntItem = std::move(other.m_cntItem);
		m_listItem = std::move(other.m_listItem);

		//deleting other object's data
		other.m_name = "";
		other.m_product = "";
		other.m_cntItem = 0;
		other.m_listItem = nullptr;
	}		

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other)noexcept{
		if(this != &other){
			for(size_t i = 0; i < m_cntItem; i++)
				delete m_listItem[i];
			delete m_listItem;

			//Stealing the data
			m_name = std::move(other.m_name);
			m_product = std::move(other.m_product);
			m_cntItem = std::move(other.m_cntItem);
			m_listItem = std::move(other.m_listItem);

			//deleting other object's data
			other.m_name = "";
			other.m_product = "";
			other.m_cntItem = 0;
			other.m_listItem = nullptr;
		}
		return *this;
	}

	bool CustomerOrder::isOrderFilled() const{
		for(size_t i = 0 ;i < m_cntItem; i++)
			if(m_listItem[i]->m_isFilled == false)
				return false;
		return true;	
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const{
		bool is_there = false;
		size_t at_index = 0;
		//find the name and save its index
		for(size_t i = 0 ;i < m_cntItem; i++)
			if(m_listItem[i]->m_itemName == itemName){
				is_there = true;
				at_index = i;
			}

		//check the bool at found index
		if(is_there){
			if(m_listItem[at_index]->m_isFilled == false)
				return false;
		}
		return true;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os){
		bool found = false;
		for(size_t i = 0 ;i < m_cntItem; i++)
			if(m_listItem[i]->m_itemName == station.getItemName())					
				found = true;
		if(found){
			if(station.getQuantity() >= 1){
				Item** temp = new Item*[m_cntItem + 1];
				for(size_t i = 0 ;i < m_cntItem; i++)
					temp[i] = m_listItem[i];
				temp[m_cntItem]->m_isFilled = true;
				//temp[m_cntItem]->m_itemName = station.getItemName();
				temp[m_cntItem]->m_serialNumber = station.getNextSerialNumber();

				m_cntItem++;
				delete[] m_listItem;
				m_listItem = temp;
				delete[] temp;
				station.updateQuantity();

				for(size_t i = 0 ;i < m_cntItem; i++)
					os << "Filled" << m_name << "," 
					   << " " << m_product << " " 
					   << "[" << m_listItem[i]->m_itemName << std::endl;
			}
			else 
				for(size_t i = 0 ;i < m_cntItem; i++)
					os << "Unable to fill" << m_name << "," 
				   	<< " " << m_product << " " 
				   	<< "[" << m_listItem[i]->m_itemName << std::endl;
		}
	}

	void CustomerOrder::display(std::ostream& os) const{
		os << m_name 
		   << m_product;
		   std::cout << m_cntItem <<std::endl;
		   for(size_t i = 0 ;i < m_cntItem; i++){
			os << "[" << std::setw(6)<< m_listItem[i]->m_serialNumber << "] "
		   	   << std::setw(m_widthField) <<m_listItem[i]->m_itemName << " - ";
		   		(m_listItem[i]->m_isFilled==true)? os<<"TO BE FILLED\n" : os << "FILLED\n";
		   }
	}
}
