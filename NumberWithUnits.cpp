
#include <iostream>
#include <fstream>
#include <map>
#include "NumberWithUnits.hpp"
using namespace std;
const double EPS = 0.001;

namespace ariel
{
    static map<string, map<string, double>> unitList;
    
   /** constructor - Checking invalid argument (if the unit in the map)
    * @param num 
    * @param unit 
    * 
    **/ 
    NumberWithUnits::NumberWithUnits(double num, const string &unit)
    {
       if (unitList.count(unit) == 0)
        {
            throw invalid_argument("No unit called "+unit);
        }
        //unitList.at(unit);
        this->num = num;
        this->unit = unit;
    }

    //============== help functions ============//
    /*
    *checking if the unit in the same types - > return val 
    *else, doing conversion
    *@param val - value that we will want to convert
    *@param src - type unit of val
    *@param dest - type unit we need convert to 
    */
    double conversion(double val,const string& src,const string& dest)
    {
        if (src == dest)
        {
            return val;
        }
        try{
            return val * unitList.at(src).at(dest);
        }
        catch(const exception& e) {
            throw invalid_argument{"Types not from the same system!"};
        }
    
        // if(unitList.at(src).at(dest)==0){
        //     throw invalid_argument{"Types not from the same system!"};
        //  }
        // return val*unitList.at(src).at(dest);
        
    }

    /** Insert into the map
     * @param unit1 
     * @param unit2 
     * */


    void insertUnit(const string& unit1, const string& unit2)
    {
        for (auto &map : unitList[unit2])
        {
            double val = unitList[unit1][unit2] * map.second;
            unitList[unit1][map.first] = val;
            unitList[map.first][unit1] = 1 / val;
        }
    }

    void NumberWithUnits::read_units(std::ifstream &units_file)
    {
        string unit1, unit2, c;
        double val1=0, val2=0;

        while (units_file >> val1 >> unit1 >> c >> val2 >> unit2)
        {
            unitList[unit1][unit2] = val2;
            unitList[unit2][unit1] = 1 / val2;
            insertUnit(unit1, unit2);
            insertUnit(unit2, unit1);
        }
    }

    //================ + ====================//

    NumberWithUnits NumberWithUnits::operator+() const
    {
        return NumberWithUnits(this->num, this->unit);
    }
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &n) const
    {
        double numCheck = conversion(n.num, n.unit, this->unit);
        return NumberWithUnits(this->num + numCheck, this->unit);
    }
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &n)
    {
        this->num += conversion(n.num, n.unit, this->unit);
        return *this;
    }

    //================ - ====================//
    NumberWithUnits NumberWithUnits::operator-() const
    {
        return NumberWithUnits((-1) * this->num, this->unit);
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &n) const
    {
        double numCheck = conversion(n.num, n.unit, this->unit);
        return NumberWithUnits(this->num - numCheck, this->unit);
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &n)
    {
        this->num -= conversion(n.num, n.unit, this->unit);
        return *this;
    }

    //================ <=> ====================//

    bool NumberWithUnits::operator>(const NumberWithUnits &n) const
    {
        double compare = conversion(n.num, n.unit, this->unit);
        return (this->num > compare);
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits &n) const
    {
        return !(*this < n);
    }
    bool NumberWithUnits::operator<(const NumberWithUnits &n) const
    {
        return (this->num < conversion(n.num, n.unit, this->unit));
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits &n) const
    {
        return !(*this > n);
    }
    bool NumberWithUnits::operator==(const NumberWithUnits &n) const
    {
        return (abs(this->num-conversion(n.num, n.unit, this->unit))<=EPS);
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits &n) const
    {
        return !(*this == n);
    }

    //================ ++ -- ====================//

    NumberWithUnits& NumberWithUnits::operator++()
    {
        ++(this->num);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int)
    {

        return NumberWithUnits(this->num++, this->unit);
    }

    NumberWithUnits& NumberWithUnits::operator--()
    {
        --(this->num);
        return *this; 
    }

    NumberWithUnits NumberWithUnits::operator--(int)
    {
        return NumberWithUnits(this->num--, this->unit);
    }


    //================ * ====================//

    NumberWithUnits operator*(double d, const NumberWithUnits &n)
    {
        return NumberWithUnits(n.num * d, n.unit);
    }

    NumberWithUnits NumberWithUnits::operator*(double n) const
    {
        return n*(*this);
    }

    //================ input - output ====================//
    std::ostream& operator<<(std::ostream &os, const NumberWithUnits &c)
    {
        os << c.num << "[" << c.unit << "]";
        return os;
    }

    // std::istream& operator>>(std::istream &is, NumberWithUnits &c)
    // {
    //     string s;
    //     is >> c.num >> s >> c.unit;
    //     return is;
    // }

    std::istream &operator>>(std::istream &is, NumberWithUnits &n) {
        double val=0;
        std::string type;
        char c=' ';
        is >> val;
        is >> c ;
        while(c!=']'){
            if(c!='['){
                type.insert(type.end(),c);
            }
            is>>c;
        }
       if(unitList[type].empty()){throw invalid_argument{"unit doesnt exist"};};
        n.num=val;
        n.unit=type;
        return is;
    }

};
