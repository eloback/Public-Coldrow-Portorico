#include "GameObject.h"
#include "TextureManager.h"


GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	this->xpos = x;
	this->ypos = y;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.h = 64;
	dstRect.w = 64;
}

void GameObject::Update() {
	//xpos++;
	//ypos++;
	
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

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

