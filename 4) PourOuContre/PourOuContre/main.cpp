/******************************************************************************

                            Le vote pour ou contre

*******************************************************************************/
using namespace std;
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>

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

unsigned comptOccurence(vector<int> & tab, int & nb) // Compte l'occurence du chiffre "nb" dans le vetor "tab"
{
    unsigned cpt = 0;
    for( unsigned i = 0; i < tab.size(); ++i )
    {
        if(tab[i] == nb)
        {
            ++cpt;
        }
    }
    return cpt;
}

unsigned indiceGagnant(vector<int> & resultatVote)
{
    int max, imax;
    max = resultatVote[1];  // Valeure maxiamle (score du gagnant)
    imax = 1;   // Indice de la valeure maximale (indice du gagnant)

    for ( unsigned i = 1; i < resultatVote.size(); ++i ) // Parcour le tableau final pour trouver le gagnant
    {
        cout << "Candidat " << i << " : " << resultatVote[i] << endl;    // Affiche le tableau

        if ( max < resultatVote[i] )        // Si le nb de vote est plus grand
        {
            max = resultatVote[i];      // J'actualise le nb de vote
            imax = i;                   // Et l'indice du gagnant.
        }
    }
    return imax;
}

vector<int> votePourContre(vector<vector<unsigned>> & tab)
{
    vector<int> resultatVote;
    resultatVote ={ -1, 0, 0, 0, 0 }; // Tableaux de résultats, l'indice 0 ne corespond à aucun candidats

    for( unsigned i = 0; i < tab.size(); ++i )  // Parcours tout les tableaux de vote des candidats
    {
        for( unsigned j = 0; j < tab.size(); ++j ) // Parcours les cellules. Si j==0 c'est un vote "pour" ; Si j==1 c'est un vote "contre"
        {
            if (j==0)   // Si c'est un vote "pour" :
            {
                resultatVote[ tab[i][j] ] += 2;     // On ajoute 2
            }
            else if (j==1)  // Si c'est un vote "contre"
            {
                resultatVote[ tab[i][j] ] -= 1;     // On enlève 1
            }
        }
    }
    return resultatVote;
}


int main()
{
    vector<vector<unsigned>> liste_vote;
    liste_vote = inputToTabTabUnsigned();

    vector<int> resultatVote;
    int imax, max; // indice et score du gagnant
    resultatVote = votePourContre(liste_vote);
    imax = indiceGagnant(resultatVote);
    max = resultatVote[imax];

    if (comptOccurence(resultatVote,max) == 1)  // Si il n'y a pas d'égalité
    {
            cout << "Le gagnant est le candidat " << imax << "." <<endl;
    }
    else    // Si il y a une égalité
    {
        cout << "Il y a une égalité, il faut refaire le vote" << endl;
    }

    return 0;
}



