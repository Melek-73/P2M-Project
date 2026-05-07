# P2M – Edge AI Gesture-Controlled Industrial HMI System

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-Raspberry%20Pi%204%20%7C%20STM32F747I-lightgrey)
![AI](https://img.shields.io/badge/AI-Edge%20Impulse%20%7C%20FOMO-brightgreen)
![Status](https://img.shields.io/badge/status-Active-success)

> A real-time Edge AI-based touchless Human-Machine Interface (HMI) for industrial environments — control dashboards with hand gestures, no physical contact required.

---

## 📌 Table of Contents

- [Overview](#overview)
- [Problem Statement](#problem-statement)
- [Proposed Solution](#proposed-solution)
- [System Architecture](#system-architecture)
- [Hardware Components](#hardware-components)
- [AI Model](#ai-model)
- [Dataset](#dataset)
- [System Workflow](#system-workflow)
- [HMI & UI Design](#hmi--ui-design)
- [Communication Architecture](#communication-architecture)
- [Performance & Optimization](#performance--optimization)
- [Technologies & Tools](#technologies--tools)
- [Current Status](#current-status)
- [Future Improvements](#future-improvements)
- [Author](#author)

---

## Overview

**P2M** is a gesture-controlled embedded HMI system that allows operators to interact with an industrial dashboard using hand gestures instead of physical buttons or touchscreens.

The project combines:

- 🤖 **Computer Vision**
- 🔌 **Embedded Systems**
- 🧠 **Edge AI**
- 📡 **Real-Time Communication**
- 🖥️ **Graphical User Interfaces**

Built on a distributed architecture using a **Raspberry Pi 4** for AI inference and an **STM32F747I Discovery Kit** for HMI rendering.

---

## 🎯 Problem Statement

Traditional industrial HMIs rely on physical interaction (buttons, touchscreens), introducing several limitations:

- Physical contact in harsh or contaminated environments
- Reduced usability when operators wear gloves
- Limited interaction flexibility
- Hygiene and maintenance concerns
- Poor ergonomics in repetitive interaction scenarios

A contactless, intelligent interaction system is needed to improve usability, flexibility, and operator experience in industrial settings.

---

## 🚀 Proposed Solution

This project introduces a **gesture-controlled embedded HMI system** based on real-time computer vision and Edge AI. The system detects hand gestures via camera and translates them into interaction events:

- 🖱️ Cursor movement
- 🧭 Navigation
- 🖱️ Click actions

### Example Use Case

An operator interacts with an industrial dashboard without ever touching the screen:

| Gesture | Action          |
| ------- | --------------- |
| 🖐 Palm | Cursor movement |
| ✊ Fist | Click / Select  |

Example dashboard elements:

- 🌡 Temperature monitoring
- ⚙ Motor speed control
- ✅ Machine status visualization
- 📊 Industrial process navigation

---

## 🏗️ System Architecture

```
Pi NoIR Camera V2
        ↓
Raspberry Pi 4
(FOMO Edge AI Inference)
        ↓ UART
STM32F747I Discovery Kit
(TouchGFX HMI + LTDC Rendering)
        ↓
Industrial Dashboard Display
```

---

## 🔧 Hardware Components

| Component                | Purpose                       |
| ------------------------ | ----------------------------- |
| Raspberry Pi 4 Model B   | Edge AI inference             |
| Pi NoIR Camera V2        | Real-time image acquisition   |
| STM32F747I Discovery Kit | HMI control and rendering     |
| LTDC TFT Display         | Dashboard visualization       |
| UART Interface           | Communication between systems |

---

## 🧠 AI Model

### Model Type

- **FOMO** (Faster Objects, More Objects) — a lightweight CNN-based object detection architecture built on **MobileNetV2**

### Training Platform

- [Edge Impulse Studio](https://edgeimpulse.com)

### Model Capabilities

- Hand detection
- Gesture classification
- Centroid extraction (x, y)

### Gesture Classes

| Class      | Description                 |
| ---------- | --------------------------- |
| Palm       | Open hand — cursor movement |
| Fist       | Closed hand — click/select  |
| Background | No hand detected            |

---

## 📂 Dataset

A custom dataset was created and manually annotated using **Edge Impulse**.

| Property        | Details  |
| --------------- | -------- |
| Training images | ~500     |
| Testing images  | ~80      |
| Class balance   | Balanced |

**Variations included:**

- Different hand positions
- Multiple lighting conditions
- Different scales and distances
- Various backgrounds
- Partial hand visibility

---

## ⚙️ System Workflow

```
1. Image Acquisition    →  Camera captures real-time frames
2. AI Inference         →  Raspberry Pi runs FOMO model on each frame
3. Feature Extraction   →  Gesture class + hand centroid (x, y) extracted
4. Signal Processing    →  EMA smoothing + gesture debouncing
5. Communication        →  Data sent via UART
                           Format: <X:120,Y:85,G:PALM>
6. Embedded Processing  →  STM32 parses data, maps to screen, triggers events
7. UI Rendering         →  TouchGFX renders dashboard via LTDC
```

---

## 🖥️ HMI & UI Design

The graphical interface was developed using the **TouchGFX** embedded GUI framework.

**Features:**

- Real-time cursor rendering
- Interactive dashboard navigation
- Embedded graphical components
- Industrial-style UI design

---

## 🔄 Communication Architecture

**Protocol:** UART

| Parameter  | Value                      |
| ---------- | -------------------------- |
| Connection | Raspberry Pi TX → STM32 RX |
| Baudrate   | 115200                     |

**Data Transmitted:**

- X coordinate
- Y coordinate
- Gesture state

**Packet format:**

```
<X:120,Y:85,G:PALM>
```

---

## ⚡ Performance & Optimization

### Latency Breakdown

| Block              | Latency   |
| ------------------ | --------- |
| AI Inference       | ~30–60 ms |
| UART Communication | ~1–2 ms   |
| STM32 Rendering    | < 5 ms    |

### Optimization Techniques

- INT8 Quantization
- Lightweight FOMO architecture
- Reduced input resolution
- Efficient UART packet structure
- Coordinate smoothing (EMA)

---

## 🧰 Technologies & Tools

### Software

| Tool                | Purpose                     |
| ------------------- | --------------------------- |
| Python              | Raspberry Pi scripting      |
| Edge Impulse Studio | Model training & deployment |
| TensorFlow Lite     | On-device inference         |
| STM32CubeIDE        | Firmware development        |
| STM32CubeMX         | Peripheral configuration    |
| TouchGFX            | Embedded GUI design         |
| FreeRTOS            | Real-time task management   |
| VNC Viewer          | Remote Pi access            |
| Minicom             | UART text interface         |

### Concepts

Edge AI · Computer Vision · CNNs · Embedded Systems · Real-Time Systems · UART Communication · LTDC Graphics · Signal Processing

---

## 👨‍💻 Author

**Melek Fourati**

---

> _This project demonstrates how Edge AI, embedded systems, and computer vision can be combined to build a modern contactless industrial HMI — transforming traditional interaction into a real-time intelligent experience._
