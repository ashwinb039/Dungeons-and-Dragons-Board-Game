#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Player {
public:
    string name;
    int health;
    int attackPower;
    int defensePower;
    int x, y;

    Player(string n, int h, int a, int d, int startX, int startY)
        : name(n), health(h), attackPower(a), defensePower(d), x(startX), y(startY) {}

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void attack(Player& other) {
        int damage = max(0, attackPower - other.defensePower);
        other.health -= damage;
        if (other.health < 0) other.health = 0;
    }

    bool isAlive() const {
        return health > 0;
    }
};

class Board {
public:
    vector<vector<char>> grid;
    int width, height;

    Board(int w, int h) : width(w), height(h) {
        grid.resize(height, vector<char>(width, '.'));
    }

    void placePlayer(const Player& player) {
        grid[player.y][player.x] = 'P';
    }

    void printBoard() const {
        for (const auto& row : grid) {
            for (char cell : row) {
                cout << cell << ' ';
            }
            cout << endl;
        }
    }
};

void battle(Player& p1, Player& p2) {
    cout << p1.name << " attacks " << p2.name << endl;
    p1.attack(p2);
    if (!p2.isAlive()) {
        cout << p2.name << " has been defeated!" << endl;
        return;
    }
    cout << p2.name << " retaliates!" << endl;
    p2.attack(p1);
    if (!p1.isAlive()) {
        cout << p1.name << " has been defeated!" << endl;
    }
}

int main() {
    srand(time(0));

    Board board(10, 10);

    Player player1("Hero", 100, 30, 10, 1, 1);
    Player player2("Monster", 80, 20, 5, 5, 5);

    board.placePlayer(player1);
    board.placePlayer(player2);

    board.printBoard();

    while (player1.isAlive() && player2.isAlive()) {
        int moveX, moveY;
        cout << "Enter move for Hero (x y): ";
        cin >> moveX >> moveY;
        player1.move(moveX, moveY);
        board.placePlayer(player1);

        if (player1.x == player2.x && player1.y == player2.y) {
            battle(player1, player2);
            break;
        }

        board.printBoard();

        if (player2.isAlive()) {
            int moveX2 = rand() % 3 - 1;
            int moveY2 = rand() % 3 - 1;
            player2.move(moveX2, moveY2);
            board.placePlayer(player2);

            if (player1.x == player2.x && player1.y == player2.y) {
                battle(player1, player2);
                break;
            }
        }

        board.printBoard();
    }

    if (player1.isAlive()) {
        cout << "Hero wins!" << endl;
    } else {
        cout << "Monster wins!" << endl;
    }

    return 0;
}
