#pragma once
#include <SFML/Graphics.hpp>
namespace gui {
static sf::Font font;
static sf::Texture black, yellow, white, blue, cyan, orange, green, purple, red;
const int us = 30;
const int margin_left = us;
const int margin_right = us * 5;
const int margin_top = us;
const int margin_bottom = us;

class GUIElements {
  public:
    const int rows;
    const int cols;
    sf::RectangleShape board_rect;
    sf::RectangleShape next_tetrimino_box;
    sf::Text score_label;
    sf::Text level_label;
    sf::RectangleShape board_hide_rect;
    sf::Text paused_text;
    sf::Text game_over_text;
    sf::Text game_over_score_label;
    sf::Text game_over_instruction_line1;
    sf::Text game_over_instruction_line2;

    GUIElements(const int rows, const int cols);
    sf::RectangleShape get_square(int row, int col, char color, bool isnext);
    sf::Text get_score(int score);
    sf::Text get_game_over_score(int score);
    sf::Text get_level(int level);
  private:
    sf::Text score_text;
    sf::Text level_text;
    sf::Text game_over_score_text;
    sf::RectangleShape init_board_rect();
    sf::RectangleShape init_next_tetrimino_box();
    sf::Text init_text();
    sf::Text init_score_label();
    sf::Text init_score();
    sf::Text init_level_label();
    sf::Text init_level();
    sf::RectangleShape init_board_hide_rect();
    sf::Text init_paused_text();
    sf::Text init_game_over_text();
    sf::Text init_game_over_score_label();
    sf::Text init_game_over_score();
    sf::Text init_game_over_instruction_line1();
    sf::Text init_game_over_instruction_line2();
};
}// namespace gui