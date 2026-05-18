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
} T_BomberKeyEvent;

class BomberInputManager
{
public:
    BomberInputManager() {}
    ~BomberInputManager() {}

    vector<T_BomberKeyEvent> process_events();

private:

};