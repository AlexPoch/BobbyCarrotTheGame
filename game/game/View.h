#include <SFML/Graphics.hpp>
using namespace sf;

View view;//объ€вили sfml объект "¬ид", который и €вл€етс€ камерой

View getPlayerCoordinateView(float x, float y) {
	float tempX = x; float tempY = y;

	if (x < 250) tempX = 250;// убираем из вида левую сторону
	if (y < 250) tempY = 250;// верхнюю сторону
	if (y > 518) tempY = 518;// нижнюю сторону
	if (x > 2294) tempX = 2294;// правую сторону

	view.setCenter(tempX, tempY); // отображение камеры 
	return view; // возвращение камеры вида
}