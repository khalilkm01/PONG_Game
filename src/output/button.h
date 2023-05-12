#ifndef BUTTON_H
#define BUTTON_H

#include <string>

class Button {
public:
    Button(const std::string& text);
    const std::string& getText() const;

private:
    std::string text;
};

#endif // BUTTON_H
