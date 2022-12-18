#include "Tool.hpp"

namespace mc {

Tool::Tool(DocumentCanvas& canvas) : _canvas{&canvas} {}

auto Tool::getDocumentCanvas() -> DocumentCanvas& { return *_canvas; }

auto Tool::getDocumentCanvas() const -> DocumentCanvas const& { return *_canvas; }

} // namespace mc
