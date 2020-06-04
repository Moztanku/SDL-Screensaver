#include"SDL.h"
#include"SDL_image.h"
#include<iostream>
#include<time.h>

class Game
{
public:
	Game();
	~Game();

	bool init(const char* title, int x, int y, int w, int h, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() {
		return _isRunning;
	}

private:
	int _cnt = 0, _whit = 0, _ehit = 0;
	bool _chg = false;
	bool _isRunning = 0;
	bool _direction = 0, direction_ = 0;
	SDL_Window *_window = nullptr;
	SDL_Renderer *_renderer = nullptr;
	SDL_Texture *_Sample_texture = nullptr;
	SDL_Rect _srcRect, _destRect;
};