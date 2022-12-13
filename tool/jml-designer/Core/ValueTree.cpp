#include "ValueTree.hpp"

namespace mc {

auto loadValueTree(juce::File const& file, bool asXml) -> juce::ValueTree
{
    if (asXml) {
        auto xml = juce::XmlDocument::parse(file);
        if (xml == nullptr) { return {}; }
        return juce::ValueTree::fromXml(*xml);
    }

    auto in = juce::FileInputStream{file};
    if (not in.openedOk()) { return {}; }
    return juce::ValueTree::readFromStream(in);
}

auto saveValueTree(juce::ValueTree const& v, juce::File const& file, bool asXml) -> bool
{
    auto tmp = juce::TemporaryFile(file);
    auto out = tmp.getFile().createOutputStream();
    if (not out->getStatus().wasOk()) { return false; }

    if (asXml) {
        if (auto xml = v.createXml(); xml) { xml->writeTo(*out); }
    } else {
        v.writeToStream(*out);
    }

    out.reset();
    if (tmp.getFile().existsAsFile()) { return tmp.overwriteTargetFileWithTemporary(); }
    return false;
}

} // namespace mc
