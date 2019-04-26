#include <SFML/Graphics.hpp> // подключение библиотеки для работы с графическими объектами
#include <SFML/Audio.hpp> // подключение библиотеки для работы с аудио объектами
#include <iostream>
#include <sstream> // подключение библиотеки для работы со строками
#include "lowerMap1.h" // подключение библиотеки карты
#include "view.h" // подключение библиотеки камеры слежения
#include "begin.h" // подключение библиотеки с начальным меню

using namespace sf; // подключение пространства имен библиотеки SFML
using namespace std; 

class objMap // класс для создания карт
{
public:
	Image image; // SFML объект Image(картинка)
	Texture texture; // SFML объект Texture(текстура)
	Sprite sprite; // // SFML объект Sprite(спрайт)
	objMap(String File) { // конструктор класса с аргументом File || File - название изображения с расширением
		image.loadFromFile("Images/" + File); // загрузка изображения по пути
		texture.loadFromImage(image); // установка текстуры из изображения
		sprite.setTexture(texture); // установка спрайта из текстуры
	}
};

class Player {
public:
	bool life = true, vozmozHodby = true, moveRight = true, moveLeft = true, moveUp = true, moveDown = true, newAccess = true; // life - жизнь персонажа, vozmozHodby - возможность ходьбы, moveRight - движение вправо, moveLeft - движение влево, moveUp - движение вверх, moveDown - движение , newAccess - . 
	float w, h, dx = 0, dy = 0, speed = 0, x, y, psevdoX, psevdoY; // w - ширина соприкосновений персонажа, h -  высота соприкосновений персонажа, dx - направление движения по х , dy -  по y , speed - скорость , x - текущая координата по х, y - по y, psevdoX  - текущая координата по х с некоторыми ограничениями, psevdoY - по y
	int dir = 0, carrots = 0, Xm = 0, Ym = 0, oldX, oldY, direction = 0, gameLevel = 0; // dir - определяет кейс направления , carrots - количество моркови, Xm - координата предыдущей клетки по j , Ym - по i , oldX - отправная точка движения по x , oldY - по i, direction - расширенная версия dir, gameLevel - уровень игры
	char stopElements[14] = { '0','u','l','d','r','!','?','(',')','#','L','U','D','R' }; // элементы, через которые персонаж пройти не может 
	int k = sizeof(stopElements); // количество непроходимых элементов
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	// КОНСТРУКТОР КЛАССА
	Player(String F, float X, float Y, float W, float H) {
		File = F;
		w = W; h = H;
		image.loadFromFile("Images/" + File);
		image.createMaskFromColor(Color(255, 0, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y; // текущие координаты по оси X и Y
		oldX = x, psevdoX = x; //old - координата блока, с которого начато движение. psevdo - координата, которая должна будет преобразована в координату X с некоторыми условиями
		oldY = y, psevdoY = y;
		sprite.setTextureRect(IntRect(224, 97, 32, 47));
	}
	//

	//ДВИЖЕНИЕ ИГРОКА
	void update(float time) { // постоянно работающая функция
		switch (dir) { // выбор направления движения
		case 0: dx = speed; dy = 0; break; // вправо
		case 1: dx = -speed; dy = 0; break; 
		case 2: dx = 0; dy = speed; break; // вниз
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

	//ВЗАИМОДЕЙСТВИЕ С КАРТОЙ
	void interectionWithMap() {
		for (int i = y / 48; i < (y + h) / 48; i++) {
			for (int j = x / 48; j < (x + w) / 48; j++) {
				for (int s = 0; s < k; s++) {
					if (TileMap[i][j] == stopElements[s]) { // если персонаж наступает на клетку с непроходимым элементом, то
						if (dy > 0) {
							psevdoY = i * 48 - h; // отталкивать вверх
						}
						if (dy < 0) {
							psevdoY = i * 48 + 48; // отталкивать вниз
						}
						if (dx > 0) {
							psevdoX = j * 48 - w; // отталкивать влево
						}
						if (dx < 0) {
							psevdoX = j * 48 + 48; // отталкивать вправо
						}
						vozmozHodby = true; // разрешать нажатие клавиши снова
					}
				}
				if (updateCarrots == true && vozmozHodby == false) { // если разрешено обнулить количество морковки и ходьба запрешена, то
					carrots = 0; // обнулить кол-во морковок
					updateCarrots = false; // обнуление морковок запрещено
				}

				if (TileMap[i][j] == 'f' && vozmozHodby == true) { // если персонаж наступил на финиш
					newMapActions(&y, &x, &carrots, &sprite, &gameLevel); // перейти в функцию для дальнейших исследований
				}

				if (TileMap[i][j] == 'T' && vozmozHodby == true) { // если персонаж наступил на клетку с активными шипами, то
					life = false; // жизнь персонажа заканчивается
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
	RenderWindow window(VideoMode(1200, 1000), "Game"); // создание окна размером 600 х 600 пикселей
	menu(window); // отображение меню
	view.reset(FloatRect(0, 200, 500, 500));//обновление слежения камеры за персонажем

	Player p("Rabbit.png", 144.0, 432.0, 48.0, 48.0); // создание объекта р класса Player со следующими аргументами ( файл, из которого необходимо брать картинку игрока  , координата возождения по x , по y , размеры игрока по x , по y

	objMap Map("map.png"); // создание объекта Map класса objMap

	Music music; // создание объекта музыки
	music.openFromFile("Sounds/main.ogg"); // загрузка файла фоновой музыки
	music.play(); // запуск музыки
	music.setLoop(true);

	Font font; // создание объекта шрифта
	font.loadFromFile("arial.ttf"); // загрузка шрифта по адресу 
	//Для моркови
	Text text("", font, 30); // создание объекта текст с параметрами ( "текст" , шрифт , размер шрифта )
	text.setFillColor(Color::White); // цвет текста
	text.setStyle(Text::Bold); // стиль текста
	//Для времени
	Text text1("", font, 20);
	text1.setFillColor(Color::White);
	text1.setStyle(Text::Bold);
	//Для уровня
	Text text2("", font, 80);
	text2.setFillColor(Color::Blue);
	text2.setStyle(Text::Bold);

	Image carrot_image; 
	carrot_image.loadFromFile("Images/Rabbit.png");
	carrot_image.createMaskFromColor(Color(255, 0, 255)); // создание маски (прозрачности) для цвета по схеме RGB (red , green , blue )
	Texture carrot_texture;
	carrot_texture.loadFromImage(carrot_image);
	Sprite carrot_sprite;
	carrot_sprite.setTexture(carrot_texture);
	carrot_sprite.setTextureRect(IntRect(287, 199, 28, 27));

	//ФИНИШ УРОВНЯ
	Image lev_Finish;
	lev_Finish.loadFromFile("Images/levelFinish.png");
	lev_Finish.createMaskFromColor(Color(185, 122, 87));
	Texture leve_Finish;
	leve_Finish.loadFromImage(lev_Finish);
	Sprite level_Finish;
	level_Finish.setTexture(leve_Finish);
	//

	float currentFrame = 0; // текущий кадр анимации
	bool legDown = false; // положение ноги
	bool rabbitDeathAnim = false; // воспроизведение гибели персонажа
	bool deathAccept = false;  // подтверждение начала анимации гибели

	Clock clock; // создание объектов времени
	Clock timer1;
	Clock gameTimeClock;
	int gameTime = 0; // игровое время
	int prevGameLevel = 0;

	while (window.isOpen()) // пока окно открыто
	{
		float timer = timer1.getElapsedTime().asSeconds(); // отсчет времени в секундах
		float time = clock.getElapsedTime().asMicroseconds();  // отсчет времени в микросекундах
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); // если персонаж жив, то вести отсчет времени игры
		clock.restart(); // перезапуск таймера
		time = time / 700; // "нормализация скорости"
		Event event; // создание объекта событие

		while (window.pollEvent(event)) // пока происходит какое либо событие
		{
			if (event.type == Event::Closed) // если было закрыто консольное окно, то тогда закрыть и окно игры
				window.close(); // закрыть окно
		}

		//ВЛЕВО
		if (p.life) { //если персонаж жив, то
			if (p.vozmozHodby && timer > 0.01) { // если он может ходить и время перехода между разными ячейками больше заданного, то
				if (Keyboard::isKeyPressed(Keyboard::Up) && p.moveUp == true) { // при нажатой клавише вверх и разрешении на ходьбу вверх
					p.oldX = p.x; // запоминание координаты X на момент начала ходьбы
					p.oldY = p.y; // запоминание координаты Y на момент начала ходьбы
					p.vozmozHodby = false; // запрет на ходьбу
					p.direction = 3; // направление движения
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) && p.moveDown == true) { // при нажатой клавише вниз и разрешении на ходьбу вниз
					p.oldX = p.x;
					p.oldY = p.y;
					p.vozmozHodby = false;
					p.direction = 2;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left) && p.moveLeft == true) { // при нажатой клавише влево и разрешении на ходьбу влево
					p.oldX = p.x;
					p.oldY = p.y;
					p.vozmozHodby = false;
					p.direction = 1;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) && p.moveRight == true) { // при нажатой клавише вправо и разрешении на ходьбу вправо
					p.oldX = p.x;
					p.oldY = p.y;
					p.vozmozHodby = false;
					p.direction = 0;
				}
				else {
					if (timer > 4) { // если клавиши передвижения персонажа не были нажаты в течении 4 секунд
						if (legDown) {// если нога опущена
							currentFrame += 0.007*time;// скорость смены текущего кадра 
							if (currentFrame > 3) currentFrame = 0, legDown = false; // установка текущего кадра в нулевой и установка ноги в поднятом положении
							p.sprite.setTextureRect(IntRect(450 - 32 * int(currentFrame), 208, 32, 47)); // вырезка кадров для сначала опущенной ноги
						}
						else if (!legDown) { // если нога поднята
							currentFrame += 0.007*time;
							if (currentFrame > 3) currentFrame = 0, legDown = true;
							p.sprite.setTextureRect(IntRect(386 + 32 * int(currentFrame), 208, 32, 47)); // вырезка кадров для сначала поднятой ноги
						}
					}
				}
			}
			if (!p.vozmozHodby) { 
				p.dir = p.direction; // направление движения
				p.speed = 0.1; // скорость персонажа
				currentFrame += 0.007*time; // скорость смены кадров анимации
				if (currentFrame > 8) currentFrame = 0;
				if (p.direction == 3) p.sprite.setTextureRect(IntRect(32 * int(currentFrame), 50, 32, 47));
				if (p.direction == 2) p.sprite.setTextureRect(IntRect(32 * int(currentFrame), 97, 32, 46));
				if (p.direction == 1) p.sprite.setTextureRect(IntRect(32 * int(currentFrame), 0, 32, 49));
				if (p.direction == 0) p.sprite.setTextureRect(IntRect(32 * int(currentFrame) - 1, 144, 32, 49));
				timer1.restart(); // обновление таймера ожидания ходьбы персонажа
				if (p.x > p.oldX + 48 || p.x < p.oldX - 48 || p.y > p.oldY + 48 || p.y < p.oldY - 48) { // если текущие координаты персонажа полностью достигли след блока
					p.vozmozHodby = true; // разрешение на ходьбу по моменту завершения пройденого пути
				}
				getPlayerCoordinateView(p.x, p.y);// передача координат персонажа для следования камеры за ним
			}
		}
		
		p.update(time); // передача времени для возможности ходьбы персонажа
		window.clear(); // очистка всего экрана от всех предыдущих неактуальных изображений
		window.setView(view); //установка камеры слежения

		//ОТОБРАЖЕНИЕ КАРТЫ НА ЭКРАНЕ
		for (int i = 0; i < HEIGHT_MAP1; i++) {
			for (int j = 0; j < WIDTH_MAP1; j++) {
				if (TileMap[i][j] == 'l') Map.sprite.setTextureRect(IntRect(0, 0, 48, 48));// трава с элементом земли слева
				if (TileMap[i][j] == 'u') Map.sprite.setTextureRect(IntRect(48, 0, 48, 48));// трава с элементом земли сверху
				if (TileMap[i][j] == 'd') Map.sprite.setTextureRect(IntRect(96, 0, 48, 48));// трава с элементом земли снизу
				if (TileMap[i][j] == 'r') Map.sprite.setTextureRect(IntRect(144, 0, 48, 48));// трава с элементом земли справа
				if (TileMap[i][j] == '0') Map.sprite.setTextureRect(IntRect(192, 0, 48, 48));// полный квадрат травы
				if (TileMap[i][j] == 'c') Map.sprite.setTextureRect(IntRect(240, 0, 48, 48));// морковь
				if (TileMap[i][j] == 'p') Map.sprite.setTextureRect(IntRect(288, 0, 48, 48));// яма от моркови
				if (TileMap[i][j] == ' ') Map.sprite.setTextureRect(IntRect(336, 0, 48, 48));// песок
				if (TileMap[i][j] == 's') Map.sprite.setTextureRect(IntRect(384, 0, 48, 48));// место возрождения персонажа
				if (TileMap[i][j] == 'f') Map.sprite.setTextureRect(IntRect(432, 0, 48, 48));// финиш

				// тут можно вспомнить о двухмерной координатной плоскости и её четвертях
				if (TileMap[i][j] == '3') Map.sprite.setTextureRect(IntRect(576, 0, 48, 48));// 3 четверть вращающегося лабиринта
				if (TileMap[i][j] == '4') Map.sprite.setTextureRect(IntRect(624, 0, 48, 48));// 4 четверть вращающегося лабиринта
				if (TileMap[i][j] == '2') Map.sprite.setTextureRect(IntRect(672, 0, 48, 48));// 2 четверть вращающегося лабиринта
				if (TileMap[i][j] == '1') Map.sprite.setTextureRect(IntRect(720, 0, 48, 48));// 1 четверть вращающегося лабиринта
				//

				if (TileMap[i][j] == '|') Map.sprite.setTextureRect(IntRect(768, 0, 48, 48));// вертикальная часть вращающегося лабиринта
				if (TileMap[i][j] == '-') Map.sprite.setTextureRect(IntRect(816, 0, 48, 48));// горизонтальная часть четверть вращающегося лабиринта
				if (TileMap[i][j] == '!') Map.sprite.setTextureRect(IntRect(960, 0, 48, 48));// вертикальный забор
				if (TileMap[i][j] == '(') Map.sprite.setTextureRect(IntRect(1008, 0, 48, 48));// левая часть забора
				if (TileMap[i][j] == '#') Map.sprite.setTextureRect(IntRect(1056, 0, 48, 48));// соединяющая левую и правую часть забора
				if (TileMap[i][j] == ')') Map.sprite.setTextureRect(IntRect(1104, 0, 48, 48));// правая часть забора
				if (TileMap[i][j] == 'T') Map.sprite.setTextureRect(IntRect(1631, 0, 48, 48));// активированная ловушка с шипами
				if (TileMap[i][j] == 't') Map.sprite.setTextureRect(IntRect(1679, 0, 48, 48));// неактивированная ловушка с шипами
				if (TileMap[i][j] == 'U') Map.sprite.setTextureRect(IntRect(1440, 0, 48, 48));// трава с элементом земли слева и снизу
				if (TileMap[i][j] == 'R') Map.sprite.setTextureRect(IntRect(1488, 0, 48, 48));// трава с элементом земли сверху и справа
				if (TileMap[i][j] == 'D') Map.sprite.setTextureRect(IntRect(1536, 0, 48, 48));// трава с элементом земли справа и снизу
				if (TileMap[i][j] == 'L') Map.sprite.setTextureRect(IntRect(1584, 0, 48, 48));// трава с элементом земли слева и сверху
				Map.sprite.setPosition(j * 48, i * 48); // установка обрезанных частей карты на экране || (j * 48, i * 48) так как каждая обрезанная картинка имеет размеры 48 х 48 пикселей 
				window.draw(Map.sprite); // отображение кусочка карты
			}
		}
		//

		//ОТОБРАЖЕНИЕ ПЕРСОНАЖА
		if (p.life) { // если игрок жив,
			window.draw(p.sprite); // то рисовать картинку персонажа
		}
		else if (!rabbitDeathAnim) { // иначе если анимация гибели персонажа ещё не была воспроизведина, то
			if (!deathAccept) { // начало анимации ещё не началось
				currentFrame = 0; // установка текущего кадра анимации в 0 для полного воспроизведения анимации гибели персонажа
				deathAccept = true; // начало анимации уже начато
			}
			currentFrame += 0.005 * time; // скорость смены кадров анимации
			if (currentFrame > 8) rabbitDeathAnim = true; // если анимация гибели полностью воспроизведена, то анимацию гибели больше не воспроизводить
			p.sprite.setTextureRect(IntRect(32 * int(currentFrame), 192, 32, 49)); // устнаовка различных изображений анимации
			window.draw(p.sprite); 
		}
		if (rabbitDeathAnim) { 
			p.sprite.setTextureRect(IntRect(224, 192, 32, 49)); // отображение последнего кадра погибшего персножажа
			window.draw(p.sprite);
		}
		//

		// ВЫВОД НА ЭКРАН КОЛИЧЕСТВА СОБРАННОЙ МОРКОВИ 
		ostringstream playerScoreString; // создание объекта строки
		playerScoreString << p.carrots;// занесение в строку
		text.setString(playerScoreString.str());// преобразование в вид строки для выода на экран
		text.setPosition(view.getCenter().x + 200, view.getCenter().y - 235);// расположение текста по заданным координатам || view.getCenter().x + 200 - взять координату Х относительно экрана и добавить к ней 200 пикселей
		window.draw(text);// вывод текст на экран 
		//

		//ВЫВОД НА ЭКРАН ПРОШЕДШЕГО ИГРОВОГО ВРЕМЕНИ
		ostringstream gameTimeString;
		gameTimeString << gameTime;
		text1.setString("Time: " + gameTimeString.str());
		text1.setPosition(view.getCenter().x - 230, view.getCenter().y - 235);
		window.draw(text1);
		//

		//ВЫВОД НА ЭКРАН ИЗОБРАЖЕНИЯ МОРКОВИ 
		carrot_sprite.setPosition(view.getCenter().x + 170, view.getCenter().y - 230);
		window.draw(carrot_sprite);
		//

		ostringstream levelFinish;
		levelFinish << p.gameLevel;
		if (prevGameLevel + 1 == p.gameLevel) { //если текущий уровень больше предыдущего на 1 , то 
			p.vozmozHodby = false; // заблокировать ходьбу персонажа
			if (Keyboard::isKeyPressed(Keyboard::Space)) {  // при нажатой клавиши space
				prevGameLevel++; // увеличить уровень предыдущей игры
				p.vozmozHodby = true; // разрешить ходьбу
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

		//ВЫВОДИТЬ ИЗОБРАЖЕНИЕ В ОКНЕ
		window.display();
		//
	}

	return 0;
}