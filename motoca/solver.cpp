#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pessoa {
    int idade;
    std::string nome; 

    Pessoa (int idade, std::string nome = "") :
        idade{idade}, nome{nome} {
    }

    friend std::ostream& operator<<(std::ostream& os, const Pessoa& pessoa) {
        os << "Nome: " << pessoa.nome << "\n";
        os << "Idade: " << pessoa.idade << ".";
        return os;
    }

};


struct Motoca {
    Pessoa* pessoa;
    int power;
    int time;

    Motoca (int power = 0, int time = 0, Pessoa* pessoa = nullptr) :
        power{power}, pessoa{pessoa}, time{time} {
    }

    bool inserirPessoa (Pessoa* pessoa) {
        if(this->pessoa != nullptr) {
            std::cout << "A moto esta ocupada\n";
            return false;
        } else if (pessoa->idade > 10) {
            std::cout << "Não tem idade para subir na moto\n";
        }
        return true;
    }

    Pessoa* descer () {
        if(this->pessoa == nullptr) {
            std::cout << "Não tem pessoa na motoca \n";
            return nullptr;
        } 
        return std::exchange(this->pessoa, nullptr);
    }

    bool buyTime (int time) { 
        if (inserirPessoa(pessoa)){
            return true;
        } else {
            std::cout << "Não é possivel comprar tempo, a moto esta ocupada!\n";
            return false;
        }
    }

    void drive (int time, int power) {
        if(time != 0 && pessoa->idade > 10) {
            std::cout << "Pode passear na moto\n";
            buzinar(power);
        } else if (time == 0) {
            std::cout << "O passeio acabou\n";
        } else {
            std::cout << "Velho demais para a motoca\n";
        }
    }

    void buzinar (int power) {
        vector<char> e = { };

        if (power != 0) {
            for (int i = 0; i < power; i++) {
                e[i] = {'e'};
            }
            std::cout << "P";
            for (int f = 0; f < power; f++) {
                std::cout << e[f];
            }
            std::cout << "m";
        }
    }

};



int main () {
    
    Pessoa pessoa(6, "Matheus");
    Motoca motoca(1, 1, &pessoa);

    std::cout << pessoa.nome << "\n";
    std::cout << motoca.pessoa->nome << "\n";

    return 0;

   /*
   vector<int> int_vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    for (const auto &item : int_vec) {
        cout << item << "; ";
    }
    cout << endl;

    return EXIT_SUCCESS;
    */
};