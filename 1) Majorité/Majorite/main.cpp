#include <vector>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

vector<unsigned> inputToTabUnsigned() // Transforme les fichiers 'votants.txt' en un tableau d'entiers naturels.
{
    ifstream ifs;
    string ligne;
    vector<unsigned> tabUnsigned;
    unsigned cpt = 0;
    while (true)
    {
        ++cpt;
        getline(cin, ligne);
        if (cpt%3 == 0 && cpt != 0) // Récupère les votes ( une ligne sur 3 )
        {
            tabUnsigned.push_back(stoul(ligne));    // Transforme les votes (str) en unsigned et les ajoutes au tableau
        }
        if (cin.eof()) break ;  // Sort à la fin du fichier
    }
    return tabUnsigned;
}

vector<unsigned> comptageVote(vector<unsigned> tab){
    vector<unsigned> depouille (4);
    for (unsigned i = 0; i<tab.size(); ++i){
        depouille[tab[i]-1] = depouille[tab[i]-1]+1;
    }
    return depouille;
}

void affichageResultat(vector<unsigned> depouillage){
    unsigned elus = 0;
    unsigned total =0;
    unsigned max = depouillage[0];
    vector<unsigned> doublon;
    for (unsigned i = 0; i<depouillage.size(); ++i){
        total = total + depouillage[i];
    }
    cout << "Le candidat " << 1 << " a obtenue " << depouillage[0] << " voix" << endl;
    for (unsigned i=1; i<4; ++i){
        if (depouillage[i]>max){
            max=depouillage[i];
            elus = i;
        }
        cout << "Le candidat " << i+1 << " a obtenue " << depouillage[i] << " voix" << endl;
    }
    for (unsigned i =0; i<4;++i){
        if (i != elus and depouillage[i]==max){
            doublon.push_back(i);
        }
    if (doublon.size()>0){
        doublon.push_back(elus);
        cout << "Les candidats ";
        for (unsigned i =0; i<doublon.size(); ++i){
            cout << doublon[i]+1 <<" ";
        }
        cout << "sont à égalité, il faut refaire un vote entre eux." << endl;
        break;
        }
    }
    if (doublon.size()==0) {
        cout << "Le candidat " << elus+1 << " est elus avec le plus de voix." << endl;
    }
}

int main(){
    vector<unsigned> liste_vote;
    liste_vote = inputToTabUnsigned();
    vector<unsigned> depouille;
    depouille = comptageVote(liste_vote);
    affichageResultat(depouille);
}
