#include <iostream>
#include <string>

using namespace std;
//including a class just for the sake of testing branches
class Test
{
public:
    Test(string name) : name{name} {}
protected:
    tring name;
};


class Vehicle
{
public:
    virtual string str() const = 0;
    virtual void draw() const = 0;
};


class SkodaOctavia : public Vehicle
{
public:
    SkodaOctavia(string color) : color{ color } {}
    virtual string str() const override { return color + " Skoda Octavia"; }
    virtual void draw() const override { cout << "DRAW: " << str() << endl; }
private:
    string color{};
};


class SkodaSuperb : public Vehicle
{
public:
    SkodaSuperb(string color) : color{ color } {}
    virtual string str() const override { return color + " Skoda Superb"; }
    virtual void draw() const override { cout << "DRAW: " << str() << endl; }
private:
    string color{};
};


class Option : public Vehicle
{
public:
    Option(const Vehicle& v) : target{ v } {}

    virtual string str() const override { return target.str(); }
    virtual void draw() const override { target.draw(); }
protected:
    const Vehicle& target;
};


class Sport : public Option
{
public:
    Sport(const Vehicle& v) : Option(v) {}
    virtual string str() const override { return target.str() + " Sport Stuff"; }
    virtual void draw() const override { target.draw(); cout << "sport.draw()"; }
};


class Comfort : public Option
{
public:
    Comfort(const Vehicle& v) : Option(v) {}
    virtual string str() const override { return target.str() + " Comfy"; }
    virtual void draw() const override { target.draw(); cout << "comfort.draw()"; }
};


class Metalized : public Option
{
public:
    Metalized(const Vehicle& v) : Option(v) {}
    virtual string str() const override { return target.str() + " Metalized color"; }
    virtual void draw() const override { target.draw(); cout << " metalized"; }
};


class Executive : public Option
{
public:
    Executive(const Vehicle& v) : Option(v) {}
    virtual string str() const override { return target.str() + " Bossy"; }
};



    int main()
{
    SkodaOctavia o{"blue"};
    SkodaSuperb s{"red"};

    Executive e{o};
    Sport ss{s};

    Metalized m {e};
    Comfort c{ss};

    Vehicle &v1{c};
    Vehicle &v2{m};

    cout << v1.str() << endl;
    cout << v2.str() << endl;


    return 0;
}
