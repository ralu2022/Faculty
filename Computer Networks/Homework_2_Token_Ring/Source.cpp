//1. Token Ring
//
//Se simuleaza 6 calculatoare('A', 'B', 'C', 'D', 'E', 'F') conectate ciclic printr - un "Token Ring", in aceasta ordine. (Calculatoarele pot fi hardcodate)
//Se introduce de la tastatura / fisier date pe care calculatoarele vor sa le trimita pe retea.
//Se creaza un token care va circula prin retea pana cand trebuie sa transporte date. (calculatoarele ridica un flag)
//Se simuleaza urmatoarele transferuri de date : C->E, F->B, A->D, E->A, B->C, D->F, unde flagurile sunt ridicate in aceasta ordine.
//Se doreste afisarea mesajelor atat la transferul de date catre token cat si la sosirea acestuia la un potential destinatar.
//Indicatie : OOP

// Pentru implementare avem nevoie de 2 clase: 
//         * clasa Computer care se ocupa de informatii privind calculatoarele din retea
//                             * definirea lor
//                             * modul de semnalizarea a faptului ca se doreste trimiterea unui mesaj (ridicarea unui steag)
//                             * receptionarea unui mesaj
//         * clasa Retea care se ocupa cu: 
//                             * adaugarea calculatoarelor in retea
//                             * functionarea retelei


#include <iostream>
#include <string>

class Calculator {
public:
    char nume;
    bool steag;
    Calculator* next;
    std::pair<char, std::string> mesaj;

    Calculator(char nume) {
        this->nume = nume;
        this->steag = false;
        this->next = nullptr;
    }

    void ridicareSteag(char destinatie, std::string data) {
        this->steag = true;
        this->mesaj = std::make_pair(destinatie, data);
        std::cout << "Steag ridicat de calculatorul " << this->nume << " si doreste transmiterea mesajului " << data << " catre " << destinatie << "\n";
    }

    void receptieMesaj(std::pair<char, std::string> data) {
        if (data.first == this->nume) {
            std::cout << "Mesajul a fost receptionat de: " << this->nume << "\n" << "\n";
            this->steag = false;
        }
       
    }

};

class Retea {
private:
    Calculator* inceputRetea;
    Calculator* sfarsitRetea;
public:
    Retea() {
        inceputRetea = nullptr;
        sfarsitRetea = nullptr;
    }

    void adaugareCalculatorInRetea(Calculator* calculator) {
        if (inceputRetea == nullptr) {
            inceputRetea = calculator;
            sfarsitRetea = calculator;
        }
        else {
            sfarsitRetea->next = calculator;
            calculator->next = inceputRetea;
            sfarsitRetea = calculator;
        }
    }

    void pasareToken() {
        Calculator* curent = inceputRetea;

        do {
            if (curent->steag) {
                std::cout << "Token-ul contine mesaj de la calculatorul:  " << curent->nume << "\n";

                if (curent->mesaj.first == curent->nume) {
                    curent->receptieMesaj(curent->mesaj);
                    curent->steag = false;
                }
                else {

                    Calculator* destinatar = curent->next;
                    while (destinatar != curent) {
                        if (destinatar->nume == curent->mesaj.first) {
                            destinatar->receptieMesaj(curent->mesaj);
                            curent->steag = false;
                            break;
                        }
                        destinatar = destinatar->next;
                    }
                    if (destinatar == curent) {
                        std::cout << "Mesajul nu poate fi livrat. Destinatarul nu este gasit in retea.\n";
                        curent->steag = false;
                    }
                }
            }
            curent = curent->next;
        } while (curent != inceputRetea);
    }

};

int main() {
    Retea network;
    Calculator* A = new Calculator('A');
    Calculator* B = new Calculator('B');
    Calculator* C = new Calculator('C');
    Calculator* D = new Calculator('D');
    Calculator* E = new Calculator('E');
    Calculator* F = new Calculator('F');

    network.adaugareCalculatorInRetea(A);
    network.adaugareCalculatorInRetea(B);
    network.adaugareCalculatorInRetea(C);
    network.adaugareCalculatorInRetea(D);
    network.adaugareCalculatorInRetea(E);
    network.adaugareCalculatorInRetea(F);

    char destinatie;
    std::string data;

    std::cout << "Introduceti mesajul transmis de la computerul C catre E: ";
    std::getline(std::cin, data);
    C->ridicareSteag('E', data);
    network.pasareToken();

    std::cout << "Introduceti mesajul transmis de la computerul F catre B: ";
    std::getline(std::cin, data);
    F->ridicareSteag('B', data);
    network.pasareToken();

    std::cout << "Introduceti mesajul transmis de la computerul A catre D: ";
    std::getline(std::cin, data);
    A->ridicareSteag('D', data);
    network.pasareToken();

    std::cout << "Introduceti mesajul transmis de la computerul E catre A: ";
    std::getline(std::cin, data);
    E->ridicareSteag('A', data);
    network.pasareToken();

    std::cout << "Introduceti mesajul transmis de la computerul B catre C: ";
    std::getline(std::cin, data);
    B->ridicareSteag('C', data);
    network.pasareToken();

    std::cout << "Introduceti mesajul transmis de la computerul D catre F: ";
    std::getline(std::cin, data);
    D->ridicareSteag('F', data);
    network.pasareToken();



    return 0;
}