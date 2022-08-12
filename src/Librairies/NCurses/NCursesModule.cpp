/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** NCurses.cpp
*/

#include "NCursesModule.hpp"

Libs::NCursesModule::NCursesModule()
{
    this->_colors.push_back({0, 0, 0, 0, 0, 0});         //Black Black
    this->_colors.push_back({0, 0, 0, 255, 0, 0});       //Black Red
    this->_colors.push_back({0, 0, 0, 0, 255, 0});       //Black Green
    this->_colors.push_back({0, 0, 0, 255, 255, 0});     //Black Yellow
    this->_colors.push_back({0, 0, 0, 0, 0, 255});       //Black Blue
    this->_colors.push_back({0, 0, 0, 255, 0, 255});     //Black Magenta
    this->_colors.push_back({0, 0, 0, 0, 255, 255});     //Black Cyan
    this->_colors.push_back({0, 0, 0, 255, 255, 255});   //Black White
    this->_colors.push_back({255, 255, 255, 0, 0, 0});   //Black White
    this->_colors.push_back({0, 0, 255, 0, 0, 255});     //Blue Blue
    this->_colors.push_back({255, 255, 0, 0, 0, 0});     //Yellow Black
}

Libs::NCursesModule::~NCursesModule()
{
    this->_is_open = false;
    endwin();
}

void Libs::NCursesModule::init(std::string name, int w, int h)
{
    (void) name;
    this->window = initscr();
    this->width = w;
    this->height = h;
    noecho();
    nodelay(this->window, true);
    curs_set(FALSE);
    mousemask(BUTTON1_PRESSED | BUTTON2_PRESSED, NULL);
    keypad(stdscr, TRUE);
    start_color();
    init_color(0, 0, 0, 0);
    init_pair(0, COLOR_BLACK, 0);
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
    init_pair(9, COLOR_BLUE, COLOR_BLUE);
    init_pair(10, COLOR_YELLOW, COLOR_BLACK);
    _is_open = true;
}

void Libs::NCursesModule::setSizePixel(std::pair<int, int> size)
{
    this->_sizePixel = size;
}

void Libs::NCursesModule::my_clear() const
{
    refresh();
    erase();
}

void Libs::NCursesModule::display() const
{

}

void Libs::NCursesModule::close()
{
    this->_is_open = false;
    endwin();
}

bool Libs::NCursesModule::isOpen() const
{
    return (this->_is_open);
}

void Libs::NCursesModule::setBackgroundColor(int r, int g, int b)
{
    int pair = this->getIndexColor({0, 0, 0, 255}, {r, g, b, 255});

    wattron(this->window, COLOR_PAIR(pair));
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLS; j++) {
            enc.my_mvprintw(i, j, " ");
        }
    }
    wattroff(this->window, COLOR_PAIR(pair));
}

int getKey(void)
{
    int ch = getch();

    if (ch != ERR) {
        return ch;
    } else {
        return 0;
    }
}

std::vector<Arcade::KeyEvent_t> Libs::NCursesModule::getEvents()
{
    MEVENT mouse;
    std::vector<Arcade::KeyEvent_t> vect;
    Arcade::KeyEvent_t event;
    int key = getKey();

    if (key == KEY_MOUSE) {
        if (getmouse(&mouse) == 0) {
            if(mouse.bstate & BUTTON1_PRESSED || mouse.bstate & BUTTON2_PRESSED) {
                event.key = Arcade::MouseClick;
                event.x = mouse.x * this->width / COLS;
                event.y = mouse.y * this->height / LINES;
            }
        }
    } else {
        event.key = mapEvent[key];
    }
    vect.push_back(event);
    return vect;
}

void Libs::NCursesModule::draw(std::unordered_map<std::string, Arcade::Rect_t> shapes, std::unordered_map<std::string, Arcade::Sprites_t> sprites, std::unordered_map<std::string, Arcade::Text_t> texts)
{
    for (size_t layer = 0; layer < 4; layer++) {
	    this->drawShape(shapes, layer);
        this->drawSprite(sprites, layer);
	    this->drawText(texts, layer);
    }
}

int Libs::NCursesModule::getIndexColor(Arcade::Color_t text, Arcade::Color_t bg)
{
    std::vector<int> rgb;
    std::vector<int> rgb2;
    int pair = -1;
    int score = 0;
    int bestScore = 9999;
    int diff = 0;

    rgb.push_back(text.r);
    rgb.push_back(text.g);
    rgb.push_back(text.b);
    rgb.push_back(bg.r);
    rgb.push_back(bg.g);
    rgb.push_back(bg.b);
    for (size_t i = 0; i < this->_colors.size(); i++) {
        score = 0;
        for (size_t j = 0; j < 6; j++) {
            diff = this->_colors[i][j] - rgb[j];
            diff = diff < 0 ? diff * -1 : diff;
            score += diff;
        }
        if (score < bestScore) {
            pair = i;
            bestScore = score;
        }
    }
    return (pair);
}

void Libs::NCursesModule::drawShape(std::unordered_map<std::string, Arcade::Rect_t> shapes, size_t layer)
{
    Arcade::Rect_t shape;
    int pair = 0;
    int y, x, h, w = 0;
    Arcade::Color_t textColor;
    Arcade::Color_t bgColor;

    for (auto it = shapes.begin(); it != shapes.end(); it++) {
        shape = it->second;
        if (shape.layer == layer) {
            textColor = {0, 0, 0, 255};
            bgColor = {shape.bg.r, shape.bg.g, shape.bg.b, shape.bg.a};
            pair = this->getIndexColor(textColor, bgColor);
            wattron(this->window, COLOR_PAIR(pair));
            setPixelPosition(y, x, shape.y, shape.x);
            setPixelPosition(h, w, shape.h, shape.w);
            centerPixelPosition(y, x);
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    enc.my_mvprintw(y + i, x + j, " ");
                }
            }
            wattroff(this->window, COLOR_PAIR(pair));
        }
    }
}

void Libs::NCursesModule::drawSprite(std::unordered_map<std::string, Arcade::Sprites_t> sprites, size_t layer)
{
    Arcade::Sprites_t sprite;
    int pair = 0;
    int y = 0;
    int x = 0;
    Arcade::Color_t textColor;
    Arcade::Color_t bgColor;

    for (auto it = sprites.begin(); it != sprites.end(); it++) {
        sprite = it->second;
        if (sprite.layer == layer) {
            if (this->_sprites.find(it->first) == this->_sprites.end() ||
            it->first.compare("game") == 0) {
                File file;
                this->_sprites[it->first] = file.readFile(sprite.path + ".txt");
            }
            textColor = {sprite.text.r, sprite.text.g, sprite.text.b, sprite.text.a};
            bgColor = {sprite.bg.r, sprite.bg.g, sprite.bg.b, sprite.bg.a};
            pair = this->getIndexColor(textColor, bgColor);
            wattron(this->window, COLOR_PAIR(pair));
            setPixelPosition(y, x, sprite.y, sprite.x);
            centerPixelPosition(y, x);
            for (std::string line : this->_sprites[it->first]) {
                enc.my_mvprintw(y, x, line);
                y += 1;
            }
            wattroff(this->window, COLOR_PAIR(pair));
        }
    }
}

void Libs::NCursesModule::drawText(std::unordered_map<std::string, Arcade::Text_t> texts, size_t layer)
{
    Arcade::Text_t text;
    int x, y = 0;

	for (auto it = texts.begin(); it != texts.end(); it++) {
		text = it->second;
        if (text.layer == layer) {
            setPixelPosition(y, x, text.y, text.x);
            centerPixelPosition(y, x);
            enc.my_mvprintw(y, x, text.text);
        }
	}
}

int Libs::NCursesModule::setPixelPosition(int &y, int &x, int positionY, int positionX)
{
    if (this->_sizePixel.second > 0) {
        y = positionY / this->_sizePixel.second;
    } else {
        y = positionY * LINES / this->height;
    }
    if (this->_sizePixel.first > 0) {
        x = positionX / this->_sizePixel.first;
    } else {
        x = positionX * COLS / this->width;
    }
}

void Libs::NCursesModule::centerPixelPosition(int &y, int &x)
{
    int addY = (LINES - (this->height / this->_sizePixel.second)) / 2;
    int addX = (COLS - (this->width / this->_sizePixel.first)) / 2;

    if (this->_sizePixel.second > 0 && this->_sizePixel.first > 0) {
        y += addY;
        x += addX;
    }
}

void Libs::NCursesModule::clearAssets()
{
    this->_shapes.clear();
    this->_sprites.clear();
}

void Libs::NCursesModule::setSizeWindows(std::pair<int, int> size)
{
    
}

extern "C" {
    std::shared_ptr<Libs::IDisplayModule> create(void)
    {
        return std::make_shared<Libs::NCursesModule>();
    }
}
