import tkinter as tk
import serial

class SerialWrapper:
    def __init__(self, device):
        self.ser = serial.Serial(device, 115200)

    def sendData(self, data):
        data += "\r\n"
        self.ser.write(data.encode())

ser = SerialWrapper('COM3')

window = tk.Tk()
# window.geometry("500x250")

speed_slider = tk.Scale(window, from_=50, to=0)
speed_slider.pack()

speed_label = tk.Label(window, text="set speed")
speed_label.pack()

window.mainloop()

def send_speed_serial(speed):
    global ser
    ser.sendData(speed)
