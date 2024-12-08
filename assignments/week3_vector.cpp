#include <iostream>
using namespace std;

class VECTOR3D {
public:
	float x, y, z;

	//생성자 -> 초기화
	VECTOR3D() :x(0.0f),y(0.0f),z(0.0f) { }
	VECTOR3D(float x, float y, float z):x(x), y(y),z(z) { }

	VECTOR3D operator+(VECTOR3D v) {
		VECTOR3D result = (*this);
		result.x += v.x;
		result.y += v.y;
		result.z += v.z;
		return result;
	}
	
	VECTOR3D operator-(VECTOR3D v) {
		VECTOR3D result = (*this);
		result.x -= v.x;
		result.y -= v.y;
		result.z -= v.z;
		return result;
	}

	VECTOR3D operator*(float val) {
		return VECTOR3D(x * val, y * val, z * val);
	}

	//단위 벡터(크기 1인 벡터)
	VECTOR3D Normalize() {
		float magnitude = sqrt(x * x + y * y + z * z);
		return VECTOR3D(x / magnitude, y / magnitude, z / magnitude);
	}

	//벡터 크기
	float Magnitude() { return sqrt(x * x + y * y + z * z); }

	// 내적
	float dotProduct(const VECTOR3D& v) {
		return x * v.x + y * v.y + z * v.z;
	}

	// 외적
	VECTOR3D crossProduct(const VECTOR3D& v) {
		VECTOR3D result;

		result.x = y * v.z - z * v.y;
		result.y = z * v.x - x * v.z;
		result.z = x * v.y - y * v.x;
		return result;
	}


};

int main() {
	float a_x, a_y, a_z ;
	float b_x, b_y, b_z;

	cout << "3차원 벡터 a와 b를 순서대로 입력하세요 a(x, y, z), b(x, y, z) " << endl; 
	cin >> a_x >> a_y >> a_z >> b_x >> b_y >> b_z;

	cout << endl;

	VECTOR3D a(a_x, a_y, a_z);
	VECTOR3D b(b_x, b_y, b_z);

	//-------------------------------------

	VECTOR3D addition = a + b;
	VECTOR3D subtraction = a - b;
	VECTOR3D scalar_multiplication_result = a * 5.0;
	VECTOR3D normalized_a = a.Normalize();
	float magnitude_a = a.Magnitude();
	float dot_product = a.dotProduct(b);
	VECTOR3D cross_product = a.crossProduct(b);
	
	cout << "Addition of a and b: (" << addition.x << ", " << addition.y << ", " << addition.z << ") " << endl;
	cout << "Subtraction of a and b: (" << subtraction.x << ", " << subtraction.y << ", " << subtraction.z << ") " << endl;
	cout << "Scalar Multiplication (5 * a): (" << scalar_multiplication_result.x << ", " << scalar_multiplication_result.y << ", " << scalar_multiplication_result.z << ")\n";
	cout << "Normalization of Vector a: (" << normalized_a.x << ", " << normalized_a.y << ", " << normalized_a.z << ")\n";
	cout << "Magnitude of Vector a: " << magnitude_a << "\n";
	cout << "Dot Product of a and b: " << dot_product << "\n";
	cout << "Cross Product of a and b: (" << cross_product.x << ", " << cross_product.y << ", " << cross_product.z << ")\n";
	
	return 0; 
}