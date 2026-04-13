#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

struct Pessoa{
    string nome;
    list <string> datas;
};

string inverte_data(const string &data){
    string dia = data.substr(0,2);
    string mes = data.substr(2,2);
    string ano = data.substr(4,2);
    int anoCurto = stoi(ano);
    int yyyy = (anoCurto <= 26) ? 2000 + anoCurto : 1900 + anoCurto;

    return to_string(yyyy) + mes + dia;
}

int main(void){
    ifstream arq("arquivo.txt");
    list<Pessoa> pessoas;
    string linha;

    if(!arq){
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    while(getline(arq, linha)){
        Pessoa p;
        string numeros = "";

        for(char c : linha){
            if(isalpha(c)){
                p.nome += c;
            } else if(isdigit(c)){
                numeros += c;
            }
        }

        for(int i = 0; i < numeros.size(); i += 6){
            p.datas.push_back(numeros.substr(i, 6));
        }

        pessoas.push_back(p);
    }

    arq.close();

    for(auto &p: pessoas){
        p.datas.sort([](string a, string b){
            return inverte_data(a) < inverte_data(b);
        });
    }

    pessoas.sort([](Pessoa a , Pessoa b){
        return a.nome < b.nome;
    });

    for(auto &p : pessoas){
        cout << p.nome << ':';
        for(auto d : p.datas){
            cout << d << " ";
        }
        cout << endl;
    } 

    return 0;
}