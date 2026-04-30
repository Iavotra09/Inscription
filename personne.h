#ifndef PERSONNE_H
#define PERSONNE_H

#include <string>
using namespace std;

class Personne
{
private:
    string nom;
    int age;

public:
    Personne(string n, int a);
    string getNom();
    void setNom(string n);
    int getAge();
    void setAge(int a);
    ~Personne();
};

#endif
