/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** SFMLModule.cpp
*/

#include "SFMLModule.hpp"

Libs::SFMLModule::SFMLModule()
{
    this->_window = nullptr;
    this->color = sf::Color::Black;
}

Libs::SFMLModule::~SFMLModule()
{
}

void Libs::SFMLModule::init(std::string name, int w, int h)
{
    this->_window = new sf::RenderWindow(sf::VideoMode(w, h), name);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->keyPressed[sf::Keyboard::A] = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        this->keyPressed[sf::Keyboard::Z] = true;
}

void Libs::SFMLModule::setSizePixel(std::pair<int, int> size)
{
    this->_sizePixel = size;
}

void Libs::SFMLModule::my_clear() const
{
    this->_window->clear(this->color);
}

void Libs::SFMLModule::display() const
{
    this->_window->display();
}

void Libs::SFMLModule::close()
{
    if (isOpen()) {
        this->_window->close();
    }
}

bool Libs::SFMLModule::isOpen() const
{
    if (this->_window == nullptr)
        return (false);
    if (!this->_window->isOpen()) {
        delete this->_window;
        return (false);
    }
    return (true);
}

void Libs::SFMLModule::setBackgroundColor(int r, int g, int b)
{
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
    this->color.a = 255;
}

bool Libs::SFMLModule::isKeyGameLib(int keyCode)
{
    if (keyCode == sf::Keyboard::A || keyCode == sf::Keyboard::B ||
    keyCode == sf::Keyboard::Q || keyCode == sf::Keyboard::S) {
        return true;
    }
    return false;
}

std::vector<Arcade::KeyEvent_t> Libs::SFMLModule::getEvents()
{
    std::vector<Arcade::KeyEvent_t> vect;

    while ((*this->_window).pollEvent(this->_event))
    {
        if (this->_event.type == sf::Event::Closed)
            (*this->_window).close();
        if (this->_event.type == sf::Event::KeyPressed && !isKeyGameLib(this->_event.key.code)) {
            Arcade::KeyEvent_t event;
            event.key = mapEvent[this->_event.key.code];
            vect.push_back(event);
        } else if (this->_event.type == sf::Event::KeyReleased && isKeyGameLib(this->_event.key.code)) {
            if (this->keyPressed.find(this->_event.key.code) == this->keyPressed.end() ||
            this->keyPressed[this->_event.key.code] == false) {
                Arcade::KeyEvent_t event;
                event.key = mapEvent[this->_event.key.code];
                vect.push_back(event);
            } else {
                this->keyPressed[this->_event.key.code] = false;
            }
        }
        if (this->_event.type == sf::Event::MouseButtonReleased) {
            Arcade::KeyEvent_t event;
            event.key = Arcade::KeyState::MouseClick;
            event.x = this->_event.mouseButton.x;
            event.y = this->_event.mouseButton.y;
            vect.push_back(event);
        }
    }
    return vect;
}

void Libs::SFMLModule::draw(std::unordered_map<std::string, Arcade::Rect_t> shapes, std::unordered_map<std::string, Arcade::Sprites_t> sprites, std::unordered_map<std::string, Arcade::Text_t> texts)
{
    for (size_t layer = 0; layer < 4; layer++) {
        this->drawShape(shapes, layer);
        this->drawSprite(sprites, layer);
        this->drawText(texts, layer);
    }
}

void Libs::SFMLModule::drawShape(std::unordered_map<std::string, Arcade::Rect_t> shapes, size_t layer)
{
    Arcade::Rect_t shape;

    for (auto it = shapes.begin(); it != shapes.end(); it++) {
        shape = it->second;
        if (shape.layer == layer) {
            if (this->_shapes.find(it->first) == this->_shapes.end()) {
                sf::RectangleShape rec(sf::Vector2f(shape.w, shape.h));
                this->_shapes[it->first] = rec;
            } else {
                this->_shapes[it->first].setSize(sf::Vector2f(shape.w, shape.h));
            }
            this->_shapes[it->first].setFillColor(sf::Color(shape.bg.r, shape.bg.g, shape.bg.b, shape.bg.a));
            this->_shapes[it->first].setPosition(sf::Vector2f(shape.x, shape.y));
            this->_window->draw(this->_shapes[it->first]);
        }
    }
}

void Libs::SFMLModule::drawSprite(std::unordered_map<std::string, Arcade::Sprites_t> sprites, size_t layer)
{
    Arcade::Sprites_t tmp;

    for (auto it = sprites.begin(); it != sprites.end(); it++) {
        tmp = it->second;
        if (tmp.layer == layer) {
            if (this->_sprites.find(it->first) == this->_sprites.end() ||
            it->first.compare("game") == 0) {
                sf::Texture texture;
                texture.loadFromFile(tmp.path + ".png");
                this->_textures[it->first] = texture;
                sf::Sprite sprite;
                sprite.setTexture(this->_textures[it->first]);
                this->_sprites[it->first] = sprite;
            }
            sf::IntRect rect;
            rect.left = tmp.rect.x;
            rect.top = tmp.rect.y;
            rect.width = tmp.rect.w;
            rect.height = tmp.rect.h;
            this->_sprites[it->first].setTextureRect(rect);
            this->_sprites[it->first].setPosition(sf::Vector2f(tmp.x, tmp.y));
            this->_window->draw(this->_sprites[it->first]);
        }
    }
}

void Libs::SFMLModule::drawText(std::unordered_map<std::string, Arcade::Text_t> texts, size_t layer)
{
    Arcade::Text_t text;

    for (auto it = texts.begin(); it != texts.end(); it++) {
        text = it->second;
        if (text.layer == layer) {
            if (this->_texts.find(it->first) == this->_texts.end()) {
                sf::Font font;
                font.loadFromFile(text.font);
                this->_fonts[it->first] = font;
                sf::Text textObj(text.text, this->_fonts[it->first], text.size);
                this->_texts[it->first] = textObj;
            } else {
                this->_texts[it->first].setCharacterSize(text.size);
                this->_texts[it->first].setString(text.text);
            }
            this->_texts[it->first].setFillColor(sf::Color(text.colorText.r, text.colorText.g, text.colorText.b, text.colorText.a));
            this->_texts[it->first].setPosition(sf::Vector2f(text.x, text.y));
            this->_window->draw(this->_texts[it->first]);
        }
    }
}

void Libs::SFMLModule::clearAssets()
{
    this->_shapes.clear();
    this->_sprites.clear();
    this->_texts.clear();
    this->_textures.clear();
}

void Libs::SFMLModule::setSizeWindows(std::pair<int, int> size)
{
    const sf::Vector2u sizeWindow = {size.first, size.second};
    sf::FloatRect sizeView(0, 0, size.first, size.second);

    this->_window->setSize(sizeWindow);
    this->_window->setView(sf::View(sizeView));
}

extern "C" {
    std::shared_ptr<Libs::IDisplayModule> create(void)
    {
        return std::make_shared<Libs::SFMLModule>();
    }
}
