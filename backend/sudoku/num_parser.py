import cv2
import numpy as np
from model import predict_digit
import matplotlib.pyplot as plt
from constants import TEST_IMAGE_PATH

def order_points(pts):
    pts = pts.reshape(4, 2)
    rect = np.zeros((4, 2), dtype="float32")

    s = pts.sum(axis=1)
    rect[0] = pts[np.argmin(s)]  # top-left
    rect[2] = pts[np.argmax(s)]  # bottom-right

    diff = np.diff(pts, axis=1)
    rect[1] = pts[np.argmin(diff)]  # top-right
    rect[3] = pts[np.argmax(diff)]  # bottom-left

    return rect

def resize_for_display(image, max_w=900, max_h=700):
    h, w = image.shape[:2]
    scale = min(max_w / w, max_h / h, 1.0)
    return cv2.resize(image, (int(w*scale), int(h*scale)))

def is_square(cnt):
    peri = cv2.arcLength(cnt, True)
    approx = cv2.approxPolyDP(cnt, 0.02 * peri, True)
    return len(approx) == 4

def preprocess_img(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    background = cv2.GaussianBlur(gray, (51, 51), 30)
    normalized = cv2.divide(gray, background, scale=255)
    _, thresh = cv2.threshold(
        normalized,
        0,
        255,
        cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU
    )
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (2, 2))
    thresh = cv2.morphologyEx(thresh, cv2.MORPH_CLOSE, kernel, iterations=3)
    #plt.imshow(thresh, cmap='gray')
    #plt.show()
    return thresh

def find_sudoku_grid(img, orig):
    contours, _ = cv2.findContours(
        img,
        cv2.RETR_EXTERNAL,
        cv2.CHAIN_APPROX_SIMPLE
    ) 
    sudoku_contour = None
    max_area = 0
    for c in contours:
        area = cv2.contourArea(c)
        if area < 10000:
            continue
        if area > max_area and is_square(c):
            max_area = area
            sudoku_contour = c
    if sudoku_contour is None:
        raise RuntimeError("Sudoku grid not found")
    sudoku_contour = max(contours, key=cv2.contourArea)
    peri = cv2.arcLength(sudoku_contour, True)
    approx = cv2.approxPolyDP(sudoku_contour, 0.02 * peri, True)
    rect = order_points(approx)
    side = 450
    dst = np.array([
        [0, 0],
        [side - 1, 0],
        [side - 1, side - 1],
        [0, side - 1]
    ], dtype="float32")
    M = cv2.getPerspectiveTransform(rect, dst)
    warped = cv2.warpPerspective(orig, M, (side, side))
    return warped

def extract_tiles(img):
    h, w = img.shape[:2]
    cell_w, cell_h = w // 9, h // 9
    cells = []
    for i in range(9):
        for j in range(9):
            x1, y1 = j * cell_w, i * cell_h
            x2, y2 = (j + 1) * cell_w, (i + 1) * cell_h
            margin = 0
            cell = img[y1+margin:y2-margin, x1+margin:x2-margin]
            cv2.rectangle(cell, (0, 0), (cell.shape[1]-1, cell.shape[0]-1), (0, 0, 255), 1)
            gray = cv2.cvtColor(cell, cv2.COLOR_BGR2GRAY)
            _, binary = cv2.threshold(
                gray, 0, 255,
                cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU
            )
            kernel = np.ones((2, 2), np.uint8)
            clean = cv2.morphologyEx(binary, cv2.MORPH_OPEN, kernel)
            cells.append(clean)
    return cells

def analyze_numbers(path):
    if not path:
        return []
    img = cv2.imread(path)
    if img is None:
        raise RuntimeError("Image not found")

    processed = preprocess_img(img)
    warped = find_sudoku_grid(processed, img)
    cells = extract_tiles(warped)
    pred = [predict_digit(c) for c in cells]

    #f_count = [i if pred[i] != real[i] else 0 for i in range(len(pred))]
    #print(f_count)

    # rows = [np.hstack(row) for row in cells]
    # grid_display = np.vstack(rows)


    # rows_concat = [np.hstack(row) for row in cells]
    # grid_display = np.vstack(rows_concat)

    # scale = 2
    # grid_display = cv2.resize(grid_display, (w * scale, h * scale))
    # plt.imshow(grid_display, cmap='gray')
    # plt.show()
    #print(pred)
    return pred

if __name__ == "__main__":
    analyze_numbers(TEST_IMAGE_PATH)