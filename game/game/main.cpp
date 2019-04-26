#include <SFML/Graphics.hpp> // ����������� ���������� ��� ������ � ������������ ���������
#include <SFML/Audio.hpp> // ����������� ���������� ��� ������ � ����� ���������
#include <iostream>
#include <sstream> // ����������� ���������� ��� ������ �� ��������
#include "lowerMap1.h" // ����������� ���������� �����
#include "view.h" // ����������� ���������� ������ ��������
#include "begin.h" // ����������� ���������� � ��������� ����

using namespace sf; // ����������� ������������ ���� ���������� SFML
using namespace std; 

class objMap // ����� ��� �������� ����
{
public:
	Image image; // SFML ������ Image(��������)
	Texture texture; // SFML ������ Texture(��������)
	Sprite sprite; // // SFML ������ Sprite(������)
	objMap(String File) { // ����������� ������ � ���������� File || File - �������� ����������� � �����������
		image.loadFromFile("Images/" + File); // �������� ����������� �� ����
		texture.loadFromImage(image); // ��������� �������� �� �����������
		sprite.setTexture(texture); // ��������� ������� �� ��������
	}
};

class Player {
public:
	bool life = true, vozmozHodby = true, moveRight = true, moveLeft = true, moveUp = true, moveDown = true, newAccess = true; // life - ����� ���������, vozmozHodby - ����������� ������, moveRight - �������� ������, moveLeft - �������� �����, moveUp - �������� �����, moveDown - �������� , newAccess - . 
	float w, h, dx = 0, dy = 0, speed = 0, x, y, psevdoX, psevdoY; // w - ������ ��������������� ���������, h -  ������ ��������������� ���������, dx - ����������� �������� �� � , dy -  �� y , speed - �������� , x - ������� ���������� �� �, y - �� y, psevdoX  - ������� ���������� �� � � ���������� �������������, psevdoY - �� y
	int dir = 0, carrots = 0, Xm = 0, Ym = 0, oldX, oldY, direction = 0, gameLevel = 0; // dir - ���������� ���� ����������� , carrots - ���������� �������, Xm - ���������� ���������� ������ �� j , Ym - �� i , oldX - ��������� ����� �������� �� x , oldY - �� i, direction - ����������� ������ dir, gameLevel - ������� ����
	char stopElements[14] = { '0','u','l','d','r','!','?','(',')','#','L','U','D','R' }; // ��������, ����� ������� �������� ������ �� ����� 
	int k = sizeof(stopElements); // ���������� ������������ ���������
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	// ����������� ������
	Player(String F, float X, float Y, float W, float H) {
		File = F;
		w = W; h = H;
		image.loadFromFile("Images/" + File);
		image.createMaskFromColor(Color(255, 0, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y; // ������� ���������� �� ��� X � Y
		oldX = x, psevdoX = x; //old - ���������� �����, � �������� ������ ��������. psevdo - ����������, ������� ������ ����� ������������� � ���������� X � ���������� ���������
		oldY = y, psevdoY = y;
		sprite.setTextureRect(IntRect(224, 97, 32, 47));
	}
	//

	//�������� ������
	void update(float time) { // ��������� ���������� �������
		switch (dir) { // ����� ����������� ��������
		case 0: dx = speed; dy = 0; break; // ������
		case 1: dx = -speed; dy = 0; break; 
		case 2: dx = 0; dy = speed; break; // ����
		case 3: dx = 0; dy = -speed; break;
		}

		psevdoX += dx*time;
		if (psevdoX > oldX + 48) psevdoX = oldX + 48, vozmozHodby = true;
		if (psevdoX < oldX - 48) psevdoX = oldX - 48, vozmozHodby = true;
		x = psevdoX;
		psevdoY += dy*time;
		if (psevdoY > oldY + 48) psevdoY = oldY + 48, vozmozHodby = true;
		if (psevdoY < oldY - 48) psevdoY = oldY - 48, vozmozHodby = true;
		y = psevdoY;

		speed = 0;
		sprite.setPosition(x, y);
		interectionWithMap();

	}
	//

	//�������������� � ������
	void interectionWithMap() {
		for (int i = y / 48; i < (y + h) / 48; i++) {
			for (int j = x / 48; j < (x + w) / 48; j++) {
				for (int s = 0; s < k; s++) {
					if (TileMap[i][j] == stopElements[s]) { // ���� �������� ��������� �� ������ � ������������ ���������, ��
						if (dy > 0) {
							psevdoY = i * 48 - h; // ����������� �����
						}
						if (dy < 0) {
							psevdoY = i * 48 + 48; // ����������� ����
						}
						if (dx > 0) {
							psevdoX = j * 48 - w; // ����������� �����
						}
						if (dx < 0) {
							psevdoX = j * 48 + 48; // ����������� ������
						}
						vozmozHodby = true; // ��������� ������� ������� �����
					}
				}
				if (updateCarrots == true && vozmozHodby == false) { // ���� ��������� �������� ���������� �������� � ������ ���������, ��
					carrots = 0; // �������� ���-�� ��������
					updateCarrots = false; // ��������� �������� ���������
				}

				if (TileMap[i][j] == 'f' && vozmozHodby == true) { // ���� �������� �������� �� �����
					newMapActions(&y, &x, &carrots, &sprite, &gameLevel); // ������� � ������� ��� ���������� ������������
				}

				if (TileMap[i][j] == 'T' && vozmozHodby == true) { // ���� �������� �������� �� ������ � ��������� ������, ��
					life = false; // ����� ��������� �������������
				}

				if ((TileMap[i][j] == '3' || TileMap[i][j] == '4' || TileMap[i][j] == '2' || TileMap[i][j] == '1' || TileMap[i][j] == '-' || TileMap[i][j] == '|' || TileMap[i][j] == 't' || TileMap[i][j] == 'c') && newAccess == true) {
					Xm = j;
					Ym = i;
					chetvert = TileMap[i][j];
					newAccess = false;
				}
				if ((i != Ym || j != Xm) && vozmozHodby == true && newAccess == false) {
					zamenaPovorota(chetvert, Xm, Ym, carrots);
					newAccess = true;
				}

				moveDown = true;
				moveLeft = true;
				moveUp = true;
				moveRight = true;
				for (int s = 0; s < k; s++) {
					if (TileMap[i][j] == '1' || TileMap[i][j] == '4' || TileMap[i][j - 1] == '3' || TileMap[i][j - 1] == '2' || TileMap[i][j - 1] == '|' || TileMap[i][j] == '|' || (TileMap[i][j] == 't' && TileMap[i][j - 1] == stopElements[s])) moveLeft = false;
					if (TileMap[i][j] == '3' || TileMap[i][j] == '2' || TileMap[i][j + 1] == '4' || TileMap[i][j + 1] == '1' || TileMap[i][j + 1] == '|' || TileMap[i][j] == '|' || (TileMap[i][j] == 't' && TileMap[i][j + 1] == stopElements[s])) moveRight = false;
					if (TileMap[i][j] == '3' || TileMap[i][j] == '4' || TileMap[i - 1][j] == '2' || TileMap[i - 1][j] == '1' || TileMap[i - 1][j] == '-' || TileMap[i][j] == '-' || (TileMap[i][j] == 't' && TileMap[i + 1][j] == stopElements[s])) moveUp = false;
					if (TileMap[i][j] == '1' || TileMap[i][j] == '2' || TileMap[i + 1][j] == '4' || TileMap[i + 1][j] == '3' || TileMap[i + 1][j] == '-' || TileMap[i][j] == '-' || (TileMap[i][j] == 't' && TileMap[i - 1][j] == stopElements[s])) moveDown = false;
				}
			}
		}
	}
};

int main()
{
	RenderWindow window(VideoMode(1200, 1000), "Game"); // �������� ���� �������� 600 � 600 ��������
	menu(window); // ����������� ����
	view.reset(FloatRect(0, 200, 500, 500));//���������� �������� ������ �� ����������

	Player p("Rabbit.png", 144.0, 432.0, 48.0, 48.0); // �������� ������� � ������ Player �� ���������� ����������� ( ����, �� �������� ���������� ����� �������� ������  , ���������� ���������� �� x , �� y , ������� ������ �� x , �� y

	objMap Map("map.png"); // �������� ������� Map ������ objMap

	Music music; // �������� ������� ������
	music.openFromFile("Sounds/main.ogg"); // �������� ����� ������� ������
	music.play(); // ������ ������
	music.setLoop(true);

	Font font; // �������� ������� ������
	font.loadFromFile("arial.ttf"); // �������� ������ �� ������ 
	//��� �������
	Text text("", font, 30); // �������� ������� ����� � ����������� ( "�����" , ����� , ������ ������ )
	text.setFillColor(Color::White); // ���� ������
	text.setStyle(Text::Bold); // ����� ������
	//��� �������
	Text text1("", font, 20);
	text1.setFillColor(Color::White);
	text1.setStyle(Text::Bold);
	//��� ������
	Text text2("", font, 80);
	text2.setFillColor(Color::Blue);
	text2.setStyle(Text::Bold);

	Image carrot_image; 
	carrot_image.loadFromFile("Images/Rabbit.png");
	carrot_image.createMaskFromColor(Color(255, 0, 255)); // �������� ����� (������������) ��� ����� �� ����� RGB (red , green , blue )
	Texture carrot_texture;
	carrot_texture.loadFromImage(carrot_image);
	Sprite carrot_sprite;
	carrot_sprite.setTexture(carrot_texture);
	carrot_sprite.setTextureRect(IntRect(287, 199, 28, 27));

	//����� ������
	Image lev_Finish;
	lev_Finish.loadFromFile("Images/levelFinish.png");
	lev_Finish.createMaskFromColor(Color(185, 122, 87));
	Texture leve_Finish;
	leve_Finish.loadFromImage(lev_Finish);
	Sprite level_Finish;
	level_Finish.setTexture(leve_Finish);
	//

	float currentFrame = 0; // ������� ���� ��������
	bool legDown = false; // ��������� ����
	bool rabbitDeathAnim = false; // ��������������� ������ ���������
	bool deathAccept = false;  // ������������� ������ �������� ������

	Clock clock; // �������� �������� �������
	Clock timer1;
	Clock gameTimeClock;
	int gameTime = 0; // ������� �����
	int prevGameLevel = 0;

	while (window.isOpen()) // ���� ���� �������
	{
		float timer = timer1.getElapsedTime().asSeconds(); // ������ ������� � ��������
		float time = clock.getElapsedTime().asMicroseconds();  // ������ ������� � �������������
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); // ���� �������� ���, �� ����� ������ ������� ����
		clock.restart(); // ���������� �������
		time = time / 700; // "������������ ��������"
		Event event; // �������� ������� �������

		while (window.pollEvent(event)) // ���� ���������� ����� ���� �������
		{
			if (event.type == Event::Closed) // ���� ���� ������� ���������� ����, �� ����� ������� � ���� ����
				window.close(); // ������� ����
		}

		//�����
		if (p.life) { //���� �������� ���, ��
			if (p.vozmozHodby && timer > 0.01) { // ���� �� ����� ������ � ����� �������� ����� ������� �������� ������ ���������, ��
				if (Keyboard::isKeyPressed(Keyboard::Up) && p.moveUp == true) { // ��� ������� ������� ����� � ���������� �� ������ �����
					p.oldX = p.x; // ����������� ���������� X �� ������ ������ ������
					p.oldY = p.y; // ����������� ���������� Y �� ������ ������ ������
					p.vozmozHodby = false; // ������ �� ������
					p.direction = 3; // ����������� ��������
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) && p.moveDown == true) { // ��� ������� ������� ���� � ���������� �� ������ ����
					p.oldX = p.x;
					p.oldY = p.y;
					p.vozmozHodby = false;
					p.direction = 2;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left) && p.moveLeft == true) { // ��� ������� ������� ����� � ���������� �� ������ �����
					p.oldX = p.x;
					p.oldY = p.y;
					p.vozmozHodby = false;
					p.direction = 1;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) && p.moveRight == true) { // ��� ������� ������� ������ � ���������� �� ������ ������
					p.oldX = p.x;
					p.oldY = p.y;
					p.vozmozHodby = false;
					p.direction = 0;
				}
				else {
					if (timer > 4) { // ���� ������� ������������ ��������� �� ���� ������ � ������� 4 ������
						if (legDown) {// ���� ���� �������
							currentFrame += 0.007*time;// �������� ����� �������� ����� 
							if (currentFrame > 3) currentFrame = 0, legDown = false; // ��������� �������� ����� � ������� � ��������� ���� � �������� ���������
							p.sprite.setTextureRect(IntRect(450 - 32 * int(currentFrame), 208, 32, 47)); // ������� ������ ��� ������� ��������� ����
						}
						else if (!legDown) { // ���� ���� �������
							currentFrame += 0.007*time;
							if (currentFrame > 3) currentFrame = 0, legDown = true;
							p.sprite.setTextureRect(IntRect(386 + 32 * int(currentFrame), 208, 32, 47)); // ������� ������ ��� ������� �������� ����
						}
					}
				}
			}
			if (!p.vozmozHodby) { 
				p.dir = p.direction; // ����������� ��������
				p.speed = 0.1; // �������� ���������
				currentFrame += 0.007*time; // �������� ����� ������ ��������
				if (currentFrame > 8) currentFrame = 0;
				if (p.direction == 3) p.sprite.setTextureRect(IntRect(32 * int(currentFrame), 50, 32, 47));
				if (p.direction == 2) p.sprite.setTextureRect(IntRect(32 * int(currentFrame), 97, 32, 46));
				if (p.direction == 1) p.sprite.setTextureRect(IntRect(32 * int(currentFrame), 0, 32, 49));
				if (p.direction == 0) p.sprite.setTextureRect(IntRect(32 * int(currentFrame) - 1, 144, 32, 49));
				timer1.restart(); // ���������� ������� �������� ������ ���������
				if (p.x > p.oldX + 48 || p.x < p.oldX - 48 || p.y > p.oldY + 48 || p.y < p.oldY - 48) { // ���� ������� ���������� ��������� ��������� �������� ���� �����
					p.vozmozHodby = true; // ���������� �� ������ �� ������� ���������� ���������� ����
				}
				getPlayerCoordinateView(p.x, p.y);// �������� ��������� ��������� ��� ���������� ������ �� ���
			}
		}
		
		p.update(time); // �������� ������� ��� ����������� ������ ���������
		window.clear(); // ������� ����� ������ �� ���� ���������� ������������ �����������
		window.setView(view); //��������� ������ ��������

		//����������� ����� �� ������
		for (int i = 0; i < HEIGHT_MAP1; i++) {
			for (int j = 0; j < WIDTH_MAP1; j++) {
				if (TileMap[i][j] == 'l') Map.sprite.setTextureRect(IntRect(0, 0, 48, 48));// ����� � ��������� ����� �����
				if (TileMap[i][j] == 'u') Map.sprite.setTextureRect(IntRect(48, 0, 48, 48));// ����� � ��������� ����� ������
				if (TileMap[i][j] == 'd') Map.sprite.setTextureRect(IntRect(96, 0, 48, 48));// ����� � ��������� ����� �����
				if (TileMap[i][j] == 'r') Map.sprite.setTextureRect(IntRect(144, 0, 48, 48));// ����� � ��������� ����� ������
				if (TileMap[i][j] == '0') Map.sprite.setTextureRect(IntRect(192, 0, 48, 48));// ������ ������� �����
				if (TileMap[i][j] == 'c') Map.sprite.setTextureRect(IntRect(240, 0, 48, 48));// �������
				if (TileMap[i][j] == 'p') Map.sprite.setTextureRect(IntRect(288, 0, 48, 48));// ��� �� �������
				if (TileMap[i][j] == ' ') Map.sprite.setTextureRect(IntRect(336, 0, 48, 48));// �����
				if (TileMap[i][j] == 's') Map.sprite.setTextureRect(IntRect(384, 0, 48, 48));// ����� ����������� ���������
				if (TileMap[i][j] == 'f') Map.sprite.setTextureRect(IntRect(432, 0, 48, 48));// �����

				// ��� ����� ��������� � ���������� ������������ ��������� � � ���������
				if (TileMap[i][j] == '3') Map.sprite.setTextureRect(IntRect(576, 0, 48, 48));// 3 �������� ������������ ���������
				if (TileMap[i][j] == '4') Map.sprite.setTextureRect(IntRect(624, 0, 48, 48));// 4 �������� ������������ ���������
				if (TileMap[i][j] == '2') Map.sprite.setTextureRect(IntRect(672, 0, 48, 48));// 2 �������� ������������ ���������
				if (TileMap[i][j] == '1') Map.sprite.setTextureRect(IntRect(720, 0, 48, 48));// 1 �������� ������������ ���������
				//

				if (TileMap[i][j] == '|') Map.sprite.setTextureRect(IntRect(768, 0, 48, 48));// ������������ ����� ������������ ���������
				if (TileMap[i][j] == '-') Map.sprite.setTextureRect(IntRect(816, 0, 48, 48));// �������������� ����� �������� ������������ ���������
				if (TileMap[i][j] == '!') Map.sprite.setTextureRect(IntRect(960, 0, 48, 48));// ������������ �����
				if (TileMap[i][j] == '(') Map.sprite.setTextureRect(IntRect(1008, 0, 48, 48));// ����� ����� ������
				if (TileMap[i][j] == '#') Map.sprite.setTextureRect(IntRect(1056, 0, 48, 48));// ����������� ����� � ������ ����� ������
				if (TileMap[i][j] == ')') Map.sprite.setTextureRect(IntRect(1104, 0, 48, 48));// ������ ����� ������
				if (TileMap[i][j] == 'T') Map.sprite.setTextureRect(IntRect(1631, 0, 48, 48));// �������������� ������� � ������
				if (TileMap[i][j] == 't') Map.sprite.setTextureRect(IntRect(1679, 0, 48, 48));// ���������������� ������� � ������
				if (TileMap[i][j] == 'U') Map.sprite.setTextureRect(IntRect(1440, 0, 48, 48));// ����� � ��������� ����� ����� � �����
				if (TileMap[i][j] == 'R') Map.sprite.setTextureRect(IntRect(1488, 0, 48, 48));// ����� � ��������� ����� ������ � ������
				if (TileMap[i][j] == 'D') Map.sprite.setTextureRect(IntRect(1536, 0, 48, 48));// ����� � ��������� ����� ������ � �����
				if (TileMap[i][j] == 'L') Map.sprite.setTextureRect(IntRect(1584, 0, 48, 48));// ����� � ��������� ����� ����� � ������
				Map.sprite.setPosition(j * 48, i * 48); // ��������� ���������� ������ ����� �� ������ || (j * 48, i * 48) ��� ��� ������ ���������� �������� ����� ������� 48 � 48 �������� 
				window.draw(Map.sprite); // ����������� ������� �����
			}
		}
		//

		//����������� ���������
		if (p.life) { // ���� ����� ���,
			window.draw(p.sprite); // �� �������� �������� ���������
		}
		else if (!rabbitDeathAnim) { // ����� ���� �������� ������ ��������� ��� �� ���� ��������������, ��
			if (!deathAccept) { // ������ �������� ��� �� ��������
				currentFrame = 0; // ��������� �������� ����� �������� � 0 ��� ������� ��������������� �������� ������ ���������
				deathAccept = true; // ������ �������� ��� ������
			}
			currentFrame += 0.005 * time; // �������� ����� ������ ��������
			if (currentFrame > 8) rabbitDeathAnim = true; // ���� �������� ������ ��������� ��������������, �� �������� ������ ������ �� ��������������
			p.sprite.setTextureRect(IntRect(32 * int(currentFrame), 192, 32, 49)); // ��������� ��������� ����������� ��������
			window.draw(p.sprite); 
		}
		if (rabbitDeathAnim) { 
			p.sprite.setTextureRect(IntRect(224, 192, 32, 49)); // ����������� ���������� ����� ��������� ����������
			window.draw(p.sprite);
		}
		//

		// ����� �� ����� ���������� ��������� ������� 
		ostringstream playerScoreString; // �������� ������� ������
		playerScoreString << p.carrots;// ��������� � ������
		text.setString(playerScoreString.str());// �������������� � ��� ������ ��� ����� �� �����
		text.setPosition(view.getCenter().x + 200, view.getCenter().y - 235);// ������������ ������ �� �������� ����������� || view.getCenter().x + 200 - ����� ���������� � ������������ ������ � �������� � ��� 200 ��������
		window.draw(text);// ����� ����� �� ����� 
		//

		//����� �� ����� ���������� �������� �������
		ostringstream gameTimeString;
		gameTimeString << gameTime;
		text1.setString("Time: " + gameTimeString.str());
		text1.setPosition(view.getCenter().x - 230, view.getCenter().y - 235);
		window.draw(text1);
		//

		//����� �� ����� ����������� ������� 
		carrot_sprite.setPosition(view.getCenter().x + 170, view.getCenter().y - 230);
		window.draw(carrot_sprite);
		//

		ostringstream levelFinish;
		levelFinish << p.gameLevel;
		if (prevGameLevel + 1 == p.gameLevel) { //���� ������� ������� ������ ����������� �� 1 , �� 
			p.vozmozHodby = false; // ������������� ������ ���������
			if (Keyboard::isKeyPressed(Keyboard::Space)) {  // ��� ������� ������� space
				prevGameLevel++; // ��������� ������� ���������� ����
				p.vozmozHodby = true; // ��������� ������
			}
			else {
				level_Finish.setPosition(view.getCenter().x - 250, view.getCenter().y - 250); 
				text2.setString(levelFinish.str());
				text2.setPosition(view.getCenter().x + 40, view.getCenter().y - 80);
				window.draw(level_Finish);
				window.draw(text2);
			}
		}
		//

		//�������� ����������� � ����
		window.display();
		//
	}

	return 0;
}