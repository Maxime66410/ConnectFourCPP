#include <iostream>

/* Permet de afficher le tableau du jeu */
void showBoard(int tab[6][7])
{
    for(int i = 0; i < 7; i++)
    {
        std::cout << i+1 << " ";
    }
    std::cout << std::endl;
    
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            switch(tab[i][j])
            {
            case 0:
                std::cout << (char)254;
                break;
            case 1:
                std::cout << "X";
                break;
            case 2:
                std::cout << "O";
                break;
            default:
                std::cout << "?";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

/* Permet de vérifier si il y a un gagnant */
bool checkLineIsWin(int tab[6][7], int currentPlayer)
{
    currentPlayer++;
    int ligne;

    // Vérification de la victoire horizontale de gauche à droite (-3 & +3)
    for (ligne = 0; ligne < 6; ligne++) {
        for (int colonne = 0; colonne <= 3; colonne++) {
            if (tab[ligne][colonne] == currentPlayer &&
                tab[ligne][colonne + 1] == currentPlayer &&
                tab[ligne][colonne + 2] == currentPlayer &&
                tab[ligne][colonne + 3] == currentPlayer) {
                return true;
                }
        }
    }
    
    // Vérification de la victoire verticale en allant vers le bas
    for (ligne = 0; ligne <= 2; ligne++) {
        for (int colonne = 0; colonne < 7; colonne++) {
            if (tab[ligne][colonne] == currentPlayer &&
                tab[ligne + 1][colonne] == currentPlayer &&
                tab[ligne + 2][colonne] == currentPlayer &&
                tab[ligne + 3][colonne] == currentPlayer) {
                return true;
                }
        }
    }

    // Vérification de la victoire en diagonale (vers le haut à droite)
    for (ligne = 3; ligne < 6; ligne++) {
        for (int colonne = 0; colonne <= 3; colonne++) {
            if (tab[ligne][colonne] == currentPlayer &&
                tab[ligne - 1][colonne + 1] == currentPlayer &&
                tab[ligne - 2][colonne + 2] == currentPlayer &&
                tab[ligne - 3][colonne + 3] == currentPlayer) {
                return true;
                }
        }
    }

    // Vérification de la victoire en diagonale (vers le bas à droite)
    for (ligne = 0; ligne <= 2; ligne++) {
        for (int colonne = 0; colonne <= 3; colonne++) {
            if (tab[ligne][colonne] == currentPlayer &&
                tab[ligne + 1][colonne + 1] == currentPlayer &&
                tab[ligne + 2][colonne + 2] == currentPlayer &&
                tab[ligne + 3][colonne + 3] == currentPlayer) {
                return true;
                }
        }
    }
    
    return false;
}

/* Game Instance */
int main(int argc, char* argv[])
{
    int tab[6][7] = {{0}}; // 0 = case vide, 1 = joueur 1, 2 = joueur 2
    int currentPlayer = 0, cptTour = 0; // 0 = joueur 1, 1 = joueur 2
    while (cptTour < 42)
    {
        showBoard(tab);
        
        // Demander la colonne au joueur actuel
        int col;
        std::cout << "Joueur " << ((currentPlayer == 0) ? "X" : "O") <<", choisissez une colonne : ";
        std::cin >> col; std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        col--;

        // Clear le terminal
        system("cls");  // NOLINT(concurrency-mt-unsafe)

        // Si l'enfant a choisi une colonne qui n'existe pas
        if (col < 0 || col > 6)
        {
            std::cout << "La colonne n'existe pas !" << std::endl;
            continue;
        }

        int isColFull = 5; // Si la colonne est pleine, elle vaudra 5
        
        // Mettre le pion dans la colonne
        for (int i = 5; i >= 0; i--)
        {
            if (tab[i][col] == 0)
            {
                isColFull--;
                switch (currentPlayer)
                {
                    case 0:
                        tab[i][col] = 1;
                    break;
                    case 1:
                        tab[i][col] = 2;
                    break;
                    default:
                        tab[i][col] = 4;
                }
                break;
            }
        }

        // Si la colonne est pleine
        if(isColFull == 5)
        {
            std::cout << "La colonne est pleine !" << std::endl;
            continue;
        }

        if (checkLineIsWin(tab, currentPlayer))
        {
            std::cout << "Le joueur " << ((currentPlayer == 0) ? "X" : "O") << " a gagner !" << std::endl;
            return 0;
        }
        
        currentPlayer = (currentPlayer == 0) ? 1 : 0;
        cptTour++;
    }

    // Si le tour est supérieur à 42, c'est qu'il n'y a pas de gagnant
    std::cout << "Match nul !" << std::endl;
    
    return 0;
}
