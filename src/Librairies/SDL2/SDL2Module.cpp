/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** SDL2.cpp
*/

#include "SDL2Module.hpp"

Libs::SDL2Module::SDL2Module()
{
}

Libs::SDL2Module::~SDL2Module()
{
}

void Libs::SDL2Module::init(std::string name, int w, int h)
{
    this->_is_open = true;
	SDL_Init(SDL_INIT_VIDEO);
	this->window = SDL_CreateWindow((name + " sdl2").c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	atexit(SDL_Quit);

	//remove pressed key before sdl2
	SDL_Event event;
	int key = 0;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			key = event.key.keysym.sym;
			this->keyPressed[key] = true;
		}
	}
}

void Libs::SDL2Module::setSizePixel(std::pair<int, int> size)
{
    this->_sizePixel = size;
}

void Libs::SDL2Module::my_clear() const
{
	SDL_RenderClear(this->renderer);
}

void Libs::SDL2Module::display() const
{
	SDL_RenderPresent(this->renderer);
}

void Libs::SDL2Module::close()
{
    this->_is_open = false;
	for (auto it = this->_fonts.begin(); it != this->_fonts.end(); it++) {
		TTF_CloseFont(it->second);
	}
	for (auto it = this->_textures.begin(); it != this->_textures.end(); it++) {
		SDL_DestroyTexture(it->second);
	}
	SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
	TTF_Quit();
    SDL_Quit();
	this->_textures.clear();
	this->_shapes.clear();
	this->_fonts.clear();
}

bool Libs::SDL2Module::isOpen() const
{
	return this->_is_open;
}

bool Libs::SDL2Module::isKeyGameLib(int keyCode)
{
    if (keyCode == SDLK_a || keyCode == SDLK_b ||
    keyCode == SDLK_q || keyCode == SDLK_s) {
        return true;
    }
    return false;
}

std::vector<Arcade::KeyEvent_t> Libs::SDL2Module::getEvents()
{
    std::vector<Arcade::KeyEvent_t> vect;
	SDL_Event event;
	Arcade::KeyEvent_t eventK;
	int key = 0;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			eventK.key = mapEvent[SDL_QUIT];
			vect.push_back(eventK);
		} else if (event.type == SDL_KEYDOWN && !isKeyGameLib(event.key.keysym.sym)) {
			key = event.key.keysym.sym;
			eventK.key = mapEvent[key];
			// std::cout << key << ", " << mapEvent[key] << std::endl;
			vect.push_back(eventK);
		} else if (event.type == SDL_KEYUP && isKeyGameLib(event.key.keysym.sym)) {
			key = event.key.keysym.sym;
			if (this->keyPressed.find(key) == this->keyPressed.end() ||
            this->keyPressed[key] == false) {
                eventK.key = mapEvent[key];
				vect.push_back(eventK);
            } else {
                this->keyPressed[key] = false;
            }
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			eventK.key = Arcade::MouseClick;
			eventK.x = event.button.x;
			eventK.y = event.button.y;
			vect.push_back(eventK);
		}
	}
    return vect;
}

void Libs::SDL2Module::setBackgroundColor(int r, int g, int b)
{
	SDL_SetRenderDrawColor(this->renderer, r, g, b, 255);
}

void Libs::SDL2Module::draw(std::unordered_map<std::string, Arcade::Rect_t> shapes, std::unordered_map<std::string, Arcade::Sprites_t> sprites, std::unordered_map<std::string, Arcade::Text_t> texts)
{
	for (size_t layer = 0; layer < 4; layer++) {
		this->drawShape(shapes, layer);
		this->drawSprite(sprites, layer);
		this->drawText(texts, layer);
	}
}

void Libs::SDL2Module::drawTexture(Arcade::SpriteRect_t rect, SDL_Texture *texture, int x, int y)
{
	SDL_Rect texture_rect;

	texture_rect.x = x;
	texture_rect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &texture_rect.w, &texture_rect.h);
	if (!(rect.h == 0 && rect.maxH == 0 && rect.maxW == 0 && rect.w == 0 && rect.x == 0 && rect.y == 0)) {
		SDL_Rect texture_rect = {x, y, rect.w, rect.h};
		SDL_Rect int_rect = {rect.x, rect.y, rect.w, rect.h};
		SDL_RenderCopy(this->renderer, texture, &int_rect, &texture_rect);
	} else {
		SDL_RenderCopy(this->renderer, texture, NULL, &texture_rect);
	}
}

void Libs::SDL2Module::drawShape(std::unordered_map<std::string, Arcade::Rect_t> shapes, size_t layer)
{
	Arcade::Rect_t shape;

	for (auto it = shapes.begin(); it != shapes.end(); it++) {
		shape = it->second;
		if (shape.layer == layer) {
			if (this->_shapes.find(it->first) == this->_shapes.end()) {
				SDL_Rect rect;
				this->_shapes[it->first] = rect;
			}
			this->_shapes[it->first].x = shape.x;
			this->_shapes[it->first].y = shape.y;
			this->_shapes[it->first].w = shape.w;
			this->_shapes[it->first].h = shape.h;
			SDL_SetRenderDrawColor(this->renderer, shape.bg.r, shape.bg.g, shape.bg.b, shape.bg.a);
			SDL_RenderFillRect(this->renderer, &this->_shapes[it->first]);
			SDL_RenderDrawRect(this->renderer, &this->_shapes[it->first]);
			SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
		}
	}
}

void Libs::SDL2Module::drawSprite(std::unordered_map<std::string, Arcade::Sprites_t> sprites, size_t layer)
{
	Arcade::Sprites_t tmp;

	for (auto it = sprites.begin(); it != sprites.end(); it++) {
		tmp = it->second;
		if (tmp.layer == layer) {
			if (this->_textures.find(it->first) == this->_textures.end() ||
			it->first.compare("game") == 0) {
				SDL_Texture *texture;
				texture = IMG_LoadTexture(this->renderer, (tmp.path + ".png").c_str());
				this->_textures[it->first] = texture;
			}
			this->drawTexture(tmp.rect, this->_textures[it->first], tmp.x, tmp.y);
		}
	}
}

SDL_Texture *Libs::SDL2Module::createText(Arcade::Text_t text, TTF_Font *font)
{
	SDL_Color color = {(Uint8)text.colorText.r, (Uint8)text.colorText.g, (Uint8)text.colorText.b, (Uint8)text.colorText.a};
	SDL_Surface *surface = TTF_RenderText_Solid(font, text.text.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	return texture;
}

void Libs::SDL2Module::drawText(std::unordered_map<std::string, Arcade::Text_t> texts, size_t layer)
{
	Arcade::Text_t text;

	for (auto it = texts.begin(); it != texts.end(); it++) {
		text = it->second;
		if (text.layer == layer) {
			if (this->_textures.find(it->first) == this->_textures.end()) {
				TTF_Font *font = TTF_OpenFont("assets/arial.ttf", text.size);
				this->_fonts[it->first] = font;
			} else {
				SDL_DestroyTexture(this->_textures[it->first]);
			}
			this->_textures[it->first] = createText(text, this->_fonts[it->first]);
			this->drawTexture(Arcade::SpriteRect_t{0, 0, 0, 0, 0, 0}, this->_textures[it->first], text.x, text.y);
		}
	}
}

void Libs::SDL2Module::clearAssets()
{
    this->_textures.clear();
	this->_shapes.clear();
	this->_fonts.clear();
}

void Libs::SDL2Module::setSizeWindows(std::pair<int, int> size)
{
    SDL_SetWindowSize(this->window, size.first, size.second);
}

extern "C" {
    std::shared_ptr<Libs::IDisplayModule> create(void)
    {
        return std::make_shared<Libs::SDL2Module>();
    }
}
