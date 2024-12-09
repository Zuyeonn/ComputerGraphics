#include <iostream>
#include <vector>
using namespace std;

class VECTOR3D {
public:
    VECTOR3D()
        : vecX(0.0f), vecY(0.0f), vecZ(0.0f) {}

    VECTOR3D(float x, float y, float z)
        : vecX(x), vecY(y), vecZ(z) {}

    float Magnitude();
    float InnerProduct(VECTOR3D v);
    VECTOR3D CrossProduct(VECTOR3D v);
    void Normalize();

    VECTOR3D operator+(VECTOR3D v);
    VECTOR3D operator-(VECTOR3D v);
    VECTOR3D operator*(float val);
    float operator*(VECTOR3D v);

    VECTOR3D operator^(VECTOR3D v) {
        return CrossProduct(v);
    }

    friend VECTOR3D operator*(float val, VECTOR3D v);

    float vecX;
    float vecY;
    float vecZ;
};

VECTOR3D VECTOR3D::operator+(VECTOR3D v) {
    VECTOR3D result = (*this);
    result.vecX += v.vecX;
    result.vecY += v.vecY;
    result.vecZ += v.vecZ;

    return result;
}

VECTOR3D VECTOR3D::operator-(VECTOR3D v) {
    VECTOR3D result = (*this);
    result.vecX -= v.vecX;
    result.vecY -= v.vecY;
    result.vecZ -= v.vecZ;

    return result;
}

VECTOR3D VECTOR3D::operator*(float val) {
    VECTOR3D result = (*this);
    result.vecX *= val;
    result.vecY *= val;
    result.vecZ *= val;

    return result;
}

float VECTOR3D::operator*(VECTOR3D v) {
    return InnerProduct(v);
}

float VECTOR3D::Magnitude() {
    return sqrt(vecX * vecX + vecY * vecY + vecZ * vecZ);
}

float VECTOR3D::InnerProduct(VECTOR3D v) {
    return (vecX * v.vecX + vecY * v.vecY + vecZ * v.vecZ);
}

VECTOR3D VECTOR3D::CrossProduct(VECTOR3D v) {
    VECTOR3D result;
    result.vecX = vecY * v.vecZ - vecZ * v.vecY;
    result.vecY = vecZ * v.vecX - vecX * v.vecZ;
    result.vecZ = vecX * v.vecY - vecY * v.vecX;

    return result;
}

void VECTOR3D::Normalize() {
    float mag = Magnitude();
    if (mag != 0.0f) {
        vecX /= mag;
        vecY /= mag;
        vecZ /= mag;
    }
}

VECTOR3D operator*(float val, VECTOR3D v) {
    VECTOR3D result;
    result.vecX = v.vecX * val;
    result.vecY = v.vecY * val;
    result.vecZ = v.vecZ * val;
    return result;
}


/*--------------------------MATRIX-------------------------*/


class MATRIX
{
public:

	MATRIX() {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				ele[i][j] = 0;
	}

	MATRIX Transpose();
	MATRIX Inverse();
	float Determinant();

	MATRIX operator+(MATRIX m);
	MATRIX operator-(MATRIX m);
	MATRIX operator*(MATRIX m);
	MATRIX operator*(float t);

	VECTOR3D operator*(VECTOR3D v);

	float ele[3][3];
	
};

MATRIX MATRIX::Transpose() {
	MATRIX result;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			result.ele[i][j] = ele[j][i];

	return result;
}

MATRIX MATRIX::Inverse() {
    MATRIX result;
    float det = Determinant();
    if (det == 0)
        return result;

    int n = 3;


    float temp[3][3];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int ti = 0;
            for (int row = 0; row < n; row++) {
                if (row == i) continue;
                int tj = 0;
                for (int col = 0; col < n; col++) {
                    if (col == j) continue;
                    temp[ti][tj] = ele[row][col];
                    tj++;
                }
                ti++;
            }

            result.ele[j][i] = (1.0f / det) * (temp[0][0] * temp[1][1] - temp[0][1] * temp[1][0]);
            if ((i + j) % 2 == 1) {
                result.ele[j][i] = -result.ele[j][i]; 
            }
        }
    }
    return result;
}

float MATRIX::Determinant() {
    float d;
    d = ele[0][0] * ele[1][1] * ele[2][2]
        - ele[0][2] * ele[1][1] * ele[2][0]
        + ele[0][1] * ele[1][2] * ele[2][0]
        - ele[0][0] * ele[1][2] * ele[2][1]
        + ele[0][2] * ele[1][0] * ele[2][1]
        - ele[0][1] * ele[1][0] * ele[2][2];

    return d;
}


MATRIX MATRIX :: operator+(MATRIX m) {
	MATRIX result;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			result.ele[i][j] = ele[i][j] + m.ele[i][j];

	return result;
}

MATRIX MATRIX :: operator-(MATRIX m) {
	MATRIX result;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			result.ele[i][j] = ele[i][j] - m.ele[i][j];

	return result;
}

MATRIX MATRIX::operator*(MATRIX m) {
	MATRIX result;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			result.ele[i][j] = 0.0;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				result.ele[i][j] += ele[i][k] * m.ele[k][j];

	return result;
}

MATRIX MATRIX::operator*(float t) {
	MATRIX result;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			result.ele[i][j] = ele[i][j] * t;

	return result;
}

VECTOR3D MATRIX::operator*(VECTOR3D v) {
    VECTOR3D result;
    result.vecX = ele[0][0] * v.vecX + ele[0][1] * v.vecY + ele[0][2] * v.vecZ;
    result.vecY = ele[1][0] * v.vecX + ele[1][1] * v.vecY + ele[1][2] * v.vecZ;
    result.vecZ = ele[2][0] * v.vecX + ele[2][1] * v.vecY + ele[2][2] * v.vecZ;
    return result;
}



/*--------------------------MAIN-------------------------*/


int main()
{
    MATRIX a, b, result;
    VECTOR3D v;
    float t;

    /*ÀÔ·Â*/
    //Matrix a
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> a.ele[i][j];

    //Matrix b
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> b.ele[i][j];

    //Scalar t
    cin >> t;

    //Vector
    cin >> v.vecX >> v.vecY >> v.vecZ;

    cout << endl;


    /*Ãâ·Â*/
    //µ¡¼À
    result = a + b;
    cout << "a + b" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << result.ele[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //»¬¼À
    result = a - b;
    cout << "a - b" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << result.ele[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //½ºÄ®¶ó °ö
    result = a * t;
    cout << "a * t" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << result.ele[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Çà·Ä º¤ÅÍ °ö¼À
    VECTOR3D result_vector = a * v;
    cout << "a * v" << endl;
    cout << result_vector.vecX << endl << result_vector.vecY << endl << result_vector.vecZ  << endl;
    cout << endl;


    //ÀüÄ¡Çà·Ä
    result = a.Transpose();
    cout << "a.Transpose()" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << result.ele[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //¿ªÇà·Ä
    float det = a.Determinant();
    if (det != 0) {
        result = a.Inverse();
        cout << "a.Inverse()" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << result.ele[i][j] << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "Not Invertible." << endl;
    }
    cout << endl;


    //Det
    cout << "determinant : " << a.Determinant() << endl;

    return 0;
}