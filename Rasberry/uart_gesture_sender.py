import sys
import serial
import json
import re
import time

# ── UART CONFIG ────────────────────────────────────────────────
ser = serial.Serial(
    port='/dev/serial0',
    baudrate=115200,
    timeout=1
)

# ── PARAMETERS ─────────────────────────────────────────────────
CONFIDENCE_THRESHOLD = 0.90
SEND_INTERVAL        = 0.03   # 30 ms → ~33 Hz
FRAME_HEIGHT         = 96     # FOMO input resolution (Y-axis inversion reference)

GESTURE_MAP = {
    "palm": 1,
    "fist": 0,
}

# ── INIT ────────────────────────────────────────────────────────
last_send_time = 0
print("Real-time UART gesture sender started")

# ── MAIN LOOP ───────────────────────────────────────────────────
for line in sys.stdin:
    line = line.strip()

    # Filter relevant lines
    if "boundingBoxes" not in line:
        continue

    # Extract JSON array
    match = re.search(r'(\[.*\])', line)
    if not match:
        continue

    try:
        detections = json.loads(match.group(1))
    except json.JSONDecodeError:
        continue

    if not detections:
        continue

    # ── Find best detection above threshold ─────────────────────
    best = max(
        (d for d in detections if d.get("value", 0) >= CONFIDENCE_THRESHOLD),
        key=lambda d: d["value"],
        default=None
    )

    if best is None:
        continue

    # ── Extract bounding box ─────────────────────────────────────
    x     = best["x"]
    y     = best["y"]
    w     = best["width"]
    h     = best["height"]
    label = best["label"]

    # ── Compute centroid ─────────────────────────────────────────
    center_x = int(x + w / 2)
    center_y = int(y + h / 2)

    # ── Invert Y axis (FOMO → LCD coordinate space) ──────────────
    center_y = FRAME_HEIGHT - center_y

    # ── Encode gesture ───────────────────────────────────────────
    gesture = GESTURE_MAP.get(label)
    if gesture is None:
        continue

    # ── Rate limiting (~33 Hz) ───────────────────────────────────
    now = time.time()
    if (now - last_send_time) < SEND_INTERVAL:
        continue
    last_send_time = now

    # ── Build and send UART packet ───────────────────────────────
    packet = f"{center_x},{center_y},{gesture}\n"
    ser.write(packet.encode())
    print(f"UART SENT → {packet.strip()}")