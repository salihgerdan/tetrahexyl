/*
 * main.cpp
 *
 *  Created on: 09 Aug 2014
 *      Author: msg
 */
#include "shapes.hpp"
#include "gui.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <random>


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
    int new_lines_cleared = 0;
    int row_color_count;
    for (int row_out = 19; row_out >= 0; row_out--) {
        row_color_count = 0;
        for (int col = 0; col < 10; col++) {
            if (board[row_out][col] != 's') {
                row_color_count += 1;
            }
        }
        if (row_color_count == 10) {
            new_lines_cleared += 1;
            for (int row = row_out; row <= 20; row++) {
                for (int col = 0; col < 10; col++) {
                    board[row][col] = board[row + 1][col];
                }
            }
        }
    }

    // multiple lines removed at once compounds for leveling up
    switch (new_lines_cleared) {
        case 1:
            score += 40 * (level + 1);
            lines_cleared += 1;
            break;
        case 2:
            score += 100 * (level + 1);
            lines_cleared += 3;
            break;
        case 3:
            score += 300 * (level + 1);
            lines_cleared += 5;
            break;
        case 4:
            score += 1200 * (level + 1);
            lines_cleared += 8;
            break;
    }

    while (lines_cleared >= 5) {
        lines_cleared -= 5;
        level_up();
    }
}

// Tetrimino
struct TetriminoImpossibleMove : public std::exception
{
	const char * what () const throw ()
    {
    	return "Movement is not possible, reverted.";
    }
};

class Tetrimino {
  public:
    const int *limit;
    const char (*block)[4];
    int pos[2] = {rows-5, (cols/2)-2};
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
        try {
            if (pos[1] < limit[0] || pos[1] > limit[1]) {
                throw TetriminoImpossibleMove();
            }
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (block[i][j] != 's') {
                        if (board[pos[0] - i][pos[1] + j] != 's') {
                            throw TetriminoImpossibleMove();
                        }
                    }
                }
            }
        } catch (TetriminoImpossibleMove e) {
        // restore the old position on failure
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

    int rand_tetrimino_type() {
        return random_dist(rng);
    }
};

void commit_piece_to_board(Tetrimino *tet) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tet->block[i][j] != 's') {
                board[tet->pos[0] - i][tet->pos[1] + j] = tet->block[i][j];
            }
        }
    }
}

void draw_screen(sf::RenderWindow &app, gui::GUIElements &gui_elements, Tetrimino* curtet, Tetrimino* nexttet) {
    if (app.isOpen()) {
        // Clear screen
        app.clear(sf::Color(38, 182, 121, 255));

        app.draw(gui_elements.board_rect);
        app.draw(gui_elements.next_tetrimino_box);
        app.draw(gui_elements.score_label);
        app.draw(gui_elements.get_score(score));
        app.draw(gui_elements.level_label);
        app.draw(gui_elements.get_level(level));

        // draw board
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] != 's') {
                    app.draw(gui_elements.get_square(i, j, board[i][j], false));
                }
            }
        }

        // draw current piece
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (curtet->block[i][j] != 's' && (curtet->pos[0] - i) < rows) {
                    app.draw(gui_elements.get_square(curtet->pos[0] - i, curtet->pos[1] + j, curtet->block[i][j], false));
                }
            }
        }

        // draw next piece
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (nexttet->block[i][j] != 's') {
                    app.draw(gui_elements.get_square(i, j, nexttet->block[i][j], true));
                }
            }
        }

        if (paused) {
            app.draw(gui_elements.board_hide_rect);
            app.draw(gui_elements.paused_text);
        }
        if (game_over) {
            app.draw(gui_elements.board_hide_rect);
            app.draw(gui_elements.game_over_text);
            app.draw(gui_elements.game_over_score_label);
            app.draw(gui_elements.get_game_over_score(score));
            app.draw(gui_elements.game_over_instruction_line1);
            app.draw(gui_elements.game_over_instruction_line2);
        }
        app.display();
    }
}

// Controls

void handle_event(sf::Event event, Tetrimino* curtet, Tetrimino* nexttet) {
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
    gui::GUIElements gui_elements = gui::GUIElements(rows,cols);

    for (int row = 0; row < 25; row++) {
        for (int col = 0; col < 10; col++) {
            board[row][col] = 's';
        }
    }

    // Create the main window
    sf::RenderWindow window(
        sf::VideoMode(gui::us * cols + gui::margin_right + gui::margin_left,
                     gui::us * rows + gui::margin_top + gui::margin_bottom),
        "Tetrahexyl");
    app = &window;
    Tetrimino *curtet = new Tetrimino;
    Tetrimino *nexttet = new Tetrimino;
    curtet->place_on_board();

    draw_screen(window, gui_elements, curtet, nexttet);
    sf::Clock clock;
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            handle_event(event, curtet, nexttet);
        }
        draw_screen(window, gui_elements, curtet, nexttet);

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
