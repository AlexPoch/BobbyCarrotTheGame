#include <SFML/Graphics.hpp>
using namespace sf;

View view;//�������� sfml ������ "���", ������� � �������� �������

View getPlayerCoordinateView(float x, float y) {
	float tempX = x; float tempY = y;

	if (x < 250) tempX = 250;// ������� �� ���� ����� �������
	if (y < 250) tempY = 250;// ������� �������
	if (y > 518) tempY = 518;// ������ �������
	if (x > 2294) tempX = 2294;// ������ �������

	view.setCenter(tempX, tempY); // ����������� ������ 
	return view; // ����������� ������ ����
}