#include <iostream>

using namespace std;
// BUSCA
bool existe (int vet[], int size, int value) {

    for (int i = 0; i < size; i++) {
        if(vet[i] == value)
            return true;    
    }
    return false;
}

int contar (int vet[], int size, int value) {

    int contador = 0;
    for (int i = 0; i < size; i++) {
        if (vet[i] == value) {
            contador = contador + 1;
        }
    }
    return contador;
}

int procurar_valor (int vet[], int size, int value) {

    int posicao;
    for (int i = 0; i < size; i++) {
        if (vet[i] == value) {
            posicao = i;
            break;
        } else {
            posicao = -1;
        }
    }
    return posicao;
}

int procurar_valor_apartir (int vet[], int size, int inicio, int value) {

    int posicao;
    for (int i = inicio; i < size; i++) {
        if (vet[i] == value) {
            posicao = i;
            break;
        } else {
            posicao = -1;
        }
    }
    return posicao;
}

// MELHOR CASO

int procurar_menor (int vet[], int size) {

    int menor {0};
    menor = vet[0];
    for (int i = 0; i < size; i++) {
        if(vet[i] < menor){
            menor = vet[i];
        } 
    }
    return menor;
}

int procurar_menor_pos (int vet[], int size) {

    int menor {0};
    int posicao {0};
    menor = vet[0];
    for (int i = 0; i < size; i++) {
        if(vet[i] < menor){
            posicao = i;
        } 
    }
    return posicao;
}

int procurar_menor_pos_apartir (int vet[], int size, int inicio) {

    int menor {0};
    int posicao;
    for (int i = inicio; i < size; i++) {
        if (vet[i] < menor) {
            posicao = i;
            break;
        } else {
            posicao = -1;
        }
    }
    return posicao;
}

int procurar_melhor_se (int vet[], int size) {

    int menor {0};
    int posicao {0};
    menor = vet[0];
    for (int i = 0; i < size; i++) {
        if(vet[i] < menor && vet[i] > 0){
            posicao = i;
        } 
    }
    return posicao;
}
//CONTAGEM 

float calcular_stress_medio (int vet[], int size) {

    float soma {0};
    for (int i = 0; i < size; i++ ) {
        soma = soma + vet[i];
    }
    float media = soma / size;
    return media;
}

string mais_homens_ou_mulheres (int vet[], int size) {

    int homem{0};
    int mulher{0};
    string retorno = "Empate";
    for (int i = 0; i < size; i++) {
        if (vet[i] > 0) {
            homem = homem + 1;
        } else if (vet[i] < 0) {
            mulher = mulher + 1;
        }
    }
    if (homem == mulher) {
        retorno = "Empate";
        return retorno;
    } else if ( homem > mulher) {
        retorno = "homens";
        return retorno;
    } else if (mulher > homem) {
        retorno = "mulheres";
        return retorno;
    }
}

string metade_homens_ou_mulheres (int vet[], int size) {
    
    string retorno;
    unsigned int acumulador {0};
    unsigned int acumuladorP {0};
    int metade {0};
    metade = size / 2;

    for (int i = 0; i < metade; i++) {
         acumulador = acumulador + vet[i]; 
    }   
    
    for (int i = metade; i < size; i++) {
        acumuladorP = acumuladorP + vet[i];
    }
    

    if (acumulador > acumuladorP) {
        retorno = "Primeira";
        return retorno;
    } else if (acumulador < acumuladorP) {
        retorno = "Segunda";
        return retorno;
    } else if (acumulador = acumuladorP) {
        retorno = "Empate";
        return retorno;
    }

}

string homens_sao_mais_estressados_que_mulheres (int vet[], int size) {

    unsigned int stressH {0};
    unsigned int stressM {0};
    string retorno = "Empate";
    for (int i = 0; i < size; i++) {
        if (vet[i] > 0) {
            stressH = stressH + vet[i];
        } else if (vet[i] < 0) {
            stressM = stressM + vet[i];
        }
    }
    if (stressH == stressM) {
        retorno = "O estresse eh o mesmo";
        return retorno;
    } else if ( stressH > stressM) {
        retorno = "homens sao mais estressados";
        return retorno;
    } else if (stressM > stressH) {
        retorno = "mulheres sao mais estressadas";
        return retorno;
    }
}

int main ()
{

    int x = 6;
    int vetor[x] = {5, 3, -1, -50, -1, -99};
    
    int m = procurar_melhor_se(vetor, x);
    std::cout << m;
}