#include "UndoManager.hpp"

#include <juce_data_structures/juce_data_structures.h>

namespace mc::lua::bindings {

auto juce_UndoManager(sol::table& state) -> void
{
    // clang-format off
    auto um = state.new_usertype<juce::UndoManager>("UndoManager",
        sol::constructors<juce::UndoManager(int, int)>(),
        sol::base_classes, sol::bases<juce::ChangeBroadcaster>()
    );
    um["perform"] = sol::overload(
        [](juce::UndoManager* self, juce::UndoableAction* action) { return self->perform(action); },
        [](juce::UndoManager* self, juce::UndoableAction* action, juce::String const& name) { return self->perform(action, name); }
    );
    um["beginNewTransaction"] = sol::overload(
        [](juce::UndoManager* self) { return self->beginNewTransaction(); },
        [](juce::UndoManager* self, juce::String const& name) { return self->beginNewTransaction(name); }
    );
    // clang-format on

    um["clearUndoHistory"]                        = &juce::UndoManager::clearUndoHistory;
    um["getNumberOfUnitsTakenUpByStoredCommands"] = &juce::UndoManager::getNumberOfUnitsTakenUpByStoredCommands;
    um["setMaxNumberOfStoredUnits"]               = &juce::UndoManager::setMaxNumberOfStoredUnits;
    um["setCurrentTransactionName"]               = &juce::UndoManager::setCurrentTransactionName;
    um["getCurrentTransactionName"]               = &juce::UndoManager::getCurrentTransactionName;
    um["canUndo"]                                 = &juce::UndoManager::canUndo;
    um["undo"]                                    = &juce::UndoManager::undo;
    um["undoCurrentTransactionOnly"]              = &juce::UndoManager::undoCurrentTransactionOnly;
    um["getUndoDescription"]                      = &juce::UndoManager::getUndoDescription;
    um["getUndoDescriptions"]                     = &juce::UndoManager::getUndoDescriptions;
    um["getTimeOfUndoTransaction"]                = &juce::UndoManager::getTimeOfUndoTransaction;
    um["getActionsInCurrentTransaction"]          = &juce::UndoManager::getActionsInCurrentTransaction;
    um["getNumActionsInCurrentTransaction"]       = &juce::UndoManager::getNumActionsInCurrentTransaction;
    um["canRedo"]                                 = &juce::UndoManager::canRedo;
    um["redo"]                                    = &juce::UndoManager::redo;
    um["getRedoDescription"]                      = &juce::UndoManager::getRedoDescription;
    um["getRedoDescriptions"]                     = &juce::UndoManager::getRedoDescriptions;
    um["getTimeOfRedoTransaction"]                = &juce::UndoManager::getTimeOfRedoTransaction;
    um["isPerformingUndoRedo"]                    = &juce::UndoManager::isPerformingUndoRedo;
}

} // namespace mc::lua::bindings
