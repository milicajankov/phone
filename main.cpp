#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Phone{
protected:
    string marka;
    string model;
    int godina;
    double cena;
public:
    Phone(string a, string b, int c, double d) : marka(a), model(b), godina(c), cena(d) { }
    int getGod() const {return godina;}
    double getCena() const {return cena;}
    virtual string getOS() const = 0;

    friend ostream& operator << (ostream& out, const Phone &p){
    out << p.marka << "," << p.model << "," << p.godina << "," << p.cena;
    return out;

    }
};

class Mobile: public Phone{ // klasa Mobile nasledjuje javno klasu Phone
protected:
    string keyboard;
public:
    Mobile(string a, string b, int c, double d, string  f): Phone(a, b, c, d), keyboard(f) {}

    virtual string getOS() const {return "";}

    friend ostream& operator <<  (ostream& out, const Mobile& p){
    out << p.marka << ", " << p.model << ", " << p.godina << ", " << p.cena << ", " << p.keyboard;
    return out;
    }
};

class Smart: public Mobile{
protected:
    string os;
public:
    Smart(string a, string b, int c, double d, string f): Mobile(a, b, c, d, "touch"), os(f) {}
    string getOS() const {return os;}

    friend ostream& operator << (ostream &out, const Smart& p){
        out << "smart, " << p.marka << " ," << p.model << " ," << p.godina << ", " << p.cena;
    }
};

int main()
{
    vector<Phone*>niz;
    niz.push_back(new Mobile("Nokia","3310",1999,600,"keypad"));
    niz.push_back(new Mobile("Nokia","N95",2007,20000,"touch"));
    niz.push_back(new Mobile("LG","C360",2011,10000,"keyboard"));
    niz.push_back(new Smart("LG","Nexus5",2012,80000,"Android"));
    niz.push_back(new Smart("Nokia","3310",1999,600,"Android"));
    niz.push_back(new Smart("Apple","Iphone",2015,90000,"iOS"));
    niz.push_back(new Smart("Nokia","Lumia640",2013,28000,"Windows"));


    for(auto el : niz)
        cout << *el << endl;

    cout << endl << "Najnoviji: "
         << **min_element(niz.begin(), niz.end(),
                          [](Phone *a, Phone *b) {return a->getGod() > b->getGod();}
                          ) << endl;

    cout << endl << "Najjeftiniji: "
         << **min_element(niz.begin(), niz.end(),
                          [](Phone *a, Phone *b) {return a->getCena() < b->getCena();}
                          ) << endl;
     double suma = 0;
    for (auto el: niz)
        suma += el->getCena();

    cout << "Prosecna cena: " << suma / niz.size() << endl;
    cout << "Android telefoni: " << count_if(niz.begin(), niz.end(),
                                             [](Phone *p){ if(p->getOS() == "Android")
                                                            return true;
                                                           return false;}
                                             ) << endl;

    // primer lambde
    auto f = [](int a, int b) {return a + b;};
    cout << endl << endl << f(4,5) << endl;

}
