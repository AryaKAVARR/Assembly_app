// Name: Arya Rajeshbhai Kavar
// Seneca Student ID: 167240217
// Seneca email: akavar@myseneca.ca
// Date of completion: 28-07-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_LINEMANAGER
#define SDDS_LINEMANAGER
#include<iostream>
#include <vector>
#include "Workstation.h"

namespace sdds
{
   class LineManager
   {
      std::vector<Workstation*> m_activeLine{}; //collection of workstation
      size_t m_cntCustomerOrder{}; //number of CustomerOrder objects
      Workstation* m_firstStation{}; //points to first active station on current line

   public:
      LineManager(const std::string& file, const std::vector<Workstation*>& stations);
      void reorderStations(); // it will reorder the workstations
      bool run(std::ostream& os); // it will performs **one** iteration of operations
      void display(std::ostream& os) const; //display function
   };
}
#endif // !SDDS_LINEMANAGER
