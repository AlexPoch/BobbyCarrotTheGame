#include <SFML/Graphics.hpp>
using namespace sf;
char chetvert; // часть вращающегося лабиринта
bool updateCarrots = false; //обнуление морковок
const int HEIGHT_MAP1 = 16; // высота карты
const int WIDTH_MAP1 = 53; // ширина карты
String TileMap[HEIGHT_MAP1] = { // карта, представленная строковым массивом
	"00000000000000000000000000000000000000000000000000000",
	"00000000000000000000000000ddddd0000000000000000000000",
	"0000000000000000000000000r ccc l000000000000000000000",
	"0000000000000000000000000rtLuRtl000000000000000000000",
	"0000000000000000000000dddD UdD l0000000000ddddd000000",
	"000000000000000000000r ccc2ccc l000000000r ccc l00000",
	"0000000ddd00d00000000r LuR LuR l000000000Dtuuutl00000",
	"00ddd0rccc0r U0000000D U0r l0D U0000ddd0rccclr l0dd00",
	"0r   UDcccUD  Ud0000r   UD UD   U00r   UDcccUD UD  U0",
	"0r s   ttt    f l000r s tc|ct   fl0r s   tttct     fl",
	"0r   LRcccLR  Lu0000r   LR LR   L00r   LRcccLR LR  L0",
	"00uuu0rccclr L0000000R L0r l0R L0000uuu0rccclr l0uu00",
	"0000000uuu00u00000000r UdD UdD l000000000RtLdDtl00000",
	"000000000000000000000r ccc1ccc l000000000r ccc l00000",
	"0000000000000000000000uuuuuuuuu00000000000uuuuu000000",
	"00000000000000000000000000000000000000000000000000000"
};

void changeMapItems(int change, float &x, float &y, Sprite &sprite, int &gameLevel) {
	switch (change) {
	case 0:
		x = 1104; // телепортация персонажа в другую область карты
		y = 432;
		sprite.setPosition(x - 48, y);
		updateCarrots = true; // обнуление количества моркови
		gameLevel = 1; // номер игрового уровень
		break;
	case 1:
		x = 1824;
		y = 432;
		sprite.setPosition(x - 48, y);
		updateCarrots = true;
		gameLevel = 2;
		break;
	case 2:

		break;
	}
}

void newMapActions(float *y, float *x, int *carrots, Sprite *sprite, int *gameLevel) {  // проверка на возможность завершения
	int changeItems = -1;
	if (*x == 672 && *y == 432 && *carrots == 12) {
		changeItems = 0;
	}
	else if (*x == 1536 && *y == 432 && *carrots == 17) {
		changeItems = 1;
	}
	else if (*x == 8 && *y == 6) {
		changeItems = 2;
	}
	changeMapItems(changeItems, *x, *y, *sprite, *gameLevel);
}

void zamenaPovorota(char chetvert, int x, int y, int &carrots) {  // функция для замены элемента на карте
	if (chetvert == '1') TileMap[y][x] = '4';
	if (chetvert == '2') TileMap[y][x] = '1';
	if (chetvert == '3') TileMap[y][x] = '2';
	if (chetvert == '4') TileMap[y][x] = '3';
	if (chetvert == '|') TileMap[y][x] = '-';
	if (chetvert == '-') TileMap[y][x] = '|';
	if (chetvert == 't') TileMap[y][x] = 'T';
	if (chetvert == 'c') carrots++, TileMap[y][x] = 'p';
}
