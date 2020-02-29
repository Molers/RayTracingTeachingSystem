#pragma once

#include "Core/Input.h"

namespace Molers {

	//基类定义dll导出 其继承的类就不用定义了

	class WindowsInput : public Input//继承自核心Core
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual  std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}


