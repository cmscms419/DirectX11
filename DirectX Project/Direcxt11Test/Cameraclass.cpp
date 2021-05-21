#include "Stdafx.h"
#include "Cameraclass.h"

CameraClass::CameraClass()
{
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

CameraClass::CameraClass(const CameraClass& other)
{

}

CameraClass::~CameraClass()
{

}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}

XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

void CameraClass::Render()
{
	XMFLOAT3 up, position, lookAT;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;


	// ������ ����Ű�� ���͸� �����մϴ�.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// XMVECTOR ����ü�� �ε��Ѵ�.
	upVector = XMLoadFloat3(&up);

	// 3D���忡�� ī�޶��� ��ġ�� �����մϴ�.
	position = m_position;

	// XMVECTOR ����ü�� �ε��Ѵ�.
	positionVector = XMLoadFloat3(&position);

	// �⺻������ ī�޶� ã���ִ� ��ġ�� �����մϴ�.
	lookAT.x = 0.0f;
	lookAT.y = 0.0f;
	lookAT.z = 1.0f;

	// XMVECTOR ����ü�� �ε��Ѵ�.
	lookAtVector = XMLoadFloat3(&lookAT);

	// yaw (y ��), pitch (x ��) �� roll (z ��)�� ȸ������ ���� ������ �����մϴ�.
	pitch = m_rotation.x * 0.0174532925f;
	yaw = m_rotation.y * 0.0174532925f;
	roll = m_rotation.z * 0.0174532925f;

	// yaw, pitch, roll ���� ���� ȸ�� ����� ����ϴ�.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//lookAt �� up ���͸� ȸ�� ��ķ� �����Ͽ� �䰡 �������� �ùٸ��� ȸ���ǵ��� �մϴ�.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector - XMVector2TransformCoord(upVector, rotationMatrix);

	// ȸ�� �� ī�޶� ��ġ�� ��� ��ġ�� ��ȯ�մϴ�.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	//���������� �� ���� ������Ʈ �� ���Ϳ��� �� ����� ����ϴ�.
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
}

void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}