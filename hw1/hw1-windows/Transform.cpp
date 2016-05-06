// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>
//Please implement the following functions:
 
/* Compute a matrix rotation, based on Rodrigues rotation formula,
   for rotating around an arbitratry axis (ex : we want to
   rotate point b(0,1,3) around arbitrary axis 3i + 2j + 5k)
   */
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// http://planetmath.org/rodriguesrotationformula
	// R(a, theta) =
	mat3 identity3 = mat3(1.0);
	vec3 normalizedAxis = glm::normalize(axis);
	double x = normalizedAxis.x, y = normalizedAxis.y, z = normalizedAxis.z;
	float radianAngle = degrees * pi / 180;

	mat3 A = mat3(0, z, -y, -z, 0, x, y, -x, 0);
	mat3 rotationMatrix = identity3 + sin(radianAngle) * A + (1 - cos(radianAngle)) * (A * A);
    
	return rotationMatrix;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// Rotated vector = R(a, theta) * axis
	mat3 R = rotate(degrees, -up);
	eye = eye * R;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 n = glm::cross(eye, -up);
	mat3 R = rotate(degrees, n);
	eye = eye * R;
	up = up * R;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// Create a coordinate frame for the camera
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);
	// Define a rotation matrix from the 3 orthonormal vectors
	mat4 rotationComponent = mat4(u.x, v.x, w.x, 0,
					 u.y, v.y, w.y, 0,
					 u.z, v.z, w.z, 0,
					 0,   0,   0 ,  1);

	// Apply appropriate translation for camera (eye) location.
	// It's important to apply translation BEFORE rotation. The translation
	// must come first (to bring camera to origin) before the rotation is applied.
	mat4 translationComponent = mat4(1, 0, 0, 0,
									 0, 1, 0, 0,
									 0, 0, 1, 0,
									 -eye.x, -eye.y, -eye.z, 1); // 1) translate by -eye

  return rotationComponent * translationComponent; // 2) apply rotation
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
