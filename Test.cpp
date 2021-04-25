#include "doctest.h"
#include <string>
#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;

const string test_file = "./units.txt";


//============================= for operator + ========================//

TEST_CASE("operator +"){
    ifstream units_file{test_file};
    NumberWithUnits a(3,"m");
    CHECK((+a).getNum()==3);
    CHECK((+a).getUnit()=="m");

    NumberWithUnits b(-40,"cm");
    CHECK((+b).getNum()==-40);
    CHECK((+b).getUnit()=="cm");

    NumberWithUnits c(5,"sec");
    CHECK((+c).getNum()==5);
    CHECK((+c).getUnit()=="sec");
}

TEST_CASE("operator +"){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK((NumberWithUnits(3,"m")+NumberWithUnits(40,"cm"))==NumberWithUnits(3.4,"m"));
    CHECK((NumberWithUnits(1,"kg")+NumberWithUnits(1,"g"))==NumberWithUnits(1.001,"kg"));
    CHECK((NumberWithUnits(1,"g")+NumberWithUnits(1,"kg"))==NumberWithUnits(1001,"g"));
    CHECK((NumberWithUnits(1,"g")+NumberWithUnits(1,"ton"))==NumberWithUnits(1000001,"g"));
    CHECK((NumberWithUnits(2,"ton")+NumberWithUnits(3,"g"))==NumberWithUnits(2.000003,"ton"));
    CHECK_THROWS_MESSAGE(NumberWithUnits(3,"m")+NumberWithUnits(5,"sec"),"Types not from the same system");
    CHECK_THROWS_MESSAGE(NumberWithUnits(5,"sec")+NumberWithUnits(3,"m"),"Types not from the same system");
}



TEST_CASE("OPERTOR +="){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a1(3,"m") , a2(40,"cm") , a3(3.4,"m");
    CHECK((a1+=a2)==a3);

    NumberWithUnits b1(1,"g") , b2(1,"kg"), b3(1001,"g");
    CHECK((b1+=b2)==b3);

    NumberWithUnits c1(1,"kg") , c2(1,"g"), c3(1.001,"kg");
    CHECK((c1+=c2)==c3);

    NumberWithUnits d1(1,"g") , d2(1,"ton"), d3(1000001,"g");
    CHECK((d1+=d2)==d3);

    NumberWithUnits e1(1,"ton") , e2(1,"g"), e3(1.000001,"ton");
    CHECK((e1+=e2)==e3);

    NumberWithUnits f1(3,"m") , f2(5,"sec");
    CHECK_THROWS_MESSAGE(f1+=f2,"Types not from the same system!");
}

//============================= for operator - ========================//


TEST_CASE("OPERTOR -"){
    ifstream units_file{test_file};
    NumberWithUnits a(3,"m");
    CHECK((-a).getNum()==-3);
    CHECK((-a).getUnit()=="m");

    NumberWithUnits b(-40,"cm");
    CHECK((-b).getNum()==40);
    CHECK((-b).getUnit()=="cm");

    NumberWithUnits c(5,"sec");
    CHECK((-c).getNum()==-5);
    CHECK((-c).getUnit()=="sec");
}


TEST_CASE("OPERTOR -"){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK((NumberWithUnits(3,"m")-NumberWithUnits(40,"cm"))==NumberWithUnits(2.6,"m"));
    CHECK((NumberWithUnits(1,"kg")-NumberWithUnits(1,"g"))==NumberWithUnits(0.999,"kg"));
    CHECK((NumberWithUnits(1,"g")-NumberWithUnits(1,"kg"))==NumberWithUnits(-999,"g"));
    CHECK((NumberWithUnits(1,"g")-NumberWithUnits(1,"ton"))==NumberWithUnits(-999999,"g"));
    CHECK((NumberWithUnits(2,"ton")-NumberWithUnits(3,"g"))==NumberWithUnits(1.999997,"ton"));
    CHECK_THROWS_MESSAGE(NumberWithUnits(3,"m")-NumberWithUnits(5,"sec"),"Unit not from the same system");
    CHECK_THROWS_MESSAGE(NumberWithUnits(5,"sec")-NumberWithUnits(3,"m"),"Unit not from the same system");
    CHECK_THROWS_MESSAGE(NumberWithUnits(5,"g")-NumberWithUnits(3,"km"),"Unit not from the same system");

}

TEST_CASE("OPERTOR -="){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a1(3,"m") , a2(40,"cm") , a3(2.6,"m");
    CHECK((a1-=a2)==a3);

    NumberWithUnits b1(1,"g") , b2(1,"kg"), b3(-999,"g");
    CHECK((b1-=b2)==b3);

    NumberWithUnits c1(1,"kg") , c2(1,"g"), c3(0.999,"kg");
    CHECK((c1-=c2)==c3);

    NumberWithUnits d1(1,"g") , d2(1,"ton"), d3(-999999,"g");
    CHECK((d1-=d2)==d3);

    NumberWithUnits e1(1,"ton") , e2(1,"g"), e3(0.999999,"ton");
    CHECK((e1-=e2)==e3);

    NumberWithUnits f1(3,"m") , f2(5,"sec");
    CHECK_THROWS_MESSAGE(f1-=f2,"Types not from the same system!");


}



//==============================  comper ==========================================//

TEST_CASE("OPERTOR >"){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK(NumberWithUnits(6,"kg")>NumberWithUnits(5,"kg"));
    CHECK(NumberWithUnits(3.5,"ton")>NumberWithUnits(3000,"kg"));
    CHECK(NumberWithUnits(7000,"m")>NumberWithUnits(6,"km"));
    CHECK(NumberWithUnits(5001,"g")>NumberWithUnits(5,"kg"));
    CHECK_FALSE(NumberWithUnits(1,"hour")>NumberWithUnits(60.1,"min"));
}


TEST_CASE("OPERTOR >="){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK(NumberWithUnits(6,"kg")>=NumberWithUnits(5,"kg"));
    CHECK(NumberWithUnits(3,"ton")>=NumberWithUnits(3000,"kg"));
    CHECK(NumberWithUnits(7000,"m")>=NumberWithUnits(6,"km"));
    CHECK(NumberWithUnits(5001,"g")>=NumberWithUnits(5,"kg"));
    CHECK(NumberWithUnits(1,"hour")>=NumberWithUnits(60,"min"));
    CHECK_FALSE(NumberWithUnits(1,"hour")>=NumberWithUnits(60.1,"min"));
}

TEST_CASE("OPERTOR <"){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK(NumberWithUnits(5,"kg")<NumberWithUnits(6,"kg"));
    CHECK(NumberWithUnits(3000,"kg")<NumberWithUnits(3.5,"ton"));
    CHECK(NumberWithUnits(6,"km")<NumberWithUnits(7000,"m"));
    CHECK(NumberWithUnits(5,"kg")<NumberWithUnits(5001,"g"));
    CHECK_FALSE(NumberWithUnits(60.1,"min")<NumberWithUnits(1,"hour"));
}

TEST_CASE("OPERTOR <="){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK(NumberWithUnits(5,"kg")<=NumberWithUnits(6,"kg"));
    CHECK(NumberWithUnits(3,"kg")<=NumberWithUnits(3,"kg"));
    CHECK(NumberWithUnits(6,"km")<=NumberWithUnits(7000,"m"));
    CHECK(NumberWithUnits(5,"kg")<=NumberWithUnits(5000,"g"));
    CHECK_FALSE(NumberWithUnits(7,"min")<=NumberWithUnits(5,"min"));

}

TEST_CASE("OPERTOR =="){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK(NumberWithUnits(3,"m")==NumberWithUnits(3,"m"));
    CHECK(NumberWithUnits(3,"km")==NumberWithUnits(3000,"m"));
    CHECK(NumberWithUnits(1,"hour")==NumberWithUnits(60,"min"));

}

TEST_CASE("OPERTOR !="){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    CHECK(NumberWithUnits(1,"hour")!=NumberWithUnits(65,"min"));
    CHECK(NumberWithUnits(4,"km")!=NumberWithUnits(3999,"m"));
    CHECK(NumberWithUnits(1,"ton")!=NumberWithUnits(60,"kg"));


}



//===============================  OPERTOR ++ / --  =================================//

TEST_CASE("OPERTOR ++_num"){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(62,"min");
    NumberWithUnits b = ++a;
    CHECK(b.getNum()==63);
    CHECK(b.getUnit()=="min");
    CHECK(a.getNum()==63);
    CHECK(a.getUnit()=="min");
            
}

TEST_CASE("OPERTOR _num++"){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(10,"ton");
    NumberWithUnits b = a++;
    CHECK(b.getNum()==10);
    CHECK(b.getUnit()=="ton");
    CHECK(a.getNum()==11);
    CHECK(a.getUnit()=="ton");
    
}

TEST_CASE("OPERTOR --_num"){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(62,"min");
    NumberWithUnits b = --a;
    CHECK(b.getNum()==61);
    CHECK(b.getUnit()=="min");
    CHECK(a.getNum()==61);
    CHECK(a.getUnit()=="min");
}

TEST_CASE("OPERTOR _num--"){
    ifstream units_file{test_file};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(10,"ton");
    NumberWithUnits b = a--;
    CHECK(b.getNum()==10);
    CHECK(b.getUnit()=="ton");
    CHECK(a.getNum()==9);
    CHECK(a.getUnit()=="ton");
}
