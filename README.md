# DirectX UI Framework Assistant

A lightweight retained-mode UI framework and layout assistant built in C++ using DirectX 11.

This project was developed for my university dissertation as a prototype framework for creating simple user interfaces inside standalone DirectX applications. It includes reusable widgets, basic input handling, automatic layout positioning, and JSON-based layout saving/loading.

## Features

* Retained-mode UI framework
* DirectX 11 rendering pipeline
* Direct2D / DirectWrite text rendering
* Reusable widgets:

  * Buttons
  * Sliders
  * Checkboxes
  * Panels
* Mouse input handling:

  * Hover detection
  * Click detection
  * Slider dragging
* Automatic vertical layout management
* Command-line UI assistant for generating layouts
* JSON save/load support using `nlohmann::json`
* Basic unit tests for layout and configuration logic

## Purpose

DirectX 11 provides low-level rendering control, but it does not include a built-in UI framework. This means developers often need to manually create interface elements such as buttons, sliders, panels and input handling from scratch.

This project explores whether a lightweight UI framework and guided assistant can reduce repetitive setup work when creating debug menus, tool overlays, or simple UI layouts for standalone DirectX applications.

## How it works

The project uses a small architecture based around:

```text
UI Assistant → Config Store → Panel → Widgets → Draw List → DirectX Renderer
                          ↓
                    JSON Save / Load
```

The command-line assistant asks the user what layout they want to create, stores the result in a configuration structure, and then generates the UI inside the DirectX application.

## Project structure

```text
source/
├── assistant/       # UI assistant and config generation
├── renderer/        # DirectX renderer and text rendering
├── ui/              # User interface, draw list and widgets
├── utility/         # JSON manager, utilities and tests
└── main.cpp
```

## Requirements

* Windows
* Visual Studio
* C++17 or later
* DirectX 11
* Direct2D
* DirectWrite
* Windows SDK
* nlohmann/json

## Current limitations

This project is a university prototype and is not production-ready.

Known limitations:

* Limited widget set
* Command-line layout generation only
* No full visual editor yet
* Basic JSON validation
* Fixed-size window
* Limited styling/customisation options

## Future improvements

Possible future work includes:

* Visual edit mode
* More widgets
* Colour customisation
* Better JSON validation
* Drag-and-drop layout editing
* Improved styling system
* More robust error handling

This project is currently shared for portfolio and educational purposes.
