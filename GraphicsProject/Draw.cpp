#include "Draw.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void draw(mesh M, sf::RenderWindow &window) {
	for (const triangle &t : M.triangles) {
		sf::VertexArray drawt(sf::Triangles, 3);

		Vector<2> pp1 = get2d(t.p1);
		Vector<2> pp2 = get2d(t.p2);
		Vector<2> pp3 = get2d(t.p3);
		drawline(pp1, pp2, window);
		drawline(pp2, pp3, window);
		drawline(pp3, pp1, window);
	}
}

void drawline(Vector<2> p1, Vector<2> p2, sf::RenderWindow &window) {
	sf::Vertex line[2];
	line[0].position = sf::Vector2f((p1[0] + 1) / 2 * SCREEN_WIDTH, (p1[1] + 1) / 2 * SCREEN_HEIGHT);
	line[1].position = sf::Vector2f((p2[0] + 1) / 2 * SCREEN_WIDTH, (p2[1] + 1) / 2 * SCREEN_HEIGHT);
	window.draw(line, 2, sf::Lines);
}