#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

class GuiEvent;

/**
 * Base class for all GUI elements (Widgets or Layout).
 */
class GuiElement {
public:
	enum SizePolicy { FixedSize, PreferedSize, ExpandingSize }

	virtual ~GuiElement();

	// Set by the layout
	// Can also be set manually when no layout is used
	int getTop() const;
	int getLeft() const;
	int getWidth() const;
	int getHeight() const;

	void setSize(int width, int height);
	void setTopLeft(int, int);

	// Used by the layout engine to set the size
	SizePolicy getHorizontalSizePolicy() const;
	SizePolicy getVerticalSizePolicy() const;
	virtual int getMinimumWidth() const;
	virtual int getMinimumHeight() const;
	virtual int getPreferedWidth() const;
	virtual int getPreferedHeight() const;

	void setHorizontalSizePolicy(SizePolicy);
	void setVerticalSizePolicy(SizePolicy);
	void setFixedWidth(int);
	void setFixedHeight(int);

protected:
	GuiElement();
	virtual void recomputeLayout(); // if _width or _height is 0, set (0, 0) size and (_x, _y_) top-left to all children
	virtual void recomputeChildPosition();
	virtual bool processEvent(GuiEvent*);

	bool hasFixedWidth() const;
	bool hasFixedHeight() const;

private:
	int _x;
	int _y;
	int _width;
	int _height;
	SizePolicy _horizontalSizePolicy;
	SizePolicy _verticalSizePolicy;
	GuiElement* _parent;
};

/**
 * Get the top location (i.e. y) of the GuiElement.
 * This is set by setTopLeft(int, int).
 * The default position is 0 (if setTopLeft has not been called()).
 */
inline int GuiElement::getTop() const {
	return _y;
}

/**
 * Get the top location (i.e. x) of the GuiElement.
 * This is set by setTopLeft(int, int).
 * The default position is 0 (if setTopLeft has not been called()).
 */
inline int GuiElement::getLeft() const {
	return _x;
}

/**
 * Get the width of the GuiElement.
 * This is set by setSize(int, int).
 * If the size has not been set, this returns -1.
 */
inline int GuiElement::getWidth() const {
	return _width < 0 ? -_width : _width;
}

/**
 * Get the height of the GuiElement.
 * This is set by setSize(int, int).
 * If the size has not been set, this returns -1.
 */
inline int GuiElement::getHeight() const {
	return _height < 0 ? -_height : _height;
}

/**
 * Get the SizePolicy for the horizontal direction of this GuiElement.
 * This is set by setHorizontalSizePolicy(SizePolicy).
 * The SizePolicy is used by parent GuiElement when they have
 * several non-fixed size children to compute the size of each
 * children from the available space.
 */
inline GuiElement::SizePolicy GuiElement::getHorizontalSizePolicy() const {
	return _horizontalSizePolicy;
}

/**
 * Get the SizePolicy for the vertical direction of this GuiElement.
 * This is set by setHorizontalSizePolicy(SizePolicy).
 * The SizePolicy is used by parent GuiElement when they have
 * several non-fixed size children to compute the size of each
 * children from the available space.
 */
inline GuiElement::SizePolicy GuiElement::getVerticalSizePolicy() const {
	return _verticalSizePolicy;
}

/**
 * Return true if the width of this GuiElement has been fixed. The width
 * can be fixed by calling setFixedWidth(int). It can be unset by changing
 * the horizontal SizePolicy to something other than FixedSize (with a call
 * to setHorizontalSizePolicy()). Calling setFixedWidth() with a negative
 * number will also unset the fixed width but will keep the horizontal
 * SizePolicy to FixedSize (which means it will use the size returned by
 * getPreferedWidth()).
 */
inline bool GuiElement::hasFixedWidth() const {
	return _width < 0 && _horizontalSizePolicy == FixedSize;
}

/**
 * Return true if the height of this GuiElement has been fixed. The height
 * can be fixed by calling setFixedHeight(int). It can be unset by changing
 * the vertical SizePolicy to something other than FixedSize (with a call
 * to setVerticalSizePolicy()). Calling setFixedHeight() with a negative
 * number will also unset the fixed height but will keep the vertical
 * SizePolicy to FixedSize (which means it will use the size returned by
 * getPreferedHeight()).
 */
inline bool GuiElement::hasFixedHeight() const {
	return _height < 0 && _verticalSizePolicy == FixedSize;
}



#endif // GUI_ELEMENT_H
