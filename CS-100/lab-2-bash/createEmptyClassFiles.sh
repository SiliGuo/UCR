#!/bin/sh
touch $1".cc"
touch $1".hh"
echo "#ifndef MyClass_hh
#define MyClass_hh

Class MyClass
{
  public:
    MyClass();
    ~MyClass();

  private:
};
#endif" >> $1.hh
echo "#include \"./$1.hh\"

MyClass::MyClass()
{}

MyClass::~MyClass()
{}" >> $1.cc
