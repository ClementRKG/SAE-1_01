/******************************************************************************

                            Le vote par notation

*******************************************************************************/
using namespace std;
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>

vector<vector<unsigned>> inputToTabTabUnsigned() // Transforme les fichiers 'votants.txt' en
                                                 // un tableau de tableau d'entiers naturels.
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

unsigned comptOccurence(vector<float> & tab, float & nb) // Compte l'occurence du chiffre "nb" dans le vetor "tab"
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

float voteParNotation(vector<vector<unsigned>> & tab)
{
    vector<float> resultatVote;
    resultatVote ={ -1, 0, 0, 0, 0 }; // Tableaux de résultats, l'indice 0 ne corespond à aucun candidats

    for( unsigned i = 0; i < tab.size(); ++i )  // Parcours tout les tableaux de vote des candidats
    {
        for( unsigned j = 0; j < tab.size(); ++j ) // Parcours les cellules. j correspond au numéro du candidat -1.
        {
           if (j==0) // Pour le candidat 1 :
           {
               resultatVote[1] += tab[i][j];
           }
           else if (j==1) // Pour le candidat 2 :
           {
                resultatVote[2] += tab[i][j];
           }
           else if (j==2) // Pour le candidat 3 :
           {
                resultatVote[3] += tab[i][j];
           }
           else if (j==3) // Pour le candidat 4 :
           {
                resultatVote[4] += tab[i][j];
           }
        }
    }
    for( unsigned i = 1; i < resultatVote.size(); ++i ) // Parcours le tableau résultat et fait la moyenne
    {
        cout << resultatVote[i]/(tab.size()) << endl;   // Affiche ( à supprimer )
        resultatVote[i] = resultatVote[i]/(tab.size()); // Fait la moyenne
    }
    cout << endl;
    float max, imax;
    max = resultatVote[1];  // Valeure maxiamle (score du gagnant)
    imax = 1;   // Indice de la valeure maximale (indice du gagnant)

    for ( unsigned i = 1; i < resultatVote.size(); ++i ) // Parcour le tableau final pour trouver le gagnant
    {
        if ( max < resultatVote[i] )        // Si le nb de vote est plus grand
        {
            max = resultatVote[i];      // J'actualise le nb de vote
            imax = i;                   // Et l'indice du gagnant.
        }
    }

    if (comptOccurence(resultatVote,max) == 1)  // Si il n'y a pas d'égalité
    {
        return imax;
    }
    else    // Si il y a une égalité
    {
        return 0;
    }
}


int main()
{
    vector<vector<unsigned>> liste_votant;
    liste_votant = inputToTabTabUnsigned();
    unsigned gagnant;
    gagnant = voteParNotation(liste_votant);
    cout << gagnant << endl;

    return 0;
}
