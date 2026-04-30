#include "inscription.h"
#include "personne.h"
#include "ui_inscription.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

#include <QString>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
using namespace std;

Inscription::Inscription(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Inscription)
{
    ui->setupUi(this);

    ui->groupBoxInscription->hide();
    ui->groupBoxDesab->hide();
    ui->groupBoxPrev->hide();
    ui->groupBoxUpdate->hide();

    connect(ui->inscrire, SIGNAL(clicked()), this, SLOT(inscrire()));
    connect(ui->desabonner, SIGNAL(clicked()), this, SLOT(desabonner()));
    connect(ui->update, SIGNAL(clicked()), this, SLOT(updateDonnee()));
    connect(ui->quitter, SIGNAL(clicked()), this, SLOT(quitter()));

    connect(ui->inscrireDel, SIGNAL(clicked()), this, SLOT(inscrireDel()));
    connect(ui->inscrireOK, SIGNAL(clicked()), this, SLOT(inscrireOK()));
    connect(ui->desabonnerDel, SIGNAL(clicked()), this, SLOT(desabonnerDel()));
    connect(ui->desabonnerOK, SIGNAL(clicked()), this, SLOT(desabonnerOK()));
    connect(ui->prendreNomDel, SIGNAL(clicked()), this, SLOT(prendreNomDel()));
    connect(ui->prendreNomOK, SIGNAL(clicked()), this, SLOT(prendreNomOK()));
    connect(ui->updateDel, SIGNAL(clicked()), this, SLOT(updateDel()));
    connect(ui->updateOK, SIGNAL(clicked()), this, SLOT(updateOK()));

    prendreListe();
    afficherListe();
}

void Inscription::prendreListe()
{
    ifstream flux("list.txt");
    string ligne;
    while(getline(flux, ligne))
    {
        string nom, age;
        stringstream ss(ligne);
        getline(ss, nom, ':');
        getline(ss, age);

        Personne p(nom, stoi(age));
        list.push_back(p);
    }
    flux.close();
}

void Inscription::updateListe()
{
    ofstream flux("list.txt");
    for(Personne& p: list)
    {
        flux << p.getNom() << ":" << p.getAge() << endl;
    }
    flux.close();
}

void Inscription::afficherListe()
{
    ui->listWidget->clear();

    for(Personne& p: list)
    {
        QString ligne = "Nom: " + QString::fromStdString(p.getNom()) + "     -      Age: " + QString::number(p.getAge());
        ui->listWidget->addItem(ligne);
    }
}

void Inscription::menuListe()
{

}

//---------------------------------------------------------------------------------
void Inscription::inscrire()
{
    ui->groupBoxInscription->show();
}

void Inscription::inscrireDel()
{
    ui->inscrireNom->clear();
    ui->inscrireAge->clear();
    ui->groupBoxInscription->hide();
}

void Inscription::inscrireOK()
{
    string nom;
    int age;

    nom = ui->inscrireNom->text().toStdString();
    age = ui->inscrireAge->text().toInt();
    Personne p(nom, age);
    list.push_back(p);
    
    updateListe();
    afficherListe();
    ui->inscrireNom->clear();
    ui->inscrireAge->clear();
    ui->groupBoxInscription->hide();
}

//--------------------------------------------------------------------------------------
void Inscription::desabonner()
{
    ui->groupBoxDesab->show();
}

void Inscription::desabonnerDel()
{
    ui->desabonnerNom->clear();
    ui->groupBoxDesab->hide();
}

void Inscription::desabonnerOK()
{
    string nom;
    nom = ui->desabonnerNom->text().toStdString();

    auto it = find_if(list.begin(), list.end(), [&](Personne p){return p.getNom()==nom;});
    if(it!=list.end())
    {
        list.erase(it);
        updateListe();
        afficherListe();
    }
    else
    {
        ui->desabonnerNom->clear();
        ui->desabonnerNom->clear();
        QMessageBox::information(this, "Erreur", "Pas trouvé");
    }
    ui->groupBoxDesab->hide();
}

//--------------------------------------------------------------------------------------
void Inscription::updateDonnee()
{
    ui->groupBoxPrev->show();
}

void Inscription::prendreNomDel()
{
    ui->prendreNom->clear();
    ui->groupBoxPrev->hide();
}

void Inscription::prendreNomOK()
{
    string nom;
    nom = ui->prendreNom->text().toStdString();
    auto it = find_if(list.begin(), list.end(), [&](Personne &p){return p.getNom()==nom;});
    if(it!=list.end())
    {
        temp=nom;
        ui->updateNom->setText(QString::fromStdString(it->getNom()));
        ui->updateAge->setText(QString::number(it->getAge()));

        ui->prendreNom->clear();
        ui->groupBoxPrev->hide();
        ui->groupBoxUpdate->show();
    }
    else
    {
        ui->prendreNom->clear();
        QMessageBox::information(this, "Erreur", "Pas trouvé");
        ui->groupBoxPrev->hide();
    }
}

void Inscription::updateDel()
{
    ui->updateNom->clear();
    ui->updateAge->clear();
    ui->groupBoxUpdate->hide();
}
void Inscription::updateOK()
{
    string nom;
    int age;

    nom = ui->updateNom->text().toStdString();
    age = ui->updateAge->text().toInt();

    auto it = find_if(list.begin(), list.end(), [&](Personne &p){return p.getNom()==temp;});
    if(it!=list.end())
    {
        it->setNom(nom);
        it->setAge(age);
    }
    
    updateListe();
    afficherListe();
    ui->updateNom->clear();
    ui->updateAge->clear();
    ui->groupBoxUpdate->hide();
}

//--------------------------------------------------------
void Inscription::quitter()
{
    if(QMessageBox::question(this, "Quitter", "Voulez-vouos vraiment quitter?")==QMessageBox::Yes)
    {
        close();
    }
}

Inscription::~Inscription()
{
    delete ui;
}
