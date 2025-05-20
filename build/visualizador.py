import serial
import struct
from time import sleep

def decode_bools(byte_value):
    return [
        (byte_value & (1 << 7)) != 0,  # Bit 7
        (byte_value & (1 << 6)) != 0,  # Bit 6
        (byte_value & (1 << 5)) != 0,  # Bit 5
        (byte_value & (1 << 4)) != 0,  # Bit 4
        (byte_value & (1 << 3)) != 0,  # Bit 3
        (byte_value & (1 << 2)) != 0,  # Bit 2
        (byte_value & (1 << 1)) != 0,  # Bit 1
        (byte_value & 1) != 0          # Bit 0
    ]

def main():
    port = 'COM6'  # Mismo que en dash_plugin.txt
    baud = 115200
    
    with serial.Serial(port, baud, timeout=1) as ser:
        print(f"Escuchando en {port}...")
        while True:
            # Buscar cabecera
            header = ser.read(2)
            if len(header) != 2 or header[0] != 0xFF or header[1] != 0x02:
                continue
            
            # Leer datos restantes
            data = ser.read(11*4 + 4 + 6 + 1)  # Tamaño total calculado
            if len(data) < 11*4 + 4 + 6 + 1:
                continue
                
            idx = 0
            
            # Decodificar floats
            float_fields = [
                "Speed (km/h)", "Engine RPM", "Brake Pressure", 
                "Brake Temp", "Fuel Ratio", "Oil Pressure",
                "Oil Temp", "Water Temp", "Battery Voltage",
                "Cruise Control", "AdBlue Ratio"
            ]
            floats = struct.unpack('11f', data[idx:idx+44])
            idx +=44
            
            for name, value in zip(float_fields, floats):
                print(f"{name}: {value:.2f}")
            
            # Decodificar booleanos
            bool_bytes = data[idx:idx+4]
            idx +=4
            
            bool_groups = [
                ["Beacon", "Parking", "L Blinker", "R Blinker", "Low Beam", "High Beam", "Brake Light", "Reverse"],
                ["Park Brake", "Motor Brake", "Air Warn", "Air Emerg", "Fuel Warn", "Batt Warn", "Oil Warn", "Water Warn"],
                ["Diff Lock", "Trailer Axle", "Lift Axle", "Dashboard Light", "Wipers", "AdBlue Warn", "Electric", "Engine"],
                ["Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Hazard"]
            ]
            
            for i, byte in enumerate(bool_bytes):
                bools = decode_bools(byte)
                for j, state in enumerate(bools):
                    if bool_groups[i][j] != "Reserved":
                        print(f"{bool_groups[i][j]}: {'ON' if state else 'OFF'}")
            
            # Odómetro
            odo_digits = struct.unpack('6B', data[idx:idx+6])
            idx +=6
            odo = sum(d * 10**(5-i) for i, d in enumerate(odo_digits))
            print(f"Odómetro: {odo} km")
            
            # String display
            str_len = data[idx]
            idx +=1
            display_str = data[idx:idx+str_len].decode('ascii')
            print(f"Display: {display_str}")
            
            print("\n" + "-"*50 + "\n")
            sleep(0.1)

if __name__ == "__main__":
    main()