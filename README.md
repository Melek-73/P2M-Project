# P2M-Project
Edge AI for Computer Vision on MCUs ; An Edge AI project focused on deploying optimized computer vision models (CNNs) on embedded MCU (STM32) devices for real-time inference.

### Hand Gesture Recognition : CNN for STM32F7

**Goal**  
Build a robust hand gesture recognition model by combining two datasets and prepare it for embedded deployment (TinyML / STM32).

## Datasets Used

| Dataset              | Sensor       | Images   | Resolution | Classes | Notes                              |
|----------------------|--------------|----------|------------|---------|------------------------------------|
| LeapGestRecog        | Leap Motion  | ~20k     | 240×640×3    | 10      | Infrared, very controlled          |
| RYN-HGD 2.0 (grayscale) | Webcam    | ~31k     | 256×256×3    | 10      | Real-world conditions              |
| **Merged**           | —            | **51 081** | —        | 10      | Final training set                 |

**Classes (10)**:  
`01_palm`, `02_l`, `03_fist`, `04_fist_moved`, `05_thumb`, `06_index`, `07_ok`, `08_palm_moved`, `09_c`, `10_down`

## Pipeline Summary

1. **Merging strategy**  
   - Copied RYN-HGD directly  
   - Added Leap images with subject prefix (`subject_folder_frame_…`) to avoid overwrites  
   → Final structure: one folder per class

2. **Class balance** (after merge)  
   ≈ 4800–5200 images per class → reasonably balanced

3. **Preprocessing**  
   - Grayscale (1 channel)  
   - Resize → **64×64**  
   - Normalize [0,1]

4. **Data split**  
   - Stratified train/val/test (~70/15/15)  

5. **Model Architecture** (lightweight CNN)  
   - Several Conv2D + MaxPool + BatchNorm + Dropout layers  
   - GlobalAveragePooling or Flatten → Dense → 10 softmax  
   - Designed to be small enough for microcontroller

6. **Training result**  
   - Test accuracy (float32): **~89.9–90.1%**  
   - Main confusions:  
     - `03_fist` ↔ `04_fist_moved`  
     - `01_palm` ↔ `08_palm_moved`  
     → caused mostly by near-identical samples in RYN-HGD dataset

7. **TinyML / STM32 Deployment**  
   - Converted to **fully integer-quantized TFLite** (int8)  
   - Final model size: **~14 KB**  
   - Quantized test accuracy: **~89.4%** (very small drop)  
   - Generated `model_data.h` → C array ready for STM32 firmware

## Key Takeaways

- Merging infrared + webcam data → better generalization  
- Model performs well overall, but **dataset ambiguity** (especially palm/palm-moved and fist/fist-moved) is the main error source  
- 14 KB int8 model → realistic for STM32F7 / similar low-power MCUs

**Final deliverables**  
- `stm32_gesture_model.tflite`  
- `model_data.h` (C header for embedded inference)

→ Ready for real-time hand gesture control on microcontroller!
