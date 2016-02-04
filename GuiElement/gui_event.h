#ifndef GUI_EVENT_H
#define GUI_EVENT_H

/**
 * Base class for all Gui events.
 */
class GuiEvent {
public:
	enum EventType {
		MousePressEvent, MouseReleaseEvent, MouseWheelEvent,
		MouseMoveEvent, MouseEnterEvent, MouseLeaveEvent,
		KeyPressEvent, KeyReleaseEvent
	}
	
	enum Modifier {
		ShiftModifier = 1, ControlModifier = 2, AltModifier = 4, MetaModifier = 8
	}
	typedef int Modifiers;
	
	EventType eventType() const;
	
	virtual ~GuiEvent();

protected:
	GuiEvent(EventType);
	
private:
	EventType _eventType;
};

/**
 * Return the EventType for this event.
 */
inline GuiEvent::EventType GuiEvent::eventType() const {
	return _eventType;
}

/**
 * Class for the mouse events.
 */
class GuiMouseEvent : public GuiEvent {
public:
	enum Button {
		LeftButton, MiddleButton, RightButton, NoButton
	}

	GuiMouseEvent(GuiEvent::EventType, int x, int y, Button btn = NoButton, Modifiers mod_keys = 0);
	GuiMouseEvent(int x, int y, int delta, Button btn = NoButton, Modifiers keys = 0); // <= for MouseWheelEvent
	virtual ~GuiMouseEvent();
	
	int mouseXLocation() const;
	int mouseYLocation() const;
	Button mouseButton() const;
	int wheelDelta() const;
	Modifiers keyModifiers() const;
	
private:
	int _x;
	int _y;
	Button _button;
	int _delta;
	Modifiers _keyModifiers;
};

/**
 * Return the x position of the mouse when the event was triggered.
 */
inline int GuiMouseEvent::mouseXLocation() const {
	return _x;
}

/**
 * Return the y position of the mouse when the event was triggered.
 */
inline int GuiMouseEvent::mouseYLocation() const {
	return _y;
}

/**
 * Mouse button that triggered the event if the event is a MousePressEvent or
 * a MouseReleaseEvent, or the button that is pressed during a MouseMoveEvent or
 * MouseWheelEvent (it might be NoButton if no buttn is pressed).
 */
inline Button GuiMouseEvent::mouseButton() const {
	return _button;
}

/**
 * Return the distance in eighths of a degree that the wheel is rotated for
 * a MouseWheelEvent. A positive value indicates that the wheel was rotated
 * forwards away from the user; a negative value indicates that the wheel
 * was rotated backwards toward the user. Most mouse types work in steps of
 * 15 degrees, in which case the delta value is a multiple of 120;
 * i.e., 120 units * 1/8 = 15 degrees.
 */
inline int GuiMouseEvent::wheelDelta() const {
	return _delta;
}

/**
 * Return the modifiers key pressed when the mouse event occurs.
 */
Modifiers GuiMouseEvent::keyModifiers() const {
	return _keyModifiers;
}


/**
 * Class for the key events.
 */
class GuiKeyEvent : public GuiEvent {
public:
	GuiKeyEvent(GuiEvent::EventType, char key, GuiEvent::Modifiers mod_keys = 0);
	virtual ~GuiKeyEvent();
	
	char key() const;
	Modifiers keyModifiers() const;
	
private:
	char _key;
	Modifiers _keyModifiers;
};

/**
 * Return the key that triggered the event. This is 0 for an unknown key.
 */
inline char GuiKeyEvent::key() const {
	return _key;
}

/**
 * Return the modifiers key pressed when the mouse event occurs.
 */
inline Modifiers GuiKeyEvent::keyModifiers() const {
	return _keyModifiers;
}


#endif // GUI_EVENT_H
