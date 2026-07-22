import numpy as np
import sounddevice as sd
import time

def play_metal_strike(frequency, duration=1.5, sample_rate=44100):
    """Generates a metallic strike sound using FM synthesis/overtones."""
    t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)
    
    # Metal sounds have inharmonic overtones (multipliers aren't perfect integers)
    overtones = [1.0, 1.6, 2.3, 3.1, 4.2]
    weights = [0.6, 0.3, 0.2, 0.1, 0.05]
    
    # Combine frequencies
    sound = np.zeros_like(t)
    for f_mult, weight in zip(overtones, weights):
        sound += weight * np.sin(2 * np.pi * frequency * f_mult * t)
        
    # Apply a sharp attack and exponential decay envelope (classic strike)
    envelope = np.exp(-5 * t) 
    sound = sound * envelope
    
    # Normalize volume
    sound = sound / np.max(np.abs(sound))
    
    # Play the sound
    sd.play(sound, sample_rate)
    sd.wait()

# --- The "Ding Dong" Sequence ---
print("🔔 Ding...")
play_metal_strike(frequency=587.33, duration=0.5) # High note (D5)

time.sleep(0.1) # Brief pause between strikes

print("🔔 Dong...")
play_metal_strike(frequency=440.00, duration=0.8) # Lower resonant note (A4)