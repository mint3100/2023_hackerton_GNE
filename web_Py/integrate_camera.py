import cv2
import numpy as np
from keras.models import load_model
import time
import serial
import termios


path = '/dev/cu.usbmodem21401'

with open(path) as f:
    attrs = termios.tcgetattr(f)
    attrs[2] = attrs[2] & ~termios.HUPCL
    termios.tcsetattr(f, termios.TCSAFLUSH, attrs)
ser = serial.Serial(path, 9600)



model = load_model("keras_Model.h5", compile=False)
class_names = open("labels.txt", "r").readlines()

def predict_image(image):
    image = cv2.resize(image, (224, 224))
    normalized_image = (image.astype(np.float32) / 127.5) - 1
    input_data = np.expand_dims(normalized_image, axis=0)
    prediction = model.predict(input_data)
    index = np.argmax(prediction)
    class_name = class_names[index]
    confidence_score = prediction[0][index]
    return class_name, confidence_score

cap = cv2.VideoCapture(0)
start_time = time.time()
end_time = start_time + 3

while time.time() < end_time:
    ret, frame = cap.read()
    
    if not ret:
        break
    
    class_name, confidence_score = predict_image(frame)
    cv2.putText(frame, f'Class: {class_name[2:]}', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
    cv2.putText(frame, f'Confidence Score: {confidence_score}', (10, 70), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
    cv2.imshow('Real-time Image Recognition', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()

print("Final Prediction:")
print("Class:", class_name[2:])
print("Confidence Score:", confidence_score)

data = class_name[2:].lower()
print(data)
ser.write(data.encode('utf-8'))