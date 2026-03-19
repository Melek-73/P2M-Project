# P2M – Embedded AI-Based Gesture-Controlled Industrial HMI System

## 1. Problem Description

Modern manufacturing environments rely heavily on **Human-Machine Interfaces (HMIs)** to monitor and control industrial processes such as temperature, motor speed, and machine status. Traditional HMIs (buttons, touchscreens) present several limitations:

- Physical contact is required → not ideal in harsh or contaminated environments
- Operators may wear gloves → touch interaction becomes unreliable
- Repetitive manual interaction → reduces efficiency and ergonomics
- Limited flexibility in interaction design

There is a need for a **contactless**, **intuitive**, and **intelligent** interface that improves operator interaction while maintaining reliability in industrial conditions.

## 2. Proposed Solution

This project introduces a **gesture-controlled embedded HMI system** based on:

- An **embedded AI model** running on a microcontroller
- A **camera** capturing user hand gestures
- A **real-time interface** displayed on an LCD
- Gesture-based navigation and control of machine parameters

The system enables operators to interact with industrial dashboards using simple hand gestures such as:

- 👉 **Swipe right** → Next screen
- 👈 **Swipe left** → Previous screen
- ✊ **Fist** → Stop machine
- 🖐 **Palm** → Open menu

This creates a **touchless**, **intuitive** control system suitable for industrial environments.

## 3. Use Case: Smart Manufacturing Dashboard

**Scenario**  
An operator supervises a production machine using an LCD dashboard displaying:

- 🌡 Temperature
- ⚙ Motor speed (RPM)
- ✅ Machine status (Running / Stopped)

Instead of using buttons or touch:

- The operator performs gestures in front of the camera
- The system recognizes the gesture using embedded AI
- The interface reacts instantly (navigation or control action)

## 4. System Architecture
Camera → Preprocessing → AI Model → Decision Logic → LCD Interface
### High-Level Architecture

### Hardware Components

- **Microcontroller**: STM32F746NG  
  - Cortex-M7 core  
  - Executes AI inference and system logic
- **Camera Sensor**: OV5640  
  - Captures real-time images of user gestures
- **Display**: TFT LCD (LTDC interface)  
  - Displays industrial dashboard and UI
- **Memory**: Internal SRAM / External SDRAM  
  - Stores frame buffers and AI data

### Software Components

- **Embedded AI Runtime**: X-CUBE-AI
- **RTOS**: FreeRTOS (task scheduling)
- **HAL Drivers**: STM32 HAL (DCMI, LTDC, DMA)
- **Application Layer**: Gesture recognition + UI logic

## 5. System Workflow

Step-by-step execution:

1. **Image Acquisition**  
   Camera captures a frame via DCMI + DMA  
   Image stored in frame buffer

2. **Preprocessing**  
   Resize image (e.g., 320×240 → 64×64)  
   Convert format (RGB → grayscale or normalized RGB)  
   Normalize pixel values (e.g., -128 to 127)

3. **AI Inference**  
   Processed image is fed into the neural network  
   Model outputs probabilities for gesture classes

4. **Decision Logic**  
   Highest probability → predicted gesture  
   Gesture mapped to system action

5. **UI Update**  
   LCD interface updated accordingly  
   Example:  
   - Gesture = “Fist” → Machine status = STOPPED  
   - Gesture = “Swipe Right” → Next dashboard page

## 6. User Interface (UI/UX Design)

The LCD displays a professional industrial dashboard:

### Interaction Model

| Gesture     | Action          |
|-------------|-----------------|
| 🖐 Palm     | Open menu       |
| 👉 Swipe Right | Next screen  |
| 👈 Swipe Left  | Previous screen |
| ✊ Fist      | Stop machine    |

## 7. AI Model Description

- **Type**: Image classification model
- **Input**: 64×64 image (grayscale or RGB)
- **Output**: Gesture class (e.g., 10 classes)

### Processing Pipeline
Image → Quantization → Tensor → Inference → Output Vector
**Output Example**
[0.01, 0.02, 0.85, 0.03, ...]
→ Predicted class = 2


## 8. Technical Concepts Used

- **Embedded AI** — Running neural networks directly on microcontrollers using optimized inference engines
- **Quantization** — Reducing model precision (float → int8) to decrease memory usage and increase speed
- **DMA** (Direct Memory Access) — Transfers camera data without CPU intervention
- **DCMI** (Digital Camera Interface) — Hardware peripheral for image capture
- **Cache Coherency** (STM32F7) — Managing CPU cache when using DMA
- **Real-Time Systems** (FreeRTOS) — Deterministic execution and task scheduling

## 9. System Constraints & Challenges

- Limited memory (embedded environment)
- Real-time processing requirements
- Camera noise vs model accuracy
- Cache and DMA synchronization issues
- Optimization of inference time

## 10. Results (Current Progress)

- ✅ AI model deployed and running on STM32
- ✅ Correct classification on test images
- ✅ LCD visualization working (color mapping)
- 🔄 Camera integration in progress

## 11. Future Improvements

- Real-time camera-based inference
- Advanced UI/UX (multi-screen navigation)
- Finger tracking (cursor-like interaction)
- Model optimization (latency reduction)
- Integration with real industrial sensors

## 12. Conclusion

This project demonstrates the feasibility of combining **embedded systems**, **artificial intelligence**, and **human-centered interaction** to build a next-generation industrial HMI.

The system transforms traditional machine control into a **contactless**, **intelligent**, and **interactive** experience, opening the door to smarter and safer manufacturing environments.

---

**👨‍💻 Author**  
Melek Fourati
