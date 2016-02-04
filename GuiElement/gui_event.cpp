#include "gui_event.h"


GuiEvent::GuiEvent(EventType type) :
	_eventType(type)
{
}

GuiEvent::~GuiEvent() {
}

/**
 * Create a GuiMouseEvent of the given type (can be MousePressEvent, MouseReleaseEvent,
 * MouseMoveEvent, MouseEnterEvent or MouseLeaveEvent) triggered with the mouse at the
 * given position and the button and modifiers keys (if any) pressed when the event is
 * triggered (or that triggered the event in the case of MousePressEvent and
 * MouseReleaseEvent events).
 */
GuiMouseEvent::GuiMouseEvent(GuiEvent::EventType type, int x, int y, Button btn, Modifiers mod_keys) :
	GuiEvent(type),
	_x(x), _y(y), _button(btn), _delta(0), _keyModifiers(mod_keys)
{	
}

/**
 * Create a GuiMouseEvent of type MouseWheelEvent triggered with the mouse at the
 * given position and the given wheel movement \p delta. It also takes the mouse
 * buttons or modifiers keys that are pressed when the event is triggered (if any).
 *
 * delta is defined in eighths of a degree. A positive value indicates that the
 * wheel was rotated forwards away from the user; a negative value indicates that
 * the wheelwas rotated backwards toward the user.
 */
GuiMouseEvent::GuiMouseEvent(int x, int y, int delta, Button btn, Modifiers keys) :
	GuiEvent(MouseWheelEvent),
	_x(x), _y(y), _button(btn), _delta(delta), _keyModifiers(keys)
{	
}

GuiMouseEvent::~GuiMouseEvent() {
}

/**
 * Create a GuiKeyEvent of the given type (can be KeyPressEent or KeyReleaseEvent) with
 * the key that triggered the event and the modifiers key that are also pressed if any.
 */
GuiKeyEvent::GuiKeyEvent(GuiEvent::EventType type, char key, GuiEvent::Modifiers mod_keys = 0) :
	GuiEvent(type),
	_key(key), _keyModifiers(mod_keys)
{	
}

GuiKeyEvent::~GuiKeyEvent() {
}
	

#endif // GUI_EVENT_H
