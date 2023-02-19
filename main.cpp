/*
 * main.cpp
 *
 *  Created on: 09 Aug 2014
 *      Author: msg
 */
#include "shapes.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <random>

using std::to_string;

sf::RenderWindow *app;

// Game
const int refresh_rate = 60;
const int default_step_wait = 500;
int step_wait = default_step_wait;
const int rows = 20;
const int cols = 10;
// add 5 to fit the new pieces on top
const int b_rows = rows + 5;
const int b_cols = cols;
char board[b_rows][b_cols];
bool game_over = false;
int score = 0;
int level = 0;
// controls the level up mechanism
int lines_cleared = 0;
bool paused = false;
std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<> random_dist(1, 7);

void level_up() {
    level += 1;
    step_wait = static_cast<int>(0.96 * step_wait);
}

void checks_after_landing() {
    int removed_lines = 0;
    int row_color_count;
    for (int row_out = 19; row_out >= 0; row_out--) {
        row_color_count = 0;
        for (int col = 0; col < 10; col++) {
            if (board[row_out][col] != 's') {
                row_color_count += 1;
            }
        }
        if (row_color_count == 10) {
            removed_lines += 1;
            for (int row = row_out; row <= 20; row++) {
                for (int col = 0; col < 10; col++) {
                    board[row][col] = board[row + 1][col];
                }
            }
        }
    }

    if (removed_lines == 1) {
        score += 40 * (level + 1);
        lines_cleared += 1;
    }
    if (removed_lines == 2) {
        score += 100 * (level + 1);
        lines_cleared += 3;
    }
    if (removed_lines == 3) {
        score += 300 * (level + 1);
        lines_cleared += 5;
    }
    if (removed_lines == 4) {
        score += 1200 * (level + 1);
        lines_cleared += 8;
    }

    while (lines_cleared >= 5) {
        lines_cleared -= 5;
        level_up();
    }
}

int rand_tetrimino_type() {
    return random_dist(rng);
}

// Tetrimino
class Tetrimino {
  public:
    const int *limit;
    const char (*block)[4];
    int pos[2] = {15, 3};
    bool landed;

    Tetrimino() {
        tetrimino_type = rand_tetrimino_type();
        landed = false;
        update_shape();
        pos[0] = limit[2];
        pos[1] = limit[3];
    }

    void place_on_board() { this->move('p'); }

    void move(char dir) {
        if (this->landed) {
            return;
        }
        int old_pos[2] = {pos[0], pos[1]};
        switch (dir) {
        case 'p':
            // initial placement on the board
            break;
        case 'd':
            pos[0] = pos[0] - 1;
            break;
        case 'l':
            pos[1] = pos[1] - 1;
            break;
        case 'r':
            pos[1] = pos[1] + 1;
            break;
        case 'o':
            rotation_state = (rotation_state + 1) % 4;
            update_shape();
            break;
        }
        bool change_accepted = true;
        if (pos[1] < limit[0] || pos[1] > limit[1]) {
            change_accepted = false;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (block[i][j] != 's') {
                    if (board[pos[0] - i][pos[1] + j] != 's') {
                        change_accepted = false;
                    }
                }
            }
        }
        // restore the old position on failure
        if (change_accepted == false) {
            pos[0] = old_pos[0];
            pos[1] = old_pos[1];
            if (dir == 'p') {
                // initial placement failed, it's over
                game_over = true;
            } else if (dir == 'd') {
                // downward movement failed, landed
                landed = true;
            } else if (dir == 'o') {
                // make sure to keep it positive
                rotation_state = (4 + rotation_state - 1) % 4;
                update_shape();
            }
        }
    }

    void hard_drop() {
        while (this->landed == false) {
            this->move('d');
        }
    }

  private:
    int tetrimino_type;
    int rotation_state = 0;

    void update_shape() {
        block = shapes::get_shape(tetrimino_type, rotation_state);
        limit = shapes::get_limit(tetrimino_type, rotation_state);
    }
};

Tetrimino *curtet;
Tetrimino *nexttet;
    
void commit_piece_to_board(Tetrimino *tet) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tet->block[i][j] != 's') {
                board[tet->pos[0] - i][tet->pos[1] + j] = tet->block[i][j];
            }
        }
    }
}

// Graphics

const int us = 30;
const int margin_left = us;
const int margin_right = us * 5;
const int margin_top = us;
const int margin_bottom = us;
static sf::Font font;
static sf::Texture black, yellow, white, blue, cyan, orange, green, purple, red;

sf::RectangleShape get_square(int row, int col, char color, bool isnext) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(us, us));
    if (isnext == false) {
        rect.setPosition(col * us + margin_left,
                         ((rows - 1) - row) * us + margin_top);
    }
    if (isnext) {
        rect.setPosition(col * us + (margin_left + us * cols + us),
                         row * us + 6 * us);
    }
    switch (color) {
    case 's':
        rect.setTexture(&black);
        break;
    case 'y':
        rect.setTexture(&yellow);
        break;
    case 'w':
        rect.setTexture(&white);
        break;
    case 'b':
        rect.setTexture(&blue);
        break;
    case 'c':
        rect.setTexture(&cyan);
        break;
    case 'o':
        rect.setTexture(&orange);
        break;
    case 'g':
        rect.setTexture(&green);
        break;
    case 'p':
        rect.setTexture(&purple);
        break;
    case 'r':
        rect.setTexture(&red);
        break;
    }
    return rect;
}

// having these as functions is probably wasteful...
// maybe store them in an object?
sf::RectangleShape get_board_rect() {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(us * cols, us * rows));
    rect.setPosition(margin_left, margin_top);
    rect.setFillColor(sf::Color(0, 0, 0, 255));
    return rect;
}

sf::RectangleShape get_next_tetrimino_box() {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(3 * us, 4 * us));
    rect.setPosition(margin_left + us * cols + us, 6 * us);
    rect.setFillColor(sf::Color(0, 0, 0, 255));
    return rect;
}

sf::Text get_score_text() {
    sf::Text text1;
    text1.setString("Score:");
    text1.setFont(font);
    text1.setCharacterSize(us - 5);
    text1.setStyle(sf::Text::Regular);
    text1.setPosition(margin_left + us * cols + us, us);
    return text1;
}

sf::Text get_score() {
    sf::Text text1;
    text1.setString(to_string(score));
    text1.setFont(font);
    text1.setCharacterSize(us - 5);
    text1.setStyle(sf::Text::Regular);
    text1.setPosition(margin_left + us * cols + us, us * 2);
    return text1;
}

sf::Text get_level_text() {
    sf::Text text1;
    text1.setString("Level:");
    text1.setFont(font);
    text1.setCharacterSize(us - 5);
    text1.setStyle(sf::Text::Regular);
    text1.setPosition(margin_left + us * cols + us, us * 3);
    return text1;
}

sf::Text get_level() {
    sf::Text text1;
    text1.setString(to_string(level));
    text1.setFont(font);
    text1.setCharacterSize(us - 5);
    text1.setStyle(sf::Text::Regular);
    text1.setPosition(margin_left + us * cols + us, us * 4);
    return text1;
}

sf::RectangleShape get_board_hide_rect() {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(us * cols, us * rows));
    rect.setPosition(margin_left, margin_top);
    rect.setFillColor(sf::Color(255, 255, 255, 200));
    return rect;
}

sf::Text get_paused_text() {
    sf::Text text1;
    text1.setString("PAUSE");
    text1.setFont(font);
    text1.setCharacterSize(us * 2);
    text1.setStyle(sf::Text::Regular);
    text1.setPosition(margin_left + us * 2, margin_top + us * 3);
    text1.setFillColor(sf::Color(0, 0, 0, 255));
    return text1;
}

sf::Text get_game_over_text() {
    sf::Text text1;
    text1.setString("GAME OVER");
    text1.setFont(font);
    text1.setCharacterSize(us * 3 / 2);
    text1.setStyle(sf::Text::Regular);
    text1.setPosition(margin_left + us, margin_top + us * 3);
    text1.setFillColor(sf::Color(0, 0, 0, 255));
    return text1;
}

sf::Text get_game_over_score_text() {
    sf::Text text1;
    text1.setString("Score:");
    text1.setFont(font);
    text1.setCharacterSize(us - 5);
    text1.setStyle(sf::Text::Regular);
    text1.setPosition(margin_left + us * 4, margin_top + us * 7);
    text1.setFillColor(sf::Color(0, 0, 0, 255));
    return text1;
}

sf::Text get_game_over_score() {
    sf::Text text1;
    text1.setString(to_string(score));
    text1.setFont(font);
    text1.setCharacterSize(us - 5);
    text1.setStyle(sf::Text::Regular);
    text1.setPosition(margin_left + us * 5, margin_top + us * 8);
    text1.setFillColor(sf::Color(0, 0, 0, 255));
    return text1;
}

sf::Text get_game_over_instruction_line1() {
    sf::Text text1;
    text1.setString("Press return key");
    text1.setFont(font);
    text1.setCharacterSize(us - 5);
    text1.setStyle(sf::Text::Regular);
    text1.setPosition(margin_left + us * 2, margin_top + us * 11);
    text1.setFillColor(sf::Color(0, 0, 0, 255));
    return text1;
}

sf::Text get_game_over_instruction_line2() {
    sf::Text text1;
    text1.setString("  to play again");
    text1.setFont(font);
    text1.setCharacterSize(us - 5);
    text1.setStyle(sf::Text::Regular);
    text1.setPosition(margin_left + us * 2, margin_top + us * 12);
    text1.setFillColor(sf::Color(0, 0, 0, 255));
    return text1;
}

void refresh_screen(sf::RenderWindow &app) {
    if (app.isOpen()) {
        // Clear screen
        app.clear(sf::Color(38, 182, 121, 255));

        app.draw(get_board_rect());
        app.draw(get_next_tetrimino_box());
        app.draw(get_score_text());
        app.draw(get_score());
        app.draw(get_level_text());
        app.draw(get_level());

        // draw board
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] != 's') {
                    app.draw(get_square(i, j, board[i][j], false));
                }
            }
        }

        // draw current piece
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (curtet->block[i][j] != 's' && (curtet->pos[0] - i) < rows) {
                    app.draw(get_square(curtet->pos[0] - i, curtet->pos[1] + j, curtet->block[i][j], false));
                }
            }
        }

        // draw next piece
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (nexttet->block[i][j] != 's') {
                    app.draw(get_square(i, j, nexttet->block[i][j], true));
                }
            }
        }

        if (paused) {
            app.draw(get_board_hide_rect());
            app.draw(get_paused_text());
        }
        if (game_over) {
            app.draw(get_board_hide_rect());
            app.draw(get_game_over_text());
            app.draw(get_game_over_score_text());
            app.draw(get_game_over_score());
            app.draw(get_game_over_instruction_line1());
            app.draw(get_game_over_instruction_line2());
        }
        app.display();
    }
}

// Controls

void handle_event(sf::Event event) {
    // Close window: exit
    if (event.type == sf::Event::Closed) {
        app->close();
    }
    if (event.type == sf::Event::KeyPressed) {
        if (paused == false) {
            switch (event.key.code) {
            case sf::Keyboard::Left:
                curtet->move('l');
                break;
            case sf::Keyboard::Right:
                curtet->move('r');
                break;
            case sf::Keyboard::Up:
                curtet->move('o');
                break;
            case sf::Keyboard::Down:
                curtet->move('d');
                break;
            case sf::Keyboard::Space:
                curtet->hard_drop();
                break;
            case sf::Keyboard::P:
                paused = true;
                break;
            default:
                break;
            }
        } else if (paused == true && event.key.code == sf::Keyboard::P) {
            paused = false;
        }
        if (game_over && event.key.code == sf::Keyboard::Return) {
            game_over = false;
            score = 0;
            level = 0;
            step_wait = default_step_wait;
            for (int row = 0; row < 25; row++) {
                for (int col = 0; col < 10; col++) {
                    board[row][col] = 's';
                }
            }
            delete curtet;
            curtet = nexttet;
            curtet->place_on_board();
            nexttet = new Tetrimino();
        }
    }
}

int main() {
    black.loadFromFile("resources/black.png");
    yellow.loadFromFile("resources/yellow.png");
    white.loadFromFile("resources/white.png");
    blue.loadFromFile("resources/blue.png");
    cyan.loadFromFile("resources/cyan.png");
    orange.loadFromFile("resources/orange.png");
    green.loadFromFile("resources/green.png");
    purple.loadFromFile("resources/purple.png");
    red.loadFromFile("resources/red.png");
    font.loadFromFile("resources/DroidSans.ttf");

    for (int row = 0; row < 25; row++) {
        for (int col = 0; col < 10; col++) {
            board[row][col] = 's';
        }
    }

    // Create the main window
    sf::RenderWindow window(
        sf::VideoMode(us * cols + margin_right + margin_left,
                      us * rows + margin_top + margin_bottom),
        "Tetrahexyl");
    app = &window;
    curtet = new Tetrimino;
    nexttet = new Tetrimino;
    curtet->place_on_board();

    refresh_screen(window);
    sf::Clock clock;
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            handle_event(event);
        }
        refresh_screen(window);

        if (!game_over && !paused && 
            clock.getElapsedTime().asMilliseconds() >= step_wait) {
            curtet->move('d');
            clock.restart();
        }
        if (curtet->landed) {
            commit_piece_to_board(curtet);
            checks_after_landing();
            delete curtet;
            curtet = nexttet;
            curtet->place_on_board();
            nexttet = new Tetrimino();
        }
        sf::sleep(sf::milliseconds(1000 / refresh_rate));
    }

    return EXIT_SUCCESS;
}
