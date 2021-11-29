#include "MainComponent.h"

#include "LuaJUCE.hpp"

auto const* script = R"(C:\Developer\moderncircuits\tests\juce-lua\src\scripts\paint.lua)";

// #include <Windows.h>
// auto listenForScriptChange() -> void
// {
//     BOOL wait  = TRUE;
//     auto notif = FindFirstChangeNotification(script, TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE);
//     if (notif != NULL) {
//         while (wait) {
//             auto const status = WaitForSingleObject(notif, INFINITE);

//             switch (status) {
//             case WAIT_OBJECT_0: {
//                 if (FindNextChangeNotification(notif) == FALSE)
//                     ExitProcess(GetLastError());
//                 else {
//                     wait = FALSE;
//                 }
//                 break;
//             }
//             default: {
//                 ExitProcess(GetLastError());
//                 break;
//             }
//             }
//         }
//     }
// }

MainComponent::MainComponent()
{
    mc::add_juce_module(_lua);
    _lua["random"] = std::ref(juce::Random::getSystemRandom());
    _lua.open_libraries(sol::lib::base);
    _lua.script_file(script);

    setSize(600, 400);
}

void MainComponent::paint(juce::Graphics& g)
{
    sol::protected_function scriptPaint = _lua["paint"];
    scriptPaint(std::ref(g));
}

void MainComponent::resized() { }

auto MainComponent::mouseDown(juce::MouseEvent const& event) -> void
{
    sol::protected_function scriptMouseDown = _lua["mouseDown"];
    scriptMouseDown(std::ref(event));
    repaint();
}
