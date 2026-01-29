import cv2
import numpy as np
from PIL import Image
from .train import PrintedDigitModel
import torch
import torchvision.transforms as transforms
from torchvision import transforms
from .constants import MODEL_PATH

model = PrintedDigitModel()
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model.load_state_dict(torch.load(MODEL_PATH))
model.to(device)
model.eval()

transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5,), (0.5,))  # MNIST normalization
])

def preprocess(gray, display=False):
    resized = cv2.resize(gray, (28, 28))

    cropped = resized[
        2:28-2,
        2:28-2
    ]

    black_pixels = np.sum(cropped < 0.8)
    total_pixels = cropped.size
    black_ratio = black_pixels / total_pixels
    if black_ratio > 0.95:
        return None # If center contains many black pixels, assume it contains no number

    img = Image.fromarray(resized)
    if display: 
        cv2.imshow("Sudoku Cells", resized)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    tensor = transform(img).unsqueeze(0).to(device)
    return tensor

def predict_digit(cell, display=False):
    tensor = preprocess(cell, display)
    if tensor is None:
        return 0
    with torch.no_grad():
        output = model(tensor)
        pred = output.argmax(dim=1, keepdim=True)
    return int(pred.item())