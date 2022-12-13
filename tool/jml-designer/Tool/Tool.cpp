#include "Tool.hpp"

namespace mc {

Tool::Tool(DocumentCanvas& canvas) : _canvas{&canvas} {}

auto Tool::canvas() -> DocumentCanvas& { return *_canvas; }

auto Tool::canvas() const -> DocumentCanvas const& { return *_canvas; }

} // namespace mc
