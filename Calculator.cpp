#include "common.cpp"

#include <vector>
#include <stdexcept>
#include <cmath>

class CalcData
{
public:
	CalcData();

	void SetPoints(std::vector<Point> points);

	void SetPoint(Point point);

	void CalcAngles();

	double CalcArgCos(Point p1, Point p2);
	
	Point CalcVector(Point A, Point B);

	void CalcLengths();

	double CalcVecLength(Point A, Point B);


private:
	std::vector<Point> points_;
};

CalcData::CalcData() {
}

void CalcData::SetPoints(std::vector<Point> points) {
	points_ = points;
}

void CalcData::SetPoint(Point point) {
	points_.push_back(point);
}

void CalcData::CalcAngles() {
	if (points_.size() < 3) {
		throw std::invalid_argument("Low points");
	}
	for (int i = 0; i < (points_.size() - 3); i + 3) {
		Point vectorAB = CalcVector(points_[i], points_[i + 1]);
		Point vectorBC = CalcVector(points_[i + 1], points_[i + 2]);
		Point vectorCA = CalcVector(points_[i + 2], points_[i]);
		auto anglA = cos(CalcArgCos(vectorAB, vectorCA));
		auto anglB = cos(CalcArgCos(vectorAB, vectorBC));
		auto anglC = cos(CalcArgCos(vectorBC, vectorCA));
	}
	for (int i = 0; i < (points_.size() - 3); ++i) {
		Point vectorAB = CalcVector(points_[i], points_[i + 1]);
		Point vectorAC = CalcVector(points_[i], points_[i + 2]);
		auto anglA = cos(CalcArgCos(vectorAB, vectorAC));
	}
}

double CalcData::CalcArgCos(Point p1, Point p2)
{
	double numerator = p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
	double denominator1 = sqrt(std::pow(p1.x, 2) + std::pow(p1.y, 2) + std::pow(p1.z, 2));
	double denominator2 = sqrt(std::pow(p2.x, 2) + std::pow(p2.y, 2) + std::pow(p2.z, 2));
	double arg = numerator / (denominator1 * denominator2);
	return arg;
}

Point CalcData::CalcVector(Point A, Point B) {
	return { B.x - A.x, B.y - A.y, B.z - A.z };
}

void CalcData::CalcLengths() {
	for (int i = 0; i < (points_.size() - 1); ++i) {
		auto length = CalcVecLength(points_[i], points_[i + 1]);
	}
}

double CalcData::CalcVecLength(Point A, Point B) {
	Point vectorAB = CalcVector(A, B);
	auto length = sqrt(std::pow(vectorAB.x, 2) + std::pow(vectorAB.y, 2) + std::pow(vectorAB.z, 2));
	return length;
}

