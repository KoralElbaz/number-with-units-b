
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


namespace ariel
{

    class NumberWithUnits
    {
        private:
            double num;
            string unit;  
    
        public:
            NumberWithUnits(double num , const string &unit);
        
            static void read_units(std::ifstream &units_file);
            
            //================ + ====================//
            NumberWithUnits operator+() const;
            NumberWithUnits operator+(const NumberWithUnits &n) const;
            NumberWithUnits& operator+=(const NumberWithUnits &n);

            //================ - ====================//
            NumberWithUnits operator-() const;
            NumberWithUnits operator-(const NumberWithUnits &n) const;
            NumberWithUnits& operator-=(const NumberWithUnits &n);

            //================ <=> ====================//
            bool operator>(const NumberWithUnits &n) const;
            bool operator>=(const NumberWithUnits &n) const;
            bool operator<(const NumberWithUnits &n) const;
            bool operator<=(const NumberWithUnits &n) const;
            bool operator==(const NumberWithUnits &n) const;
            bool operator!=(const NumberWithUnits &n) const;


            //================ ++ -- ====================//
            NumberWithUnits& operator++();
            NumberWithUnits operator++(int);

            NumberWithUnits& operator--();
            NumberWithUnits operator--(int);

            //================ * ====================//
            friend NumberWithUnits operator*(double d, const NumberWithUnits &n);
            NumberWithUnits operator*(double n) const;

            //================ input - output ====================//
            friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &c);

            friend std::istream &operator>>(std::istream &is, NumberWithUnits &n);

    };
}