#include "GameObject.h"
#include "TextureManager.h"


GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	this->xpos = x;
	this->ypos = y;
	
	srcRect = { 0, 0, 80, 80 };
	dstRect.h = 64;
	dstRect.w = 64;
}

GameObject::~GameObject()
{
	SDL_DestroyTexture(objTexture);
}

void GameObject::Update() {
	dstRect.x = xpos;
	dstRect.y = ypos;
	dstRect.h = srcRect.h * 2;
	dstRect.w = srcRect.w * 2;
}

void GameObject::Render() {
	TextureManager::Draw(objTexture, srcRect, dstRect);
}

void GameObject::Collision(int x, int y)
{
}

