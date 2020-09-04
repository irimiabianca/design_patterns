// command.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Behavior design pattern
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class ActionEvent
{

};


class ButtonPressed : public ActionEvent
{

};

class ActionListener // COMMAND!
{
public:
    virtual void actionPerformed(const ActionEvent& event) = 0;
    //virtual void addActionListener(ActionListener* listener) = 0;
};

class Widget
{
public:
    virtual void eventOccured(const ActionEvent& event) = 0;
};


class Button : public Widget
{
public:
    virtual void eventOccured(const ActionEvent& event) override
    {
        pressed = !pressed;
        if (listener != nullptr)
            listener->actionPerformed(event); // callback when event happens (client code!)
    }
    //register caalback
    virtual void addActionListener(ActionListener* listener)
    {
        this->listener = listener;
    }
private:
    bool pressed{}; // false
    ActionListener *listener{};

};

//client code (start)
class OkActionListener : public ActionListener
{
    virtual void actionPerformed(const ActionEvent& e)
    {
        thread t{ []() { cout << this_thread::get_id()<< ":OK\n"; } };
        t.join();
    }
};

class Cancel : public ActionListener
{
    virtual void actionPerformed(const ActionEvent& e)
    {
       
        thread t{ []() {cout << this_thread::get_id() << "cancel\n"; } };
        t.join();
    }
};


int main()
{
    //client code (start)
    Button ok{};
    Button cancel{};

    OkActionListener oal{};
    Cancel cal{};

    ok.addActionListener(&oal);
    cancel.addActionListener(&cal);
    //client code (end)

    //platform code
    this_thread::sleep_for(500ms);
    thread t{ [&ok, &cancel]() {
        for (int i = 0; i < 100; i++) {
        ok.eventOccured(ButtonPressed{});
        cancel.eventOccured(ButtonPressed{});
        this_thread::sleep_for(30ms);
        }
    }
    };
    //[](){};--se declara un lamda(o functie anonima)


    t.join();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
