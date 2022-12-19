project(jml-designer VERSION 0.1.0)

find_package(mc-core REQUIRED)

set_directory_properties(
    PROPERTIES
        JUCE_COMPANY_NAME       "Modern Circuits"
        JUCE_COMPANY_COPYRIGHT  "Copyright 2022 Modern Circuits. All rights reserved."
)

juce_add_binary_data(JMLDesigner_BinaryData
    HEADER_NAME
        "BinaryData.hpp"
    NAMESPACE
        mcbd
    SOURCES
        "Resources/svg/tool_circle.svg"
        "Resources/svg/tool_rectangle.svg"
        "Resources/svg/tool_select.svg"

        "Resources/svg/outline/content_copy.svg"
        "Resources/svg/outline/content_cut.svg"
        "Resources/svg/outline/content_paste.svg"
        "Resources/svg/outline/file_open.svg"
        "Resources/svg/outline/open_in_new.svg"
        "Resources/svg/outline/redo.svg"
        "Resources/svg/outline/save_as.svg"
        "Resources/svg/outline/save.svg"
        "Resources/svg/outline/undo.svg"
)

juce_add_gui_app(jml-designer
    PRODUCT_NAME
        "JML Designer"
)

set_target_properties(jml-designer
    PROPERTIES
        UNITY_BUILD_MODE GROUP
)

set(sources
    "Application/Application.cpp"
    "Application/Application.hpp"
    "Application/Main.cpp"
    "Application/MainComponent.cpp"
    "Application/MainComponent.hpp"

    "Component/Button.hpp"
    "Component/PropertyPanel.hpp"
    "Component/TreeView.hpp"

    "Document/Document.cpp"
    "Document/Document.hpp"
    "Document/DocumentCanvas.cpp"
    "Document/DocumentCanvas.hpp"
    "Document/DocumentEditor.cpp"
    "Document/DocumentEditor.hpp"

    "Export/Exporter.hpp"
    "Export/ImageExporter.cpp"
    "Export/ImageExporter.hpp"

    "Layer/Layer.cpp"
    "Layer/Layer.hpp"
    "Layer/LayerExportPanel.cpp"
    "Layer/LayerExportPanel.hpp"
    "Layer/LayerPropertyPanel.cpp"
    "Layer/LayerPropertyPanel.hpp"
    "Layer/LayerSelection.cpp"
    "Layer/LayerSelection.hpp"
    "Layer/LayerTree.cpp"
    "Layer/LayerTree.hpp"
    "Layer/LayerTreeItem.cpp"
    "Layer/LayerTreeItem.hpp"

    "Layer/Group/GroupLayer.cpp"
    "Layer/Group/GroupLayer.hpp"

    "Layer/Shape/ShapeLayer.cpp"
    "Layer/Shape/ShapeLayer.hpp"

    "LookAndFeel/LookAndFeel.hpp"

    "Menu/CommandIDs.hpp"
    "Menu/MenuBar.cpp"
    "Menu/MenuBar.hpp"

    "Tool/SelectionTool.cpp"
    "Tool/SelectionTool.hpp"
    "Tool/ShapeTool.cpp"
    "Tool/ShapeTool.hpp"
    "Tool/Tool.cpp"
    "Tool/Tool.hpp"
    "Tool/ToolBar.cpp"
    "Tool/ToolBar.hpp"
)

target_sources(jml-designer PRIVATE ${sources})
set_source_files_properties(jml-designer ${sources} PROPERTIES UNITY_GROUP "src")

target_compile_definitions(jml-designer
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:jml-designer,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:jml-designer,JUCE_VERSION>"
        _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING=1
)

target_include_directories(jml-designer
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(jml-designer
    PRIVATE
        mc::mc_gui_extra
    PUBLIC
        JMLDesigner_BinaryData

        mc-core::mc-core

        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
