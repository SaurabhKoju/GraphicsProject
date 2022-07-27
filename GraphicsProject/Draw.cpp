#include "Draw.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "Lighting.h"

const float INF = 1000000000;

sf::Color applyLighting(sf::Color c, float ambient, Vec4 normal, Vec4 light) {

	float ka  = 1;
	float cosTheta = max((dot(normalize(normal), normalize(light))), 0)/magnitudeSquared(light);
	return sf::Color(
			min((float)c.r * (ambient * ka + cosTheta), 255),
			min((float)c.g * (ambient * ka + cosTheta), 255),
			min((float)c.b * (ambient * ka + cosTheta), 255),
			c.a);

}


void draw(mesh M, sf::RenderWindow &window, Camera cam, Vec4 light) {
	std::vector<sf::Vertex> vertexarray;


	std::vector<std::vector<float> > zbuffer(SCREEN_HEIGHT, std::vector<float>(SCREEN_WIDTH, INF));
	Mat4 compressx = getScaleMatrix(Vec4{ aspect_ratio, 1, 1});
	Mat4 translateCam = getTranslateMatrix(Zero4 - cam.position);
	Mat4 camTransform = worldtoCam(cam);
	Mat4 Transform = compressx * camTransform * translateCam;

	for (triangle t : M.triangles) {
		Vec4 v1 = t.p1 - t.p0;
		Vec4 v2 = t.p2 - t.p0;
		Vec4 cross_product = v1 * v2;

		if (dot(cross_product, t.p0 - cam.position) > 0)continue;
		
		Vector<4> pp0 = get2d(Transform*t.p0);
		Vector<4> pp1 = get2d(Transform*t.p1);
		Vector<4> pp2 = get2d(Transform*t.p2);

		Mat4 maptoScreen = getScaleMatrix({ SCREEN_WIDTH / float(2), SCREEN_HEIGHT / float(2), 1 }) * getTranslateMatrix({ 1, 1, 0 });
		pp0 = maptoScreen * pp0;
		pp1 = maptoScreen * pp1;
		pp2 = maptoScreen * pp2;
		
		//rasterize(triangle{ pp0, pp1, pp2, t.fillColor }, window, 1, cross_product, light, zbuffer);

		Vec4 centre = { 0, 0, 0, 0 };
		Vec4 vn0 = normalize( t.p0 - centre);
		Vec4 vn1 = normalize( t.p1 - centre);
		Vec4 vn2 = normalize( t.p2 - centre);




		//rasterize

		
		int xmin = std::min({ pp0[0], pp1[0], pp2[0] });
		int xmax = std::max({ pp0[0], pp1[0], pp2[0] });
		int ymin = std::min({ pp0[1], pp1[1], pp2[1] });
		int ymax = std::max({ pp0[1], pp1[1], pp2[1] });

		Vec4 arean = (pp1 - pp0) * (pp2 - pp0);

		for (int i = max(0, ymin); i <= min(ymax, SCREEN_HEIGHT-1); i++) {
			for (int j = max(0, xmin); j <= min(xmax, SCREEN_WIDTH-1); j++) {
				Vec4 currentPoint = { (float)j, (float)i};
				bool up1 = false, up2 = false, up3 = false;
				Vec4 cp0 = (pp1 - pp0) * (currentPoint - pp0);
				Vec4 cp1 = (pp2 - pp1) * (currentPoint - pp1);
				Vec4 cp2 = (pp0 - pp2) * (currentPoint - pp2);
				if (cp0[2] >= 0)up1 = true;
				if (cp1[2] >= 0)up2 = true;
				if (cp2[2] >= 0)up3 = true;

				if (up1 != up2 || up2 != up3) continue;

				float l2 = abs(cp0[2] / arean[2]);
				float l0 = abs(cp1[2] / arean[2]);
				float l1 = abs(cp2[2] / arean[2]);

				float depth = l0 * pp0[2] + l1 * pp1[2] + l2 * pp2[2];
				if (depth >= zbuffer[i][j])continue;
				zbuffer[i][j] = depth;

				Vec4 normal = l0 * vn0 + l1 * vn1 + l2 * vn2;

				Vec4 vertexCoordinates = l0 * t.p0 + l1 * t.p1 + l2 * t.p2;
				//sf::Color c = applyLighting(t.fillColor, 0.2, cross_product, light - vertexCoordinates);
				sf::Color c = applyLighting2(light - vertexCoordinates, cross_product, cam.position - vertexCoordinates, 0.2, t.mtl);
				vertexarray.push_back(sf::Vertex{ sf::Vector2f{float(j), float(i)}, c });
			}
		}
		
	}


	if(vertexarray.size())
		window.draw(&vertexarray[0], vertexarray.size(), sf::Points);
	/*
		rasterize(triangle{ pp0, pp1, pp2, t.fillColor }, window, 0.1, cross_product, {light - surfaceCenter}, zbuffer);
		*/
}
