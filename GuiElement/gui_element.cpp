#include "gui_element.h"

/** \enum GuiElement::SizePolicy
 * The SizePolicy of a GuiElement defines how its parent sets the size
 * of all its children depending on the available space.
 */

/** \var GuiElement::FixedSize
 *
 * The width/height of ths GuiElement is fixed to the getPreferedWidth()/getPreferedHeight()
 * or to an arbitrary fixed width/height set using setFixedWidth()/setFixedHeight().
 * The GuiElement might still be smaller than this width/height however if when using the
 * getMinimumWidth() and getMinimumHeight() of all the widgets in the layout it still uses
 * more space than what is available. The GUI might not be really usable however if such a
  * case arise.
 */

/** \var GuiElement::PreferedSize
 *
 * The value returned by getPreferedWidth()/getPreferedHeight() is the prefered value, but
 * it can be smaller (down to the value returned by getMinimumWidth()/getMinimumHeight())
 * or bigger if more space is available and there is no expanding GuiElement in the layout.
 * The GuiElement might even be smaller than the getMinimumWidth()/getMinimumHeight() if
 * when using the minimum size for all the GuiElement it still takes more space than what
 * is available. The GUI might not be really usable however if such a case arise.
 */

/** \var GuiElement::ExpandingSize
 *
 * The value returned by getPreferedWidth()/getPreferedHeight() is the prefered value, but
 * it will take more space if available. The size can also be smaller than the prefered one
 * (down to the value returned by getMinimumWidth()/getMinimumHeight()) if needed.
 * The GuiElement might even be smaller than the getMinimumWidth()/getMinimumHeight() if
 * when using the minimum size for all the GuiElement it still takes more space than what
 * is available. The GUI might not be really usable however if such a case arise.
 */

/**
 * Construct a GuiElement with a default top-left position of (0, 0), a width
 * and height of 0 and a SizePolicy of PreferedSize in both directions.
 */
GuiElement::GuiElement() :
	_x(0), _y(0), _width(0), _height(0),
	_horizontalSizePolicy(PreferedSize),
	_verticalSizePolicy(PreferedSize),
	_parent(0)
{
}

/**
 * GuiElement destructor.
 */
GuiElement::~GuiElement() {
}

/**
 * Set the size of this GuiElement. It will also resize its children to fit
 * into the new given size.
 */
void GuiElement::setSize(int width, int height) {
	if (_width == width && _height == height)
		return;

	_width = width;
	_height = height;
	recomputeLayout();
}

/**
 * Set the top-left position of this GuiElement to the given ones.
 */
void GuiElement::setTopLeft(int y, int x) {
	if (_y == y && _x == x)
		return;

	_y = y;
	_x = x;
	recomputeChildPosition();
}

/**
 * Get the minimum width of this GuiElement. By default this returns 0 unless
 * a fixed width has been set. This function can be reimplemented in derived
 * classes, but this reimplementation should check first that a fixed width
 * has not been set using hasFixedWidth() and if one has been set it should
 * then return getWidth():
 * \code
int MyGuiElement::getMinimumWidth() {
	if (hasFixedWidth())
		return getWidth();

	// my custom GuiElement implementation here
	int min_width = 42; // because this is the answer to everything
	return min_width;
}
 * \endcode
 */
int GuiElement::getMinimumWidth() const {
	if (hasFixedWidth())
		return getWidth();
	return 0;
}

/**
 * Get the minimum height of this GuiElement. By default this returns 0 unless
 * a fixed height has been set. This function can be reimplemented in derived
 * classes, but this reimplementation should check first that a fixed height
 * has not been set using hasFixedHeight() and if one has been set it should
 * then return getHeight():
 * \code
int MyGuiElement::getMinimumHeight() {
	if (hasFixedHeight())
		return getHeight();

	// my custom GuiElement implementation here
	int min_height = 42; // because this is the answer to everything
	return min_height;
}
 * \endcode
 */
int GuiElement::getMinimumHeight() const {
	if (hasFixedHeight())
		return getHeight();
	return 0;
}

/**
 * Get the prefered width of this GuiElement. By default this returns 0 unless
 * a fixed width has been set. This function can be reimplemented in derived
 * classes, but this reimplementation should check first that a fixed width
 * has not been set using hasFixedWidth() and if one has been set it should
 * then return getWidth():
 * \code
int MyGuiElement::getMinimumWidth() {
	if (hasFixedWidth())
		return getWidth();

	// my custom GuiElement implementation here
	int width = 84; // because we want it bigger than getMinimumWidth()
	return width;
}
 * \endcode
 */
int GuiElement::getPreferedWidth() const {
	if (hasFixedWidth())
		return getWidth();
	return 0;
}

/**
 * Get the prefered height of this GuiElement. By default this returns 0 unless
 * a fixed height has been set. This function can be reimplemented in derived
 * classes, but this reimplementation should check first that a fixed height
 * has not been set using hasFixedHeight() and if one has been set it should
 * then return getHeight():
 * \code
int MyGuiElement::getMinimumWidth() {
	if (hasFixedHeight())
		return getHeight();

	// my custom GuiElement implementation here
	int height = 84; // because we want it bigger than getMinimumWidth()
	return height;
}
 * \endcode
 */
int GuiElement::getPreferedHeight() const {
	if (hasFixedHeight())
		return getHeight();
	return 0;
}

/**
 * Set the SizePolicy of this GuiElement for the horizontal direction.
 * The SizePolicy of a GuiElement defines how its parent sets the size
 * of all its children depending on the available space.
 */
void GuiElement::setHorizontalSizePolicy(SizePolicy policy) {
	if (policy == _horizontalSizePolicy)
		_horizontalSizePolicy = policy;
	if (_parent != 0)
		_parent->recomputeLayout();
}

/**
 * Set the SizePolicy of this GuiElement for the vertical direction.
 * The SizePolicy of a GuiElement defines how its parent sets the size
 * of all its children depending on the available space.
 */
void GuiElement::setVerticalSizePolicy(SizePolicy policy) {
	if (policy == _verticalSizePolicy)
		_verticalSizePolicy = policy;
	if (_parent != 0)
		_parent->recomputeLayout();
}

/**
 * Fix the width of this GuiElement. If the given \p width is negative,
 * it will unfix the width but will keep the horizontal SizePolicy to
 * fixed (which means it will use the preferedWidth()). You can also
 * unset a fixed width by calling setHorizontalSizePolicy() with
 * anything other than FixedWidth.
 */
void GuiElement::setFixedWidth(int width) {
	if (_width == -width && _horizontalSizePolicy == FixedSize)
		return;
	_width = -width;
	_horizontalSizePolicy = FixedSize;
	if (_parent != 0)
		_parent->recomputeLayout();
}

/**
 * Fix the height of this GuiElement. If the given \p height is negative,
 * it will unfix the height but will keep the horizontal SizePolicy to
 * fixed (which means it will use the preferedWidth()). You can also
 * unset a fixed width by calling setHorizontalSizePolicy() with
 * anything other than FixedWidth.
 */
void GuiElement::setFixedHeight(int height) {
	if (_height == -height && _verticalSizePolicy == FixedSize)
		return;
	_height = -height;
	_verticalSizePolicy = FixedSize;
	if (_parent != 0)
		_parent->recomputeLayout();
}

/**
 * This recomputes the size and position of the child GuiElement.
 * By default this function does nothing. Typically it will be reimplemented
 * in a layout GuiElement (e.g. GuiHorizontalLayout).
 */
void GuiElement::recomputeLayout() {
}

/**
 * Process the given event and return true if the event was accepted by
 * this GuiElement. If not accepted it can be processed by the parents
 * until one GuiElement accept it.
 * The default implementation does nothing and returns false.
 */
bool GuiElement::processEvent(GuiEvent*) {
	return false;
}

