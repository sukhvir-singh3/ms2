#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include <iostream>
#include "Station.h" 

namespace sdds{
	struct Item{
		std::string m_itemName;
		size_t m_serialNumber{0};
		bool m_isFilled{false};

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder{
		private:
			std::string m_name;
			std::string m_product;
			size_t m_cntItem;
			Item** m_listItem;
			inline static size_t m_widthField = 0;
		public:
			CustomerOrder();
			~CustomerOrder();
			CustomerOrder(const std::string& str);
			CustomerOrder(const CustomerOrder& other);
			CustomerOrder& operator=(const CustomerOrder& other) = delete;
			CustomerOrder(CustomerOrder&& other) noexcept;
			CustomerOrder& operator=(CustomerOrder&& other) noexcept;
			bool isOrderFilled() const;
			bool isItemFilled(const std::string& itemName) const;
			void fillItem(Station& station, std::ostream& os);
			void display(std::ostream& os) const;
	};
}
#endif
