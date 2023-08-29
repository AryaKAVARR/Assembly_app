// Name: Arya Rajeshbhai Kavar
// Seneca Student ID: 167240217
// Seneca email: akavar@myseneca.ca
// Date of completion: 28-07-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Station.h"
#include<iostream>
#include<string>
#include<iomanip>
#include "Utilities.h"

using namespace std;

namespace sdds
{
   size_t Station::m_widthField{};
   int Station::id_generator{ 1 };


   std::string Station::trim(const std::string& str)
   {
      const string& whitespace = " \t\n\r\f\v";

      const size_t start_pos = str.find_first_not_of(whitespace);
      if (start_pos == string::npos) return ""; // no content

      const size_t end_pos = str.find_last_not_of(whitespace);
      const size_t len = end_pos - start_pos + 1;

      return str.substr(start_pos, len);
   }

   Station::Station(const std::string str)
   {
      Utilities utils{};
      bool more = true;
      size_t pos = 0u;

      this->id = Station::id_generator++;
      this->m_name = utils.extractToken(str, pos, more);
      this->ser_number = stoul(utils.extractToken(str, pos, more));
      this->no_stock = stoul(utils.extractToken(str, pos, more));

      if (this->m_widthField < utils.getFieldWidth()) {
         this->m_widthField = utils.getFieldWidth();
      }

      this->m_desc = this->trim(utils.extractToken(str, pos, more));
   }

   const std::string& Station::getItemName() const
   {
      return this->m_name;
   }

   size_t Station::getNextSerialNumber()
   {
      return this->ser_number++;
   }

   size_t Station::getQuantity() const
   {
      return this->no_stock;
   }
   void Station::display(std::ostream& os, bool full) const
   {
      if (full) {
         os << setw(3) << setfill('0') << right << this->id << " | ";
         os << setw(Station::m_widthField) << setfill(' ') << left << this->m_name << " | ";
         os.unsetf(ios::left);
         os << setw(6) << setprecision(6) << fixed << setfill('0') << this->ser_number << " | ";
         os << setw(4) << setfill(' ') << this->no_stock << " | ";
         os << this->m_desc << endl;
      }
      else {
         os << setw(3) << setfill('0') << right << this->id << " | ";
         os << setw(Station::m_widthField) << setfill(' ') << left << this->m_name << " | ";
         os.unsetf(ios::left);
         os << setw(6) << setprecision(6) << fixed << setfill('0') << this->ser_number << " | " << endl;
      }
   }
   void Station::updateQuantity()
   {
      if (this->no_stock >= 0 && (this->no_stock - 1) >= 0)
         --this->no_stock;
   }

}