#include "gui.hpp"
using std::to_string;

namespace gui {

GUIElements::GUIElements(const int rows, const int cols): rows(rows), cols(cols) {
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
    board_rect = init_board_rect();
    next_tetrimino_box = init_next_tetrimino_box();
    score_label = init_score_label();
    score_text = init_score();
    level_label = init_level_label();
    level_text = init_level();
    board_hide_rect = init_board_hide_rect();
    paused_text = init_paused_text();
    game_over_text = init_game_over_text();
    game_over_score_label = init_game_over_score_label();
    game_over_instruction_line1 = init_game_over_instruction_line1();
    game_over_instruction_line2 = init_game_over_instruction_line2();
}

sf::RectangleShape GUIElements::get_square(int row, int col, char color, bool isnext) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(us, us));
    if (!isnext) {
        // current piece
        rect.setPosition(col * us + margin_left,
                         ((rows - 1) - row) * us + margin_top);
    } else {
        // next piece
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

sf::Text GUIElements::get_score(int score) {
    score_text.setString(to_string(score));
    return score_text;
}

sf::Text GUIElements::get_game_over_score(int score) {
    game_over_score_text.setString(to_string(score));
    return game_over_score_text;
}

sf::Text GUIElements::get_level(int level) {
    level_text.setString(to_string(level));
    return level_text;
}

sf::RectangleShape GUIElements::init_board_rect() {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(us * cols, us * rows));
    rect.setPosition(margin_left, margin_top);
    rect.setFillColor(sf::Color(0, 0, 0, 255));
    return rect;
}

sf::RectangleShape GUIElements::init_next_tetrimino_box() {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(3 * us, 4 * us));
    rect.setPosition(margin_left + us * cols + us, 6 * us);
    rect.setFillColor(sf::Color(0, 0, 0, 255));
    return rect;
}

sf::Text GUIElements::init_text() {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(us - 5);
    text.setStyle(sf::Text::Regular);
    return text;
}

sf::Text GUIElements::init_score_label() {
    sf::Text text = GUIElements::init_text();
    text.setString("Score:");
    text.setPosition(margin_left + us * cols + us, us);
    return text;
}

sf::Text GUIElements::init_score() {
    sf::Text text = GUIElements::init_text();
    text.setPosition(margin_left + us * cols + us, us * 2);
    return text;
}

sf::Text GUIElements::init_level_label() {
    sf::Text text = GUIElements::init_text();
    text.setString("Level:");
    text.setPosition(margin_left + us * cols + us, us * 3);
    return text;
}

sf::Text GUIElements::init_level() {
    sf::Text text = GUIElements::init_text();
    text.setPosition(margin_left + us * cols + us, us * 4);
    return text;
}

sf::RectangleShape GUIElements::init_board_hide_rect() {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(us * cols, us * rows));
    rect.setPosition(margin_left, margin_top);
    rect.setFillColor(sf::Color(255, 255, 255, 200));
    return rect;
}

sf::Text GUIElements::init_paused_text() {
    sf::Text text = GUIElements::init_text();
    text.setString("PAUSE");
    text.setCharacterSize(us * 2);
    text.setPosition(margin_left + us * 2, margin_top + us * 3);
    text.setFillColor(sf::Color(0, 0, 0, 255));
    return text;
}

sf::Text GUIElements::init_game_over_text() {
    sf::Text text = GUIElements::init_text();
    text.setString("GAME OVER");
    text.setCharacterSize(us * 3 / 2);
    text.setPosition(margin_left + us, margin_top + us * 3);
    text.setFillColor(sf::Color(0, 0, 0, 255));
    return text;
}

sf::Text GUIElements::init_game_over_score_label() {
    sf::Text text = GUIElements::init_text();
    text.setString("Score:");
    text.setPosition(margin_left + us * 4, margin_top + us * 7);
    text.setFillColor(sf::Color(0, 0, 0, 255));
    return text;
}

sf::Text GUIElements::init_game_over_score() {
    sf::Text text = GUIElements::init_text();
    text.setPosition(margin_left + us * 5, margin_top + us * 8);
    text.setFillColor(sf::Color(0, 0, 0, 255));
    return text;
}

sf::Text GUIElements::init_game_over_instruction_line1() {
    sf::Text text = GUIElements::init_text();
    text.setString("Press return key");
    text.setPosition(margin_left + us * 2, margin_top + us * 11);
    text.setFillColor(sf::Color(0, 0, 0, 255));
    return text;
}

sf::Text GUIElements::init_game_over_instruction_line2() {
    sf::Text text = GUIElements::init_text();
    text.setString("  to play again");
    text.setPosition(margin_left + us * 2, margin_top + us * 12);
    text.setFillColor(sf::Color(0, 0, 0, 255));
    return text;
}

} // namespace gui