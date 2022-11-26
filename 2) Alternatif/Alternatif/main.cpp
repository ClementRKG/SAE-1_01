#include <vector>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

vector<vector<unsigned>> inputToTabTabUnsigned() // Transforme les fichiers 'votants.txt' en un tableau d'entiers naturels.
{
    ifstream ifs;
    string ligne;
    string temporaire;
    vector<vector<unsigned>> tabTabUnsigned;
    vector<unsigned> tabUnsigned;
    unsigned cpt = 0;

    while (true)
    {
        ++cpt;
        getline(cin, ligne);
        if (cpt%3 == 0 && cpt != 0) // Récupère les votes ( une ligne sur 3 )
        {
            for(unsigned i = 0; i < ligne.size(); ++i)  // Ajoute chaque chiffre séparé par des virgules
                                                        // dans un tableau d'entier naturel
            {
                if(ligne[i] != ',')
                {
                    temporaire += ligne[i];
                }
                else if(ligne[i] == ',')
                {
                    tabUnsigned.push_back(stoul(temporaire));
                    temporaire = "";
                }
            }
            tabUnsigned.push_back(stoul(temporaire));
            temporaire = "";

            tabTabUnsigned.push_back(tabUnsigned);  // Ajoute le tableau avec les 4 votes d'un votant dans
                                                    // le grand tableau de tableau d'entier naturel
            tabUnsigned = {};
        }
        if (cin.eof()) break ;  // Sort à la fin du fichier
    }
    return tabTabUnsigned;
}

vector<unsigned> comptageVote(vector<vector<unsigned>> & tableau){ // compte les voix en ne regardant que le premier élément de chaque vecteurs.
    vector<unsigned> depouille (4);
    for (size_t i = 0; i<tableau.size(); ++i){
        if (tableau[i].size() == 0) continue;
        else{depouille[tableau[i][0]-1] = depouille[tableau[i][0]-1]+1;}
    }
    return depouille;
}

vector<unsigned> TrouverMax(vector<unsigned> & tableau){ // trouve le maximum (1) et son indice (0).
    unsigned max = tableau[0];
    unsigned indice = 0;
    for (size_t i = 0; i < tableau.size(); ++i){
        if (tableau[i] > max){
            max = tableau[i];
            indice = i;
        }
    }
    vector<unsigned> resultat {indice,max};
    return resultat;
}

unsigned TrouverMin(const vector<unsigned> & tableau){ // trouve le minimum et renvoie son indice en excluant tous les minimum de zéro, sinon le vote ne marcherais pas.
    unsigned min;
    unsigned indice (tableau.size());
    for (size_t i = 0; i<tableau.size(); ++i){ // permet d'être sûr que la valeur minimal initialisée n'est pas 0 car si on met simplemen min = tableau[0] si tableau[0] vaut 0 bah ça casse tout
        if (tableau[i] != 0){
            min = tableau[i];
            indice = i;
            break;
        }
    }
    for (size_t i = 0; i < tableau.size(); ++i){
        if (tableau[i] < min and tableau[i] !=0){
            min = tableau[i];
            indice = i;
        }
    }
    unsigned resultat = indice;
    return resultat;
}

unsigned ComptageTotal(vector<unsigned> & tableau){ // renvoie l'addition de toute les valeurs d'un vecteur.
    unsigned total = 0;
    for (size_t i = 0; i<tableau.size();++i)
        {total = total + tableau[i];}
    return total;
}

void redistributionDesVotesDuDernier(vector<vector<unsigned>> & listeVote, unsigned dernier){ //si le premier élément du vecteur est équivalent au dernier (celui le moins voté), supprime l'élément
    for (size_t i = 0; i< listeVote.size() ; ++i){
        if (listeVote[i][0] == dernier and listeVote[i].size()>0)
            listeVote[i].erase(listeVote[i].begin()+0);
    }
}

unsigned voteAlternatif(vector<vector<unsigned>> & listeVoteDeBase){
    vector<vector<unsigned>> listeVoteActuelle = listeVoteDeBase;
    vector<unsigned> elimine; // vecteur comprenant la liste des candidats éliminé, permet de ne pas les compter au comptage si quelqu'un est éliminé.
    while (true){
        vector<unsigned> VoteCompte = comptageVote(listeVoteActuelle); // compte les premiers éléments de chaque vecteurs et les mets dans un vecteur de taille 4
        vector<unsigned> elu = TrouverMax(VoteCompte); // trouve l'indice en 0 et le maximum en 1 dans le vecteur VoteCompté
        unsigned dernier = TrouverMin(VoteCompte); // trouve l'indice en 0 et le minimum en 1 dans le vecteur VoteCompté
        unsigned total = ComptageTotal(VoteCompte); // compte le nombre total de voix, permet de savoir si l'élu est élu a la majorité
        vector<unsigned> doublon = {};

        for (size_t i = 0; i<4 ; ++i) // cette boucle permet de mettre les doublons dans un vecteurs si il y en a
        {
            if (VoteCompte[i] == elu[1] and i != elu[0])
                doublon.push_back(i);
        }
        if (doublon.size()> 0) //si il y a un ou plusieurs doublons, l'elu est rajouté dans la liste de doublons et ça affiche les doublons
        {
            doublon.push_back(elu[0]);
            redistributionDesVotesDuDernier(listeVoteActuelle,dernier+1);
            continue;
        }
        if (elu[1] >= total-elu[1]) return elu[0]+1; // si cette condition est vraie, l'elu a au moins la moitié des voies et est donc élu
        else
        {
            redistributionDesVotesDuDernier(listeVoteActuelle, dernier+1);
            continue;
        }
    }
    return 0;
}

int main()
{
    vector<vector<unsigned>> liste_votant;
    liste_votant = inputToTabTabUnsigned();
    cout << "Le gagnant est le candidat " << voteAlternatif(liste_votant) << endl;
}
