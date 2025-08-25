import serial
import struct
import time
import math

# MSP command
MSP_SET_RAW_RC = 0xC8

def build_msp_packet(cmd, payload=b''):
    size = len(payload)
    checksum = size ^ cmd
    for b in payload:
        checksum ^= b
    return b'$M<' + bytes   ([size, cmd]) + payload + bytes([checksum])

def main():
    port = '/dev/ttyAMA0'     # Change to your Pi's serial port
    baudrate = 115200         # Or whatever you set in iNav Ports tab

    try:
        ser = serial.Serial(port, baudrate, timeout=0.05)
    except serial.SerialException as e:
        print(f"Could not open serial port: {e}")
        return

    freq = 0.5  # Hz (how fast to oscillate)
    t0 = time.time()
    print("Sending sinusoidal RC commands on CH1-4. Ctrl+C to stop.")
    try:
        while True:
            t = time.time() - t0
            # Sine wave between 1000 and 2000
            amplitude = 500
            offset = 1500
            ch1 = int(offset + amplitude * math.sin(2*math.pi*freq*t + 0))
            ch2 = int(offset + amplitude * math.sin(2*math.pi*freq*t + math.pi/2))
            ch3 = int(offset + amplitude * math.sin(2*math.pi*freq*t + math.pi))
            ch4 = int(offset + amplitude * math.sin(2*math.pi*freq*t + 3*math.pi/2))
            rc_channels = [ch1, ch2, ch3, ch4] + [1500]*4  # 8 channels total
            payload = b''.join(struct.pack('<H', v) for v in rc_channels)
            packet = build_msp_packet(MSP_SET_RAW_RC, payload)
            ser.write(packet)
            # For debugging, print first 4 channels
            print(f"\rCH1-4: {ch1} {ch2} {ch3} {ch4}", end='', flush=True)
            time.sleep(0.02)  # 50Hz
    except KeyboardInterrupt:
        print("\nStopped.")
    finally:
        ser.close()

if __name__ == "__main__":
    main()
