#include <SFML/Graphics.hpp>

using namespace sf;

void menu(RenderWindow &window) {
	Texture  menuNewGameTexture, menuAboutProgrammTexture, menuExitTexture, devListTexture, menuBackground;
	menuNewGameTexture.loadFromFile("Images/newGame.png");
	menuAboutProgrammTexture.loadFromFile("Images/aboutProgramm.png");
	menuExitTexture.loadFromFile("Images/exit.png");
	devListTexture.loadFromFile("Images/devList.png");
	menuBackground.loadFromFile("Images/menu.png");
	Sprite newGame(menuNewGameTexture), aboutProgramm(menuAboutProgrammTexture), exit(menuExitTexture), devList(devListTexture), menuBg(menuBackground);
	bool isMenu = 1; // показывать меню
	int menuNum = 0; // вкладка из меню
	newGame.setPosition(100, 30);  // лева€ верхн€€ координата начала отображени€ кнопки
	aboutProgramm.setPosition(100, 90);
	exit.setPosition(100, 150);
	menuBg.setScale(3.24324f, 3.5971f); // раст€гивание картинки на главном меню
	menuBg.setPosition(0, 0);

	///////ћ≈Ќё///////
	while (isMenu) { // пока вкладка меню активна
		newGame.setColor(Color::White); // после того, как курсор убрали с кнопки, сделать кнопку снова светлой  
		aboutProgramm.setColor(Color::White);
		exit.setColor(Color::White);
		menuNum = 0;
		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { newGame.setColor(Color(255, 255, 255, 180)); menuNum = 1; } // при нахождении курсора в области с 100 и 30 по X и Y соответсвенно и в области с 300 и 50 по X и Y соответсвенно, тогда делать кнопку немного прозрачной и перейти по направлению кнопки
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { aboutProgramm.setColor(Color(255, 255, 255, 180)); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { exit.setColor(Color(255,255,255,180)); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (menuNum == 1) isMenu = false; // закрыть меню и перейти к игре
			if (menuNum == 2) {
				window.draw(devList); // показать лист разработчиков
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape)); // по нажатию кнопки Escape перейти обратно в меню
			}
			if (menuNum == 3){ 
				isMenu = false; // выключить меню
				window.close(); // закрыть окно игры
			}

		}

		window.draw(menuBg);
		window.draw(newGame);
		window.draw(aboutProgramm);
		window.draw(exit);

		window.display();
	}
}