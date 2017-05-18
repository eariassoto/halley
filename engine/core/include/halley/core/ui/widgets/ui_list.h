#pragma once

#include "../ui_widget.h"
#include "halley/core/graphics/sprite/sprite.h"
#include "halley/core/graphics/text/text_renderer.h"
#include "ui_button.h"

namespace Halley {
	class UIStyle;
	class UIListItem;

	class UIList : public UIWidget {
		friend class UIListItem;

	public:
		struct Buttons {
			int accept = -1;
			int next = -1;
			int prev = -1;
			bool xAxis = false;
			bool yAxis = false;
		};

		explicit UIList(const String& id, std::shared_ptr<UIStyle> style, UISizerType orientation = UISizerType::Vertical, int nColumns = 1);

		void setSelectedOption(int option);
		void setSelectedOptionId(const String& id);
		int getSelectedOption() const;
		const String& getSelectedOptionId() const;

		void addTextItem(const String& id, const String& label);
		void addItem(const String& id, std::shared_ptr<UIWidget> widget, float proportion = 0, Vector4f border = {}, int fillFlags = UISizerFillFlags::Fill);
		void addItem(const String& id, std::shared_ptr<UISizer> sizer, float proportion = 0, Vector4f border = {}, int fillFlags = UISizerFillFlags::Fill);
		void clear();

		void setInputButtons(const Buttons& button);
		void updateInputDevice(InputDevice& device) override;

	protected:
		void draw(UIPainter& painter) const override;
		void update(Time t, bool moved) override;

	private:
		std::shared_ptr<UIStyle> style;
		UISizerType orientation;
		Sprite sprite;
		std::vector<std::shared_ptr<UIListItem>> items;

		int curOptionHighlight = -1;
		int curOption = -1;
		int nColumns = 1;
		Buttons inputButtons;

		void onItemClicked(UIListItem& item);
		void addItem(std::shared_ptr<UIListItem> item);
	};

	class UIListItem : public UIClickable {
	public:
		explicit UIListItem(const String& id, UIList& parent, std::shared_ptr<UIStyle> style, int index);

		void onClicked(Vector2f mousePos) override;
		void setSelected(bool selected);
		int getIndex() const;

	protected:
		void draw(UIPainter& painter) const override;
		void update(Time t, bool moved) override;

	private:
		UIList& parent;
		std::shared_ptr<UIStyle> style;
		int index;
		Sprite sprite;
		bool selected = false;

		void doSetState(State state) override;
		void updateSpritePosition();
	};
}
