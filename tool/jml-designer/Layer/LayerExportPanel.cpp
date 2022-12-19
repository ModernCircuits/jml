#include "LayerExportPanel.hpp"

#include "Component/PropertyPanel.hpp"

namespace mc {

struct ExportButtonPropertyComponent final : juce::ButtonPropertyComponent
{
    explicit ExportButtonPropertyComponent(std::function<void()>&& callback)
        : juce::ButtonPropertyComponent{"Image", false}, _callback{std::move(callback)}
    {
        jassert(_callback);
    }

    ~ExportButtonPropertyComponent() override = default;

    auto buttonClicked() -> void override { _callback(); }
    [[nodiscard]] auto getButtonText() const -> juce::String override { return "Select File"; }

private:
    std::function<void()> _callback;
};

LayerExportPanel::LayerExportPanel(LayerSelection& selection) : _selection{selection}
{
    auto const exportProperties = juce::Array<juce::PropertyComponent*>{
        new ExportButtonPropertyComponent{[this] { launchExportFileChooser(); }},
        new juce::ChoicePropertyComponent{
            _format,
            "Format",
            juce::StringArray{"PNG", "JPG"},
            juce::Array{toVar(ImageExporter::Format::png), toVar(ImageExporter::Format::jpg)},
        },
    };

    _panel.clear();
    _panel.addSection("Export", exportProperties);
    addAndMakeVisible(_panel);
}

auto LayerExportPanel::resized() -> void
{
    auto area = getLocalBounds();
    _panel.setBounds(area.reduced(2));
}

auto LayerExportPanel::launchExportFileChooser() -> void
{
    auto const format = fromVar<ImageExporter::Format>(_format);

    auto const* msg       = "Please select the image file you want to save to...";
    auto const dir        = juce::File::getCurrentWorkingDirectory();
    auto const* const ext = format == ImageExporter::Format::png ? "*.png" : "*.jpg";
    _fileChooser          = makeUnique<juce::FileChooser>(msg, dir, ext);

    auto const chooserFlags = juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::warnAboutOverwriting;
    auto const load = [this, format](juce::FileChooser const& chooser) { exportToImage(chooser.getResult(), format); };
    _fileChooser->launchAsync(chooserFlags, load);
}

auto LayerExportPanel::exportToImage(juce::File const& file, ImageExporter::Format format) -> void
{
    auto const layers = _selection.getLayers();
    if (layers.size() != 1) { return; }

    auto const& selected = layers[0];
    if (selected == nullptr) { return; }

    if (file.existsAsFile()) { file.deleteFile(); }
    auto out = file.createOutputStream();
    if (out == nullptr) { return; }

    auto exporter = ImageExporter{format};
    auto result   = exporter.exportLayer(*out, *selected);
    if (result.failed()) { DBG(result.getErrorMessage()); }
}

} // namespace mc
