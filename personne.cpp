#include "personne.h"
using namespace std;

Personne::Personne(string n, int a)
{
    nom=n;
    age=a;
}

string Personne::getNom()
{
    return nom;
}

void Personne::setNom(string n)
{
    nom=n;
}

int Personne::getAge()
{
    return age;
}

void Personne::setAge(int a)
{
    age=a;
}

Personne::~Personne() {}
