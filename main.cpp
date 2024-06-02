#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <map>

using namespace std;

// Singleton Pattern pentru gestionarea unică a bibliotecii
class Biblioteca;

// Observer Pattern pentru actualizarea autorilor atunci când o carte nouă este adăugată
class Observer {
public:
    virtual void update(const string &carte) = 0;
};

class Autor : public Observer {
private:
    string nume;
    string nationalitate;
    int anul_nasterii;
public:
    Autor(const string &n, const string &nat, int an) : nume(n), nationalitate(nat), anul_nasterii(an) {}

    // Getters
    string getNume() const { return nume; }
    string getNationalitate() const { return nationalitate; }
    int getAnulNasterii() const { return anul_nasterii; }

    // Setters
    void setNume(const string &n) { nume = n; }
    void setNationalitate(const string &nat) { nationalitate = nat; }
    void setAnulNasterii(int an) { anul_nasterii = an; }

    // Metoda pentru afișarea informațiilor despre autor
    void afiseazaInformatii() const {
        cout << "Nume: " << nume << ", Nationalitate: " << nationalitate << ", Anul nasterii: " << anul_nasterii << endl;
    }

    void update(const string &carte) override {
        cout << "Autorul " << nume << " a fost notificat despre adăugarea cărții: " << carte << endl;
    }
};

class Carte {
private:
    string titlu;
    string autor;
    int anul_publicarii;
    string gen;
public:
    Carte(const string &t, const string &a, int an, const string &g) : titlu(t), autor(a), anul_publicarii(an), gen(g) {}

    // Getters
    string getTitlu() const { return titlu; }
    string getAutor() const { return autor; }
    int getAnulPublicarii() const { return anul_publicarii; }
    string getGen() const { return gen; }

    // Setters
    void setTitlu(const string &t) { titlu = t; }
    void setAutor(const string &a) { autor = a; }
    void setAnulPublicarii(int an) { anul_publicarii = an; }
    void setGen(const string &g) { gen = g; }

    // Metoda pentru afișarea informațiilor despre carte
    void afiseazaInformatii() const {
        cout << "Titlu: " << titlu << ", Autor: " << autor << ", Anul publicarii: " << anul_publicarii << ", Gen: " << gen << endl;
    }
};

// Clasa iterator pentru iterat prin carti
class Iterator {
private:
    vector<shared_ptr<Carte>>::iterator current;
    vector<shared_ptr<Carte>>::iterator end;
public:
    Iterator(vector<shared_ptr<Carte>>::iterator start, vector<shared_ptr<Carte>>::iterator end) : current(start), end(end) {}

    bool hasNext() {
        return current != end;
    }

    shared_ptr<Carte> next() {
        return *current++;
    }
};

class Biblioteca {
private:
    vector<shared_ptr<Carte>> carti;
    vector<shared_ptr<Autor>> autori;
    static shared_ptr<Biblioteca> instanta;

    Biblioteca() {}

public:
    static shared_ptr<Biblioteca> getInstanta() {
        if (instanta == nullptr) {
            instanta = shared_ptr<Biblioteca>(new Biblioteca());
        }
        return instanta;
    }

    void adaugaCarte(const shared_ptr<Carte> &carte) {
        carti.push_back(carte);
        for (auto &autor : autori) {
            if (autor->getNume() == carte->getAutor()) {
                autor->update(carte->getTitlu());
            }
        }
    }

    void eliminaCarte(const string &titlu) {
        carti.erase(remove_if(std::begin(carti), std::end(carti),
                               [&titlu](const shared_ptr<Carte> &carte) { return carte->getTitlu() == titlu; }),
                    std::end(carti));
    }

    shared_ptr<Carte> gasesteCarte(const string &titlu) {
        auto it = find_if(std::begin(carti), std::end(carti),
                          [&titlu](const shared_ptr<Carte> &carte) { return carte->getTitlu() == titlu; });
        if (it != std::end(carti)) {
            return *it;
        }
        return nullptr;
    }

    void afiseazaCarti() const {
        for (const auto &carte : carti) {
            carte->afiseazaInformatii();
        }
    }

    void adaugaAutor(const shared_ptr<Autor> &autor) {
        autori.push_back(autor);
    }

    Iterator getIterator() {
        return Iterator(carti.begin(), carti.end());
    }

    vector<shared_ptr<Autor>> getAutori() const {
        return autori;
    }
};

shared_ptr<Biblioteca> Biblioteca::instanta = nullptr;

// Funcție șablon pentru afișarea elementelor dintr-un container
template<typename T>
void afiseazaElemente(const T &container) {
    for (const auto &element : container) {
        element->afiseazaInformatii();
    }
}

// Clasă șablon pentru un catalog de cărți
template<typename T>
class Catalog {
private:
    map<string, T> catalog;
public:
    void adaugaInCatalog(const string &cheie, const T &valoare) {
        catalog[cheie] = valoare;
    }

    T gasesteInCatalog(const string &cheie) {
        return catalog[cheie];
    }

    void afiseazaCatalogul() const {
        for (const auto &element : catalog) {
            element.second->afiseazaInformatii();
        }
    }
};

void afiseazaMeniu() {
    cout << "\nMeniu Biblioteca:\n";
    cout << "1. Adauga o carte\n";
    cout << "2. Elimina o carte\n";
    cout << "3. Gaseste o carte\n";
    cout << "4. Afiseaza toate cartile\n";
    cout << "5. Adauga un autor\n";
    cout << "6. Afiseaza toti autorii\n";
    cout << "0. Iesire\n";
    cout << "Alege o optiune: ";
}

void adaugaCarte(shared_ptr<Biblioteca> &biblioteca) {
    string titlu, autor
    , gen;
    int anul_publicarii;

    cout << "Titlul cartii: ";
    getline(cin, titlu);

    cout << "Autorul cartii: ";
    getline(cin, autor);

    cout << "Anul publicarii: ";
    cin >> anul_publicarii;

    cout << "Genul cartii: ";
    cin.ignore();
    getline(cin, gen);

    auto carte = make_shared<Carte>(titlu, autor, anul_publicarii, gen);
    biblioteca->adaugaCarte(carte);
    cout << "Cartea a fost adaugata cu succes.\n";
}

void eliminaCarte(shared_ptr<Biblioteca> &biblioteca) {
    string titlu;
    cout << "Introdu titlul cartii de eliminat: ";
    cin.ignore();
    getline(cin, titlu);

    biblioteca->eliminaCarte(titlu);
    cout << "Cartea a fost eliminata cu succes.\n";
}

void gasesteCarte(shared_ptr<Biblioteca> &biblioteca) {
    string titlu;
    cout << "Introdu titlul cartii de gasit: ";
    cin.ignore();
    getline(cin, titlu);

    auto carte = biblioteca->gasesteCarte(titlu);
    if (carte) {
        cout << "Cartea a fost gasita:\n";
        carte->afiseazaInformatii();
    } else {
        cout << "Cartea nu a fost gasita.\n";
    }
}

void adaugaAutor(shared_ptr<Biblioteca> &biblioteca) {
    string nume, nationalitate;
    int anul_nasterii;

    cout << "Numele autorului: ";
    getline(cin, nume);
    cin.ignore();
    cout << "Nationalitatea autorului: ";
    getline(cin, nationalitate);
    cin.ignore();
    cout << "Anul nasterii: ";
    cin >> anul_nasterii;

    auto autor = make_shared<Autor>(nume, nationalitate, anul_nasterii);
    biblioteca->adaugaAutor(autor);
    cout << "Autorul a fost adaugat cu succes.\n";
}

void afiseazaAutori(shared_ptr<Biblioteca> &biblioteca) {
    cout << "Autori in biblioteca:\n";
    for (const auto &autor : biblioteca->getAutori()) {
        autor->afiseazaInformatii();
    }
}

int main() {
    auto biblioteca = Biblioteca::getInstanta();
    int optiune;

    do {
        afiseazaMeniu();
        cin >> optiune;

        switch (optiune) {
            case 1:
                adaugaCarte(biblioteca);
                break;
            case 2:
                eliminaCarte(biblioteca);
                break;
            case 3:
                gasesteCarte(biblioteca);
                break;
            case 4:
                biblioteca->afiseazaCarti();
                break;
            case 5:
                adaugaAutor(biblioteca);
                break;
            case 6:
                afiseazaAutori(biblioteca);
                break;
            case 0:
                cout << "Iesire.\n";
                break;
            default:
                cout << "Optiune invalida. Te rog sa incerci din nou.\n";
        }
    } while (optiune != 0);

    return 0;
}
