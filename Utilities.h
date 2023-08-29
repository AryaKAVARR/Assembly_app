#// Name: Arya Rajeshbhai Kavar
// Seneca Student ID: 167240217
// Seneca email: akavar@myseneca.ca
// Date of completion: 28-07-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_UTILITIES
#define SDDS_UTILITIES 
#include<string>

namespace sdds
{
   class Utilities
   {
      size_t m_widthField{ 1 };
      static char m_delimiter;
      std::string trim(const std::string& str);

   public:
      void setFieldWidth(size_t newWidth);//sets the width to newWidth
      size_t getFieldWidth() const { return this->m_widthField; }; // returns the width
      std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
      static void setDelimiter(char newDelimiter);//sets the delimeter
      static char getDelimiter();//returns the delimeter
   };
}
#endif // !SDDS_UTILITIES
