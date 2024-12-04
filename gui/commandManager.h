#include "command.h"
#include <stack>

class CommandManager {
public:
    void executeCommand(Command* command) {
        command->execute();
        undoStack.push(command);
        while (!redoStack.empty()) {
            delete redoStack.top();
            redoStack.pop();
        }
    }

    void undo() {
        if (undoStack.empty()) return;
        Command* command = undoStack.top();
        undoStack.pop();
        command->undo();
        redoStack.push(command);
    }

    void redo() {
        if (redoStack.empty()) return;
        Command* command = redoStack.top();
        redoStack.pop();
        command->execute();
        undoStack.push(command);
    }

    bool undoIsEmpty() {
        return undoStack.empty();
    }

    bool redoIsEmpty() {
        return redoStack.empty();
    }

private:
    std::stack<Command*> undoStack;
    std::stack<Command*> redoStack;
};
