#include <sstream>
#include "Model.h"

namespace neko {
	bool Model::load(const std::string& filename) {
		std::string buffer;
		neko::readFile(filename, buffer);

		std::istringstream stream(buffer);

		// read color
		stream >> m_color;

		// read number of points
		std::string line;
		std::getline(stream, line);
		int numPoints = std::stoi(line);

		//read vector2 points
		for (int i = 0; i < numPoints; i++) {
			vec2 point;
			stream >> point;
			m_points.push_back(point);
		}

		return true;
	}

	void Model::draw(Renderer& renderer, const vec2& position, float rotation, float scale) {
		if (m_points.empty()) return;

		renderer.setColor(Color::toInt(m_color.r), Color::toInt(m_color.g), Color::toInt(m_color.b), Color::toInt(m_color.a));

		for (int i = 0; i < m_points.size() - 1; i++) {
			vec2 p1 = (m_points[i] * scale).rotate(rotation) + position;
			vec2 p2 = (m_points[i + 1] * scale).rotate(rotation) + position;

			renderer.drawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Model::draw(Renderer& renderer, const Transform transform) {
		draw(renderer, transform.position, transform.rotation, transform.scale);
	}

	float Model::getRadius() {
		if (m_radius) return m_radius;

		for (auto point : m_points) {
			float length = point.length();
			m_radius = max(m_radius, length);
		}

		return m_radius;
	}
}
