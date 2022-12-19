#include <iostream>
#include <vector>

using namespace std;

// Function to check if two or more characters are next to each other
// in the game grid
bool areCharactersAdjacent(vector<vector<char>> game, char c1, char c2) {
  int rows = game.size();
  int cols = game[0].size();

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // Check if current character is c1 or c2
      if (game[i][j] == c1 || game[i][j] == c2) {
        // Check if c1 or c2 is present in any of the 8 adjacent cells
        if ((i > 0 && game[i-1][j] == c1) || (i > 0 && game[i-1][j] == c2) ||
            (i < rows-1 && game[i+1][j] == c1) || (i < rows-1 && game[i+1][j] == c2) ||
            (j > 0 && game[i][j-1] == c1) || (j > 0 && game[i][j-1] == c2) ||
            (j < cols-1 && game[i][j+1] == c1) || (j < cols-1 && game[i][j+1] == c2)) {
          return true;
        }
      }
    }
  }

  return false;
}

int main() {
  // Test the function with a sample game grid
  vector<vector<char>> game = {{'X', 'O', 'X'},
                               {'O', 'X', 'O'},
                               {'X', 'O', 'X'}};

  char c1 = 'X';
  char c2 = 'O';

  if (areCharactersAdjacent(game, c1, c2)) {
    cout << "Characters " << c1 << " and " << c2 << " are adjacent." << endl;
    chooseattack ();
  } else {
    cout << "Characters " << c1 << " and " << c2 << " are not adjacent." << endl;
    healteammate ();
  }

  return 0;
}
