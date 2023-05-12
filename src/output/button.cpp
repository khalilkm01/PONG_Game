#include "button.h"

Button::Button(const std::string &text) : text(text) {}

const std::string &Button::getText() const
{
    return text;
}
