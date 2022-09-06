#include "Lighting.h"

sf::Color applyLighting(Vec4 light, Vec4 normal, Vec4 view, float ambientIntensity, material m) {
	float attenuation = 1 + 0.045*magnitude(light) + 0.0075*magnitudeSquared(light);
	float luminosity = 1 / attenuation;
	light = normalize(light);
	normal = normalize(normal);
	view = normalize(view);

	uint8_t color[3];

	float final_intensity[3];

	Vec4 reflection = 2 * dot(light, normal) * normal - light;
	for (int i = 0; i < 3; i++) {
		float intensity = 0;
		float ambient = m.ka[i] * ambientIntensity;
		float diffuse = max(dot(light, normal), 0) * m.kd[i] * luminosity;
		float specular = diffuse > 0 ? pow(max(dot(reflection, view), 0), m.ns) * m.ks[i] * luminosity : 0;
		intensity = ambient + diffuse + specular;
		final_intensity[i] = intensity;
	}
	float ma  = std::max({ final_intensity[0], final_intensity[1], final_intensity[2] });
	float scale = ma <= 1 ? 1 : 1 / ma;

	for (int i = 0; i < 3; i++) {
		final_intensity[i] *= scale;
		color[i] = final_intensity[i] * 255;
	}


	return(sf::Color(color[0], color[1], color[2]));
}