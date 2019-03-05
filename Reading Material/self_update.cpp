class Updatable
{
public:
    virtual void update() = 0;
};

class SomeClass : public Updatable
{
public:
    virtual void update()
    {
        printf("update for SomeClass was called\n");
    }
};

class AnotherClass : public Updatable
{
public:
    virtual void update()
    {
        printf("update for AnotherClass was called\n");
    }
};

int main()
{
    Updatable* v[10];
    int n = 0;
    SomeClass a, b;
    AnotherClass c, d;
    v[n++] = &a;
    v[n++] = &b;
    v[n++] = &c;
    v[n++] = &d;

    for (int i = 0; i < n; i++)
        v[i]->update();
}

///////////Alternate Version

class base 
{ 
public: 
    virtual void print () 
    { cout<< "print base class" <<endl; } 
  
    void show () 
    { cout<< "show base class" <<endl; } 
}; 
  
class derived:public base 
{ 
public: 
    void print () 
    { cout<< "print derived class" <<endl; } 
  
    void show () 
    { cout<< "show derived class" <<endl; } 
}; 
  
int main() 
{ 
    base *bptr; 
    derived d; 
    bptr = &d; 
      
    //virtual function, binded at runtime 
    bptr->print();  
      
    // Non-virtual function, binded at compile time 
    bptr->show();  
}


