#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QMainWindow>
#include <vector>
#include "personne.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class Inscription;
}
QT_END_NAMESPACE

class Inscription : public QMainWindow
{
    Q_OBJECT

public:
    Inscription(QWidget *parent = nullptr);
    void prendreListe();
    void updateListe();
    void afficherListe();
    void menuListe();
    ~Inscription();

private slots:
    void inscrire();
    void desabonner();
    void updateDonnee();
    void quitter();

    void inscrireDel();
    void inscrireOK();
    void desabonnerDel();
    void desabonnerOK();
    void prendreNomDel();
    void prendreNomOK();
    void updateDel();
    void updateOK();

    void menuDansListe(QPoint pos);

private:
    Ui::Inscription *ui;
    vector <Personne> list;
    string temp;
};
#endif // INSCRIPTION_H
