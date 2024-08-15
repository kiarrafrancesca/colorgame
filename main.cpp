#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class Color {
private:
    string colors[6];

public:
    int money = 0;

    Color() {
        colors[0] = "Red";
        colors[1] = "Blue";
        colors[2] = "Green";
        colors[3] = "Yellow";
        colors[4] = "Orange";
        colors[5] = "Pink";
    };

    string get_color(int index) {
        return colors[index];
    }

    int color_index(string color_name) {
        for (int i = 0; i < 6; ++i) {
            if (colors[i] == color_name) {
                return i;
            }
        }
        return -1;
    }

    void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif 
    }

    void press_return() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nPress 'enter' to return.";
        cin.get();
        clear_screen();
    }

    void display_color(const string& text, const string& color) {
        string color_code;

        if (color == "Red") color_code = "\033[31m";
        else if (color == "Blue") color_code = "\033[34m";
        else if (color == "Green") color_code = "\033[32m";
        else if (color == "Yellow") color_code = "\033[33m";
        else if (color == "Orange") color_code = "\033[38;5;208m";
        else if (color == "Pink") color_code = "\033[35m";

        cout << color_code << text << "\033[0m";
    }

    void dice_roll(vector<string>& dice_results) {
        srand(static_cast<unsigned>(time(0)));
        Color color;

        for (int i = 0; i < 3; ++i) {
            int index = rand() % 6;
            dice_results.push_back(color.get_color(index));
        }
    }

    void play_game(int bet_amount) {
        Color color;
        string player_color;
        int player_color_index;
        char choice;

        while (true) {
            display_color("Red", "Red");
            cout << " | ";
            display_color("Blue", "Blue");
            cout << " | ";
            display_color("Green", "Green");
            cout << " | ";
            display_color("Yellow", "Yellow");
            cout << " | ";
            display_color("Orange", "Orange");
            cout << " | ";
            display_color("Pink", "Pink");
            cout << "\n";

            cout << "\nEnter a color: ";
            cin >> player_color;

            player_color_index = color.color_index(player_color);
            if (player_color_index == -1) {
                clear_screen();
                cout << "Invalid choice of color.\n" << endl;
                continue;
            }
            break;
        }
        clear_screen();

        vector<string> dice_results;
        dice_roll(dice_results);

        cout << "Dice rolling...\n" << endl;

        cout << "------------------------------" << endl;
        cout << "  ";
        for (int i = 0; i < 3; ++i) {
            cout << "| ";
            display_color(dice_results[i], dice_results[i]);
            cout << " ";
        }
        cout << "|\n";
        cout << "------------------------------" << endl;

        int count = 0;
        for (int i = 0; i < 3; ++i) {
            if (dice_results[i] == player_color) {
                count++;
            }
        }

        cout << "\nYour color appeared " << count << " times.\n" << endl;

        int winnings = 0;
        if (count == 0 || count == 1) {
            cout << "Better luck next time!" << endl;
        }
        if (count == 2) {
            winnings = bet_amount * 2;
            cout << "You won $" << winnings << endl;
        }
        if (count == 3) {
            winnings = bet_amount * 3;
            cout << "You won $" << winnings << endl;
        }

        money += winnings;

        play_again();
    }

    void play_again() {
        char choice;

        cout << "\nWould you like to play another round? Y/N: ";
        cin >> choice;
        clear_screen();

        if (choice == 'y' || choice == 'Y') {
            int bet_amount = get_bet_amount();
            if (bet_amount > 0) {
                int bet_result = verify_bet(bet_amount);
                if (bet_result == 2) {
                    play_game(bet_amount);
                }
            }
        }
        else {
            main_menu();
        }
    }

    int get_bet_amount() {
        int bet_amount;

        while (true) {
            cout << "Enter amount you want to bet (enter 0 to cancel): $";

            if (cin >> bet_amount) {
                if (bet_amount == 0) {
                    clear_screen();
                    return 0;
                }
                else if (bet_amount < 0) {
                    clear_screen();
                    cout << "Pleas enter a positive integer.\n" << endl;
                }
                else if (bet_amount > money) {
                    clear_screen();
                    cout << "Insufficience balance. You only have $" << money << " in your wallet." << endl;
                }
                else {
                    clear_screen();
                    return bet_amount;
                }
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                clear_screen();
                cout << "Please enter an integer.\n" << endl;
            }
        }
    }

    int verify_bet(int bet_amount) {
        int choice;

        while (true) {
            cout << "+----------------------------------+" << endl;
            cout << "               $" << bet_amount << endl;
            cout << "+----------------------------------+" << endl;
            cout << "| [1] Confirm bet                  |" << endl;
            cout << "| [2] Change bet                   |" << endl;
            cout << "+----------------------------------+" << endl;
            cout << "| [0] Cancel                       |" << endl;
            cout << "+----------------------------------+" << endl;
            cout << " Enter your choice: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                clear_screen();
                cout << "Please enter a valid choice from the menu.\n" << endl;
                continue;
            }

            switch (choice) {
            case 0:
                clear_screen();
                return 0;
            case 1:
                clear_screen();
                cout << "Your bet of $" << bet_amount << " has been confirmed." << endl;
                money -= bet_amount;
                press_return();
                clear_screen();
                return 2;
            case 2:
                clear_screen();
                if (bet_amount == 0) {
                    return 0;
                }
                return 1;
            default:
                cout << "Please enter a valid choice from the menu.\n" << endl;
                break;
            }
        }
    }

    void instructions() {
        cout << "+----------------------------------------+" << endl;
        cout << "|              INSTRUCTIONS              |" << endl;
        cout << "+----------------------------------------+" << endl;
        cout << " Objectives:" << endl;
        cout << " -----------" << endl;
        cout << " 1. Correctly predict how many times your chosen color will appear when three dice are rolled." << endl;
        cout << " 2. The game uses six different color: Red, Blue, Green, Yellow, Orange, and Pink." << endl;
        cout << " 3. Three six-sided dice are used, each with one face for each color." << endl;
        cout << "\n";
        cout << " How to Play?" << endl;
        cout << " ------------" << endl;
        cout << " Step 1. Choose a color." << endl;
        cout << " Step 2. Place a bet." << endl;
        cout << " Step 3. Roll the dice." << endl;
        cout << "\n";
        cout << " Winning:" << endl;
        cout << " --------" << endl;
        cout << " If the chosen color appears once, the player wins no points." << endl;
        cout << " If the chosen color appears twice, the player wins 2 times their bet." << endl;
        cout << " If the chosen color appears thrice, the player wins 3 times their bet." << endl;

        press_return();
    }

    void wallet() {
        int choice;
        int money;

        while (true) {
            cout << "+----------------------------------------+" << endl;
            cout << "|                  WALLET                |" << endl;
            cout << "+----------------------------------------+" << endl;
            cout << "| [1] Balance                            |" << endl;
            cout << "| [2] Top-up                             |" << endl;
            cout << "+----------------------------------------+" << endl;
            cout << "| [3] Return to Main Menu                |" << endl;
            cout << "+----------------------------------------+" << endl;
            cout << " Enter your choice: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                clear_screen();
                cout << "Please enter a valid choice from the menu.\n" << endl;
                continue;
            }

            switch (choice) {
            case 1:
                clear_screen();
                balance();
                break;
            case 2:
                clear_screen();
                top_up();
                break;
            case 3:
                clear_screen();
                return;
            default:
                cout << "Please enter a valid choice from the menu." << endl;
            }
        }
    }

    void balance() {
        cout << "+----------------------------------------+" << endl;
        cout << " Amount in wallet: $" << money << endl;
        cout << "+----------------------------------------+" << endl;

        press_return();
    }

    void top_up() {
        int topup;

        while (true) {
            cout << "+--------------------------------------------------+" << endl;
            cout << "|                       TOP-UP                     |" << endl;
            cout << "+--------------------------------------------------+" << endl;
            cout << " Enter amount to top-up (enter 0 to cancel): ";

            if (!(cin >> topup)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                clear_screen();
                cout << "Please enter an integer.\n" << endl;
                continue;
            }

            if (topup < 0) {
                clear_screen();
                cout << "Please enter a positive integer." << endl;
            }
            else if (topup == 0) {
                clear_screen();
                return;
            }
            else {
                money += topup;
                clear_screen();
                cout << "You have successfully topped up $" << topup <<". Your new balance is $" << money << endl;
                press_return();
                return;
            }
        }
    }   

    void main_menu() {
        int choice;

        while (true) {
            cout << "+----------------------------------+" << endl;
            cout << "|       Welcome to ColorGame!      |" << endl;
            cout << "+----------------------------------+" << endl;
            cout << "| Select an option:                |" << endl;
            cout << "| [1] Start Game                   |" << endl;
            cout << "| [2] Instructions                 |" << endl;
            cout << "| [3] Wallet                       |" << endl;
            cout << "+----------------------------------+" << endl;
            cout << "| [4] Exit                         |" << endl;
            cout << "+----------------------------------+" << endl;
            cout << " Enter your choice: ";
            
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                clear_screen();
                cout << "Please enter a valid choice from the menu.\n" << endl;
                continue;
            }

            switch (choice) {
            case 1:
                clear_screen();
                while (true) {
                    int bet_amount = get_bet_amount();
                    if (bet_amount == 0) {
                        break;
                    }
                    else {
                        int bet_result = verify_bet(bet_amount);
                        if (bet_result == 0) {
                            break;
                        }
                        else if (bet_result == 1) {
                            int bet_amount = get_bet_amount();
                            if (bet_amount == 0) {
                                break;
                            }
                        }
                        else if (bet_result == 2) {
                            play_game(bet_amount);
                            break;
                        }
                    }
                }
                break;
            case 2:
                clear_screen();
                instructions();
                break;
            case 3:
                clear_screen();
                wallet();
                break;
            case 4:
                cout << "Exiting..." << endl;
                exit(0);
            default:
                clear_screen();
                cout << "Please enter a valid choice from the menu.\n" << endl;
            }
        }
    } 
};

int main() {
    Color game;
	game.main_menu();

	return 0;
}