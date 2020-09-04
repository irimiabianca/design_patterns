#include <iostream>
#include <string>

using namespace std;


class Platform;


class Image
{
public:
    static Platform &platform;
    Image(string name): name{name} {}

    virtual void load() = 0; // se incarca imag de pe disk
    virtual void rotate(int angle) = 0;

protected:
    string name{};
};


class Platform
{
public:
    virtual void open(string name) = 0;
    virtual void render(Image &img) = 0;
    virtual void rotate(int angle) = 0;
};


class LibOpenGL
{
public:
    void operation1() { cout << "OGL::operation1\n"; }
    void operation2() { cout << "OGL::operation2\n"; }
    void operation3() { cout << "OGL::operation3\n"; }

};


class LibDirectX
{
public:
    void operation1() { cout << "Dx::operation1\n"; }
    void operation2() { cout << "DX::operation2\n"; }
    void operation3() { cout << "DX::operation3\n"; }
    void operation4() { cout << "DX::operation4\n"; }
};

class Linux : public Platform
{
public:
    virtual void open(string name) override
    {
        cout << "Linux::open\n";
        lib.operation1();
    }
    virtual void render(Image &img) override
    {
        cout << "Linux::render\n";
        lib.operation2();

    }
    virtual void rotate(int angle) override
    {
        cout << "Linux::rotate\n";
        lib.operation2();
        lib.operation3();

    }
private:
    LibOpenGL lib{};

};


class Windows : public Platform
{
public:
    virtual void open(string name) override
    {
        cout << "Windows::open\n";
        lib.operation1();
        lib.operation2();
    }
    virtual void render(Image &img) override
    {
        cout << "Windows::render\n";
        lib.operation2();

    }
    virtual void rotate(int angle) override
    {
        cout << "Windows::rotate\n";
        lib.operation2();
        lib.operation3();
        lib.operation4();

    }
private:
    LibDirectX lib{};

};


class Png : public Image
{
public:
    Png(string name) : Image(name + ".png") {}

    virtual void load() override
    {
        platform.open(name);
        cout << "Png:load\n";
        platform.render(*this);
    }

    virtual void rotate(int angle) override
    {
        cout << "Png::roatate begin\n";
        platform.rotate(*this);
        platform.render(*this);
    }
};


class Jpg : public Image
{
public:
    Jpg(string name) : Image(name + ".jpg") {}

    virtual void load() override
    {
        platform.open(name);
        cout << "Jpg:load\n";
        platform.render(*this);
    }

    virtual void rotate(int angle) override
    {
        cout << "Jpg::roatate begin\n";
        platform.rotate(*this);
        platform.render(*this);
        cout << "Jpg::rotate end\n";
    }
};


Windows WINDOWS{};
Linux LINUX{};
//logic for choosing platform
Platform &Image::platform{WINDOWS};

int main()
{
    Png png{"img1"};
    Jpg jpg{"img2"};

    Image &img1{png};
    Image &img2{jpg};

    img1.load();
    img1.rotate(90);

    img2.load();
    img2.rotate(90);

    return 0;
}
