#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

int main() {
	//	Paths to textures
	string background = "images/backgrounds/winter.png";
	string foreground = "images/characters/yoda.png";

	//	Initialize the textures & images
	Texture backgroundTex;
	if (!backgroundTex.loadFromFile(background)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}

	Texture foregroundTex;
	if (!foregroundTex.loadFromFile(foreground)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}


	Image backgroundImage;
	backgroundImage = backgroundTex.copyToImage();

	Image foregroundImage;
	foregroundImage = foregroundTex.copyToImage();

	//	Grab size and create output image container
	Vector2u sz = backgroundImage.getSize();
	Image outputImg = foregroundTex.copyToImage();

	//	Hardcode top-left pixel as the green screen colour
	Color bgColour = foregroundImage.getPixel(0, 0);

	for (int y = 0; y < sz.y; y++) {
		for (int x = 0; x < sz.x; x++) {
			//	Check if the pixel matches with the green screen colour
			Color pix = foregroundImage.getPixel(x, y);
			//	Replace if the pixel is matching with the background colour instead
			if (pix == bgColour)
				outputImg.setPixel(x, y, backgroundImage.getPixel(x, y));
		}
	}

	//	Render the window
	RenderWindow window(VideoMode(1024, 768), "Here's the output");
	Sprite sprite1;
	Texture tex1;

	tex1.loadFromImage(outputImg);
	sprite1.setTexture(tex1);

	window.clear();
	window.draw(sprite1);
	window.display();

	while (true);
}