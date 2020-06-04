#include "header.h"

Game::Game() {

}
Game::~Game() {

}

bool Game::init(const char* title, int x, int y, int w, int h, bool fullscreen) {
	srand(time(NULL));
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cerr << "SDL not initialized!" << std::endl;
		return false;
	}
	_window = SDL_CreateWindow(title, x, y, w, h, flags);
	if (_window == nullptr) {
		std::cerr << "Window not created!" << std::endl;
		return false;
	}
	_renderer = SDL_CreateRenderer(_window,-1,0);
	if (_renderer == nullptr) {
		std::cerr << "Renderer not created!" << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	_isRunning = true;
//Texture initialization
	SDL_Surface* tmpSurface = IMG_Load("assets/png/TEST_64.png");
	_Sample_texture = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
//
	_destRect.h = 128;
	_destRect.w = 128;
	return true;
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		_isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&_destRect.x, &_destRect.y);
			_destRect.w++;
			_destRect.h++;
			_destRect.x -= _destRect.w / 2;
			_destRect.y -= _destRect.h / 2;
			_direction = !_direction;
			direction_ = !direction_;
			SDL_DestroyTexture(_Sample_texture);
			switch (rand() % 8) {
			case 0: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64.png"); break;
			case 1: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_R.png"); break;
			case 2: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_G.png"); break;
			case 3: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_B.png"); break;
			case 4: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_C.png"); break;
			case 5: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_M.png"); break;
			case 6: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_Y.png"); break;
			case 7: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_K.png"); break;
			}
	default:
		break;
	}
}

void Game::update() {
	_cnt++;
	if (_direction) _destRect.x--;
		else _destRect.x++;
	if (direction_)	_destRect.y--;
		else _destRect.y++;
	if (_destRect.x == (800 - 128) || _destRect.x == 0) {
		_whit++;
		_chg = true;
		_direction = !_direction;
	}
	if (_destRect.y == (600 - 128) || _destRect.y == 0) {
		_whit++;
		_chg = true;
		direction_ = !direction_;
	}
	if ((_destRect.y == (600 - 128) || _destRect.y == 0) && (_destRect.x == (800 - 128) || _destRect.x == 0)) {
		_ehit++;
	}
	if ((_destRect.y == (600 - 128) || _destRect.y == 0) || (_destRect.x == (800 - 128) || _destRect.x == 0)) {
		SDL_DestroyTexture(_Sample_texture);
		switch (rand() % 8) {
		case 0: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64.png"); break;
		case 1: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_R.png"); break;
		case 2: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_G.png"); break;
		case 3: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_B.png"); break;
		case 4: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_C.png"); break;
		case 5: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_M.png"); break;
		case 6: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_Y.png"); break;
		case 7: _Sample_texture = IMG_LoadTexture(_renderer, "assets/png/TEST_64_K.png"); break;
		}
	}
	if (_chg) {
		system("cls");
		std::cout << "Wall_Hit - " << _whit << std::endl;
		std::cout << "Edge_Hit - " << _ehit << std::endl;
		std::cout << "Edge_Hit% - " << (double)(_ehit * 100) / _whit << "%" << std::endl;
		_chg = false;
	}
}

void Game::render() {
	SDL_RenderClear(_renderer);
	SDL_RenderCopy(_renderer, _Sample_texture, NULL, &_destRect);
	SDL_RenderPresent(_renderer);
}

void Game::clean() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}

// 00000001	00000010	
//