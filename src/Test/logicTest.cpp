#include <gtest/gtest.h>
#include "../Logic/ObjController.h"

#define _USE_MATH_DEFINES
#include <cmath>

TEST(Reader, readTest) {
	s21::ObjReader& reader = s21::ObjReader::getObjReader();
	reader.processFile("Models/cube.obj");
	ASSERT_EQ(reader.getEdges().size(), 50);
	ASSERT_EQ(reader.getVerts().size(), 24);
  EXPECT_TRUE(true);
}

TEST(Transform, moveXTest) {
	s21::ObjController& control = s21::ObjController::getObjController();
	s21::ObjReader& reader = s21::ObjReader::getObjReader();
	reader.processFile("Models/cube.obj");
	std::vector<double> verts = reader.getVerts();
	std::vector<double> result = verts;
	control.transformObj(s21::kMoveX,result, 5);
	for (int i = 0; i < verts.size(); i += 3) {
		ASSERT_EQ(verts[i],result[i] - 5);
	}
}

TEST(Transform, moveYTest) {
	s21::ObjController& control = s21::ObjController::getObjController();
	s21::ObjReader& reader = s21::ObjReader::getObjReader();
	reader.processFile("Models/cube.obj");
	std::vector<double> verts = reader.getVerts();
	std::vector<double> result = verts;
	control.transformObj(s21::kMoveY, result, 5);
	for (int i = 1; i < verts.size(); i += 3) {
		ASSERT_EQ(verts[i], result[i] - 5);
	}
}

TEST(Transform, moveZTest) {
	s21::ObjController& control = s21::ObjController::getObjController();
	s21::ObjReader& reader = s21::ObjReader::getObjReader();
	reader.processFile("Models/cube.obj");
	std::vector<double> verts = reader.getVerts();
	std::vector<double> result = verts;
	control.transformObj(s21::kMoveZ, result, 5);
	for (int i = 2; i < verts.size(); i += 3) {
		ASSERT_EQ(verts[i], result[i] - 5);
	}
}

TEST(Transform, rotateXTest) {
	s21::ObjController& control = s21::ObjController::getObjController();
	s21::ObjReader& reader = s21::ObjReader::getObjReader();
	reader.processFile("Models/cube.obj");
	std::vector<double> verts = reader.getVerts();
	std::vector<double> result = verts;
	double deg = 45 * M_PI / 180;
	control.transformObj(s21::kRotX, result, 45);
	for (int i = 0; i < verts.size(); i += 3) {
		ASSERT_EQ(result[i + 1], verts[i + 1] * cos(deg) + verts[i + 2] * sin(deg));
		ASSERT_EQ(result[i + 2], -verts[i + 1] * sin(deg) + verts[i + 2] * cos(deg));
	}
}

TEST(Transform, rotateYTest) {
	s21::ObjController& control = s21::ObjController::getObjController();
	s21::ObjReader& reader = s21::ObjReader::getObjReader();
	reader.processFile("Models/cube.obj");
	std::vector<double> verts = reader.getVerts();
	std::vector<double> result = verts;
	double deg = 45 * M_PI / 180;
	control.transformObj(s21::kRotY, result, 45);
	for (int i = 0; i < verts.size(); i += 3) {
		ASSERT_EQ(result[i], verts[i] * cos(deg) + verts[i + 2] * sin(deg));
		ASSERT_EQ(result[i + 2], -verts[i] * sin(deg) + verts[i + 2] * cos(deg));
	}
}

TEST(Transform, rotateZTest) {
	s21::ObjController& control = s21::ObjController::getObjController();
	s21::ObjReader& reader = s21::ObjReader::getObjReader();
	reader.processFile("Models/cube.obj");
	std::vector<double> verts = reader.getVerts();
	std::vector<double> result = verts;
	double deg = 45 * M_PI / 180;
	control.transformObj(s21::kRotZ, result, 45);
	for (int i = 0; i < verts.size(); i += 3) {
		ASSERT_EQ(result[i], verts[i] * cos(deg) + verts[i + 1] * sin(deg));
		ASSERT_EQ(result[i + 1], -verts[i] * sin(deg) + verts[i + 1] * cos(deg));
	}
}

TEST(Transform, scaleTest) {
	s21::ObjController& control = s21::ObjController::getObjController();
	s21::ObjReader& reader = s21::ObjReader::getObjReader();
	reader.processFile("Models/cube.obj");
	std::vector<double> verts = reader.getVerts();
	std::vector<double> result = verts;
	control.transformObj(s21::kScale, result, 5);
	for (int i = 0; i < verts.size(); i += 3) {
		ASSERT_EQ(verts[i], result[i] / 5);
	}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
