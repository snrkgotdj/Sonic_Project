#pragma once

class Texture
	;
class StartBack
{
private:
	Texture* BackTex;
	Texture* BackTex1;

public:
	void init();
	void render(HDC _dc);
public:
	StartBack();
	~StartBack();
};

