#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "controller.h"
#include "tools.h"
#include "startinterface.h"
#include "map.h"
#include "snake.h"
#include "food.h"

void Controller::Start() // Start interface
{
    SetWindowSize(41, 32); // Set the window size
    SetColor(2); // Set the color for the start animation
    StartInterface* start = new StartInterface(); // Dynamically allocate a StartInterface class object named start
    start->Action(); // Start the animation
    delete start; // Release the memory space

    // Set the cursor position and output the prompt, wait for any key press to end
    SetCursorPosition(13, 26);
    std::cout << "Press any key to start... ";
    SetCursorPosition(13, 27);
    system("pause");
}

void Controller::Select() // Selection interface
{
    // Initialize interface options
    SetColor(3);
    SetCursorPosition(13, 26);
    std::cout << "                          ";
    SetCursorPosition(13, 27);
    std::cout << "                          ";
    SetCursorPosition(6, 21);
    std::cout << "Please select the game difficulty: ";
    SetCursorPosition(6, 22);
    std::cout << "(Use up and down arrows to select)";
    SetCursorPosition(27, 22);
    SetBackColor(); // Set background color for the first option to indicate it is currently selected
    std::cout << "Easy Mode";
    SetCursorPosition(27, 24);
    SetColor(3);
    std::cout << "Normal Mode";
    SetCursorPosition(27, 26);
    std::cout << "Hard Mode";
    SetCursorPosition(27, 28);
    std::cout << "Inferno Mode";
    SetCursorPosition(0, 31);
    score = 0;

    // Up and down arrow selection module
    int ch; // Record the input value
    key = 1; // Record the selected item, initially select the first one
    bool flag = false; // Record whether the Enter key has been pressed, initially set to false
    while ((ch = _getch()))
    {
        switch (ch) // Detect the input key
        {
        case 72: // UP arrow key
            if (key > 1) // When the currently selected item is the first one, the UP arrow key is invalid
            {
                switch (key)
                {
                case 2:
                    SetCursorPosition(27, 22); // Set the background color for the item to be selected
                    SetBackColor();
                    std::cout << "Easy Mode";
                    SetCursorPosition(27, 24); // Remove the background color from the previously selected item
                    SetColor(3);
                    std::cout << "Normal Mode";
                    --key;
                    break;
                case 3:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << "Normal Mode";
                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << "Hard Mode";
                    --key;
                    break;
                case 4:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << "Hard Mode";
                    SetCursorPosition(27, 28);
                    SetColor(3);
                    std::cout << "Inferno Mode";
                    --key;
                    break;
                }
            }
            break;
        case 80: // DOWN arrow key
            if (key < 4)
            {
                switch (key)
                {
                case 1:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << "Normal Mode";
                    SetCursorPosition(27, 22);
                    SetColor(3);
                    std::cout << "Easy Mode";
                    ++key;
                    break;
                case 2:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << "Hard Mode";
                    SetCursorPosition(27, 24);
                    SetColor(3);
                    std::cout << "Normal Mode";
                    ++key;
                    break;
                case 3:
                    SetCursorPosition(27, 28);
                    SetBackColor();
                    std::cout << "Inferno Mode";
                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << "Hard Mode";
                    ++key;
                    break;
                }
            }
            break;
        case 13: // Enter key
            flag = true;
            break;
        default: // Invalid key
            break;
        }
        if (flag)
            break; // Enter key is pressed to confirm, exit the input checking loop

        SetCursorPosition(0, 31); // Place the cursor at the bottom left to avoid cursor flickering affecting the game experience
    }

    switch (key) // Set the movement speed of the snake according to the selected option, the smaller the speed value, the faster the speed
    {
    case 1:
        speed = 135;
        break;
    case 2:
        speed = 100;
        break;
    case 3:
        speed = 60;
        break;
    case 4:
        speed = 30;
        break;
    default:
        break;
    }
}

void Controller::DrawGame() // Draw the game interface
{
    system("cls"); // Clear the screen

    // Draw the map
    SetColor(3);
    Map* init_map = new Map();
    init_map->PrintInitmap();
    delete init_map;

    // Draw the sidebar
    SetColor(3);
    SetCursorPosition(33, 1);
    std::cout << "Greedy Snake";
    SetCursorPosition(34, 2);
    std::cout << "Snake";
    SetCursorPosition(31, 4);
    std::cout << "Difficulty: ";
    SetCursorPosition(36, 5);
    switch (key)
    {
    case 1:
        std::cout << "Easy Mode";
        break;
    case 2:
        std::cout << "Normal Mode";
        break;
    case 3:
        std::cout << "Hard Mode";
        break;
    case 4:
        std::cout << "Inferno Mode";
        break;
    default:
        break;
    }
    SetCursorPosition(31, 7);
    std::cout << "Score: ";
    SetCursorPosition(37, 8);
    std::cout << "     0";
    SetCursorPosition(33, 13);
    std::cout << "Move with arrow keys";
    SetCursorPosition(33, 15);
    std::cout << "Pause with ESC key";
}

int Controller::PlayGame() // Secondary game loop
{
    // Initialize the snake and food
    Snake* csnake = new Snake();
    Food* cfood = new Food();
    SetColor(6);
    csnake->InitSnake();
    srand((unsigned)time(NULL)); // Set the random number seed, without this the food's position will be fixed
    cfood->DrawFood(*csnake);

    // Game loop
    while (csnake->OverEdge() && csnake->HitItself()) // Judge whether hitting the wall or itself, that is, whether still alive
    {
        // Call out the selection menu
        if (!csnake->ChangeDirection()) // When the Esc key is pressed
        {
            int tmp = Menu(); // Draw the menu and get the return value
            switch (tmp)
            {
            case 1: // Continue the game
                break;
            case 2: // Restart the game
                delete csnake;
                delete cfood;
                return 1; // Return 1 as the return value of PlayGame function to the Game function, indicating restart
            case 3: // Quit the game
                delete csnake;
                delete cfood;
                return 2; // Return 2 as the return value of PlayGame function to the Game function, indicating quit
            default:
                break;
            }
        }

        if (csnake->GetFood(*cfood)) // Eat the food
        {
            csnake->Move(); // The snake grows
            UpdateScore(1); // Update the score, 1 is the score weight
            RewriteScore(); // Redraw the score
            cfood->DrawFood(*csnake); // Draw new food
        }
        else
        {
            csnake->NormalMove(); // The snake moves normally
        }

        if (csnake->GetBigFood(*cfood)) // Eat the time - limited food
        {
            csnake->Move();
            UpdateScore(cfood->GetProgressBar() / 5); // The score is determined according to the time - limited food progress bar
            RewriteScore();
        }

        if (cfood->GetBigFlag()) // If there is time - limited food at this time, make it flash
        {
            cfood->FlashBigFood();
        }

        Sleep(speed); // Create the moving effect of the snake
    }

    // The snake dies
    delete csnake; // Release the allocated memory space
    delete cfood;
    int tmp = GameOver(); // Draw the game over interface and return the selected item
    switch (tmp)
    {
    case 1:
        return 1; // Restart
    case 2:
        return 2; // Quit
    default:
        return 2;
    }
}

// Update the score
void Controller::UpdateScore(const int& tmp)
{
    // The score obtained is determined according to the game difficulty and the passed - in parameter tmp
    score += key * 10 * tmp;
}

// Redraw the score
void Controller::RewriteScore()
{
    // To keep the score right - aligned at the end, set the maximum score to 6 digits, calculate the number of current score digits, fill the remaining digits with spaces, and then output the score
    SetCursorPosition(37, 8);
    SetColor(11);
    int bit = 0;
    int tmp = score;
    while (tmp != 0)
    {
        ++bit;
        tmp /= 10;
    }
    for (int i = 0; i < (6 - bit); ++i)
    {
        std::cout << " ";
    }
    std::cout << score;
}

// Selection menu
int Controller::Menu()
{
    // Draw the menu
    SetColor(11);
    SetCursorPosition(32, 19);
    std::cout << "Menu: ";
    Sleep(100);
    SetCursorPosition(34, 21);
    SetBackColor();
    std::cout << "Continue Game";
    Sleep(100);
    SetCursorPosition(34, 23);
    SetColor(11);
    std::cout << "Restart";
    Sleep(100);
    SetCursorPosition(34, 25);
    std::cout << "Quit Game";
    SetCursorPosition(0, 31);

    // Selection part
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = _getch()))
    {
        switch (ch)
        {
        case 72: // UP
            if (tmp_key > 1)
            {
                switch (tmp_key)
                {
                case 2:
                    SetCursorPosition(34, 21);
                    SetBackColor();
                    std::cout << "Continue Game";
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << "Restart";
                    --tmp_key;
                    break;
                case 3:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << "Restart";
                    SetCursorPosition(34, 25);
                    SetColor(11);
                    std::cout << "Quit Game";
                    --tmp_key;
                    break;
                }
            }
            break;
        case 80: // DOWN
            if (tmp_key < 3)
            {
                switch (tmp_key)
                {
                case 1:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << "Restart";
                    SetCursorPosition(34, 21);
                    SetColor(11);
                    std::cout << "Continue Game";
                    ++tmp_key;
                    break;
                case 2:
                    SetCursorPosition(34, 25);
                    SetBackColor();
                    std::cout << "Quit Game";
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << "Restart";
                    ++tmp_key;
                    break;
                }
            }
            break;
        case 13: // Enter
            flag = true;
            break;
        default:
            break;
        }

        if (flag)
        {
            break;
        }
        SetCursorPosition(0, 31);
    }

    if (tmp_key == 1) // If "Continue Game" is selected, then erase the menu
    {
        SetCursorPosition(32, 19);
        std::cout << "      ";
        SetCursorPosition(34, 21);
        std::cout << "        ";
        SetCursorPosition(34, 23);
        std::cout << "        ";
        SetCursorPosition(34, 25);
        std::cout << "        ";
    }
    return tmp_key;
}

void Controller::Game()//Game level one loop
{
    Start();//Start screen
    while (true)//The game can be viewed as an endless loop until the loop ends when you exit the game
    {
        Select();//Selection interface
        DrawGame();//Drawing the game interface
        int tmp = PlayGame();//Open the game loop, and when restarting or exiting the game, end the loop and return a value to tmp
        if (tmp == 1) //Restart the game when the return value is 1
        {
            system("cls");
            continue;
        }
        else if (tmp == 2) //Exit the game when the return value is 2
        {
            break;
        }
        else
        {
            break;
        }
    }
}

int Controller::GameOver() // Game over interface
{
    // Draw the game over interface
    Sleep(500);
    SetColor(11);
    SetCursorPosition(10, 8);
    std::cout << "-----------------------------------------------";
    Sleep(30);
    SetCursorPosition(9, 9);
    std::cout << " |               Game Over!!!              |";
    Sleep(30);
    SetCursorPosition(9, 10);
    std::cout << " |                                         |";
    Sleep(30);
    SetCursorPosition(9, 11);
    std::cout << " |              So sorry! You're dead.     |";
    Sleep(30);
    SetCursorPosition(9, 12);
    std::cout << " |                                         |";
    Sleep(30);
    SetCursorPosition(9, 13);
    std::cout << " |             Your score is:               |";
    SetCursorPosition(24, 13);
    std::cout << score;
    Sleep(30);
    SetCursorPosition(9, 14);
    std::cout << " |                                          |";
    Sleep(30);
    SetCursorPosition(9, 15);
    std::cout << " |   Do you want to play another round?     |";
    Sleep(30);
    SetCursorPosition(9, 16);
    std::cout << " |                                          |";
    Sleep(30);
    SetCursorPosition(9, 17);
    std::cout << " |                                          |";
    Sleep(30);
    SetCursorPosition(9, 18);
    std::cout << " |    Yes, okay        No, studying is more |";
    Sleep(30);
    SetCursorPosition(9, 19);
    std::cout << " |             interesting.                 |";
    Sleep(30);
    SetCursorPosition(9, 20);
    std::cout << " |                                          |";
    Sleep(30);
    SetCursorPosition(10, 21);
    std::cout << "-----------------------------------------------";

    Sleep(100);
    SetCursorPosition(12, 18);
    SetBackColor();
    std::cout << "Yes, okay";
    SetCursorPosition(0, 31);

    // Selection part
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = _getch()))
    {
        switch (ch)
        {
        case 75: // LEFT
            if (tmp_key > 1)
            {
                SetCursorPosition(12, 18);
                SetBackColor();
                std::cout << "Yes, okay";
                SetCursorPosition(20, 18);
                SetColor(11);
                std::cout << "No, studying is more interesting";
                --tmp_key;
            }
            break;
        case 77: // RIGHT
            if (tmp_key < 2)
            {
                SetCursorPosition(20, 18);
                SetBackColor();
                std::cout << "No, studying is more interesting";
                SetCursorPosition(12, 18);
                SetColor(11);
                std::cout << "Yes, okay";
                ++tmp_key;
            }
            break;
        case 13: // Enter
            flag = true;
            break;
        default:
            break;
        }

        SetCursorPosition(0, 31);
        if (flag)
        {
            break;
        }
    }

    SetColor(11);
    switch (tmp_key)
    {
    case 1:
        return 1; // Restart
    case 2:
        return 2; // Quit
    default:
        return 1;
    }
}