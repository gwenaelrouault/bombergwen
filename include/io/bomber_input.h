#pragma once

#include <vector>
#include <string>

using namespace std;

typedef enum {
    BOMBER_QUIT,
    BOMBER_KEY_ESCAPE,
    BOMBER_KEY_UP,
    BOMBER_KEY_DOWN,
    BOMBER_KEY_LEFT,
    BOMBER_KEY_RIGHT,
    BOMBER_KEY_UP_CANCEL,
    BOMBER_KEY_DOWN_CANCEL,
    BOMBER_KEY_LEFT_CANCEL,
    BOMBER_KEY_RIGHT_CANCEL,
    BOMBER_KEY_ACTION
} T_BomberKeyEvent;

class BomberInputManager
{
public:
    BomberInputManager() {}
    ~BomberInputManager() {}

    vector<T_BomberKeyEvent> process_events();

private:

};