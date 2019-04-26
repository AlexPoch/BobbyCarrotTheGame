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
	bool isMenu = 1; // ���������� ����
	int menuNum = 0; // ������� �� ����
	newGame.setPosition(100, 30);  // ����� ������� ���������� ������ ����������� ������
	aboutProgramm.setPosition(100, 90);
	exit.setPosition(100, 150);
	menuBg.setScale(3.24324f, 3.5971f); // ������������ �������� �� ������� ����
	menuBg.setPosition(0, 0);

	///////����///////
	while (isMenu) { // ���� ������� ���� �������
		newGame.setColor(Color::White); // ����� ����, ��� ������ ������ � ������, ������� ������ ����� �������  
		aboutProgramm.setColor(Color::White);
		exit.setColor(Color::White);
		menuNum = 0;
		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { newGame.setColor(Color(255, 255, 255, 180)); menuNum = 1; } // ��� ���������� ������� � ������� � 100 � 30 �� X � Y ������������� � � ������� � 300 � 50 �� X � Y �������������, ����� ������ ������ ������� ���������� � ������� �� ����������� ������
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { aboutProgramm.setColor(Color(255, 255, 255, 180)); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { exit.setColor(Color(255,255,255,180)); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (menuNum == 1) isMenu = false; // ������� ���� � ������� � ����
			if (menuNum == 2) {
				window.draw(devList); // �������� ���� �������������
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape)); // �� ������� ������ Escape ������� ������� � ����
			}
			if (menuNum == 3){ 
				isMenu = false; // ��������� ����
				window.close(); // ������� ���� ����
			}

		}

		window.draw(menuBg);
		window.draw(newGame);
		window.draw(aboutProgramm);
		window.draw(exit);

		window.display();
	}
}