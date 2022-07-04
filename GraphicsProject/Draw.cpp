#include "Draw.h"
#include <iostream>


void draw(mesh M, sf::RenderWindow &window, Camera cam) {
	Mat4 compressx = getScaleMatrix(Vec3{ aspect_ratio, 1, 1});
	Mat4 translateCam = getTranslateMatrix(Vec3{ 0, 0, 0 } - cam.position);
	Mat4 camTransform = rotateCam(cam);
	Mat4 Transform = compressx*camTransform * translateCam;
	for (const triangle &t : M.triangles) {
		sf::VertexArray drawt(sf::Triangles, 3);

		Vec4 v1 = t.p2 - t.p1;
		Vec4 v2 = t.p3 - t.p2;
		Vec3 cross_product = v1 * v2;

		if (dot(cross_product, cam.look) > 0)continue;


		Vector<2> pp1 = get2d(Transform*t.p1);
		Vector<2> pp2 = get2d(Transform*t.p2);
		Vector<2> pp3 = get2d(Transform*t.p3);
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