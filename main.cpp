#include <iostream>
#include <string>

class Toy
{
public:

    Toy(std::string inName) : name(inName) {};
    Toy() : Toy("None") {};

private:
    std::string name;
};

class SharedPtrToy
{

public:
    SharedPtrToy() {};

    SharedPtrToy(const SharedPtrToy& other)
    {
        obj = other.obj;
        countRef = other.countRef;
        ++(*countRef);
    }
    SharedPtrToy& operator= (const SharedPtrToy& other)
    {
        if (this == &other)
        {
            return *this;
        }
            
        clear();

        obj = other.obj;
        countRef = other.countRef;
        ++(*countRef);

        return *this;
    }

    ~SharedPtrToy()
    {
        clear();
    }

    void clear()
    {
        if (obj != nullptr)
        {
            --(*countRef);
            if (*countRef == 0)
            {
                delete obj;
                delete countRef;
            }
        }
        obj = nullptr;
        countRef = nullptr;
    }

    void setObj(Toy* inToy)
    {
        obj = inToy;
    }

    void setRef(int* inCountRef)
    {
        countRef = inCountRef;
    }

private:
    Toy* obj = nullptr;
    int* countRef = nullptr;
    
};

SharedPtrToy makeSharedPtrToy(std::string inToyName)
{
    SharedPtrToy tmp;
    tmp.setObj(new Toy(inToyName));
    tmp.setRef(new int(1));
    return tmp;
}

class Dog
{
public:

    Dog(std::string inName, int inAge, SharedPtrToy inToy) : name(inName), lovelyToy(inToy)
    {
        if (inAge >= 0 && inAge <= 30)
        {
            age = inAge;
        } 
        else
        {
            age = 0;
        }        
    }
    Dog(std::string inName, int inAge) : Dog(inName, inAge, makeSharedPtrToy("SameToy")) {};
    Dog(int inAge, SharedPtrToy inToy) : Dog("Druzhok", inAge, inToy) {};
    Dog() : Dog("Druzhok", 0, makeSharedPtrToy("SameToy")) {};

private:
    std::string name;
    int age;
    SharedPtrToy lovelyToy;
};



int main()
{
    SharedPtrToy ball = makeSharedPtrToy("Ball");
    SharedPtrToy bone = makeSharedPtrToy("Bone");

    Dog a("Iriska", 1, ball);
    Dog b(2, bone);
    Dog c = a;

    ball.clear();

    Dog d(b);
    Dog e("Sharick", 3);
}