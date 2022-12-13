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

target_sources(jml-designer
    PRIVATE
        LookAndFeel.hpp
        Main.cpp
        MainComponent.cpp
        MainComponent.hpp

        Component/Button.hpp
        Component/TreeView.hpp

        Core/ValueTree.cpp
        Core/ValueTree.hpp

        Document/Document.cpp
        Document/Document.hpp
        Document/DocumentCanvas.cpp
        Document/DocumentCanvas.hpp
        Document/DocumentEditor.cpp
        Document/DocumentEditor.hpp

        Layer/Layer.cpp
        Layer/Layer.hpp
        Layer/LayerCanvas.cpp
        Layer/LayerCanvas.hpp
        Layer/LayerPropertyPanel.cpp
        Layer/LayerPropertyPanel.hpp
        Layer/LayerTreeView.cpp
        Layer/LayerTreeView.hpp
        Layer/LayerTreeViewItem.cpp
        Layer/LayerTreeViewItem.hpp

        Layer/Group/GroupLayer.cpp
        Layer/Group/GroupLayer.hpp
        Layer/Group/GroupLayerCanvas.cpp
        Layer/Group/GroupLayerCanvas.hpp
        Layer/Group/GroupLayerTreeViewItem.cpp
        Layer/Group/GroupLayerTreeViewItem.hpp

        Layer/Rectangle/RectangleLayer.cpp
        Layer/Rectangle/RectangleLayer.hpp
        Layer/Rectangle/RectangleLayerCanvas.cpp
        Layer/Rectangle/RectangleLayerCanvas.hpp
        Layer/Rectangle/RectangleLayerTreeViewItem.cpp
        Layer/Rectangle/RectangleLayerTreeViewItem.hpp

        Menu/CommandIDs.hpp
        Menu/MenuBar.cpp
        Menu/MenuBar.hpp

        Property/ColorPropertyComponent.cpp
        Property/ColorPropertyComponent.hpp
        Property/FilePropertyComponent.cpp
        Property/FilePropertyComponent.hpp
        Property/ValuePropertyComponent.cpp
        Property/ValuePropertyComponent.hpp

        Tool/SelectionTool.cpp
        Tool/SelectionTool.hpp
        Tool/ShapeTool.cpp
        Tool/ShapeTool.hpp
        Tool/Tool.cpp
        Tool/Tool.hpp
        Tool/ToolBar.cpp
        Tool/ToolBar.hpp
)

target_compile_definitions(jml-designer
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:jml-designer,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:jml-designer,JUCE_VERSION>"
)

target_include_directories(jml-designer
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(jml-designer
    PRIVATE
        mc::mc_gui_basics
        juce::juce_gui_extra
    PUBLIC
        JMLDesigner_BinaryData

        mc-core::mc-core

        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
