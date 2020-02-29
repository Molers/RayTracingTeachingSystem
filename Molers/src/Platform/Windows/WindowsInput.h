#pragma once

#include "Core/Input.h"

namespace Molers {

	//���ඨ��dll���� ��̳е���Ͳ��ö�����

	class WindowsInput : public Input//�̳��Ժ���Core
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual  std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}


